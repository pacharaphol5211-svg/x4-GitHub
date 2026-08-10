#include <ZEED32_OPT_IMU60new.h>
#include "EEPROM.h"
float Angle_Z, saveAngle = 180, statusAngle = 0;
int colorL, colorR;                                                    //เขียว 1 เหลือง 2 แดง 3
char StandL = 'G', StandR = 'R';                                       //เริ่มต้น แท่นหลุมซ้าย = เขียว ,หลุมขวา = แดง
int LoadColorL = 0, LoadColorR = 0, statusLoadL = 0, statusLoadR = 0;  //ตัวแปรสถานะ สี และ ว่างหรือไม่
int statusDrop1 = 0, statusDrop2 = 0, statusDrop3 = 0, LastLift;       //สีหลุมที่วางและสรุปหาหลุมที่ว่าง
long Encodepoint;
unsigned long timer_start, timer_end;
float total_end;
int timer_state = 0;

int ColorHANL = 0, ColorHANR = 0, ColorLoadL = 0, ColorLoadR = 0;

#define valueSen 550                                //ตั้งค่า Sensor ถ้าค่ามากกว่าหมายถึงเจอเส้นสีดำดูค่าที่จอ
#define lowspeed 35                                 //ตั้งค่า ความเร็วขั้นต่ำ
int SpeedSpinL = 100, LimitAngleSpinL = 22;         //ตั้งค่าความเร็วในการหมุน ซ้าย, ตั้งค่าลิมิตองศา มุมในการหมุน ซ้าย เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
int SpeedSpinR = 100, LimitAngleSpinR = 28;         //ตั้งค่าความเร็วในการหมุน ขวา, ตั้งค่าลิมิตองศา มุมในการหมุน ขวา เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า

int SpeedSpinLSlow = 110, LimitAngleSpinLSlow = 12;  //ตั้งค่าความเร็วในการหมุน ซ้าย แบบช้า, ตั้งค่าลิมิตองศา มุมในการหมุน ซ้าย เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
int SpeedSpinRSlow = 110, LimitAngleSpinRSlow = 20;  //ตั้งค่าความเร็วในการหมุน ขวา แบบช้า, ตั้งค่าลิมิตองศา มุมในการหมุน ขวา เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า

int SpeedTurnL = 120, LimitAngleTurnL = 33;         //ตั้งค่าความเร็วในการเลี้ยวเทริน ซ้าย , ตั้งค่าลิมิตองศา มุมในการเลี้ยว ซ้าย เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า (จูนค่าพยายามให้ตั้งฉากพอดี)
int SpeedTurnR = 120, LimitAngleTurnR = 30;         //ตั้งค่าความเร็วในการเลี้ยวเทริน ขวา , ตั้งค่าลิมิตองศา มุมในการเลี้ยว ขวา เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า (จูนค่าพยายามให้ตั้งฉากพอดี)

int SpeedTurnBL = 120, LimitAngleTurnBL = 33;       //ตั้งค่าความเร็วในการเลี้ยวเทริน ถอยหลังซ้าย , ตั้งค่าลิมิตองศา มุมในการเลี้ยว ถอยหลังซ้าย เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า (จูนค่าพยายามให้ตั้งฉากพอดี)
int SpeedTurnBR = 110, LimitAngleTurnBR = 38;       //ตั้งค่าความเร็วในการเลี้ยวเทริน ถอยหลังขวา , ตั้งค่าลิมิตองศา มุมในการเลี้ยว ถอยหลังขวา เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า (จูนค่าพยายามให้ตั้งฉากพอดี)

int SpeedReturn = 40, ReturnValue = 100;             //ค่าความเร็วหลังชนเส้นให้ย้อนกลับ ความเร็วย้อนกลับ , ระยะทาง encoder (พยายามจูนให้อยู่ตรงกลาง ช่อง!)

void setup() {
  Serial.begin(115200);
  BeginEASY32(1);
  setEncoder();
  ReadValueSensorEEPROM();
  setupRGB();
  notifyBATT();  //เปิดโหมดแจ้งเตือนแบตอ่อน

  //--------------------------------- จูนตั้งค่ามอเตอร์ให้ความเร็วใกล้เคียงกัน  เพื่อเดินหน้าว่าหุ่นเดินตรงมั้ย MT(-150,-150,1500); -----------------------------------------//
  //--------- ** ทดสอบโดยสั่ง MT(100,100,1000); เช็คอาการหุ่นว่าเดินหน้า เอียงมากมั้ยแล้วปรับ % ความเร็วให้หุ่นเดินตรงก่อน **
  SetMotorForward(100.0, 100.0, 100.0, 100.0);  // ตั้งค่ามอเตอร์เดินหน้า M1, M2, M3, M4 100%  สามารถเพิ่มลดเช่น 90% เพื่อลดความเร็วลง 10%
  //--------- ** ทดสอบโดยสั่ง MT(-100,-100,1000); เช็คอาการหุ่นว่าเดินถอยหลัง เอียงมากมั้ยแล้วปรับ % ความเร็วให้หุ่นเดินตรงก่อน **
  SetMotorBackward(100.0, 100.0, 100.0, 100.0);  // ตั้งค่ามอเตอร์ถอยหลัง M1, M2, M3, M4 100%  สามารถเพิ่มลดเช่น 95% เพื่อลดความเร็วลง 5%
  //----------------------------------------------------------------------------------------------------------------------------------------------------//
  //  TEST_Servo();  //เปิด Serial Monitor กรอกค่าองศาเพื่อหาองศา Servo กด SW1 เพื่อ เลือก Servo HL HR AL AR
  //  ReadRGB();  //ทดสอบอ่านค่าสี RGB อย่าลืมคาริเบตค่า

  HanLR('o', 'o');
  delay(200);

  HanLR('c', 'c');
  ArmLR('f', 'f');

  SW();
  Can1();
  Can2();
  Can3();
  End();
}

void loop() {
  ST();
}

void SW() {
  while (1) {
    if (digitalRead(sw1) == 0) {
      BZ(1, 100);
      timer_state = 1;
      timer_start = millis();
      ResetAngle_Z();
      ResetAngle_Y();
      ResetAngle_X();
      break;
    } else {
      LiftToZero();
    }
    if (digitalRead(swMode) == 0) {
      BZ(1, 200);
      SW_ModeRun();
    }
    if (digitalRead(sw2) == 0) {
      BZ(1, 200);
      CaribrateSensor();
    }
    DisplayMonitor();
  }



  delay(200);
}

#define STOP ST
void ST() {
  if (timer_state == 1) {
    timer_end = millis();
    total_end = (timer_end - timer_start) / 1000.0;
    timer_state = 0;
  }

  while (1) {
    if (digitalRead(sw1) == 0) {
      BZ(1, 100);
      timer_state = 1;
      timer_start = millis();
      break;
    }
    DisplayMonitor();
  }
  delay(200);
}

void DisplayMonitor() {
  MPU_RUN();
  MotorShot(0);
  Serial.print(Angle_Z);
  Serial.print("\t");
  Serial.print(analog(A0));
  Serial.print("\t");
  Serial.print(analog(A1));
  Serial.print("\t");
  Serial.print(analog(A2));
  Serial.print("\t");
  Serial.print(analog(A3));
  Serial.print("\t");
  Serial.print(analog(A4));
  Serial.print("\t");
  Serial.print(analog(A5));
  Serial.print("\t");
  Serial.print(analog(A6));
  Serial.print("\t");
  Serial.print(analog(A7));
  Serial.print("\t");
  Serial.print(GetRPM());
  Serial.print("\t");
  Serial.print(total_end);
  Serial.print("\t");
  Serial.print("VBATT ");
  Serial.println(INA.getBusVoltage(), 1);

  OLED.setTextColor(SH110X_WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.print("Z ");
  OLED.print(int(Angle_Z / 10));
  OLED.setTextSize(1);  //monitor
  OLED.print(" Y ");
  OLED.println(ReadAngle_Y());
  OLED.setCursor(60, 10);
  OLED.print(" X ");
  OLED.println(ReadAngle_X());
  OLED.println("");
  OLED.print("SF ");
  OLED.print("|");
  OLED.print(Analog(A0));
  OLED.print(" ");
  OLED.print("|");
  OLED.print(Analog(A1));
  OLED.print(" ");
  OLED.print("|");
  OLED.println(Analog(A2));
  OLED.println("");
  OLED.print("SB ");
  OLED.print("|");
  OLED.print(Analog(A3));
  OLED.print(" ");
  OLED.print("|");
  OLED.print(Analog(A4));
  OLED.print(" ");
  OLED.print("|");
  OLED.println(Analog(A5));
  OLED.println("");
  OLED.print("Timer: ");
  OLED.println(total_end, 3);
  OLED.println("");
  OLED.print("Ultra: ");
  OLED.println(Ultra());
  OLED.setCursor(70, 74);
  OLED.print("BATT:");
  OLED.println(INA.getBusVoltage(), 1);
  OLED.println("");
  OLED.print("Lift: ");
  OLED.println(GetEncodeLift());
  OLED.println("");
  OLED.print("Move: ");
  OLED.println((GetEncodeMove() / 18));
  OLED.println("");

  OLED.display();
  OLED.clearDisplay();
}

void notifyBATT() {
  if (INA.getBusVoltage() > 5.5 && INA.getBusVoltage() < 7.9) {
    while (1) {
      if (digitalRead(sw1) == 0) {
        BZ(1, 100);
        break;
      }

      OLED.setTextColor(SH110X_WHITE);
      OLED.setCursor(0, 0);
      OLED.setTextSize(2);
      OLED.println(" LOW BATT");
      OLED.println("");
      OLED.print(INA.getBusVoltage(), 1);
      OLED.println(" volt !");

      OLED.display();
      OLED.clearDisplay();
    }
  }
}

int stateMode = 0;
void SW_ModeRun() {
  while (1) {
    if (stateMode == 0) {
      if (digitalRead(swMode) == 0) {
        BZ(1, 200);
        stateMode = 1;
      }
      MonitorRGB();
    } else if (stateMode == 1) {
      TEST_ServoMode();
      BZ(1, 200);
      stateMode = 0;
    }
  }
}

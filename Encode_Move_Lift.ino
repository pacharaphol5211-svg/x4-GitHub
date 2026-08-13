#include <ESP32Encoder.h>
ESP32Encoder encodeMove;
ESP32Encoder encoderLift;
#define Value_ENcoder 18  //ตัวหารค่า encoder

//--------------------------------------------------------------- Encoder Move Setup ------------------------------------------------------------------//

const int PPR = 4096;  // จำนวน Pulse ต่อ 1 รอบ
unsigned long lastTime = 0;
long lastCount = 0;
float currentRPM = 0;

void setEncoder() {
  encodeMove.attachFullQuad(34, 35);
  encodeMove.clearCount();
  setLift();
}

int64_t encoderOffset = 0;
long GetEncodeMove() {
  return encodeMove.getCount() - encoderOffset;
}

void ResetEncodeMove() {
  long currentRaw = encodeMove.getCount();  // อ่านค่าดิบจาก Encoder ณ วินาทีนี้
  encoderOffset = currentRaw;               // เก็บค่านี้ไว้เป็นจุดลบ (Offset)
  lastCount = currentRaw;                   // อัปเดตตัวแปรความเร็วให้เริ่มนับจากจุดเดียวกัน
}

long lastPosRPM = 0;
unsigned long lastTimeRPM = 0;
float filteredRPM = 0;
float maxRPM = 0;

void ResetRPM() {
  lastPosRPM = encodeMove.getCount();  // ตั้งจุดเริ่มนับตำแหน่งใหม่ให้เท่ากับค่าปัจจุบัน
  lastTimeRPM = millis();              // ตั้งเวลาเริ่มนับใหม่
  filteredRPM = 0;                     // ล้างค่า Filter ความเร็วเดิม
  maxRPM = 0;                          // ล้างค่าความเร็วสูงสุด
}

float GetRPM() {
  unsigned long now = millis();

  // ตรวจสอบทุกๆ 10ms
  if (now - lastTimeRPM >= 10) {
    long currentPos = encodeMove.getCount();
    long deltaPos = currentPos - lastPosRPM;  // คำนวณผลต่างจากจุดสุดท้ายที่บันทึก

    // คำนวณรอบ/นาที (RPM)
    float revolutions = (float)deltaPos / PPR;
    float rpm = revolutions * (60000.0 / 10.0);  // 60,000ms ใน 1 นาที / ช่วงเวลา 10ms

    // EMA filter กรองความผันผวน
    filteredRPM = (filteredRPM * 0.8) + (rpm * 0.2);

    float absoluteRPM = abs(filteredRPM);
    if (absoluteRPM > maxRPM) {
      maxRPM = absoluteRPM;
    }

    lastPosRPM = currentPos;
    lastTimeRPM = now;
  }

  return filteredRPM;
}

float GetMaxRPM() {  // ฟังก์ชันสำหรับดูค่าสูงสุด
  return maxRPM;
}

//--------------------------------------------------------------- Encoder Lift Setup ------------------------------------------------------------------//
//--------------------------------------------------------------- Encoder Lift Setup ------------------------------------------------------------------//
float Kp = 1.5;
float Ki = 0.8;
float Kd = 0.1;
int SpeedDownLift = 255;

long setpoint = 0;
long lastError = 0;
int speed_PID;
float integral = 0;
unsigned long lastTimeLift = 0;
int statusLift = 0;

long GetEncodeLift() {
  return encoderLift.getCount();
}

void ResetEncoderLift() {
  encoderLift.clearCount();
}

unsigned long timer_Liftdown;
void Lift(int positions_) {  //หยุดรอลิฟถึงกำหนด positions
  MotorStop();
  setpoint = positions_;
  Encodepoint = setpoint;
  int state;
  if (GetEncodeLift() < positions_) state = 0;
  else if (GetEncodeLift() >= positions_) state = 1;

  while (1) {
    // SetAngle50();
    if (state == 0) {
      if (GetEncodeLift() < (positions_ - 120)) {
        Motor5(-255);
      } else {
        Motor5('s');
        break;
      }
    } else if (state == 1) {
      if (GetEncodeLift() > (positions_ + 200)) {
        Motor5(-SpeedDownLift);
      } else {
        Motor5('s');
        break;
      }
    }
  }
  MotorStop();
  timer_Liftdown = millis();

  while (1) {
    if (statusLift == 0) {
      PIDLIFT();
      // SetAngle50();
    } else {
      Motor5('s');
      MotorStop();
      setpoint = positions_;
      break;
    }
  }

  MotorFreq(400);
}

long lastEncoderValue = 0;
unsigned long lastStallCheckTime = 0;

void PIDLIFT() {
  unsigned long now = millis();

  // --- ส่วนที่ 1: ระบบ Stall Check (เพิ่มกำลังเมื่อขยับช้า) ---
  if (now - lastStallCheckTime >= 100) {  // เช็คทุกๆ 100ms
    long currentEncoder = GetEncodeLift();
    long diff = abs(currentEncoder - lastEncoderValue);

    // ถ้าความเปลี่ยนแปลงน้อยกว่า 10 หน่วย และยังไม่ถึงเป้าหมาย
    if (diff < 10 && abs(setpoint - currentEncoder) > 50) {
      if (setpoint > currentEncoder) {
        Motor5(-255);  // อัดไฟเต็มเพื่อส่งกำลังขึ้น
        delay(50);    // ให้เวลามอเตอร์ทำงานสั้นๆ
      } else {
        Motor5(-SpeedDownLift);  // ส่งกำลังลง
        delay(50);
      }
    }

    lastEncoderValue = currentEncoder;  // อัปเดตค่าล่าสุด
    lastStallCheckTime = now;
  }

  // --- ส่วนที่ 2: การคำนวณ PID ปกติ ---
  float dt = (now - lastTimeLift) / 1000.0;
  if (dt <= 0) dt = 0.001;

  long error = setpoint - GetEncodeLift();
  integral += error * dt;
  integral = constrain(integral, -10000, 10000);

  float derivative = (error - lastError) / dt;
  float output = Kp * error + Ki * integral + Kd * derivative;

  // หากใกล้เป้าหมาย (Deadzone)
  if (abs(error) < 50) {
    Motor5('s');
    integral = 0;
    statusLift = 1;  // หลุดออกจาก while ในฟังก์ชัน Lift
    return;
  }

  lastError = error;
  lastTimeLift = now;

  // กำหนดย่านกำลังขั้นต่ำ (Minimum Drive)
  int down = -50, up = 200;
  if (output > 0 && output < up) output = up;
  else if (output < 0 && output > down) output = down;

  output = constrain(output, -150, 255);
  int power = output;

  // ส่วนการสั่งการ Motor
  if (setpoint > 0) {
    if (GetEncodeLift() < (setpoint - 120)) {
      Motor5(255);
    } else if (GetEncodeLift() > (setpoint + 400)) {
      Motor5(-SpeedDownLift);
    } else {
      Motor5(power);  // ใช้พลังจาก PID
      statusLift = 0;
    }
  } else {
    LiftToZero();
  }
}

// ฟังก์ชั่นเลื่อนมอเตอร์กลับสู่ตำแหน่ง 0
void LiftToZero() {
  if (analog(6) < 1000) {
    Motor5(200);
  } else {
    Motor5(0);
    ResetEncoderLift();
  }
}

// ฟังก์ชันกำหนดเป้าหมายให้กับ PID
void MoveLift(long targetPoint) {
  targetPoint = targetPoint;
  setpoint = targetPoint;
  Encodepoint = setpoint;
  integral = 0;
  lastError = 0;
  statusLift = 0;
}

void setLift() {
  encoderLift.attachHalfQuad(26, 25);
  encoderLift.clearCount();
  lastTimeLift = millis();
  MoveLift(0);
}

//--------------------------------------------------------------- Move FFe BBe -----------------------------------------------------------------------//
int resetPID_FF_BB = 0;
void FFe(int speed, long ENCODE) {
  ResetEncodeMove();
  if (resetPID_FF_BB == 1) ResetErrorPID();  //reset เมื่อวิ่งสวนทาง

  long cEncode = ENCODE * Value_ENcoder;

  if (ENCODE >= 1000) {  //ถ้าระยะวิ่งมากกว่า 1000
    while (1) {
      if (GetEncodeMove() < ((ENCODE - 500) * Value_ENcoder)) {  //เหลือระยะ 500 ให้ใช้ lowspeed
        ControlSpeedForward(saveAngle, speed);
      } else {
        break;
      }
    }
  } else {  //ถ้าระยะวิ่งน้อยกว่า 1000
    while (1) {
      if (GetEncodeMove() < ((ENCODE - 300) * Value_ENcoder)) {  //เหลือระยะ 300 ให้ใช้ lowspeed
        ControlSpeedForward(saveAngle, speed);
      } else {
        break;
      }
    }
  }

  if (speed >= 200) {
    MotorShot(255);
    delay(5);
  }

  while (GetEncodeMove() < cEncode) {  //ถ้าระยะเอ็นโค้ดยังคงเหลือให้ใช้ lowSpeed ไปยังเป้าหมาย
    ControlSpeedForward(saveAngle, lowspeed);
  }
  MotorShot(255);
  Motor5('s');
  resetPID_FF_BB = 0;
}

void BBe(int speed, long ENCODE) {
  ResetEncodeMove();
  if (resetPID_FF_BB == 0) ResetErrorPID();  //reset เมื่อวิ่งสวนทาง
  long cEncode = ENCODE * Value_ENcoder;

  if (ENCODE >= 1000) {  //ถ้าระยะวิ่งมากกว่า 1000
    while (1) {
      if (GetEncodeMove() > -((ENCODE - 500) * Value_ENcoder)) {  //เหลือระยะ 500 ให้ใช้ lowspeed
        ControlSpeedBackward(saveAngle, speed);
      } else {
        break;
      }
    }
  } else {  //ถ้าระยะวิ่งน้อยกว่า 1000
    while (1) {
      if (GetEncodeMove() > -((ENCODE - 300) * Value_ENcoder)) {  //เหลือระยะ 300 ให้ใช้ lowspeed
        ControlSpeedBackward(saveAngle, speed);
      } else {
        break;
      }
    }
  }

  if (speed >= 200) {
    MotorShot(255);
    delay(5);
  }

  while (GetEncodeMove() > -cEncode) {
    ControlSpeedBackward(saveAngle, lowspeed);
  }
  MotorStop();
  Motor5('s');
  resetPID_FF_BB = 1;
}

void FFe(int speed, long ENCODE, int Free) {
  ResetEncodeMove();
  if (resetPID_FF_BB == 1) ResetErrorPID();  //reset เมื่อวิ่งสวนทาง

  long cEncode = ENCODE * Value_ENcoder;
  while (GetEncodeMove() < cEncode) {
    ControlSpeedForward(saveAngle, speed);
  }
  MotorStop();
  Motor5('s');
  resetPID_FF_BB = 0;
}

void BBe(int speed, long ENCODE, int Free) {
  ResetEncodeMove();
  if (resetPID_FF_BB == 0) ResetErrorPID();  //reset เมื่อวิ่งสวนทาง

  long cEncode = ENCODE * Value_ENcoder;
  while (GetEncodeMove() > -cEncode) {
    ControlSpeedBackward(saveAngle, speed);
  }
  MotorStop();
  Motor5('s');
  resetPID_FF_BB = 1;
}

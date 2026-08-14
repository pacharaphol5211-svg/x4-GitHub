#define NUM_SENSORS 6
int Sensor[NUM_SENSORS];
int minValue[NUM_SENSORS];
int maxValue[NUM_SENSORS];

#include <Ultrasonic.h>
Ultrasonic ultrasonic(32, 33);
int Ultra() {
  int MaxDis = 30;
  int Dis = ultrasonic.read();
  if (Dis == 0) Dis = 30;
  if (Dis > 30) Dis = 30;
  return Dis;
}

void Improve(uint16_t minF0, uint16_t minF1, uint16_t minF2, uint16_t minB0, uint16_t minB1, uint16_t minB2,
             uint16_t maxF0, uint16_t maxF1, uint16_t maxF2, uint16_t maxB0, uint16_t maxB1, uint16_t maxB2) {
  minValue[0] = minF0;
  minValue[1] = minF1;
  minValue[2] = minF2;
  minValue[3] = minB0;
  minValue[4] = minB1;
  minValue[5] = minB2;

  maxValue[0] = maxF0;
  maxValue[1] = maxF1;
  maxValue[2] = maxF2;
  maxValue[3] = maxB0;
  maxValue[4] = maxB1;
  maxValue[5] = maxB2;
}

void ReadValueSensorEEPROM() {
  if (!EEPROM.begin(256)) {
    delay(1000);
    ESP.restart();
  }
  Serial.println("อ่านค่า SENSOR EEPROM");
  int v[12];  // สร้าง Array เก็บค่า min 6 ค่า และ max 6 ค่า
  for (int i = 0; i < 12; i++) {
    v[i] = EEPROM.readUInt(i * 4);
  }
  Improve(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11]);
}

void readCalibrate() {
  for (int i = 0; i < 6; i++) {
    unsigned int calmin, calmax, rangeValue;
    long x = 0;
    calmin = minValue[i];
    calmax = maxValue[i];
    x = map(analog(i), calmin, calmax, 0, 1000);
    if (x < 0) x = 0;
    if (x > 1000) x = 1000;
    Sensor[i] = x;
  }
}

int Analog(int ReadSensor_) {
  readCalibrate();
  int valueSensor = 0;
  valueSensor = Sensor[ReadSensor_];
  return valueSensor;
}


int minSR0, minSR1, minSR2, minSR3, minSR4, minSR5;
int maxSR0, maxSR1, maxSR2, maxSR3, maxSR4, maxSR5;
void CaribrateSensor() {
  MotorStop();
  BZ(2, 100);
  while (1) {
    if (digitalRead(sw1) == 0) break;
    OLED.clearDisplay();
    OLED.setTextSize(2);
    OLED.setCursor(0, 0);
    OLED.println(" Caribrate");
    OLED.setTextSize(1);
    OLED.println("");
    OLED.println("  Move to White Area");
    OLED.println("");
    OLED.println("  Press SW1 to Start");
    OLED.display();
  }
  BZ(2, 100);
  delay(200);

  while (1) {
    OLED.setTextSize(1);
    OLED.setTextColor(SH110X_WHITE);
    OLED.setCursor(0, 0);
    OLED.println("--Press SW1 to Save--");
    OLED.println("");
    OLED.print("SF ");
    OLED.print("|");
    OLED.print(analog(A0));
    OLED.print(" ");
    OLED.print("|");
    OLED.print(analog(A1));
    OLED.print(" ");
    OLED.print("|");
    OLED.println(analog(A2));
    OLED.println("");
    OLED.print("SB ");
    OLED.print("|");
    OLED.print(analog(A3));
    OLED.print(" ");
    OLED.print("|");
    OLED.print(analog(A4));
    OLED.print(" ");
    OLED.print("|");
    OLED.println(analog(A5));
    OLED.display();
    OLED.clearDisplay();

    if (digitalRead(sw1) == 0) {
      minSR0 = analog(A0);
      minSR1 = analog(A1);
      minSR2 = analog(A2);
      minSR3 = analog(A3);
      minSR4 = analog(A4);
      minSR5 = analog(A5);
      BZ(2, 100);
      delay(200);
      break;
    }
  }

  while (1) {
    OLED.setTextSize(1);
    OLED.setTextColor(SH110X_WHITE);
    OLED.setCursor(0, 0);
    OLED.println("---Min Value Color---");
    OLED.println("");
    OLED.print("SF ");
    OLED.print("|");
    OLED.print(minSR0);
    OLED.print(" ");
    OLED.print("|");
    OLED.print(minSR1);
    OLED.print(" ");
    OLED.print("|");
    OLED.println(minSR2);
    OLED.println("");
    OLED.print("SB ");
    OLED.print("|");
    OLED.print(minSR3);
    OLED.print(" ");
    OLED.print("|");
    OLED.print(minSR4);
    OLED.print(" ");
    OLED.print("|");
    OLED.println(minSR5);

    OLED.println("");
    OLED.println("--Press SW1 to Save--");
    OLED.println("---Max Value Color---");
    OLED.println("");
    OLED.print("SF ");
    OLED.print("|");
    OLED.print(analog(A0));
    OLED.print(" ");
    OLED.print("|");
    OLED.print(analog(A1));
    OLED.print(" ");
    OLED.print("|");
    OLED.println(analog(A2));
    OLED.display();
    OLED.clearDisplay();

    if (digitalRead(sw1) == 0) {
      maxSR0 = analog(A0);
      maxSR1 = analog(A1);
      maxSR2 = analog(A2);
      BZ(2, 100);
      delay(200);
      break;
    }
  }

  while (1) {
    OLED.setTextSize(1);  //monitor
    OLED.setTextColor(SH110X_WHITE);
    OLED.setCursor(0, 0);
    OLED.println("---Min Value Color---");
    OLED.println("");
    OLED.print("SF ");
    OLED.print("|");
    OLED.print(minSR0);
    OLED.print(" ");
    OLED.print("|");
    OLED.print(minSR1);
    OLED.print(" ");
    OLED.print("|");
    OLED.println(minSR2);
    OLED.println("");
    OLED.print("SB ");
    OLED.print("|");
    OLED.print(minSR3);
    OLED.print(" ");
    OLED.print("|");
    OLED.print(minSR4);
    OLED.print(" ");
    OLED.print("|");
    OLED.println(minSR5);

    OLED.println("");
    OLED.println("-SF Max Value Color--");
    OLED.println("");
    OLED.print("SF ");
    OLED.print("|");
    OLED.print(maxSR0);
    OLED.print(" ");
    OLED.print("|");
    OLED.print(maxSR1);
    OLED.print(" ");
    OLED.print("|");
    OLED.println(maxSR2);

    OLED.println("");
    OLED.println("--Press SW1 to Save--");
    OLED.println("-SB Max Value Color--");
    OLED.println("");
    OLED.print("SF ");
    OLED.print("|");
    OLED.print(analog(A3));
    OLED.print(" ");
    OLED.print("|");
    OLED.print(analog(A4));
    OLED.print(" ");
    OLED.print("|");
    OLED.println(analog(A5));

    OLED.display();
    OLED.clearDisplay();

    if (digitalRead(sw1) == 0) {
      maxSR3 = analog(A3);
      maxSR4 = analog(A4);
      maxSR5 = analog(A5);
      BZ(2, 100);
      delay(200);
      break;
    }
  }

  while (1) {
    // Save ค่าเข้า EEPROM
    int values[] = { minSR0, minSR1, minSR2, minSR3, minSR4, minSR5, maxSR0, maxSR1, maxSR2, maxSR3, maxSR4, maxSR5 };
    for (int i = 0; i < 12; i++) {
      EEPROM.writeUInt(i * 4, values[i]);
    }
    EEPROM.commit();

    // อ่านค่าจาก EEPROM เข้า Improve
    int v[12];
    for (int i = 0; i < 12; i++) {
      v[i] = EEPROM.readUInt(i * 4);
    }
    Improve(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11]);

    BZ(1, 100);
    OLED.clearDisplay();
    OLED.setTextSize(2);
    OLED.setCursor(0, 0);
    OLED.println("***Save***");
    OLED.display();
    delay(500);
    BZ(1, 100);
    break;
  }
}

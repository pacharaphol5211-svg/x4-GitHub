float compForward[4] = { 100.0, 100.0, 100.0, 100.0 };   // % ชดเชยมอเตอร์ตอน "เดินหน้า"  (speed > 0)
float compBackward[4] = { 100.0, 100.0, 100.0, 100.0 };  // % ชดเชยมอเตอร์ตอน "ถอยหลัง"  (speed < 0)

// เซ็ตค่าชดเชยตอนเดินหน้า (มอเตอร์ 1–4)
void SetMotorForward(float m1, float m2, float m3, float m4) {
  compForward[0] = m1;
  compForward[1] = m2;
  compForward[2] = m3;
  compForward[3] = m4;
}

// เซ็ตค่าชดเชยตอนถอยหลัง (มอเตอร์ 1–4)
void SetMotorBackward(float m1, float m2, float m3, float m4) {
  compBackward[0] = m1;
  compBackward[1] = m2;
  compBackward[2] = m3;
  compBackward[3] = m4;
}

int applyCompensation(int speed, int index) {
  if (speed == 0) return 0;
  float percent;
  if (speed > 0) {  // เดินหน้า
    percent = compForward[index];
  } else {  // ถอยหลัง
    percent = compBackward[index];
  }
  return (int)(speed * percent / 100.0);
}

// มอเตอร์ซ้าย-ขวา ด้านหน้า: Motor1 (LF), Motor2 (RF)
void MotorF(int speedLF, int speedRF) {
  Motor1(applyCompensation(speedLF, 0));  // index 0 = Motor1
  Motor2(applyCompensation(speedRF, 1));  // index 1 = Motor2
}

// มอเตอร์ซ้าย-ขวา ด้านหลัง: Motor3 (LB), Motor4 (RB)
void MotorB(int speedLB, int speedRB) {
  Motor3(applyCompensation(speedLB, 2));  // index 2 = Motor3
  Motor4(applyCompensation(speedRB, 3));  // index 3 = Motor4
}

void MT(int speedL, int speedR) {
  MotorF(speedL, speedR);
  MotorB(speedL, speedR);
}

void MT(int speedL, int speedR, int MsDelay) {
  MotorF(speedL, speedR);
  MotorB(speedL, speedR);
  delay(MsDelay);
}

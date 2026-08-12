#include <cmath>
float AnglePlus_Manual = 0.0;
float Calz = 0;

void Cal(float i) {
  Calz += i;
  AnglePlus_Manual = Calz * 10;
}

void CalReset() {
  Calz = 0;
  AnglePlus_Manual = 0;
}

void MPU_RUN() {
  float raw = ReadAngle_Z();
  float AnglePlus = AnglePlus_Manual;
  Angle_Z = fmod(raw + AnglePlus + 3600.0, 3600.0);
}

unsigned long stopTimer;  // ตัวแปรสำหรับจับเวลาตอนหุ่นติด

void FTK(int Speed, int _encode_) {
  while (1) {
    if (ReadAngle_Y() > 177) {
      ControlSpeedForward(saveAngle, Speed);
    } else {
      break;
    }
  }

  MotorShot(255);
  delay(100);
  ResetEncodeMove();
  long cEncode = _encode_ * 18;

  stopTimer = 0;
  while (GetEncodeMove() < cEncode) {
    float currentSpeedRPM = GetRPM();
    if (abs(currentSpeedRPM) < 3) {  //ถ้า encoder ไม่พบการเคลื่อนไหวหรือหมุนน้อยกว่ากำหนดจะเริ่มจับเวลา
      if (stopTimer == 0) {
        stopTimer = millis();
      }

      if (millis() - stopTimer > 500) {  // ถ้าหยุดนิ่งค้างไว้นานเกิน 500ms (ปรับเวลาได้ตามเหมาะสม)
        MT(200, 200, 100);               // สั่งเพิ่มแรงส่งด้วย มอเตอร์
        MotorStop();
        stopTimer = 0;
      } else {
        ControlSpeedForward(saveAngle, Speed);
      }
    } else {
      stopTimer = 0;
      ControlSpeedForward(saveAngle, Speed);
    }
  }

  MotorStop();
  Motor5('s');
}


void BTK(int Speed, int _encode_) {
  while (1) {
    if (ReadAngle_Y() < 183) {
      ControlSpeedBackward(saveAngle, Speed);
    } else {
      break;
    }
  }

  MotorShot(255);
  delay(100);
  ResetEncodeMove();
  long cEncode = _encode_ * 18;

  stopTimer = 0;
  while (GetEncodeMove() > -cEncode) {
    float currentSpeedRPM = GetRPM();

    // ตรวจสอบว่าหุ่นหยุดนิ่งหรือล้อฟรีน้อยกว่า 3 RPM หรือไม่
    if (abs(currentSpeedRPM) < 3) {
      if (stopTimer == 0) {
        stopTimer = millis();
      }

      if (millis() - stopTimer > 500) {
        MT(-200, -200, 100);
        MotorStop();
        stopTimer = 0;
      } else {
        ControlSpeedBackward(saveAngle, Speed);
      }
    } else {
      stopTimer = 0;
      ControlSpeedBackward(saveAngle, Speed);
    }
  }

  MotorStop();
  Motor5('s');
}

void UpSlope() {
  while (1) {
    if (ReadAngle_Y() > 173) {
      ControlSpeedForward(saveAngle, 110);
    } else {
      break;
    }
  }

  while (1) {
    if (ReadAngle_Y() < 178) {
      ControlSpeedForward(saveAngle, 80);
    } else {
      break;
    }
  }
}

void DownSlope() {
  while (1) {
    if (ReadAngle_Y() < 184) {
      ControlSpeedForward(saveAngle, 100);
    } else {
      break;
    }
  }

  while (1) {
    if (ReadAngle_Y() > 180) {
      ControlSpeedForward(saveAngle, 80);
    } else {
      break;
    }
  }
}

void BUpSlope() {
  while (1) {
    if (ReadAngle_Y() < 186) {
      ControlSpeedBackward(saveAngle, 110);
    } else {
      break;
    }
  }

  while (1) {
    if (ReadAngle_Y() > 180) {
      ControlSpeedBackward(saveAngle, 60);
    } else {
      break;
    }
  }
}

void BDownSlope() {
  while (1) {
    if (ReadAngle_Y() > 173) {
      ControlSpeedBackward(saveAngle, 100);
    } else {
      break;
    }
  }

  while (1) {
    if (ReadAngle_Y() < 179) {
      ControlSpeedBackward(saveAngle, 60);
    } else {
      break;
    }
  }
}


void SpinL() {

  float batt = INA.getBusVoltage();
  int speedSpin;
  int limitAngle;
  // ปรับค่าตามแรงดันแบต
  if (batt >= 8.35) {
    // ประมาณ 8.4V
    speedSpin = 105;
    limitAngle = 23;//เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  }
  else if (batt >= 8.15) {
    // ประมาณ 8.2 - 8.3V
    speedSpin = 110;
    limitAngle = 19;//เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  }
  else if (batt >= 7.95) {
    // ประมาณ 8.0 - 8.1V
    speedSpin = 130;
    limitAngle = 21;
  }
  else {
    // ต่ำกว่า 8.0V
    speedSpin = 155;
    limitAngle = 20;
  }
  Stop(100);
  int DesiredAngle = (saveAngle <= 90) ? saveAngle + 270 : saveAngle - 90;
  saveAngle = DesiredAngle;

  while (1) {

    MPU_RUN();

    int Degree = Angle_Z / 10;
    int error = Degree - DesiredAngle;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    if (abs(error) <= limitAngle) break;
    int targetRPM = constrain(abs(error) * 2, 50, speedSpin);
    MT(-targetRPM, targetRPM);
  }
  MotorShot(255);
  delay(50);
  // SetAngle ตามแรงดันแบต
  if (batt >= 8.35) {

    SetAngle30(0.2, 0.05, 0.1, 40, 50, 200);

  }
  else if (batt >= 8.15) {

    SetAngle30(0.2, 0.05, 0.1, 40, 55, 200);

  }
  else if (batt >= 7.95) {

    SetAngle30(0.2, 0.05, 0.1, 40, 60, 200);

  }
  else {

    SetAngle30(0.2, 0.05, 0.1, 40, 65, 200);

  }
  MotorShot(255);

  ResetEncodeMove();
  ResetErrorPID();

  MotorShot(255);
  delay(120);
}

void SpinL2() {
  Stop(100);
  int DesiredAngle = (saveAngle <= 90) ? saveAngle + 270 : saveAngle - 90;
  saveAngle = DesiredAngle;
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    int error = Degree - DesiredAngle;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    if (abs(error) <= 35) break;
    int targetRPM = constrain(abs(error) * 2, 50, SpeedSpinL);
    MT(-targetRPM, targetRPM);
  }
  MotorShot(255);
  delay(50);
  SetAngle50();

  ResetEncodeMove();
  ResetErrorPID();
}


void SpinR() {

  float batt = INA.getBusVoltage();
int speedLF;
int speedLB;
int speedRF;
int speedRB;
int limitAngle;
  
if (batt >= 8.35) { //เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  speedLF = 105;   // ซ้ายหน้า
  speedLB = 115;   // ซ้ายหลัง
  speedRF = 105;   // ขวาหน้า
  speedRB = 115;   // ขวาหลัง
  limitAngle = 60;
}
else if (batt >= 8.15) {
  speedLF = 110;
  speedLB = 120;
  speedRF = 110;
  speedRB = 120;

  limitAngle = 64;
}
else if (batt >= 7.95) { //เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  speedLF = 130;
  speedLB = 140;
  speedRF = 130;
  speedRB = 140;

  limitAngle = 50;
}
else {
  speedLF = 155;
  speedLB = 165;
  speedRF = 155;
  speedRB = 165;

  limitAngle = 27;
}
  Stop(100);
  int DesiredAngle = (saveAngle >= 270) ? saveAngle - 270 : saveAngle + 90;
  saveAngle = DesiredAngle;
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    int error = Degree - DesiredAngle;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    if (abs(error) <= limitAngle) break;
    int targetSpeed = constrain(abs(error) * 2, 50, speedSpin);
    MT(targetSpeed, -targetSpeed);
  }
  // SetAngle ตามแรงดันแบต
  if (batt >= 8.35) {

    SetAngle30(0.2, 0.05, 0.1, 40, 50, 200);
  }
  else if (batt >= 8.15) {
    SetAngle30(0.2, 0.05, 0.1, 40, 55, 200);
  }
  else if (batt >= 7.95) {
    SetAngle30(0.2, 0.05, 0.1, 40, 60, 200);
  }
  else {
    SetAngle30(0.2, 0.05, 0.1, 40, 65, 200);
  }
  MotorShot(255);

  ResetEncodeMove();
  ResetErrorPID();

  MotorShot(255);
  delay(120);
}


void SpinL(int slow) {
  float batt = INA.getBusVoltage();
  int speedSpin;
  int limitAngle;
  if (batt >= 8.35) {
    // 8.4V
    speedSpin = 90;
    limitAngle = 25; //เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  }
  else if (batt >= 8.15) {
    // 8.2 - 8.3V
    speedSpin = 100;
    limitAngle = 28; //เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  }
  else if (batt >= 7.95) {
    // 8.0 - 8.1V
    speedSpin = 120;
    limitAngle = 24;
  }
  else {
    // ต่ำกว่า 8.0V
    speedSpin = 120;
    limitAngle = 20;
  }

  Stop(100);
  int DesiredAngle = (saveAngle <= 90) ? saveAngle + 270 : saveAngle - 90;
  saveAngle = DesiredAngle;
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    int error = Degree - DesiredAngle;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    if (abs(error) <= limitAngle) break;
    int targetRPM = constrain(abs(error) * 2, 60, speedSpin);
    MT(-targetRPM, targetRPM);
  }
  // SetAngle Slow ตามแรงดันแบต
  if (batt >= 8.35) {
    SetAngle30(0.2, 0.05, 0.1, 30, 50, 200);
  }
  else if (batt >= 8.15) {
    SetAngle30(0.2, 0.05, 0.1, 32, 55, 200);
  }
  else if (batt >= 7.95) {
    SetAngle30(0.2, 0.05, 0.1, 35, 60, 200);
  }
  else {
    SetAngle30(0.2, 0.05, 0.1, 38, 65, 200);
  }
  MotorShot(255);

  ResetEncodeMove();
  ResetErrorPID();
}

void SpinR(int slow) {
  float batt = INA.getBusVoltage();
  int speedSpin;
  int limitAngle;
  if (batt >= 8.35) {
    // 8.4V
    speedSpin = 90;
    limitAngle = 38;//เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  }
  else if (batt >= 8.15) {
    // 8.2 - 8.3V
    speedSpin = 105;
    limitAngle = 53;//เลี้ยวเกินให้เพิ่มค่า เลี้ยวขาดให้ลดค่า
  }
  else if (batt >= 7.95) {
    // 8.0 - 8.1V
    speedSpin = 110;
    limitAngle = 24;
  }
  else {
    // ต่ำกว่า 8.0V
    speedSpin = 115;
    limitAngle = 24;
  }
  Stop(100);
  int DesiredAngle = (saveAngle >= 270) ? saveAngle - 270 : saveAngle + 90;
  saveAngle = DesiredAngle;
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    int error = Degree - DesiredAngle;
    if (error > 180) error -= 360;
    if (error < -180) error += 360;
    if (abs(error) <= limitAngle) break;
    int targetSpeed = constrain(abs(error) * 2, 60, speedSpin);
    MT(targetSpeed, -targetSpeed);
  }
  // SetAngle Slow ตามแรงดันแบต
  if (batt >= 8.35) {
    SetAngle30(0.2, 0.05, 0.1, 30, 50, 200);
  }
  else if (batt >= 8.15) {
    SetAngle30(0.2, 0.05, 0.1, 32, 55, 200);
  }
  else if (batt >= 7.95) {
    SetAngle30(0.2, 0.05, 0.1, 35, 60, 200);
  }
  else {
    SetAngle30(0.2, 0.05, 0.1, 38, 65, 200);
  }
  MotorShot(255);

  ResetEncodeMove();
  ResetErrorPID();
}


int SpeedBreak = 13;
void TurnL() {
  if (saveAngle <= 0) saveAngle = 360;
  int DesiredAngle = saveAngle - 90;
  saveAngle = DesiredAngle;  //บันทึกมุม

  MotorShot(100);
  delay(5);

  int EndDegree = LimitAngleTurnL;  //ระยะหยุดเมื่อเข้าใกล้องศาที่ต้องการ พยายามให้เกือบตั้งฉากเพื่อวิ่งต่อเนื่อง
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    if (DesiredAngle == 270) {
      if (Degree >= 0 && Degree < 90) {
        MT(-SpeedBreak, SpeedTurnL);
      } else if (Degree - saveAngle > EndDegree) {
        MT(-SpeedBreak, SpeedTurnL);
      } else {
        break;
      }
    } else {
      if (Degree - saveAngle > EndDegree) {
        MT(-SpeedBreak, SpeedTurnL);
      } else {
        break;
      }
    }
  }


  ResetEncodeMove();
  ResetErrorPID();
}

void TurnR() {
  if (saveAngle >= 360) saveAngle = 0;
  int DesiredAngle = saveAngle + 90;
  saveAngle = DesiredAngle;  //บันทึกมุม

  MotorShot(100);
  delay(5);

  int EndDegree = LimitAngleTurnR;  //ระยะหยุดเมื่อเข้าใกล้องศาที่ต้องการ พยายามให้เกือบตั้งฉากเพื่อวิ่งต่อเนื่อง
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    if (DesiredAngle == 90) {
      if (Degree >= 270 && Degree < 359) {
        MT(SpeedTurnR, -SpeedBreak);
      } else if (abs(Degree - saveAngle) > EndDegree) {
        MT(SpeedTurnR, -SpeedBreak);
      } else {
        break;
      }
    } else {
      if (abs(Degree - saveAngle) > EndDegree) {
        MT(SpeedTurnR, -SpeedBreak);
      } else {
        break;
      }
    }
  }

  ResetEncodeMove();
  ResetErrorPID();
}

void TurnBR() {
  if (saveAngle >= 360) saveAngle = 0;
  int DesiredAngle = saveAngle + 90;
  saveAngle = DesiredAngle;  //บันทึกมุม

  MotorShot(100);
  delay(5);

  int EndDegree = LimitAngleTurnBR;  //องศาระยะหยุดเมื่อเข้าใกล้องศาที่ต้องการ เลี้ยวเกินเพิ่มค่า เลี้ยวขาดลดค่า
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    if (DesiredAngle == 90) {
      if (Degree >= 270 && Degree < 359) {
        MT(SpeedBreak, -SpeedTurnBR);
      } else if (abs(Degree - saveAngle) > EndDegree) {
        MT(SpeedBreak, -SpeedTurnBR);
      } else {
        break;
      }
    } else {
      if (abs(Degree - saveAngle) > EndDegree) {
        MT(SpeedBreak, -SpeedTurnBR);
      } else {
        break;
      }
    }
  }

  ResetEncodeMove();
  ResetErrorPID();
}

void TurnBL() {
  if (saveAngle <= 0) saveAngle = 360;
  int DesiredAngle = saveAngle - 90;
  saveAngle = DesiredAngle;  //บันทึกมุม

  MotorShot(100);
  delay(5);

  int EndDegree = LimitAngleTurnBL;  //องศาระยะหยุดเมื่อเข้าใกล้องศาที่ต้องการ เลี้ยวเกินเพิ่มค่า เลี้ยวขาดลดค่า
  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    if (DesiredAngle == 270) {
      if (Degree >= 0 && Degree < 90) {
        MT(-SpeedTurnBL, SpeedBreak);
      } else if (Degree - saveAngle > EndDegree) {
        MT(-SpeedTurnBL, SpeedBreak);
      } else {
        break;
      }
    } else {
      if (Degree - saveAngle > EndDegree) {
        MT(-SpeedTurnBL, SpeedBreak);
      } else {
        break;
      }
    }
  }

  ResetEncodeMove();
  ResetErrorPID();
}

void Stop(int timer_Stop) {
  SetAngle30(0.15, 0.1, 0.09, 20, 50, timer_Stop);
}

float speedIntegral = 0;
float lastSpeedError = 0;
float currentOutputPWM = 0;
float smoothRPM = 0;          // ตัวแปรเก็บค่า RPM ที่ผ่านการกรองแล้ว
float internalTarget = 0;     // ค่า Target ที่ค่อยๆ ไต่ระดับ
float currentStepTarget = 0;  // ตัวแปรสำหรับเก็บค่าเป้าหมายที่กำลังไต่ระดับไปหา Target ใหม่

void ControlSpeedForward(int DesiredAngle, float TargetInput) {
  float finalTargetRPM = map(TargetInput, 0, 255, 0, 1000);
  float minStartRPM = (30.0 * 1000.0) / 255.0;  // คำนวณค่าเริ่มต้นที่ระดับ 30 (117 RPM)

  // --- 1. Target Transition Logic (เพิ่ม Jump Start) ---
  float targetStepUp = 150.0;
  float targetStepDown = 1000.0;

  if (currentStepTarget < finalTargetRPM) {
    // ถ้าเริ่มจากหยุดนิ่ง ให้กระโดดไปที่ 30 ทันที
    if (currentStepTarget == 0 && finalTargetRPM > 0) {
      currentStepTarget = minStartRPM;
    } else {
      currentStepTarget += targetStepUp;
    }
    if (currentStepTarget > finalTargetRPM) currentStepTarget = finalTargetRPM;
  } else if (currentStepTarget > finalTargetRPM) {
    currentStepTarget -= targetStepDown;
    if (currentStepTarget < finalTargetRPM) currentStepTarget = finalTargetRPM;
  }

  // --- 2. Safety / Reset ---
  if (TargetInput <= 0) {
    currentStepTarget = 0;
    internalTarget = 0;
    speedIntegral = 0;
    currentOutputPWM = 0;
    smoothRPM = 0;
    MotorStop();
    return;
  }

  // --- 3. Ramping Logic ---
  float rampStepUp = 35.0;
  float rampStepDown = 1000.0;

  if (internalTarget < currentStepTarget) {
    internalTarget += rampStepUp;
    if (internalTarget > currentStepTarget) internalTarget = currentStepTarget;
  } else if (internalTarget > currentStepTarget) {
    internalTarget -= rampStepDown;
    if (internalTarget < currentStepTarget) internalTarget = currentStepTarget;
  }

  // --- 4. Filter, Feed-forward, PID ---
  smoothRPM = (smoothRPM * 0.7) + (GetRPM() * 0.3);
  float feedForwardPWM = (internalTarget * 255.0) / 1000.0;
  float error = internalTarget - smoothRPM;
  speedIntegral += error * 0.03;
  speedIntegral = constrain(speedIntegral, -150, 150);
  float derivative = (error - lastSpeedError) / 0.01;
  lastSpeedError = error;

  float speedKp = 0.1, speedKi = 0.08, speedKd = 0.01;
  float pidAdjustment = (error * speedKp) + (speedIntegral * speedKi) + (derivative * speedKd);

  currentOutputPWM = feedForwardPWM + pidAdjustment;
  currentOutputPWM = constrain(currentOutputPWM, 0, 255);
  Forward(DesiredAngle, (int)currentOutputPWM);
}

float speedIntegralBK = 0;
float lastSpeedErrorBK = 0;
float currentOutputPWMBK = 0;
float smoothRPMBK = 0;
float internalTargetBK = 0;
float currentStepTargetBK = 0;

void ControlSpeedBackward(int DesiredAngle, float TargetInput) {
  float finalTargetRPM = map(TargetInput, 0, 255, 0, 1000);
  float minStartRPM = (30.0 * 1000.0) / 255.0;  // ค่าเริ่มต้นที่ระดับ 30

  // --- 1. Target Transition Logic (เพิ่ม Jump Start) ---
  float targetStepUp = 150.0;
  float targetStepDown = 1000.0;

  if (currentStepTargetBK < finalTargetRPM) {
    // ถ้าเริ่มจากหยุดนิ่ง ให้กระโดดไปที่ 30 ทันที
    if (currentStepTargetBK == 0 && finalTargetRPM > 0) {
      currentStepTargetBK = minStartRPM;
    } else {
      currentStepTargetBK += targetStepUp;
    }
    if (currentStepTargetBK > finalTargetRPM) currentStepTargetBK = finalTargetRPM;
  } else if (currentStepTargetBK > finalTargetRPM) {
    currentStepTargetBK -= targetStepDown;
    if (currentStepTargetBK < finalTargetRPM) currentStepTargetBK = finalTargetRPM;
  }

  // --- 2. Safety / Reset ---
  if (TargetInput <= 0) {
    currentStepTargetBK = 0;
    internalTargetBK = 0;
    speedIntegralBK = 0;
    currentOutputPWMBK = 0;
    smoothRPMBK = 0;
    MotorStop();
    return;
  }

  // --- 3. Ramping Logic ---
  float rampStepUp = 40.0;
  float rampStepDown = 1000.0;

  if (internalTargetBK < currentStepTargetBK) {
    internalTargetBK += rampStepUp;
    if (internalTargetBK > currentStepTargetBK) internalTargetBK = currentStepTargetBK;
  } else if (internalTargetBK > currentStepTargetBK) {
    internalTargetBK -= rampStepDown;
    if (internalTargetBK < currentStepTargetBK) internalTargetBK = currentStepTargetBK;
  }

  // --- 4. Filter, Feed-forward, PID ---
  float rawRPM = abs(GetRPM());
  smoothRPMBK = (smoothRPMBK * 0.7) + (rawRPM * 0.3);

  float feedForwardPWM = (internalTargetBK * 255.0) / 1000.0;
  float error = internalTargetBK - smoothRPMBK;
  speedIntegralBK += error * 0.03;
  speedIntegralBK = constrain(speedIntegralBK, -150, 150);
  float derivative = (error - lastSpeedErrorBK) / 0.01;
  lastSpeedErrorBK = error;

  float speedKp = 0.1, speedKi = 0.08, speedKd = 0.01;
  float pidAdjustment = (error * speedKp) + (speedIntegralBK * speedKi) + (derivative * speedKd);

  currentOutputPWMBK = feedForwardPWM + pidAdjustment;
  currentOutputPWMBK = constrain(currentOutputPWMBK, 0, 255);
  Backward(DesiredAngle, (int)currentOutputPWMBK);
}


int LastErrorForward = 0;
int LastErrorBackWord = 0;
void ResetErrorPID() {
  LastErrorForward = 0;
  LastErrorBackWord = 0;

  speedIntegral = 0;
  lastSpeedError = 0;
  currentOutputPWM = 0;
  smoothRPM = 0;
  internalTarget = 0;
  currentStepTarget = 0;

  speedIntegralBK = 0;
  lastSpeedErrorBK = 0;
  currentOutputPWMBK = 0;
  smoothRPMBK = 0;
  internalTargetBK = 0;
  currentStepTargetBK = 0;

  ResetRPM();
}

void Forward(int DesiredAngle, int Speed) {
  saveAngle = DesiredAngle;
  float Kp, Kd;
  if (Speed <= 100) Kp = 0.8, Kd = 3.2;
  else if (Speed <= 200) Kp = 1.1, Kd = 4.0;
  else Kp = 1.3, Kd = 5.0;
  MPU_RUN();
  PIDLIFT();
  float ErrorAngle = (DesiredAngle * 10) - Angle_Z;

  if (ErrorAngle > 1800) ErrorAngle -= 3600;
  else if (ErrorAngle <= -1800) ErrorAngle += 3600;
  float PID_ValueAngle = (Kp * ErrorAngle) + (Kd * (ErrorAngle - LastErrorForward));
  LastErrorForward = ErrorAngle;

  int LeftPower = Speed + (int)PID_ValueAngle;
  int RightPower = Speed - (int)PID_ValueAngle;

  int minPower = -10;
  LeftPower = constrain(LeftPower, minPower, Speed);
  RightPower = constrain(RightPower, minPower, Speed);

  MotorF(LeftPower, RightPower);
  MotorB(LeftPower, RightPower);
  yield();
}

void Backward(int DesiredAngle, int Speed) {
  saveAngle = DesiredAngle;
  float Kp, Kd;
  if (Speed <= 100) Kp = 0.8, Kd = 3.2;
  else if (Speed <= 200) Kp = 1.1, Kd = 4.0;
  else Kp = 1.3, Kd = 5.0;
  MPU_RUN();
  PIDLIFT();
  float ErrorAngle = (DesiredAngle * 10) - Angle_Z;

  if (ErrorAngle > 1800) ErrorAngle -= 3600;
  else if (ErrorAngle <= -1800) ErrorAngle += 3600;
  float PID_ValueAngle = (Kp * ErrorAngle) + (Kd * (ErrorAngle - LastErrorBackWord));
  LastErrorBackWord = ErrorAngle;

  int LeftPower = Speed - (int)PID_ValueAngle;
  int RightPower = Speed + (int)PID_ValueAngle;

  int minPower = -10;
  LeftPower = constrain(LeftPower, minPower, Speed);
  RightPower = constrain(RightPower, minPower, Speed);

  MotorF(-LeftPower, -RightPower);
  MotorB(-LeftPower, -RightPower);
  yield();
}


void FF(int speed, long ENCODE) {
  if (speed < 100) SetAngle50();
  FFe(speed, ENCODE, 1);

  while (1) {
    if (Analog(1) > valueSen) break;
    ControlSpeedForward(saveAngle, lowspeed);
  }

  MotorShot(255);
  delay(250);
  BBe(60,235);
  MotorShot(255);
  delay(250);
}

void FFb(int speed, long ENCODE) {
  // วิ่งไปข้างหน้าช่วงแรก
  if (speed < 100) SetAngle50();
  FFe(speed, ENCODE, 1);

  // กางแขนซ้ายและขวา
  ArmLR('b', 'b');

  // วิ่งช้าต่อจนเซนเซอร์ตรวจพบ
  while (Analog(1) <= valueSen) {
    ControlSpeedForward(saveAngle, lowspeed);
  }
  
  MotorShot(255);
  delay(50);
  BBe(40,235); //
  MotorShot(255);
  delay(50);
  // หุบแขน แล้วถอยกลับด้วย BBe
  ArmLR('g', 'g');
  BBe(SpeedReturn, ReturnValue, 1);

  MotorShot(255);
}

void FF(int speed, long ENCODE, int _encode_) {
  if (speed < 50) SetAngle50();
  FFe(speed, ENCODE, 1);

  while (1) {
    if (Analog(1) > valueSen) break;
    ControlSpeedForward(saveAngle, lowspeed);
  }
  
  delay(50);
  ResetErrorPID();

  while (1) {
    if (Analog(1) > valueSen) {
      ControlSpeedBackward(saveAngle, 20);
    } else {
      
      break;
    }
  }

  BBe(60,235);
  delay(50);
}

void ReadAngle() {
  while (1) {
    MPU_RUN();
    Serial.println(Angle_Z);
  }
}

void BB(int speed, long ENCODE) {
  if (speed < 50) SetAngle50();
  BBe(speed, ENCODE, 1);

  while (1) {
    if (Analog(4) > valueSen) break;
    ControlSpeedBackward(saveAngle, lowspeed);
  }

  MotorShot(255);
  delay(50);
  FFe(SpeedReturn, ReturnValue, 1);
  MotorShot(255);
}


void BB(int speed, long ENCODE, int _encode_) {
  if (speed < 50) SetAngle50();
  BBe(speed, ENCODE, 1);

  while (1) {
    if (Analog(4) > valueSen) break;
    ControlSpeedBackward(saveAngle, lowspeed);
  }


  delay(50);
  ResetErrorPID();

  while (1) {
    if (Analog(4) > valueSen) {
      ControlSpeedForward(saveAngle, 20);
    } else {
      delay(50);
      break;
    }
  }

  FFe(60,235);
  delay(50);
}

void FFt(int speed, unsigned long time) {
  unsigned long time_ = millis();
  while (millis() - time_ < time) {
    ControlSpeedForward(saveAngle, speed);
  }
  MotorStop();
}

void BBt(int speed, unsigned long time) {
  unsigned long time_ = millis();
  while (millis() - time_ < time) {
    ControlSpeedBackward(saveAngle, speed);
  }
  MotorStop();
}


int IntegralRotationSet2 = 0, LastErrorRotationSet2 = 0;
void SetAngle(int Set) {  // รักษามุมขณะจอด
  MPU_RUN();
  int CurrentAngle = Angle_Z;
  int ErrorRotation = Set * 10 - CurrentAngle;
  if (ErrorRotation > 1800) ErrorRotation -= 3600;
  else if (ErrorRotation < -1800) ErrorRotation += 3600;

  if (abs(ErrorRotation) < 20) {
    MotorStop();
    return;
  } else if (abs(ErrorRotation) < 50) {
    IntegralRotationSet2 = 0;
  }

  IntegralRotationSet2 += ErrorRotation;
  IntegralRotationSet2 = constrain(IntegralRotationSet2, -1000, 1000);
  int DerivativeRotation = ErrorRotation - LastErrorRotationSet2;
  int PID_ValueRotation = (0.1 /*Kp*/ * ErrorRotation) + (0.05 /*Ki*/ * IntegralRotationSet2) + (0.05 /*Kd*/ * DerivativeRotation);
  LastErrorRotationSet2 = ErrorRotation;
  int Speed = constrain(abs(PID_ValueRotation), 28, 40);
  int RightPower = (ErrorRotation > 0) ? -Speed : Speed;
  int LeftPower = -RightPower;

  MotorF(LeftPower, RightPower);
  MotorB(LeftPower, RightPower);
  yield();
}

void SetAngle50() {  // รักษามุมขณะจอด
  int IntegralRotationSet3 = 0, LastErrorRotationSet3 = 0;
  long timerOut_Set50 = millis();
  while (1) {
    MPU_RUN();
    int CurrentAngle = Angle_Z;
    int ErrorRotation = saveAngle * 10 - CurrentAngle;
    if (ErrorRotation > 1800) ErrorRotation -= 3600;
    else if (ErrorRotation < -1800) ErrorRotation += 3600;

    if (abs(ErrorRotation) < 30) {
      MotorShot(255);
      break;
    }

    if (millis() - timerOut_Set50 > 1000) break;  //เกิน 1 วินาทีให้ออกทันทีป้องกันค้าง
    IntegralRotationSet3 += ErrorRotation;
    IntegralRotationSet3 = constrain(IntegralRotationSet3, -1000, 1000);
    int DerivativeRotation = ErrorRotation - LastErrorRotationSet3;
    int PID_ValueRotation = (0.11 /*Kp*/ * ErrorRotation) + (0.055 /*Ki*/ * IntegralRotationSet3) + (1.5 /*Kd*/ * DerivativeRotation);
    LastErrorRotationSet3 = ErrorRotation;
    int Speed = constrain(abs(PID_ValueRotation), 60, 80);  //Speed Min Max ปรับตามความเหมาะสม
    int RightPower = (ErrorRotation > 0) ? -Speed : Speed;
    int LeftPower = -RightPower;

    MotorF(LeftPower, RightPower);
    MotorB(LeftPower, RightPower);
    yield();
  }
  ResetEncodeMove();
  ResetErrorPID();
}


void SetAngle30(float kp, float kd, float ki, int minSpeed, int maxSpeed, int timeOut) {  // บังคับเข้ามุม
  int IntegralRotationSet4 = 0, LastErrorRotationSet4 = 0;
  long timer_Set30 = millis();
  while (1) {
    MPU_RUN();
    int CurrentAngle = Angle_Z;
    int ErrorRotation = saveAngle * 10 - CurrentAngle;
    if (ErrorRotation > 1800) ErrorRotation -= 3600;
    else if (ErrorRotation < -1800) ErrorRotation += 3600;

    if (abs(ErrorRotation) < 30) {
      MotorStop();
      break;
    }

    if (millis() - timer_Set30 > timeOut) break;
    IntegralRotationSet4 += ErrorRotation;
    IntegralRotationSet4 = constrain(IntegralRotationSet4, -1000, 1000);
    int DerivativeRotation = ErrorRotation - LastErrorRotationSet4;
    int PID_ValueRotation = (kp * ErrorRotation) + (ki * IntegralRotationSet4) + (kd * DerivativeRotation);
    LastErrorRotationSet4 = ErrorRotation;
    int Speed = constrain(abs(PID_ValueRotation), minSpeed, maxSpeed);
    int RightPower = (ErrorRotation > 0) ? -Speed : Speed;
    int LeftPower = -RightPower;

    MotorF(LeftPower, RightPower);
    MotorB(LeftPower, RightPower);
    yield();
  }
  ResetEncodeMove();
  ResetErrorPID();
}

void SetF() {  //คำสั่ง Set หน้าตรงเส้น
  SetAngle50();
  while (1) {
    if (Analog(0) < valueSen && Analog(2) < valueSen) {
      ControlSpeedForward(saveAngle, lowspeed);
    } else if (Analog(0) > valueSen && Analog(2) < valueSen) {
      MT(-30, 70);
    } else if (Analog(0) < valueSen && Analog(2) > valueSen) {
      MT(70, -30);
    } else {
      CalReset();
      ResetAngle_Z();
      ResetAngle_Y();
      ResetAngle_X();
      break;
    }
  }

  saveAngle = 180;
  MotorShot(255);
  delay(100);
  BBe(SpeedReturn, ReturnValue);

  ResetEncodeMove();
  ResetErrorPID();
}


void SetB() {  //คำสั่ง Set หลังตรงเส้น
  SetAngle50();
  while (1) {
    if (Analog(3) < valueSen && Analog(5) < valueSen) {
      ControlSpeedBackward(saveAngle, lowspeed);
    } else if (Analog(3) > valueSen && Analog(5) < valueSen) {
      MT(30, -70);
    } else if (Analog(3) < valueSen && Analog(5) > valueSen) {
      MT(-70, 30);
    } else {
      CalReset();
      ResetAngle_Z();
      ResetAngle_Y();
      ResetAngle_X();
      break;
    }
  }

  saveAngle = 180;
  MotorShot(255);
  delay(100);
  FFe(SpeedReturn, ReturnValue);

  ResetEncodeMove();
  ResetErrorPID();
}

void BBst(int speed, long ENCODE) {
  if (speed < 30) SetAngle50();
  BBt(lowspeed, 40);
  int Speed_Stop = speed;
  ResetEncodeMove();
  ENCODE = ENCODE * 2;

  while (GetEncodeMove() > -ENCODE) {
    if (analog(3) > valueSen && analog(5) < valueSen) {
      MotorF(-speed, 30);
      MotorB(-speed, 30);
      delay(15);
    } else if (analog(3) < valueSen && analog(5) > valueSen) {
      MotorF(30, -speed);
      MotorB(30, -speed);
      delay(15);
    } else {
      Backward(saveAngle, speed);
    }
  }

  MotorShot(200);
  delay(10);

  while (1) {
    if (speed > lowspeed) speed = speed - 10;
    if (speed < lowspeed) speed = lowspeed;

    if (analog(4) > valueSen) break;
    Backward(saveAngle, lowspeed);
  }

  Motor5('s');
  MotorF(-Speed_Stop, -Speed_Stop);
  MotorB(-Speed_Stop, -Speed_Stop);
  delay(5);
  delay(50);
  FFe(60,160);

}

void FFtt(int speed, unsigned long time) {
  unsigned long time_ = millis();

  while (millis() - time_ < time) {
    Forward(saveAngle, speed);
    SetAngle(saveAngle);
  }

  MotorStop();
  Motor5('s');
}

void BBtt(int speed, unsigned long time) {
  unsigned long time_ = millis();

  while (millis() - time_ < time) {
    Backward(saveAngle, speed);
    SetAngle(saveAngle);
  }

  MotorStop();
  Motor5('s');
}

void SpinSet(char spin) {
  if (spin == 'r') {  //เลี้ยวขวา
    MotorShot(255);
    delay(500);
    SpinR();
    MotorShot(255);
    delay(500);
    while (analog(0) < valueSen) {
      Forward(saveAngle, 30);
    }
    MotorShot(255);
    delay(500);
    ResetEncodeMove();

    while (analog(3) < valueSen) {
      Backward(saveAngle, 30);
    }
    MotorShot(255);
    delay(200);
    long encoder_distance = GetEncodeMove();
    long return_distance = encoder_distance * -1;
    long return_BB = return_distance / 35;  //เพิ่มตรงนี้ ถ้าเดินย้อนกลับกิน 1 ให้ ลด ถ้าเดินมากินมา 3 ไปให้เพิ่ม   1 2 3
    FFee(30, return_BB);                    //เพิ่มตรงนี้****
    MotorShot(255);
    delay(200);
    SpinL();
    MotorShot(255);
    delay(200);

  } else {  //เลี้ยวซ้าย
    MotorShot(255);
    delay(500);
    SpinL();
    MotorShot(255);
    delay(500);
    while (analog(2) < valueSen) {
      Forward(saveAngle, 30);
    }
    MotorShot(255);
    delay(500);
    ResetEncodeMove();

    while (analog(5) < valueSen) {
      Backward(saveAngle, 30);
    }
    MotorShot(255);
    delay(500);
    long encoder_distance = GetEncodeMove();
    long return_distance = encoder_distance * -1;
    long return_BB = return_distance / 30;  //เพิ่มตรงนี้ ถ้าเดินย้อนกลับกิน 3 ให้ ลด ถ้าเดินมาเกิน 1 มากไปให้เพิ่ม   1 2 3
    FFee(35, return_BB);
    MotorShot(255);
    delay(200);
    SpinR();
    MotorShot(255);
    delay(200);
  }
}
void FFst(int speed, long ENCODE) {
  // 🌟 ปรับความเร็วลูปแรกขึ้นมาหน่อยเป็น 50 เพื่อให้ผ่านช่วงแรกไวขึ้น ไม่เอื่อย
  speed = 25; 

  if (speed < 100) SetAngle50();
  
  int Speed_Stop = speed;
  FFt(lowspeed, 50);
  ResetEncodeMove();
  ENCODE = ENCODE * 4; 
  
  // ลูปที่ 1: เปลี่ยนเป็นวิ่งตรงอย่างเดียว ไม่ต้องเช็กเซนเซอร์ส่ายไปมา จะได้ไม่เสียเวลา
  while (GetEncodeMove() < ENCODE) {
    Forward(saveAngle, speed); 
  }

  MotorShot(200);
  delay(10);

  // ลูปที่ 2: พอใกล้ถึงระยะ ค่อยตัดเข้าโหมดคลานช้ามากเพื่อเตรียมเบรก
  while (1) {
    speed = lowspeed; // บังคับให้ช้าลงทันทีก่อนเจอเส้นตัด

    if (analog(1) > valueSen) break; // เจอเส้นตัดปุ๊บ เบรกทันที
    Forward(saveAngle, speed);
    delay(5); 
  }

  // จังหวะเบรกสวนกลับตอนจบ
  Motor5('s');
  MotorF(-45, -45); // กระแทกเบรกแรงขึ้นเพื่อหยุดความเร็ว 50
  MotorB(-45, -45);
  delay(60);        // เพิ่มเวลาเบรกเล็กน้อย
  
  MotorShot(255);
  delay(50);
  
  MotorStop(); 
}
// --- ฟังก์ชันเลี้ยวซ้ายแบบ ช้าๆ ชัวร์ๆ 100% ---
void SpinLT() {
  if (saveAngle <= 0) saveAngle = 360;
  int DesiredAngle = saveAngle - 90;
  saveAngle = DesiredAngle;  // บันทึกมุมเป้าหมาย

  int EndDegree = 2;  // เหลืออีกแค่ 2 องศาค่อยหลุดลูป เพราะรถวิ่งช้ามาก ไม่ลอยลำแน่นอน
  int speed = 52;     // ตัวแปรเก็บความเร็วที่จะปรับเปลี่ยนแบบไดนามิก

  while (1) {
    MPU_RUN();
    int Degree = Angle_Z / 10;
    
    // --- โครงสร้างควบคุมความเร็ว 2 จังหวะ ---
    if (DesiredAngle == 270) {
      if (Degree >= 0 && Degree < 90) {
        speed = 52; // จังหวะแรก: ออกตัวแรงพอดีๆ
      } else if (Degree - saveAngle > 20) {
        speed = 52; 
      } else {
        speed = 32; // จังหวะสอง: ใกล้ถึงแล้ว ลดเหลือความเร็วเต่าคลาน
      }
    } else {
      if (Degree - saveAngle > 20) {
        speed = 52; // จังหวะแรก
      } else {
        speed = 32; // จังหวะสอง
      }
    }

    // --- เช็คเงื่อนไขการหยุดเลี้ยว ---
    if (DesiredAngle == 270) {
      if (Degree >= 0 && Degree < 90) {
        MT(-speed, speed); 
      } else if (Degree - saveAngle > EndDegree) {
        MT(-speed, speed);
      } else {
        break; 
      }
    } else {
      if (Degree - saveAngle > EndDegree) {
        MT(-speed, speed);
      } else {
        break; 
      }
    }
  }

  MT(0, 0); // เบรกสนิทลดแรงเฉื่อย
  delay(60);

  // ใช้ PID ความเร็วต่ำ (ไม่เกิน 18) และเพิ่มเวลาเป็น 350ms เพื่อให้ดึงมุมนิ่งสนิทชัวร์ๆ
  SetAngle30(0.18, 0.1, 0.08, 12, 18, 350);  
  
  MT(0, 0); 
  delay(150);
}
void FFee(int speed, long ENCODE) {
  long cEncode = ENCODE * Value_ENcoder;
  long slowDownPoint;
  ResetEncodeMove();
  if (ENCODE > 500) {
    slowDownPoint = (ENCODE - 300) * Value_ENcoder;
    while (GetEncodeMove() < slowDownPoint) {
      Forward(saveAngle, speed);
    }
  } else if (ENCODE > 100) {
    slowDownPoint = (ENCODE - 100) * Value_ENcoder;
    while (GetEncodeMove() < slowDownPoint) {
      Forward(saveAngle, speed);
    }
  }

  while (GetEncodeMove() < cEncode) {
    Forward(saveAngle, lowspeed);
  }

  MotorStop();
}
void St(char spin) {
  int checkSpeedF = 30;
  int checkSpeedB = 15;

  // ค่า index 0 = ขวา('r'), index 1 = ซ้าย('l')
  int halfCellStep[2] = {20, 18};   // ← ใส่ค่าจริงจาก calibrate แต่ละฝั่ง

  int side = (spin == 'r') ? 0 : 1;
  int senIdx = (spin == 'r') ? 0 : 2;

  delay(50);
  if (spin == 'r') SpinR(); else SpinL();
  delay(50);

  // ขาไป: เดินหน้าช้าลงเมื่อใกล้เส้น (กันเหวี่ยง overshoot)
  while (analog(senIdx) < valueSen - 10) {
    Forward(saveAngle, checkSpeedF);
  }
  while (analog(senIdx) < valueSen) {
    Forward(saveAngle, checkSpeedF / 2);
  }
  MotorShot(255);
  delay(100);

  // ขากลับ: ถอยช้าๆ จนกว่า sensor หลุดจากเส้นดำ
  while (analog(senIdx) >= valueSen) {
    Backward(saveAngle, checkSpeedB);
  }
  MotorShot(255);
  delay(100);

  // ถอยต่อด้วย BBe โดยใช้ tick ที่ calibrate มาแยกซ้าย-ขวา
  BBe(165, halfCellStep[side]);
  MotorShot(255);
  delay(50);

  if (spin == 'r') SpinL(); else SpinR();
  MotorShot(255);
  delay(50);
}


void StT(char spin) {
  // === ตัวแปรสำหรับปรับความเร็วตอนเดินหน้าเช็คเส้น (จูนตรงนี้ได้เลย) ===
  int checkSpeedF = 30; 

  if (spin == 'r') {  // ==================== เลี้ยวขวา ====================
    delay(50);
    SpinR(1);
     delay(50);

    // --- [รอบที่ 1] เดินหน้าเช็คเส้นครั้งแรก ---
    while (analog(0) < valueSen) {
      Forward(saveAngle, checkSpeedF);
    }
     

    // --- [ถอยกลับจุดเริ่ม] เปลี่ยนมาใช้ BBe ดื้อๆ ตามที่ขอครับ ---
    BBe(40, 105);  // หลุดเช็คครั้งที่ 1 เสร็จ สั่งถอยยาวกลับมาจุดเดิมทันที (ปรับเลข 165 เพิ่ม/ลดได้ตามต้องการ)
    
       delay(50);
    SpinL(1); // เลี้ยวคืน
       delay(50);

  } else {  // ==================== เลี้ยวซ้าย ====================
     delay(120);
    SpinL(1);
      delay(50);

    // --- [รอบที่ 1] เดินหน้าเช็คเส้นครั้งแรก ---
    while (analog(2) < valueSen) {
      Forward(saveAngle, checkSpeedF);
    }
    MotorShot(255);   



    // --- [ถอยกลับจุดเริ่ม] เปลี่ยนมาใช้ BBe ดื้อๆ ตามที่ขอครับ ---
    BBe(40, 180);  // หลุดเช็คครั้งที่ 2 เสร็จ สั่งถอยยาวกลับมาจุดเดิมทันที (ปรับเลข 165 เพิ่ม/ลดได้ตามต้องการ)
    
    MotorShot(255);   delay(50);
    SpinR(1); // เลี้ยวคืน
    MotorShot(255);   delay(50);
  }
}

/*---------------------------------- มือซ้าย ---------------------------------*/
#define HanL_Open 86    //องศาอ้ามือจับ
#define HanL_hOpen 138  //องศาอ้ามือจับเพื่อให้กระป๋องหลุดมือ
#define HanL_Close 160  //องศาหยิบกระป๋อง   **ห้ามให้ปลายมือแตะกัน เริ่มต้น
/*---------------------------------- มือขวา ---------------------------------*/
#define HanR_Open 123   //องศาอ้ามือจับ
#define HanR_hOpen 144  //องศาอ้ามือจับเพื่อให้กระป๋องหลุดมือ
#define HanR_Close 167  //องศาหยิบกระป๋อง   **ห้ามให้ปลายมือแตะกัน เริ่มต้น
/*---------------------------------- แขนซ้าย ---------------------------------*/
#define ArmL_F 37    //องศาเอาแขนไปด้านหน้า เพื่อแลกเปลี่ยนกระป๋อง เริ่มต้น
#define ArmL_G 69   //องศาสำหรับเข้าหยิบกระป๋อง
#define ArmL_C 86   //องศาสำหรับ วางกระป๋องหลุมด้านนอก
#define ArmL_B 167   //องศาเอามือไปด้านหลัง
#define ArmL_L 167  //องศาเอามือไปวางกระป๋องด้านหลัง
/*---------------------------------- แขนขวา ---------------------------------*/
#define ArmR_F 37   //องศาเอาแขนไปด้านหน้า เพื่อแลกเปลี่ยนกระป๋อง เริ่มต้น
#define ArmR_G 67   //องศาสำหรับเข้าหยิบกระป๋อง
#define ArmR_C 86   //องศาสำหรับ วางกระป๋องหลุมด้านนอก
#define ArmR_B 95   //องศาเอามือไปด้านหลัง
#define ArmR_L 148  //องศาเอามือไปวางกระป๋องด้านหลัง


void Arm_L_() {
#define Swing 10
#define time_Swing 18
  Motor5('s');
  Servo(3, ArmL_C);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(3, ArmL_C + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    delay(time_Swing);
  }
}

void Arm_R_() {
#define Swing 10
#define time_Swing 18
  Motor5('s');
  Servo(1, ArmR_C);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(1, ArmR_C - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }
}

void Arm_RC_() {
#define Swing 10
#define time_Swing 18
  Motor5('s');
  Servo(1, ArmR_F);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(1, ArmR_F - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(1, (ArmR_F - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(1, (ArmR_F + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(1, (ArmR_F - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(1, (ArmR_F + Swing) - i);
    delay(time_Swing);
  }
  Servo(1, ArmR_F);
  delay(200);
}


void Arm_LC_() {
#define Swing 10
#define time_Swing 18
  Motor5('s');
  Servo(3, ArmL_F);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(3, ArmL_F + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_F + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_F - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_F + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(3, (ArmL_F - Swing) + i);
    delay(time_Swing);
  }
  Servo(3, ArmL_F);
  delay(200);
}


void Arm_L_R_() {  //วาง ซ้าย และ ขวา
#define Swing 10
#define time_Swing 20
  Motor5('s');
  Servo(3, ArmL_C);
  Servo(1, ArmR_C);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(3, ArmL_C + i);
    Servo(1, ArmR_C - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }

  Servo(3, ArmL_C);
  Servo(1, ArmR_C);
  delay(200);
}


void Arm_L_C_() {
#define Swing 10
#define time_Swing 20
  Motor5('s');
  Servo(3, ArmL_C);
  Servo(1, ArmR_F);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(3, ArmL_C + i);
    Servo(1, ArmR_F - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    Servo(1, (ArmR_F - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    Servo(1, (ArmR_F + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_C + Swing) - i);
    Servo(1, (ArmR_F - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(3, (ArmL_C - Swing) + i);
    Servo(1, (ArmR_F + Swing) - i);
    delay(time_Swing);
  }

  Servo(3, ArmL_C);
  Servo(1, ArmR_F);
  delay(200);
}

void Arm_C_R_() {
#define Swing 10
#define time_Swing 20
  Motor5('s');
  Servo(3, ArmL_F);
  Servo(1, ArmR_C);
  delay(200);
  for (int i = 0; i < Swing; i++) {
    Servo(3, ArmL_F + i);
    Servo(1, ArmR_C - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_F + Swing) - i);
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_F - Swing) + i);
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing * 2; i++) {
    Servo(3, (ArmL_F + Swing) - i);
    Servo(1, (ArmR_C - Swing) + i);
    delay(time_Swing);
  }
  for (int i = 0; i < Swing; i++) {
    Servo(3, (ArmL_F - Swing) + i);
    Servo(1, (ArmR_C + Swing) - i);
    delay(time_Swing);
  }
  Servo(3, ArmL_F);
  Servo(1, ArmR_C);
  delay(200);
}

int valueServoHL, valueServoHR, valueServoAL, valueServoAR;
void HanL(char _position_) {
  if (_position_ == 'c') {
    Servo(4, HanL_Close);
    valueServoHL = HanL_Close;
  } else if (_position_ == 'o') {
    Servo(4, HanL_Open);
    valueServoHL = HanL_Open;
  } else if (_position_ == 'O') {
    Servo(4, HanL_hOpen);
    for (int i = HanL_hOpen; i > HanL_Open; i--) {
      Servo(4, i);
      delay(8);
    }
    valueServoHL = HanL_Open;
  } else if (_position_ == 'h') {
    Servo(4, HanL_hOpen);
    valueServoHL = HanL_hOpen;
  } else if (_position_ == 'H') {
    Servo(4, HanL_Open + 15);
    valueServoHL = HanL_Open + 15;
  }
}

void HanR(char _position_) {
  if (_position_ == 'c') {
    Servo(2, HanR_Close);
    valueServoHR = HanR_Close;
  } else if (_position_ == 'o') {
    Servo(2, HanR_Open);
    valueServoHR = HanR_Open;
  } else if (_position_ == 'O') {
    Servo(2, HanR_hOpen);
    for (int i = HanR_hOpen; i > HanR_Open; i--) {
      Servo(2, i);
      delay(8);
    }
    valueServoHR = HanR_Open;
  } else if (_position_ == 'h') {
    Servo(2, HanR_hOpen);
    valueServoHR = HanR_hOpen;
  } else if (_position_ == 'H') {
    Servo(2, HanR_Open + 15);
    valueServoHR = HanR_Open + 15;
  }
}

void ArmL(char _position_) {
  if (_position_ == 'c') {
    Servo(3, ArmL_C);
    valueServoAL = ArmL_C;
  } else if (_position_ == 'f') {
    Servo(3, ArmL_F);
    valueServoAL = ArmL_F;
  } else if (_position_ == 'F') {
    Servo(3, ArmL_F - 5);
    valueServoAL = ArmL_F - 5;
  } else if (_position_ == 'b') {
    Servo(3, ArmL_B);
    valueServoAL = ArmL_B;
  } else if (_position_ == 'g') {
    Servo(3, ArmL_G);
    valueServoAL = ArmL_G;
  } else if (_position_ == 'L') {
    Servo(3, ArmL_L);
    valueServoAL = ArmL_L;
  }
}

void ArmR(char _position_) {
  if (_position_ == 'c') {
    Servo(1, ArmR_C);
    valueServoAR = ArmR_C;
  } else if (_position_ == 'f') {
    Servo(1, ArmR_F);
    valueServoAR = ArmR_F;
  } else if (_position_ == 'F') {
    Servo(1, ArmR_F - 5);
    valueServoAR = ArmR_F - 5;
  } else if (_position_ == 'b') {
    Servo(1, ArmR_B);
    valueServoAR = ArmR_B;
  } else if (_position_ == 'g') {
    Servo(1, ArmR_G);
    valueServoAR = ArmR_G;
  } else if (_position_ == 'L') {
    Servo(1, ArmR_L);
    valueServoAR = ArmR_L;
  }
}


void HanLR(char LL, char RR) {
  if (LL == 'c') {
    HanL('c');
  } else if (LL == 'o') {
    HanL('o');
  } else if (LL == 'O') {
    HanL('O');
  } else if (LL == 'h') {
    HanL('h');
  } else if (LL == 'H') {
    HanL('H');
  }

  if (RR == 'c') {
    HanR('c');
  } else if (RR == 'o') {
    HanR('o');
  } else if (RR == 'O') {
    HanR('O');
  } else if (RR == 'h') {
    HanR('h');
  } else if (RR == 'H') {
    HanR('H');
  }
}

void ArmLR(char LL, char RR) {
  if (LL == 'c') {
    ArmL('c');
  } else if (LL == 'g') {
    ArmL('g');
  } else if (LL == 'f') {
    ArmL('f');
  } else if (LL == 'F') {
    ArmL('F');
  } else if (LL == ' F') {
    ArmL('F');
  } else if (LL == 'b') {
    ArmL('b');
  } else if (LL == 'L') {
    ArmL('L');
  }

  if (RR == 'c') {
    ArmR('c');
  } else if (RR == 'g') {
    ArmR('g');
  } else if (RR == 'f') {
    ArmR('f');
  } else if (RR == 'F') {
    ArmR('F');
  } else if (RR == 'F') {
    ArmR('F');
  } else if (RR == 'b') {
    ArmR('b');
  } else if (RR == 'L') {
    ArmR('L');
  }
}

void DropL() {
  Motor5('s');
  HanL('h');
  delay(300);
  HanL('o');
  delay(200);
}

void DropR() {
  Motor5('s');
  HanR('h');
  delay(300);
  HanR('o');
  delay(200);
}

void DropR(char i) {
  Motor5('s');
  HanR('h');
  delay(300);
  HanR(i);
  delay(200);
}

void DropL(char i) {
  Motor5('s');
  HanL('h');
  delay(300);
  HanL(i);
  delay(200);
}


void DropLR() {
  Motor5('s');
  HanLR('h', 'h');
  delay(300);
  HanLR('o', 'o');
  delay(200);
}

void SwapLR() {
  Motor5('s');
  HanR('o');
  if (valueServoAR >= ArmR_B) {
    ArmR('F');
    delay(200);
  }
  ArmR('F');
  delay(300);
  ArmL('f');
  delay(300);
  HanR('c');
  delay(200);
  HanL('o');
  delay(200);
  ArmR('c');
  delay(200);
  ArmL('c');
}

void SwapRL() {
  Motor5('s');
  HanL('o');
  if (valueServoAL >= ArmL_B) {
    ArmL('F');
    delay(200);
  }
  ArmL('F');
  delay(300);
  ArmR('f');
  delay(300);
  HanL('c');
  delay(200);
  HanR('o');
  delay(200);
  ArmL('c');
  delay(200);
  ArmR('c');
}

void TEST_Servo() {
  HanLR('c', 'c');
  ArmLR('c', 'c');
  while (1) {
    OLED.clearDisplay();
    OLED.setTextColor(SH110X_WHITE);
    OLED.setCursor(0, 0);
    OLED.setTextSize(2);
    OLED.println(" Set Servo");
    OLED.println("");
    OLED.print("HL : ");
    OLED.println(valueServoHL);
    OLED.display();
    //------------------------------------------- Setting Han L ------------------------------------------------------//
    while (1) {
      if (Serial.available() > 0) {
        int input = Serial.parseInt();  // อ่านค่าตัวเลขจาก Serial
        if (input > 0 && input <= 180) {
          Servo(4, input);
          Serial.print("มือซ้ายหมุนเซอร์โวไปที่: ");
          Serial.println(input);
          OLED.clearDisplay();
          OLED.setCursor(0, 0);
          OLED.println(" Set Servo ");
          OLED.print("HL : ");
          OLED.println(input);
          OLED.display();
        }
      }

      if (digitalRead(sw1) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }
    }
    //------------------------------------------- Setting Han R ------------------------------------------------------//
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.println(" Set Servo ");
    OLED.print("HR : ");
    OLED.println(valueServoHR);
    OLED.display();
    while (1) {
      if (Serial.available() > 0) {
        int input = Serial.parseInt();  // อ่านค่าตัวเลขจาก Serial
        if (input > 0 && input <= 180) {
          Servo(2, input);
          Serial.print("มือขวาหมุนเซอร์โวไปที่: ");
          Serial.println(input);
          OLED.clearDisplay();
          OLED.setCursor(0, 0);
          OLED.println(" Set Servo ");
          OLED.print("HR : ");
          OLED.println(input);
          OLED.display();
        }
      }

      if (digitalRead(sw1) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }
    }

    //------------------------------------------- Setting Arm L ------------------------------------------------------//
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.println(" Set Servo ");
    OLED.print("AL : ");
    OLED.println(valueServoAL);
    OLED.display();
    while (1) {
      if (Serial.available() > 0) {
        int input = Serial.parseInt();  // อ่านค่าตัวเลขจาก Serial
        if (input > 0 && input <= 180) {
          Servo(3, input);
          Serial.print("แขนซ้ายหมุนเซอร์โวไปที่: ");
          Serial.println(input);
          OLED.clearDisplay();
          OLED.setCursor(0, 0);
          OLED.println(" Set Servo ");
          OLED.print("AL : ");
          OLED.println(input);
          OLED.display();
        }
      }

      if (digitalRead(sw1) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }
    }

    //------------------------------------------- Setting Arm R ------------------------------------------------------//
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.println(" Set Servo ");
    OLED.print("AR : ");
    OLED.println(valueServoHR);
    OLED.display();
    while (1) {
      if (Serial.available() > 0) {
        int input = Serial.parseInt();  // อ่านค่าตัวเลขจาก Serial
        if (input > 0 && input <= 180) {
          Servo(1, input);
          Serial.print("แขนขวาหมุนเซอร์โวไปที่: ");
          Serial.println(input);
          OLED.clearDisplay();
          OLED.setCursor(0, 0);
          OLED.println(" Set Servo ");
          OLED.print("AR : ");
          OLED.println(input);
          OLED.display();
        }
      }

      if (digitalRead(sw1) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }
    }
  }
}


void TEST_ServoMode() {
  ArmLR('c', 'c');
  HanLR('h', 'h');
  while (1) {
    OLED.clearDisplay();
    OLED.setTextColor(SH110X_WHITE);
    OLED.setCursor(0, 0);
    OLED.setTextSize(2);
    OLED.println(" Set Servo");
    OLED.println("");
    OLED.print("HL : ");
    OLED.println(valueServoHL);
    OLED.display();
    //------------------------------------------- Setting Han L ------------------------------------------------------//
    Servo(4, valueServoHL);
    while (1) {
      if (digitalRead(sw1) == 0) {
        valueServoHL++;
        BZ(1, 100);
      }

      if (digitalRead(sw2) == 0) {
        valueServoHL--;
        BZ(1, 100);
      }

      if (valueServoHL < 0) valueServoHL = 0;
      if (valueServoHL > 180) valueServoHL = 180;

      if (digitalRead(swMode) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }

      Servo(4, valueServoHL);
      OLED.clearDisplay();
      OLED.setCursor(0, 0);
      OLED.println(" Set Servo ");
      OLED.print("HL : ");
      OLED.println(valueServoHL);
      OLED.display();
    }
    //------------------------------------------- Setting Han R ------------------------------------------------------//
    Servo(2, valueServoHR);
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.println(" Set Servo ");
    OLED.print("HR : ");
    OLED.println(valueServoHR);
    OLED.display();
    while (1) {
      if (digitalRead(sw1) == 0) {
        valueServoHR++;
        BZ(1, 100);
      }

      if (digitalRead(sw2) == 0) {
        valueServoHR--;
        BZ(1, 100);
      }

      if (valueServoHR < 0) valueServoHR = 0;
      if (valueServoHR > 180) valueServoHR = 180;

      if (digitalRead(swMode) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }

      Servo(2, valueServoHR);
      OLED.clearDisplay();
      OLED.setCursor(0, 0);
      OLED.println(" Set Servo ");
      OLED.print("HR : ");
      OLED.println(valueServoHR);
      OLED.display();
    }

    //------------------------------------------- Setting Arm L ------------------------------------------------------//
    Servo(3, valueServoAL);
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.println(" Set Servo ");
    OLED.print("AL : ");
    OLED.println(valueServoAL);
    OLED.display();
    while (1) {
      if (digitalRead(sw1) == 0) {
        valueServoAL++;
        BZ(1, 100);
      }

      if (digitalRead(sw2) == 0) {
        valueServoAL--;
        BZ(1, 100);
      }

      if (valueServoAL < 0) valueServoAL = 0;
      if (valueServoAL > 180) valueServoAL = 180;

      if (digitalRead(swMode) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }

      Servo(3, valueServoAL);
      OLED.clearDisplay();
      OLED.setCursor(0, 0);
      OLED.println(" Set Servo ");
      OLED.print("AL : ");
      OLED.println(valueServoAL);
      OLED.display();
    }

    //------------------------------------------- Setting Arm R ------------------------------------------------------//
    Servo(1, valueServoAR);
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    OLED.println(" Set Servo ");
    OLED.print("AR : ");
    OLED.println(valueServoAR);
    OLED.display();
    while (1) {
      if (digitalRead(sw1) == 0) {
        valueServoAR++;
        BZ(1, 100);
      }

      if (digitalRead(sw2) == 0) {
        valueServoAR--;
        BZ(1, 100);
      }

      if (valueServoAR < 0) valueServoAR = 0;
      if (valueServoAR > 180) valueServoAR = 180;

      if (digitalRead(swMode) == 0) {
        BZ(1, 100);
        delay(200);
        break;
      }

      Servo(1, valueServoAR);
      OLED.clearDisplay();
      OLED.setCursor(0, 0);
      OLED.println(" Set Servo ");
      OLED.print("AR : ");
      OLED.println(valueServoAR);
      OLED.display();
    }
  }
}

/*
void GetCanLoad1(int UltraMin, int _Lift_) {  //หยิบครั้งที่ 1 เพื่อโหลด
  HanLR('o', 'o');
  ArmLR('g', 'g');
  ResetEncodeMove();
  ResetErrorPID();

  while (1) {  // เมื่อระยะห่างจากกระป๋อง Speed เร็ว
    MoveLift(_Lift_);
    if (Ultra() > 15) {
      ControlSpeedForward(saveAngle, 50);
    } else {
      break;
    }
  }

  Lift(_Lift_);
  Motor5('s');

  while (1) {
    if (Ultra() > UltraMin) {
      ControlSpeedForward(saveAngle, 35);
    } else {
      FFe(30, 10);
      MotorShot(255);
      HanLR('c', 'c');
      delay(200);

      HanLR('h', 'h');  //เพิ่ม SetCan ก่อน break;
      delay(200);
      HanLR('c', 'c');
      break;
    }
  }

  Lift(Encodepoint + 1000);  //ยกแขนเพิ่มหลังหยิบกระป๋อง
  CheckColorL();
  CheckColorR();
  ColorLoadL = colorL;
  ColorLoadR = colorR;

  LoadCanLR();
  Lift(Encodepoint + 1000);

  Motor5('s');
  ResetEncodeMove();
  ResetErrorPID();
  MotorShot(255);
}



void GetCanLoad2(int UltraMin, int _Lift_) {  //หยิบครั้งที่ 2
  HanLR('o', 'o');
  ArmLR('g', 'g');
  ResetEncodeMove();
  ResetErrorPID();

  while (1) {  // เมื่อระยะห่างจากกระป๋อง Speed เร็ว
    MoveLift(_Lift_);
    if (Ultra() > 15) {
      ControlSpeedForward(saveAngle, 50);
    } else {
      break;
    }
  }

  Lift(_Lift_);
  Motor5('s');

  while (1) {
    if (Ultra() > UltraMin) {
      ControlSpeedForward(saveAngle, 35);
    } else {
      FFe(30, 10);
      MotorShot(255);
      HanLR('c', 'c');
      delay(200);

      HanLR('h', 'h');  //เพิ่ม SetCan ก่อน break;
      delay(200);
      HanLR('c', 'c');
      break;
    }
  }

  Lift(Encodepoint + 1000);  //ยกแขนเพิ่มหลังหยิบกระป๋อง
  CheckColorL();
  CheckColorR();
  ColorHANL = colorL;
  ColorHANR = colorR;
  MonitorRGBx4();

  Motor5('s');
  ResetEncodeMove();
  ResetErrorPID();
  MotorShot(255);
}


void Drop180_1(int UltraMin, int _Lift_) {  //ไปวางรอบที่ 1
  LastLift = _Lift_;                        //เก็บค่า lift ไว้ใช้กรณีวางเพิ่มกระป๋องซ้ำ
  ArmLR('c', 'c');
  Lift(_Lift_);
  ResetEncodeMove();
  ResetErrorPID();
  Motor5('s');

  while (1) {
    if (Ultra() > UltraMin) {
      ControlSpeedForward(saveAngle, 35);
    } else {
      while (1) {
        if (analog(7) < 1000) {
          ControlSpeedForward(saveAngle, 30);
        } else {
          MotorShot(255);
          Motor5('s');
          delay(100);
          break;
        }
      }
      break;
    }
  }

  MotorShot(255);
  Motor5('s');
  ResetEncodeMove();
  ResetErrorPID();

  Auto_Drop180_1();
}

void Drop180_2(int UltraMin, int _Lift_) {  //ไปวางรอบที่ 2
  LastLift = _Lift_;                        //เก็บค่า lift ไว้ใช้กรณีวางเพิ่มกระป๋องซ้ำ
  ArmLR('c', 'c');
  Lift(_Lift_);
  ResetEncodeMove();
  ResetErrorPID();
  Motor5('s');

  while (1) {
    if (Ultra() > UltraMin) {
      ControlSpeedForward(saveAngle, 35);
    } else {
      while (1) {
        if (analog(7) < 1000) {
          ControlSpeedForward(saveAngle, 30);
        } else {
          MotorShot(255);
          Motor5('s');
          delay(100);
          break;
        }
      }
      break;
    }
  }

  MotorShot(255);
  Motor5('s');
  ResetEncodeMove();
  ResetErrorPID();

  Auto_Drop180_2();
}


void Auto_Drop180_1() {
  if (ColorLoadL == 3 && ColorLoadR == 3 && ColorHANL == 2 && ColorHANR == 1) {  //RRYG
    DropCan2('c', 'l');
    BBe(80, 300);
    GetLoadR();
    SetCan();
    Lift(LastLift);
    ArmLR('b', 'c');
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 3 && ColorLoadR == 3 && ColorHANL == 1 && ColorHANR == 2) {  ///RRGY
    DropCan2('l', 'c');
    BBe(80, 300);
    GetLoadR();
    SetCan();
    Lift(LastLift);
    ArmLR('b', 'c');
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 3 && ColorLoadR == 2 && ColorHANL == 3 && ColorHANR == 1) {  ///RYRG
    ArmLR('f', 'c');
    delay(300);
    HanL('h');
    Arm_LC_();
    HanLR('O', 'c');
    delay(200);
    BBe(80, 300);
    SwapRL();
    ArmLR('c', 'F');
    MoveLimit(30);
    HanLR('c', 'c');
    Lift(LastLift + 500);
    BBe(80, 300);
    ArmLR('c', 'c');
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'r');
    // ST();
  } else if (ColorLoadL == 3 && ColorLoadR == 1 && ColorHANL == 3 && ColorHANR == 2) {  ///RGRY
    DropCan2('b', 'c');
    BBe(80, 300);
    ArmLR('c', 'F');
    delay(200);
    SwapLR();
    SetCan();
    ArmLR('b', 'c');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'r');
    // ST();

  } else if (ColorLoadL == 3 && ColorLoadR == 2 && ColorHANL == 1 && ColorHANR == 3) {  ///RYGR
    DropCan2('l', 'r');
  } else if (ColorLoadL == 3 && ColorLoadR == 1 && ColorHANL == 2 && ColorHANR == 3) {  ///RGYR
    DropCan2('c', 'r');
  } else if (ColorLoadL == 2 && ColorLoadR == 3 && ColorHANL == 3 && ColorHANR == 1) {  ///YRRG
    ArmLR('f', 'c');
    delay(300);
    HanL('h');
    Arm_LC_();
    HanLR('O', 'c');
    delay(200);
    BBe(80, 300);
    SwapRL();
    ArmLR('c', 'F');
    MoveLimit(30);
    HanLR('c', 'c');
    Lift(LastLift + 500);
    BBe(80, 300);
    ArmLR('c', 'c');
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'r');
  } else if (ColorLoadL == 1 && ColorLoadR == 3 && ColorHANL == 3 && ColorHANR == 2) {  ///GRRY
    DropCan2('b', 'c');
    BBe(80, 300);
    ArmLR('c', 'F');
    delay(200);
    SwapLR();
    SetCan();
    ArmLR('b', 'c');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 2 && ColorLoadR == 3 && ColorHANL == 1 && ColorHANR == 3) {  ///YRGR
    DropCan2('l', 'r');
  } else if (ColorLoadL == 1 && ColorLoadR == 3 && ColorHANL == 2 && ColorHANR == 3) {  ///GRYR
    DropCan2('c', 'r');
  } else if (ColorLoadL == 2 && ColorLoadR == 1 && ColorHANL == 3 && ColorHANR == 3) {  ///YGRR
    DropCan2('b', 'r');
    BBe(80, 300);
    ArmLR('c', 'f');
    delay(200);
    SwapLR();
    delay(200);
    GetLoadL();
    SetCan();
    ArmLR('c', 'b');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('c', 'b');
  } else if (ColorLoadL == 1 && ColorLoadR == 2 && ColorHANL == 3 && ColorHANR == 3) {  ///GYRR
    DropCan2('b', 'r');
    BBe(80, 300);
    ArmLR('c', 'f');
    delay(200);
    SwapLR();
    delay(200);
    GetLoadL();
    SetCan();
    ArmLR('l', 'b');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'b');
  } else {
    BZ(3, 100);
    while (1) {
      MotorStop();
    }
  }
}


void Auto_Drop180_2() {
  if (ColorLoadL == 3 && ColorLoadR == 3 && ColorHANL == 2 && ColorHANR == 1) {  //RRYG
    BBe(80, 300);
    GetLoadL();
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('r', 'b');
  } else if (ColorLoadL == 3 && ColorLoadR == 3 && ColorHANL == 1 && ColorHANR == 2) {  //RRGY
    BBe(80, 300);
    GetLoadL();
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('r', 'b');
  } else if (ColorLoadL == 3 && ColorLoadR == 2 && ColorHANL == 3 && ColorHANR == 1) {  ///RYRG)
    BBe(80, 300);
    GetLoadR();
    SetCan();
    ArmLR('b', 'c');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'c');
    BBe(80, 300);
    GetLoadL();
    SwapLR();
    SetCan();
    ArmLR('b', 'c');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 3 && ColorLoadR == 1 && ColorHANL == 3 && ColorHANR == 2) {  ///RGRY
    BBe(80, 300);
    GetLoadR();
    SetCan();
    SwapRL();
    ArmLR('l', 'b');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'b');
    BBe(80, 300);
    GetLoadL();
    SwapLR();
    SetCan();
    ArmLR('b', 'r');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 3 && ColorLoadR == 2 && ColorHANL == 1 && ColorHANR == 3) {  ///RYGR
    BBe(80, 300);
    GetLoadLR();
    SetCan();
    ArmLR('b', 'c');
    HanL('c');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'c');
    BBe(80, 300);
    ArmLR('c', 'f');
    HanL('c');
    delay(200);
    SwapLR();
    ArmLR('b', 'r');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 3 && ColorLoadR == 1 && ColorHANL == 2 && ColorHANR == 3) {  ///RGYR
    BBe(80, 300);
    GetLoadR();
    SetCan();
    SwapRL();
    delay(200);
    ArmLR('c', 'b');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'b');
    BBe(80, 300);
    GetLoadL();
    SwapLR();
    delay(200);
    SetCan();
    ArmLR('b', 'c');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('b', 'r');
  } else if (ColorLoadL == 2 && ColorLoadR == 3 && ColorHANL == 3 && ColorHANR == 1) {  ///YRRG
    BBe(80, 300);
    GetLoadLR();
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('c', 'r');
  } else if (ColorLoadL == 1 && ColorLoadR == 3 && ColorHANL == 3 && ColorHANR == 2) {  ///GRRY
    BBe(80, 300);
    GetLoadLR();
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'r');
  } else if (ColorLoadL == 2 && ColorLoadR == 3 && ColorHANL == 1 && ColorHANR == 3) {  ///YRGR
    BBe(80, 300);
    GetLoadLR();
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('c', 'r');
  } else if (ColorLoadL == 1 && ColorLoadR == 3 && ColorHANL == 2 && ColorHANR == 3) {  ///GRYR
    BBe(80, 300);
    GetLoadLR();
    SetCan();
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'r');
  } else if (ColorLoadL == 2 && ColorLoadR == 1 && ColorHANL == 3 && ColorHANR == 3) {  ///YGRR
    HanR('h');
    Arm_R_();
    HanR('O');
    BBe(80, 300);
    GetLoadR();
    SetCan();
    SwapRL();
    HanR('c');
    ArmR('b');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('l', 'b');
  } else if (ColorLoadL == 1 && ColorLoadR == 2 && ColorHANL == 3 && ColorHANR == 3) {  ///GYRR
    HanR('h');
    Arm_R_();
    HanR('O');
    BBe(80, 300);
    GetLoadR();
    SetCan();
    SwapRL();
    HanR('c');
    ArmR('b');
    Lift(LastLift);
    MoveLimit(30);
    DropCan2('c', 'b');
  }
}
*/
void GetCan(int UltraMin, int _Lift_ , char arm) {

  if (arm == 'l') {
    HanLR('o', 'c'); 
    ArmLR('g','b');
  } 
  else if (arm == 'r') {
    HanLR('c', 'o');
    ArmLR('b','g');
  }
  else {
    HanLR('o', 'o');
    ArmLR('g','g');
  }

  unsigned long time_set = millis();
  while (millis() - time_set < 200) {
    ResetAngle_Z();
    MoveLift(_Lift_);
  }

  while (1) {  // เมื่อระยะห่างจากกระป๋อง Speed เร็ว
    MoveLift(_Lift_);
    if (Ultra() > 20) {
      Forward(saveAngle, 50);
    } else {
      MotorShot(255);
      delay(10);
      break;
    }
  }

  Lift(_Lift_);
  MT(50, 50, 50);

  while (1) {
    Motor5('s');
    if (Ultra() > UltraMin) {
      Forward(saveAngle, 30);
    } else {
      //FFe(30,70);  //เดินหน้าเพิ่มนิดหน่อย
      
      MotorShot(255);
      
      delay(120);

      break;
    }
  }


    //SelectGetCan();  // Auto คัดแยกกระป๋อง
    delay(120);
    //FFe(10,80);
    //delay(500);


  if (arm == 'l'){
    HanLR('c','c');
    delay(120);
    
    Lift(Encodepoint + 800);
    MotorShot(255);
    delay(120);
    BBe(30, 550 ,0.5);
    delay(200);
    Lift(850);
    delay(120);

  }
  else if (arm == 'r'){
    HanLR('c','c');
    delay(120);

    Lift(Encodepoint + 800);
    MotorShot(255);
    delay(120);
    BBe(30, 550 ,0.5);
    delay(200);
    Lift(850);
    delay(120);

  }
  else{
    HanLR('c', 'c');
    delay(120);

    Lift(Encodepoint + 800);
    MotorShot(255);
    delay(120);
    BBe(30, 550 ,0.5);
    delay(200);
    Lift(850);
    delay(120);
  }
  
  







   
  /*
  CheckColorL();
  delay(500);
  CheckColorR();
  colorcan();
  */
}





int Get2 = 0;
void GetCan2(int UltraMin, int _Lift_) {
  HanLR('o', 'o');
  ArmLR('g', 'g');

  unsigned long time_set = millis();
  while (millis() - time_set < 200) {
    SetAngle(saveAngle);
    MoveLift(_Lift_);
  }

  Lift(_Lift_);
  FFe(100, 100,  0);

  while (1) {
    Motor5('s');
    if (Ultra() > UltraMin) {
      Forward(saveAngle, 30);
    } else {
      MotorShot(255);
      HanLR('c', 'c');
      delay(300);
      break;
    }
  }

  Lift(Encodepoint + 300);  //ยกแขนเพิ่มหลังหยิบกระป๋อง
  Get2 = 1;
  /*
  CheckColorL();
  CheckColorR();
  */
  SetCan();
  colorcan();
  MotorShot(255);
  delay(120);
}






void GetCan3(int UltraMin, int _Lift_) {
  HanLR('o', 'o');
  ArmLR('g', 'g');
  unsigned long time_set = millis();
  while (millis() - time_set < 200) {
    SetAngle(saveAngle);
    MoveLift(_Lift_);
  }

  while (1) {  // เมื่อระยะห่างจากกระป๋อง Speed เร็ว
    MoveLift(_Lift_);
    if (Ultra() > 20) {
      Forward(saveAngle, 50);
    } else {
      MotorShot(255);
      delay(10);
      break;
    }
  }

  Lift(_Lift_);
  MT(50, 50, 50);

  while (1) {
    Motor5('s');
    if (Ultra() > UltraMin) {
      Forward(saveAngle, 30);
    } else {
      //FFe(30,70);  //เดินหน้าเพิ่มนิดหน่อย
      
      MotorShot(255);
      
      delay(120);

      break;
    }
  }
  
  //SelectGetCan();  // Auto คัดแยกกระป๋อง
    delay(500);
   //FFe(10,150);
    //delay(500);

Lift(880);
delay(120);

  HanL('c');
  HanR('c');
  delay(120);
  

  Lift(2000);
  MotorShot(255);
  delay(120);
  BBe(30, 300 ,0.5);
  delay(120);
  Lift(1200);
 delay(120);





   
  /*
  CheckColorL();
  delay(500);
  CheckColorR();
  colorcan();
  */
}







void swcan() {
   Lift(0);
    ArmLR('f', 'g');
    delay(500);
    HanLR('o', 'c'); 
    delay(500);
    BBe(40,200,0.5);
    ArmLR('f', 'f');
    delay(500);
    HanL('c');
    delay(500);
    HanR('o');
    delay(500);
    ArmLR('c', 'f');
    delay(500);
    FFe(40,200,0.5);
    HanR('c');
    delay(500);
    ArmLR('g', 'g');
    delay(500);
}

void colorcan() {
  if(colorR == 1 && colorL == 3 || colorR == 2 && colorL == 3 || colorR == 2 && colorL == 3 ||  colorR == 1 && colorL == 2 ){
    Lift(0);
    ArmLR('f', 'g');
    delay(500);
    HanLR('o', 'c'); 
    delay(500);
    BBe(40,200,0.5);
    ArmLR('f', 'f');
    delay(500);
    HanL('c');
    delay(500);
    HanR('o');
    delay(500);
    ArmLR('c', 'f');
    delay(500);
    FFe(40,200,0.5);
    HanR('c');
    delay(500);
    ArmLR('g', 'g');
    delay(500);
     

  }else{

  }

}

void SelectGetCan() {
  CheckColorL();
  CheckColorR();

  if (colorL == 1 && colorR == 1) {  //กรณีซ้ำ สีเขียว
    HanLR('c', 'o');
    colorR = 0;
  } else if (colorL == 2 && colorR == 2) {  //กรณีซ้ำ สีเหลือง
    HanLR('c', 'o');
    colorR = 0;
  } else if (colorL == 3 && colorR == 3) {  //กรณีซ้ำ สีแดง
    HanLR('o', 'c');
    colorL = 0;
  } else if (colorL == 3 && colorR == 1) {  //กรณี ซ้ายและขวาต้องสลับกัน
    ArmLR('f', 'c');
    delay(300);
    HanLR('h', 'c');
    delay(200);
    HanLR('o', 'c');
    ArmL('F');
    delay(200);
    BBt(50, 300);
    SwapRL();
    ArmLR('c', 'F');
    FFt(50, 100);
    if (Get2 == 1) {  //กรณีสลับกระป๋องแบบไม่มีแท่นต้องกลับไปเก็บกระป๋องแดงด้วย timer
      FFt(50, 260);
    } else MoveUltra(2);  //เดินหน้าด้วย ระยะ อัลตร้า กรณีมีแท่น
    HanLR('c', 'c');
    delay(200);
    ArmLR('c', 'c');
    Get2 = 0;  //reset
  }
}

void SelectDropCan() {
  if (colorL == 1 && colorR == 2) DropCan2('l', 'c');
  else if (colorL == 2 && colorR == 3) DropCan2('c', 'r');
  else if (colorL == 1 && colorR == 3) DropCan2('l', 'r');
  else if (colorL == 3 && colorR == 2) DropCan2('c', 'r');
  else if (colorL == 2 && colorR == 1) DropCan2('l', 'c');
  else if (colorL == 1 && colorR == 0) DropCan2('l', 'b');
  else if (colorL == 0 && colorR == 3) DropCan2('b', 'r');
  else if (colorL == 2 && colorR == 0) DropCan2('c', 'b');
  else DropCan2('l', 'r');
}


int delayHan = 200;
void DropCan2(char LL, char RR) {
  if (LL == 'l' && RR == 'r') {  //ซ้ายวางซ้าย ขวาวางขวา
    ArmLR('c', 'c');
    delay(300);
    HanLR('h', 'h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_L_R_();
    delay(200);
    HanLR('o', 'o');
    delay(300);
  } else if (LL == 'l' && RR == 'c') {  //ซ้ายวางซ้าย ขวาวางกลาง
    ArmLR('c', 'f');
    delay(300);
    HanLR('h', 'h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_L_C_();
    delay(200);
    HanLR('H', 'o');
    ArmR('F');
    delay(300);
  } else if (LL == 'c' && RR == 'r') {  //ซ้ายวางกลาง  ขวาวางขวา
    ArmLR('f', 'c');
    delay(300);
    HanLR('h', 'h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_C_R_();
    delay(200);
    HanLR('o', 'H');
    ArmL('F');
    delay(300);
  } else if (LL == 'b' && RR == 'r') {  //วางขวาอย่างเดียว
    ArmLR('b', 'c');
    delay(300);
    HanR('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_R_();
    delay(200);
    HanR('o');
    delay(200);
  } else if (LL == 'l' && RR == 'b') {  //วางซ้ายอย่างเดียว
    ArmLR('c', 'b');
    delay(300);
    HanL('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_L_();
    delay(200);
    HanL('o');
    delay(200);
  } else if (LL == 'c' && RR == 'b') {  //ซ้ายวางกลางอย่างเดียว
    ArmLR('f', 'b');
    delay(300);
    HanL('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_LC_();
    delay(200);
    HanL('o');
    ArmL('F');
    delay(200);
  } else if (LL == 'b' && RR == 'c') {  //ขวาวางกลางอย่างเดียว
    ArmLR('b', 'f');
    delay(300);
    HanR('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_RC_();
    delay(200);
    HanR('o');
    ArmR('F');
    delay(200);
  } else if (LL == 'r' && RR == 'c') {  //ซ้ายวางขวา ขวาวางกลาง
    ArmLR('b', 'f');
    delay(300);
    HanR('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_RC_();
    delay(200);
    HanR('o');
    ArmR('F');
    delay(300);
    BBt(50, 300);
    SwapLR();
    delay(300);
    ArmLR('b', 'c');
    FFt(50, 100);
    MoveUltra(2);  //เดินหน้าด้วย ระยะ อัลตร้า
    HanR('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_R_();
    delay(200);
    HanR('H');
    delay(300);
  } else if (LL == 'c' && RR == 'l') {  //ซ้ายวางกลาง ขวาวางซ้าย
    ArmLR('f', 'b');
    delay(300);
    HanL('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_LC_();
    delay(200);
    HanL('o');
    ArmL('F');
    delay(300);
    BBt(50, 300);
    SwapRL();
    delay(300);
    ArmLR('c', 'b');
    FFt(50, 100);
    MoveUltra(2);  //เดินหน้าด้วย ระยะ อัลตร้า
    HanL('h');
    Motor5(-200);
    delay(delayHan);
    Motor5('s');
    delay(100);
    Arm_L_();
    delay(200);
    HanL('H');
    delay(300);
  }
}

void MoveUltra(int cm) {
  while (1) {
    if (Ultra() > cm) {
      Forward(saveAngle, 23);
    } else {
      FFt(23, 150);  //เดินหน้าเพิ่มนิดหน่อย
      MotorShot(100);
      delay(5);
      break;
    }
  }
}

void DropCan(int UltraMin, int _Lift_) {
  unsigned long time_set = millis();
  while (millis() - time_set < 200) {
    SetAngle(saveAngle);
    MoveLift(_Lift_);
  }

  Lift(_Lift_);

  while (1) {
    MoveLift(_Lift_);
    if (Ultra() > 10) {
      Forward(saveAngle, 30);
    } else {
      MotorShot(100);
      delay(5);
      break;
    }
  }

  MT(50, 50, 50);
  while (1) {
    Motor5('s');
    if (Ultra() > UltraMin) {
      Forward(saveAngle, 20);
    } else {
      //FFe(20,70);  //เดินหน้าเพิ่มนิดหน่อย
      
      Motor5('s');
      MotorShot(255);
      break;
    }
  }
  //SelectDropCan();  Auto Drop

  
  MotorStop();
  delay(200); 
  
  
}

void SetCan() {
 delay(200);
  ArmR('c');
  ArmL('c');
  delay(200);
  MotorStop();
  delay(150);
  Lift(0);
  MotorStop();
  delay(500);
  HanLR('o', 'o');
  delay(500);
  HanLR('c', 'c');
  delay(100);
  Lift(400);
  Stop(100);
}

void DropCanM(int UltraMin, int _Lift_) {
   SetCan();
  unsigned long time_set = millis();
  while (millis() - time_set < 200) {
    SetAngle(saveAngle);
    MoveLift(_Lift_);
  }

  Lift(_Lift_);

  while (1) {
    MoveLift(_Lift_);
    if (Ultra() > 10) {
      Forward(saveAngle, 30);
    } else {
      MotorShot(100);
      delay(5);
      break;
    }
  }

  MT(50, 50, 50);
  while (1) {
    Motor5('s');
    if (Ultra() > UltraMin) {
      Forward(saveAngle, 20);
    } else {
      //FFe(30,70);  //เดินหน้าเพิ่มนิดหน่อย
      
      Motor5('s');
      MotorShot(255);
      break;
    }
  }
  //SelectDropCan();  // Auto Drop
  MotorStop();
  delay(200); 
  
  
}
void SetLR(){ 
  SpinL();
  delay(1500); 
  SpinR(); 
  delay(1500);
  SpinL(); 
  }
void SetAH(){
 
  Lift(0);
  HanLR('c', 'c');   
  delay(10);       
  ArmLR('f', 'f');   
  
}

void DropLA(){



}
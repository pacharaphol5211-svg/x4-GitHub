void Can1() {

FF(200, 750);
SpinL();
FFe(150, 550);
SpinL();
BB(100,450);
delay(500);
SpinR();
delay(500);
FFe(40,235);
St('l');
delay(500);
GetCan(1, 1600,'o');
delay(500);

SpinL();
FFe(150,1200);
SpinL(1);
BB(40,200);
SpinR();
delay(250);
FFe(40,235);
St('l');
delay(500);
DropCan(1,3600);
DropCan2('l','r');

BB(40,100);
delay(500);
SetAH();
delay(500);
SpinL();
Lift(600);
delay(500);
FF(150,750);

}

void Can2() {
}

void Can3() {
}

void Can4() {
}

void End() {
}

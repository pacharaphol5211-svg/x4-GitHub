#include <Wire.h>
#include <math.h>
#include "Adafruit_TCS34725.h"
#define PCA9548A_ADDR 0x70
Adafruit_TCS34725 tcs_ = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c;

//----------------------------------------- จุดบันทึกค่าสีกระป๋อง (ปรับจูนค่าได้ที่นี่) --------------------------------------------//
// รูปแบบ: {R, G, B}
uint8_t CAN_RED[3] = { 105, 85, 62 };     // ค่ากระป๋องแดงอ้างอิง
uint8_t CAN_YELLOW[3] = { 88, 104, 40 };  // ค่ากระป๋องเหลืองอ้างอิง

// ค่าความคลาดเคลื่อนที่ยอมรับได้ (ยิ่งน้อยยิ่งเข้มงวด)
// สำหรับ Euclidean Distance แนะนำให้เริ่มที่ 15.0 - 20.0 ค่ากึ่งกลางระหว่าง แดง vs เขียว
const float tol = 18.0;

//----------------------------------------- ฟังก์ชันจัดการ Multiplexer --------------------------------------------//
void selectMuxChannel(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(PCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

//----------------------------------------- ฟังก์ชันอ่านค่าจากเซนเซอร์ --------------------------------------------//
void TSC(int num) {
  r = 0;
  g = 0;
  b = 0;
  c = 0;
  selectMuxChannel(num);
  delay(10);  // รอให้เซนเซอร์พร้อมทำงานหลังสลับ Channel
  tcs_.getRawData(&r, &g, &b, &c);
}

float valueMatch = 0.0;
//----------------------------------------- ฟังก์ชันเปรียบเทียบสี (Euclidean Distance) --------------------------------------------//
bool ColorMatch(float r, float g, float b, float r_ref, float g_ref, float b_ref, float threshold) {
  float dr = r - r_ref;
  float dg = g - g_ref;
  float db = b - b_ref;
  float distance = sqrt(dr * dr + dg * dg + db * db);
  valueMatch = distance;
  return distance <= threshold;
}

//----------------------------------------- ฟังก์ชัน Setup และการอ่านค่า --------------------------------------------//
void setupRGB() {
  Wire.begin();
  selectMuxChannel(0);
  if (tcs_.begin()) { Serial.println("TCS34725 Sensor 0 Found"); }

  selectMuxChannel(1);
  if (tcs_.begin()) { Serial.println("TCS34725 Sensor 1 Found"); }
}

void CheckColorL() {
  TSC(1);  // อ่านเซนเซอร์ฝั่งซ้าย (Mux Channel 1)
  float red = (float)r / c * 256;
  float green = (float)g / c * 256;
  float blue = (float)b / c * 256;

  Serial.print("มือซ้าย  -> ");
  Serial.print("R:");
  Serial.print(red);
  Serial.print(" G:");
  Serial.print(green);
  Serial.print(" B:");
  Serial.print(blue);
  Serial.print("\t สีที่อ่านได้: ");

  if (ColorMatch(red, green, blue, CAN_RED[0], CAN_RED[1], CAN_RED[2], tol)) {
    Serial.print("แดง");
    colorL = 3;
  } else if (ColorMatch(red, green, blue, CAN_YELLOW[0], CAN_YELLOW[1], CAN_YELLOW[2], tol)) {
    Serial.print("เหลือง");
    colorL = 2;
  } else {
    Serial.print("เขียว");
    colorL = 1;
  }

  Serial.print("\t Match: ");
  Serial.print(valueMatch);
}

void CheckColorR() {
  TSC(0);  // อ่านเซนเซอร์ฝั่งขวา (Mux Channel 0)
  float red = (float)r / c * 256;
  float green = (float)g / c * 256;
  float blue = (float)b / c * 256;

  Serial.print("\t");
  Serial.print("มือขวา -> ");
  Serial.print("R:");
  Serial.print(red);
  Serial.print(" G:");
  Serial.print(green);
  Serial.print(" B:");
  Serial.print(blue);
  Serial.print("\t สีที่อ่านได้: ");

  if (ColorMatch(red, green, blue, CAN_RED[0], CAN_RED[1], CAN_RED[2], tol)) {
    Serial.print("แดง");
    colorR = 3;
  } else if (ColorMatch(red, green, blue, CAN_YELLOW[0], CAN_YELLOW[1], CAN_YELLOW[2], tol)) {
    Serial.print("เหลือง");
    colorR = 2;
  } else {
    Serial.print("เขียว");
    colorR = 1;
  }

  Serial.print("\t Match: ");
  Serial.println(valueMatch);
}

void ReadRGB() {
  while (1) {
    MonitorRGB();
  }
}

void MonitorRGB() {
  ArmLR('c', 'c');
  HanLR('h', 'h');
  OLED.setTextSize(1);
  OLED.setTextColor(SH110X_WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println(" COLOR CAN");
  OLED.println("");
  CheckColorL();
  OLED.print("HL : ");
  if (colorL == 3) OLED.println("R");
  else if (colorL == 2) OLED.println("Y");
  else OLED.println("G");
  OLED.println("");
  CheckColorR();
  OLED.print("HR : ");
  if (colorR == 3) OLED.println("R");
  else if (colorR == 2) OLED.println("Y");
  else OLED.println("G");

  OLED.display();
  OLED.clearDisplay();
}

void StopMonitorRGB() {
  MotorStop();
  OLED.setTextSize(1);
  OLED.setTextColor(SH110X_WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println(" COLOR CAN");
  OLED.println("");
  OLED.print("HL : ");
  if (colorL == 3) OLED.println("R");
  else if (colorL == 2) OLED.println("Y");
  else OLED.println("G");
  OLED.println("");
  OLED.print("HR : ");
  if (colorR == 3) OLED.println("R");
  else if (colorR == 2) OLED.println("Y");
  else OLED.println("G");

  OLED.display();
  OLED.clearDisplay();

  // while (1) {
  //   if (digitalRead(sw1) == 0) break;
  // }
  // delay(300);
}


void MonitorRGBx4() {
  OLED.setTextSize(1);
  OLED.setTextColor(SH110X_WHITE);
  OLED.setCursor(0, 0);
  OLED.setTextSize(2);
  OLED.println(" COLOR CAN");

  OLED.println("");
  OLED.print("LoL : ");
  if (ColorLoadL == 3) OLED.println("R");
  else if (ColorLoadL == 2) OLED.println("Y");
  else OLED.println("G");
  OLED.print("LoR : ");
  if (ColorLoadR == 3) OLED.println("R");
  else if (ColorLoadR == 2) OLED.println("Y");
  else OLED.println("G");
  OLED.println("");
  OLED.print("HL : ");
  if (ColorHANL == 3) OLED.println("R");
  else if (ColorHANL == 2) OLED.println("Y");
  else OLED.println("G");
  OLED.print("HR : ");
  if (ColorHANR == 3) OLED.println("R");
  else if (ColorHANR == 2) OLED.println("Y");
  else OLED.println("G");

  OLED.display();
  OLED.clearDisplay();
}
#define LCD_PWR 2
#define LCD_DC 3
#define LCD_E 4
#define LCD_BUS 5

void setup() {
  pinMode(LCD_PWR, OUTPUT);
  pinMode(LCD_DC, OUTPUT);
  pinMode(LCD_E, OUTPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(LCD_BUS + i, OUTPUT);
  }
  digitalWrite(LCD_E, LOW);
  digitalWrite(LCD_DC, LOW);
  digitalWrite(LCD_PWR, HIGH);
  delay(30);
  
  for (int i = 0; i < 3; i++) {
    lcdWrite(0, 0x30, 10);
    delay(6);
  }
  
  lcdWrite(0, 0x3C, 10);
  delay(1);
  lcdWrite(0, 0x08, 50); // display off
  lcdWrite(0, 0x01, 2000); // display clear
  lcdWrite(0, 0x04, 50); // direction and shift
  lcdWrite(0, 0x0F, 50); // display off
  lcdWrite(1, 0x41, 50);
  lcdWrite(0, 0xC0, 50);
  lcdWrite(1, 0x31, 50);
  /*
  lcdWrite(0, 0x2C, 50); // 4-bit, 2-lines, 5x11 font
  lcdWrite(0, 0x04, 50); // display off
  lcdWrite(0, 0x01, 2000); // display clear
  lcdWrite(0, 0x04, 50); // direction and shift
  lcdWrite(0, 0x05, 50); // display on
  
  lcdWrite(1, 0x61, 50);
  lcdWrite(1, 0x63, 50);
  */
}

void lcdWrite(byte dc, byte v, int t) {
  digitalWrite(LCD_DC, dc != 0 ? HIGH : LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(LCD_BUS + i, v % 2 != 0 ? HIGH : LOW);
    v /= 2;
  }
  delayMicroseconds(1000);
  digitalWrite(LCD_E, HIGH);
  delayMicroseconds(1000);
  digitalWrite(LCD_E, LOW);
  delayMicroseconds(1000);
  delayMicroseconds(3000);
}

void writeHalf(byte v) {
  delayMicroseconds(1000);
  digitalWrite(LCD_E, HIGH);
  delayMicroseconds(1000);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LCD_BUS + i, v % 2 != 0 ? HIGH : LOW);
    v /= 2;
  }
  delayMicroseconds(1000);
  digitalWrite(LCD_E, LOW);
  delayMicroseconds(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

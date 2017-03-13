#define LCD_PWR 2
#define LCD_DC 3
#define LCD_E 4
#define LCD_BUS 5

long counter = 0;

void setup() {
  pinMode(LCD_PWR, OUTPUT);
  pinMode(LCD_DC, OUTPUT);
  pinMode(LCD_E, OUTPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(LCD_BUS + i, OUTPUT);
  }
  digitalWrite(LCD_E, LOW);
  digitalWrite(LCD_DC, LOW);
  digitalWrite(LCD_PWR, HIGH);
  delay(30);
  
  for (int i = 0; i < 3; i++) {
    writeHalf(0x3);
    delay(6);
  }

  writeHalf(0x2);
  delayMicroseconds(50);
  lcdOptions(false, true, false);
  lcdOnOff(false, false, false);
  lcdClear();
  lcdDirAndShift(true, false);
  lcdOnOff(true, false, false);
  lcdPuts("You are doing");
  lcdRowCol(1, 0);
  lcdPuts("nothing:");
}

void lcdOnOff(bool disp, bool cur, bool blnk) {
  lcdWrite(0, 0x08 | (disp ? 4 : 0) | (cur ? 2 : 0) | (blnk ? 1 : 0), 50);
}

void lcdOptions(bool fullBus, bool twoLines, bool smallFont) {
  lcdWrite(0, 0x20 | (fullBus ? 0x10 : 0) | (twoLines ? 8 : 0) | (smallFont ? 4 : 0), 50);
}

void lcdClear() {
  lcdWrite(0, 0x01, 2000);
}

void lcdHome() {
  lcdWrite(0, 0x02, 2000);
}

void lcdDirAndShift(bool dir, bool shift) {
  lcdWrite(0, 0x04 | (dir ? 2 : 0) | (shift ? 1 : 0), 50);
}

void lcdRowCol(byte row, byte col) {
  lcdWrite(0, 0x80 | (row << 6) | col, 50);
}

void lcdPutc(byte c) {
  lcdWrite(1, c, 50);
}

void lcdPuts(const char s[]) {
  for (int i = 0; s[i] != 0; s++) {
    lcdPutc(s[i]);
  }
}

void lcdWrite(byte dc, byte v, int t) {
  digitalWrite(LCD_DC, dc != 0 ? HIGH : LOW);
  writeHalf(v >> 4);
  writeHalf(v & 0xF);
  delayMicroseconds(t);
}

void writeHalf(byte v) {
  delayMicroseconds(1);
  digitalWrite(LCD_E, HIGH);
  for (int i = 0; i < 4; i++) {
    digitalWrite(LCD_BUS + i, v % 2 != 0 ? HIGH : LOW);
    v /= 2;
  }
  delayMicroseconds(1);
  digitalWrite(LCD_E, LOW);
  delayMicroseconds(1);
}

void loop() {
  delay(1000);
  char textBuf[16];
  counter += 1;
  itoa(counter, textBuf, 10);
  lcdRowCol(1, 9);
  lcdPuts(textBuf);
  lcdPutc('s');
}

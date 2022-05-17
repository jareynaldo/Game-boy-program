#include <LiquidCrystal.h>

// C++ code
//

byte slash[8] = { // setting custom character
  B00100,
  B01110,
  B11111,
  B01101,
  B00100,
  B11011,
  B01110,
  B01001,
}

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
 lcd.begin(16, 2);
 lcd.createChar(7, slash);
}

void loop() {
  lcd.print("Welcome to Arduino");
  delay(3000);
  lcd.clear();
  
  for( int i=0; i<=15; i++){
    lcd.setCursor(i,0);
    lcd.write(7);
    delay(1000);
    lcd.clear();
  }
  
  
  
  lcd.setCursor(2,1);
  lcd.print("how to LCD");
  delay(3000);
  
  lcd.clear();
  
  lcd.blink();
  delay(3000);
  lcd.setCursor(7,1);
  delay(3000);
  lcd.noBlink();
  
  lcd.cursor();// underscore cursor
  delay(3000);
  lcd.noCursor();
  
  lcd.clear();
  
  
  
  
  lcd.print("Hello, world!");
  delay(500);
  lcd.clear();
  delay(500);
  lcd.setCursor(5,1);
  lcd.print("it works!!");
  delay(500);
  lcd.clear();
}
// C++ code
//

#include "Keypad.h"
#include "LiquidCrystal.h"
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


byte hashtag[8] = { // setting custom character
  B01010,
  B01010,
  B11111,
  B01010,
  B01010,
  B11111,
  B01010,
  B01010
};


#define ROW   4
#define COL   
char key[ROW][COL] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
uint8_t row_line[ROW] = {7, 6, 5, 4};
uint8_t col_line[COL] = {3, 2, 1, 0};
Keypad keypad = Keypad( makeKeymap(key), row_line, col_line, ROW, COL );

int keepingCount =  0;
char hashtagValue = '#';
char key = keypad.getKey();

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // initialized the LCD as 16x2
  lcd.createChar(7, hashtag);
  
}



void loop() {
  
  
  startScreen();
  //start sequence
  
  if(key){
    
    Serial.print("*****");
    Serial.print(char(key));
    Serial.println("*****");


       if(key == hashtagValue ){
      lcd.print("Welcome to");
      lcd.setCursor(2, 1);
      lcd.print("Math Q's");

      }
  }
  
 
    
}

void startScreen(){
lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(2, 1);
  lcd.print("to the game     ");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("please press");
  lcd.setCursor(2, 1);
  lcd.write(7);
  lcd.setCursor(3, 1);
  lcd.print(" to start");
  delay(3000);
  lcd.clear();  
}
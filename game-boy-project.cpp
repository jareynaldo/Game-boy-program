#include <IRremote.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,7);
const int RECV_PIN = 2;
const int LED = 10;

IRrecv irrecv(RECV_PIN);
decode_results results;

int firstnum[5];
int secondnum[5];
int resultnum[5];
int score = 0;
volatile boolean selection[4] = {false,false,false,false};
String usernumber[5];
int usernumberint[5];
volatile int eachmodecount = 0;
volatile long int irval = 0;
volatile int times = 0;
volatile int samebuttonpressed = 0;
int currenttime = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(LED, OUTPUT);
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(RECV_PIN), detection, RISING);
  while(!selection[3])
  {
    gameIntro();
  }
}

void loop()
{
    if(!selection[0])
    {
      gameMode();
    }
    if(irval == 0xFD08F7)
    {
      irval = 0;
      selection[0] = true;
      if(!selection[1])
      {
        while(samebuttonpressed<2)
        {
          levelSelect();
        }
        selection[1] = true;        
      }
      else
      {
        irval = 0;
        selection[2] = true;
      }
    }
    if(selection[2] && eachmodecount < 5)
    {
      irval = 0;
      for(int i = 3; i>0; i--)
      {
        lcd.clear();
        lcd.setCursor(7,0);
        lcd.print(i);
        delay(1000);
      }
      lcd.setCursor(7,1);
      lcd.print("Go");
      delay(500);
      additionEasy();
      selection[2] = false;
      
    }
    if(!selection[2] && eachmodecount == 5)
    {
      delay(1000);
      roundResult();
      Serial.println("Over");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Your Score:");
      lcd.setCursor(13,0);
      lcd.print(score);
      lcd.setCursor(6,1);
      lcd.print("Over");
      selection[2] = true;
    }
}

void detection()
{
  while(irrecv.decode(&results))
  {
    selection[3] = true;
    irval = results.value;
    if(irval == 0xFD08F7 && !selection[1])
    {
      samebuttonpressed++;
    }
      if(irval == 0xFD30CF && selection[2])
      {
        usernumber[times].concat(0);
      }
      if(irval == 0xFD08F7 && selection[2])
      {
        usernumber[times].concat(1);
      }
      if(irval == 0xFD8877 && selection[2])
      {
        usernumber[times].concat(2);
      }
      if(irval == 0xFD48B7 && selection[2])
      {
        usernumber[times].concat(3);
      }
      if(irval == 0xFD28D7 && selection[2])
      {
        usernumber[times].concat(4);
      }
      if(irval == 0xFDA857 && selection[2])
      {
        usernumber[times].concat(5);
      }
      if(irval == 0xFD6897 && selection[2])
      {
        usernumber[times].concat(6);
      }
      if(irval == 0xFD18E7 && selection[2])
      {
        usernumber[times].concat(7);
      }
      if(irval == 0xFD9867 && selection[2])
      {
        usernumber[times].concat(8);
      }
      if(irval == 0xFD58A7 && selection[2])
      {
        usernumber[times].concat(9);
      }
      Serial.println(irval, HEX);
      Serial.println(usernumber[times]);
      lcd.setCursor(12,1);
      lcd.print(usernumber[times]);
      irrecv.resume();
  }
}
void gameIntro()
{
  lcd.clear();
  lcd.home();
  lcd.print(" Welcome to the");
  lcd.setCursor(0,1);
  lcd.print(" Math Problems");
  delay(2000);
  lcd.clear();
  lcd.home();
  lcd.print("  Solving Game");
  delay(2000);
  lcd.clear();
  lcd.home();
  lcd.print(" PRESS ANY KEY");
  lcd.setCursor(0,1);
  lcd.print("   TO START");
  delay(1000);
}
void gameMode()
{
  lcd.clear();
  lcd.home();
  lcd.print("1) Addition");
  lcd.setCursor(0,1);
  lcd.print("2) Subtraction");
  delay(1000);
  lcd.clear();
  lcd.home();
  lcd.print("3) Multiplication");
  lcd.setCursor(0,1);
  lcd.print("4) Division");
  delay(1000);
}
void levelSelect()
{
  lcd.clear();
  lcd.home();
  lcd.print("1) Easy");
  lcd.setCursor(0,1);
  lcd.print("2) Hard");
  delay(1000);
  lcd.clear();
  lcd.home();
  lcd.print("3) Advanced");
  lcd.setCursor(0,1);
  lcd.print("4) Genius");
  delay(1000);
}
void additionEasy()
{
  for(times = 0; times < 5; times++)
  {
    eachmodecount++;
    firstnum[times]=random(1,10);
    secondnum[times]= random(1,10);
    resultnum[times] = firstnum[times] + secondnum[times];
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Q#:");
    lcd.setCursor(3,0);
    lcd.print(eachmodecount);
    lcd.setCursor(6,0);
    lcd.print(firstnum[times]);
    lcd.setCursor(8,0);
    lcd.print("+");
    lcd.setCursor(10,0);
    lcd.print(secondnum[times]);
    lcd.setCursor(12,0);
    lcd.print("=");
    lcd.setCursor(14,0);
    //lcd.print(resultnum[times]);   //uncomment this to see the result directly in the LCD
    lcd.setCursor(0,1);
    lcd.print("You Typed:");
    delay(10000);
  }
}
void roundResult()
{
  usernumberint[0] = usernumber[0].toInt();
  usernumberint[1] = usernumber[1].toInt();
  usernumberint[2] = usernumber[2].toInt();
  usernumberint[3] = usernumber[3].toInt();
  usernumberint[4] = usernumber[4].toInt();
  
  if(usernumberint[0] == resultnum[0])
  {
    score++;
  }
  if(usernumberint[1] == resultnum[1])
  {
    score++;
  }
  if(usernumberint[2] == resultnum[2])
  {
    score++;
  }
  if(usernumberint[3] == resultnum[3])
  {
    score++;
  }
  if(usernumberint[4] == resultnum[4])
  {
    score++;
  }
  if(usernumberint[0] != resultnum[0])
  {
    score--;
  }
  if(usernumberint[1] != resultnum[1])
  {
    score--;
  }
  if(usernumberint[2] != resultnum[2])
  {
    score--;
  }
  if(usernumberint[3] != resultnum[3])
  {
    score--;
  }
  if(usernumberint[4] != resultnum[4])
  {
    score--;
  }
}

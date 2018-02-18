#include <LiquidCrystal.h>
#define ACTIVE LOW
#define INACTIVE HIGH

byte i, j;
byte c[4] = {6, 7, 8, 9}, r[4] = {10, 11, 12, 13};    //these are pins from hex keypad, which is to be changed, such that they will not conflict with lcd pins
byte code;
byte cCaptured, rCaptured;
byte userInput[5], userIpCount, userCode[3], cardInput[12];
int t;

/*
  The circuit for LCD:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
*/

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  for (i = 0; i < 4; i++)
  {
    pinMode(c[i], OUTPUT);
    pinMode(r[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  lcd.begin(16, 2);
  userIpCount = 0;
  lcd.clear();
  lcd.print("Enter Book-Code:");
  lcd.setCursor(5, 1);
  lcd.blink();
}

void loop()
{
  rCaptured = 4;
  cCaptured = 4;
  for (i = 0; i < 4; i++)
  {
    for (byte k = 0; k < 4; k++)
      if (k == i)
        digitalWrite(c[k], ACTIVE);
      else
        digitalWrite(c[k], INACTIVE);
    for (j = 0; j < 4; j++)
      if (digitalRead(r[j]) == ACTIVE)
      {
        rCaptured = j;
        cCaptured = i;
      }
  }
  if ((cCaptured * 4 + rCaptured) < 16)
  {
    userInput[userIpCount++] = cCaptured * 4 + rCaptured;
    if (userIpCount == 5)
    {
      userIpCount = 0;
      userCode[0] = userInput[0];
      userCode[1] = 16 * userInput[1] + userInput[2];
      userCode[2] = 16 * userInput[3] + userInput[4];
      delay(500);
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(4, 0);
      lcd.print("Searching");
    }
  }
  if (userIpCount == 1)
  {
    lcd.clear();
    lcd.print("Enter Book-Code:");
    lcd.setCursor(5, 1);
    lcd.blink();
  }

  if (!userIpCount)
  {
    //rest of the code
    if (Serial.available())
    {
      Serial.readBytes(cardInput, 12);
      cardInput[8] %= 16;
      for (i = 0; i < 3; i++)
      {
        if (cardInput[i + 8] != userCode[i])
          break;
      }
      if (i == 3)
      {
        lcd.setCursor(2, 1);
        lcd.print("            ");
        lcd.setCursor(2, 1);
        lcd.print("Book found!");
      }
      else
      {
        lcd.setCursor(5, 1);
        lcd.print("       ");
        lcd.setCursor(5, 1);
        for (j = 0; j < byte(millis() % 6000); j++)
          lcd.write('-');
      }
    }
  }
}

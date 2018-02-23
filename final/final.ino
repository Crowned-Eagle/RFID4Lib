#include <Keypad.h>
#include <Key.h>
#include <LiquidCrystal.h>

byte i, c[4] = {14, 15, 16, 17}, r[4] = {18, 19, 20, 21};
byte userInput[5], userIpCount, userCode[3], cardInput[12];
boolean searchOn;

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
byte keyMap[4][4] = {{1, 2, 3, 10},
  {4, 5, 6, 11},
  {7, 8, 9, 12},
  {14, 0, 15, 13}
};
//Keypad constructor ==> (makeKeymap(keys array), row array, column array,no. of rows, no. of columns)
Keypad  keypad = Keypad(makeKeymap(keyMap), r, c, 4, 4);

void setup()
{
  Serial.begin(9600);
  keypad.addEventListener(keypadEvent);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Enter Book-Code:");
  lcd.setCursor(5, 1);
  lcd.blink();
  searchOn = false;
}

void loop()
{
  if (searchOn)
  {
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
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Book found!");
      }
    }
  }
}

void keypadEvent(KeypadEvent key)
{
  if (!userIpCount)
  {
    searchOn = false;
    lcd.clear();
    lcd.print("Enter Book-Code:");
    lcd.setCursor(5, 1);
    lcd.blink();
  }
  userInput[userIpCount++] = key;
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
    searchOn = true;
  }
}

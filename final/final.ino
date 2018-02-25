#include <Keypad.h>
#include <Key.h>
#include <LiquidCrystal.h>

byte i, r[4] = {14, 15, 16, 17}, c[4] = {18, 19, 20, 21};
char userInput[5], userIpCount, cardInput[12];
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
char keyMap[4][4] = {{'1', ' 2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'E', '0', 'F', 'D'}
};

//Keypad constructor ==> (makeKeymap(keys array), row array, column array,no. of rows, no. of columns)
Keypad  keypad = Keypad(makeKeymap(keyMap), r, c, 4, 4);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Enter Book-Code:");
  lcd.setCursor(5, 1);
  lcd.blink();
  searchOn = false;
}

void loop()
{
  char key;
  key = keypad.getKey();
  if (key)
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
    lcd.print(key);
  }
  if (userIpCount == 5)
  {
    userIpCount = 0;
    delay(500);
    lcd.clear();
    lcd.noCursor();
    lcd.setCursor(4, 0);
    lcd.print("Searching");
    searchOn = true;
  }
  if (searchOn)
  {
    if (Serial.available())
    {
      Serial.readBytes(cardInput, 12);
      Serial.print("card id - ");
      Serial.println(cardInput);
      for (i = 0; i < 5; i++)
      {
        if (cardInput[i + 6] != userInput[i])
          break;
      }
      if (i == 5)
      {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Book found!");
      }
    }
  }
  else
    while (Serial.available())
      Serial.read();
}

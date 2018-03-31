/*
 * code for first demo after soldering
 */


#include <Keypad.h>
#include <Key.h>
#include <LiquidCrystal.h>
#define buzzerPin 13

byte i, r[4] = {2, 3, 4, 5}, c[4] = {6, 7, 8, 9};
char userInput[5], userIpCount, cardInput[12];
boolean searchOn, matched;

/*
  The circuit for LCD:
   LCD RS pin to digital pin A0
   LCD Enable pin to digital pin A1
   LCD D4 pin to digital pin A2
   LCD D5 pin to digital pin A3
   LCD D6 pin to digital pin A4
   LCD D7 pin to digital pin A5
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
*/

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
char keyMap[4][4] = {{'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'E', '0', 'F', 'D'}
};

//Keypad constructor ==> (makeKeymap(keys array), row array, column array,no. of rows, no. of columns)
Keypad  keypad = Keypad(makeKeymap(keyMap), r, c, 4, 4);

void setup()
{
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.println("  A Product by  ");
  lcd.setCursor(0, 1);
  lcd.print("    AGJP Inc.");
  lcd.noBlink();
  delay(2000);
  lcd.clear();
  lcd.print("Enter Code:");
  lcd.setCursor(5, 1);
  lcd.blink();
  searchOn = false;
  matched = false;
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
      digitalWrite(buzzerPin, LOW);
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
    lcd.setCursor(2, 0);
    lcd.print("Searching ...");
    searchOn = true;
  }
  if (searchOn)
  {
    //animateSearch();
    if (Serial.available())
    {
      Serial.readBytes(cardInput, 12);
      for (i = 0; i < 5; i++)
      {
        if (cardInput[i + 6] != userInput[i])
          break;
      }
      if (i == 5)
      {
        matched = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(" Book found!!");
        lcd.setCursor(0, 1);
        lcd.print("Press, any key.");
        digitalWrite(buzzerPin, HIGH);
        delay(1200);
        digitalWrite(buzzerPin, LOW);        
      }
    }
  }
  else
    while (Serial.available())
      Serial.read();
}

/*
  void animateSearch()
  {
  byte pos;
  lcd.setCursor(0, 1);
  pos = byte(millis() / 1000) / 32;
  if (pos / 16)
    pos = 31 - pos;
  for (i = 0; i < pos; i++)
    lcd.print(" ");
  lcd.print("-");
  for (++i; i < 16; i++)
    lcd.print(" ");
  }
*/

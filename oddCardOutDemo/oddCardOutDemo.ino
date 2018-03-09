#include<LiquidCrystal.h>

int i = 0;
char input[12];

/*
 * only for demonstration purpose
 * actual logic will differ from current logic
 */

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.println("  A Product by  ");
  lcd.setCursor(0, 1);
  lcd.print("    AGJP Inc.");
  lcd.noBlink();
}

void loop()
{
  while (!Serial.available());

  Serial.readBytes(input, 12);
  lcd.clear();
  switch (input[6])
  {
    case '1':
      lcd.print("  Valid Book.");
      lcd.setCursor(0, 1);
      lcd.print("Place in row: 1");
      break;
    case '2':
      lcd.print(" Valid Book.");
      lcd.setCursor(0, 1);
      lcd.print("Place in row: 2");
      break;
    case 'F':
      lcd.print(" Invalid Book!!");
      //  lcd.setCursor(0,1);
      //  lcd.print("");
      break;
    default :
      lcd.print(" Valid Book.");
      lcd.setCursor(0, 1);
      lcd.print("Place in row: 3");
      break;
  }
}

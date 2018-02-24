#include <Keypad.h>
#include <Key.h>

byte i, r[4] = {14, 15, 16, 17}, c[4] = {18, 19, 20, 21};
//byte userInput[5], userIpCount, userCode[3], cardInput[12];

char keyMap[4][4] = {{'1',' 2', '3', 'A'},
  {'4','5', '6', 'B'},
  {'7','8','9', 'C'},
  {'E', '0', 'F', 'D'}
};
//Keypad constructor ==> (makeKeymap(keys array), row array, column array,no. of rows, no. of columns)
Keypad  keypad = Keypad(makeKeymap(keyMap), r, c, 4, 4);

void setup()
{
  Serial.begin(9600);
  //keypad.addEventListener(keypadEvent);
}

void loop()
{
 char key=keypad.getKey();
 if(key)
 Serial.println(key);
}

/*void keypadEvent(KeypadEvent key)
{
  Serial.println("key pressed");
  if (key < 10)
    Serial.print('0' + key);
  else
    Serial.print('A' + key);
}*/

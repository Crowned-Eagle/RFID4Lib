int count = 0;                                          // count = 0
char cardInput[12];                                         // character array of size 12
char userInput[5];
//char code2match[12] = {'1', '1', '0', '0', '7', '7', '9', 'B', 'D', '7', '2', 'A'};
//boolean flag = 0;                                       // flag =0
void setup()
{
  Serial.begin(9600);                                  // begin serial port with baud rate 9600bps

}
void loop()
{
  Serial.flush();
  //while (!Serial.available());
  if (Serial.available() == 12)
  {
    Serial.readBytes(cardInput,12);

    Serial.print("Card ID - ");
    Serial.println(cardInput);      // Print RFID tag number
    for (count = 0; count < 5; count++)
    {
      if (cardInput[count + 7] != userInput[count])
        break;
    }
    if (count == 5)
      Serial.println("Yes, we got it!");

  }
  else
    Serial.println(Serial.available());

  if (Serial.available() == 5)
  {
    Serial.readBytes(userInput, 5);
    Serial.print("User Input - ");
    Serial.println(userInput);
  }
  delayMicroseconds(500);

}

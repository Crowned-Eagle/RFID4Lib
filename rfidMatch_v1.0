int count = 0;                                          // count = 0
char input[12];                                         // character array of size 12
char code2match[12] = {'1', '1', '0', '0', '7', '7', '9', 'B', 'D', '7', '2', 'A'};
boolean flag = 0;                                       // flag =0
void setup()
{
  Serial.begin(9600);                                  // begin serial port with baud rate 9600bps

}
void loop()
{
  if (Serial.available())
  {
    Serial.readBytes(input, 12);
    delay(1);

    Serial.print("Card ID - ");
    Serial.println(input);      // Print RFID tag number

    for (count = 0; count < 12; count++)
    {
      if (input[count] != code2match[count])
        break;
    }
    if (count == 12)
      Serial.println("Yes, we got it!");
    //digitalWrite(13, HIGH);


  }
}

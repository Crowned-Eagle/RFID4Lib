int count = 0;                                    // count = 0
char userInput[5];

void setup()
{
  //delay(1000);
  Serial.begin(9600);                            // begin serial port with baud rate 9600bps

}
void loop()
{
  if (Serial.available() < 5)
  {
    Serial.read();
  }
  else if (Serial.available() >= 5)
  {
    for (int i = 0; i < 5; i++)
    {
      userInput[i] = Serial.read();
    }
    
    while (Serial.available() > 0)
    {
      Serial.read();
    }
    
    Serial.print("User Input - ");
    Serial.println(userInput);
  }

  delay(100);
}

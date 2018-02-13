int count = 0;                                          // count = 0
char userInput[5];
//char code2match[12] = {'1', '1', '0', '0', '7', '7', '9', 'B', 'D', '7', '2', 'A'};
void setup()
{
  Serial.begin(9600);                            // begin serial port with baud rate 9600bps

}
void loop()
{
    if (Serial.available() > 5)
    {
       Serial.read();
    }
    
    else if (Serial.available() < 5)
    {
    	Serial.read();
    }
    
    else
    {
       Serial.readBytes(userInput, 5);
       Serial.print("User Input - ");
       Serial.println(userInput);
    }

  delay(1000);
}
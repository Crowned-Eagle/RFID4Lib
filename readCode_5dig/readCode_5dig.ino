char input[12];
char code[5];
void setup()
{
  Serial.begin(9600);

}
void loop()
{
  if (Serial.available())
  {
    Serial.readBytes(input, 12);
    for (byte j = 0; j < 5; j++)
      code[j] = input[j + 6];

    Serial.print("Code = ");
    Serial.println(code);
  }
}

byte i, j;
byte c[4] = {6, 7, 8, 9}, r[4] = {10, 11, 12, 13};
byte code;
byte cCaptured, rCaptured;
byte userInput[5], userIpCount;

#define ACTIVE LOW
#define INACTIVE HIGH

void setup()
{
  for (i = 0; i < 4; i++)
  {
    pinMode(c[i], OUTPUT);
    pinMode(r[i], INPUT_PULLUP);
  }
  Serial.begin(9600);
  userIpCount = 0;
}

void loop()
{
  rCaptured = 4;
  cCaptured = 4;
  for (i = 0; i < 4; i++)
  {
    for (byte k = 0; k < 4; k++)
      if (k == i)
        digitalWrite(c[k], ACTIVE);
      else
        digitalWrite(c[k], INACTIVE);
    for (j = 0; j < 4; j++)
      if (digitalRead(r[j]) == ACTIVE)
      {
        rCaptured = j;
        cCaptured = i;
      }
  }
  if ((cCaptured * 4 + rCaptured) < 16)
  {
    userInput[userIpCount++] = cCaptured * 4 + rCaptured;
    if (userIpCount == 5)
      userIpCount = 0;
  }

  if (!userIpCount)
  {
    //rest of the code
  }
}

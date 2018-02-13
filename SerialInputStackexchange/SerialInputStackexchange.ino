char userInput[6];  // Holds 5 user characters, plus null terminator.
// [...]

void setup()
{
  userInput[0] = '\0';  // Initialize string to empty
  Serial.begin(9600);
  //  [...]
}

void loop()
{
  uint8_t processInput = 0;   // Set to 1 if we have complete entry
  while (Serial.available() > 0)
  {
    char input = Serial.read();
    if (input == '\r' || input == '\n')
    {
      // Have received a terminating character,
      // Flush the rest of the buffer
      while (Serial.available())
      {
        Serial.read();
      }

      // Here, do what you need to do with the input

      for (int i = 0; i < 5; i++)
      {
        userInput[i] = Serial.read();
      }
      processInput = 1;

    }
    else
    {
      int s_len = strnlen(userInput, 5); // Get current length of userInput
      if (s_len < 5)
      {
        userInput[s_len++] = input;      // Append character
        userInput[s_len] = '\0';         // Null-terminate string
      }
      else
      {
        // User has entered more than 5 characters and no terminating
        // character; here is where you can decide to clear the userInput
        // and start over, or just drop the first character and care
        // about the most recent 5, etc. Here, we will clear the input
        // and start over; The 6th character is dropped/ignored and
        // user input starts again. It is as though the 6th character
        // entered is like pressing Enter, but it does not process
        // the incoming data, beacuse 6 characters is an invalid input.
        userInput[0] = '\0';
        processInput = 0;
      }
    }
  }

  if (processInput)
  {
    Serial.print("User input - ");
    Serial.println(userInput);

    if (strnlen(userInput, 5) == 5)
    {
      // Do something **here** with the input string!!
    }
    else
    {
      // Invalid input
      Serial.println("Error: invalid data");
    }
  }
  //  [...]
}

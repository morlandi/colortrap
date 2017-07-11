// Adapted from:
// http://allaboutee.com/2014/12/27/esp8266-arduino-code-and-circuit/

#include <SoftwareSerial.h>

// make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
SoftwareSerial esp8266(2,3);

void setup()
{
    Serial.begin(9600);
    esp8266.begin(9600); // your esp's baud rate might be different

    Serial.println("esp8266 initialized at 9600 baudrate and waiting for AT commands ...");
}


void echo_received_chars(SoftwareSerial& esp_obj) 
{
    while( esp_obj.available() )
    {
      // The esp has data so display its output to the serial window
      char c = esp_obj.read(); // read the next character.

      Serial.write(c);
      
      /*
      if (c == 13) {
        Serial.write("[CR]");
      }
      else if (c == 10) {
        Serial.write("[LF]"); 
      }
      else {
        Serial.write(c);
      }
      */
    }
}

String command = "";

void loop()
{
    echo_received_chars(esp8266);

    while( Serial.available() )
    {
        char c = (char)Serial.read();
        command += c;

        if (c == 13) // CR ?
        {
           esp8266.println(command);
           //Serial.println(command + "[CR]");
           command = "";
        }
    }

  /*
  if(Serial.available())
  {
    // the following delay is required because otherwise the arduino will read
    // the first letter of the command but not the rest
    // In other words without the delay if you use AT+RST, for example,
    // the Arduino will read the letter A send it, then read the rest and send it
    // but we want to send everything at the same time.
    //delay(1000);

    String command = "";
    while(Serial.available()) // read the command character by character
    {
        // read one character
        command += (char)Serial.read();
        //delay(1);
    }
    Serial.println(command);
    
    //esp8266.println(command); // send the read character to the esp8266

    while(Serial.available()) // read the command character by character
    {
        // read one character
        int i = Serial.read();
        Serial.println(i);
    }
    //Serial.println(command);
    
  }
    */
}

// Adapted from:
// http://allaboutee.com/2014/12/27/esp8266-arduino-code-and-circuit/

#include <SoftwareSerial.h>

// make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
SoftwareSerial esp8266(2,3);

String ssid = "brainstorm2";
String password = "********";

// AT+CWJAP_CUR="brainstorm2","*********"
String wifi_connection_string = "AT+CWJAP_CUR=\"" + ssid + "\",\"" + password + "\"";


void echo_received_chars(SoftwareSerial& esp_obj) 
{
    while( esp_obj.available() )
    {
      // The esp has data so display its output to the serial window
      char c = esp_obj.read(); // read the next character.
      Serial.write(c);
    }
}

void wifi_connect() 
{
    Serial.println("Establishing wifi connection ...");

    esp8266.println("AT+RST");
    delay(3000);
  
    esp8266.println("AT+CWMODE_CUR=1");
    delay(3000);
    echo_received_chars(esp8266);

    esp8266.println(wifi_connection_string);
    delay(3000);
    echo_received_chars(esp8266);
}

void setup()
{
    Serial.begin(9600);
    esp8266.begin(9600); // your esp's baud rate might be different

    wifi_connect();

    Serial.println("Esp8266 initialized at 9600 baudrate and waiting for AT commands ...");
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
           command = "";
        }
    }

}


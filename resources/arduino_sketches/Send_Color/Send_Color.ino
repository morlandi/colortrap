
#include <SoftwareSerial.h>
#include <Wire.h>
#include <GroveColorSensor.h>
// make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
SoftwareSerial esp8266(2,3);

//String SSID = "brainstorm1";
String SSID = "WIND-WiFi-5732";
String PASSWORD = "********";
String HOST = "colortrap.brainstorm.it";
String PORT = "80";
//String HOST = "192.168.98.25";
//String PORT = "8000";



// AT+CWJAP_CUR="brainstorm2","*********"
String wifi_connection_string = "AT+CWJAP_DEF=\"" + SSID + "\",\"" + PASSWORD + "\"";

/////////////////////////////////////////////////////////////////////////////////////
// Helpers

void echo_received_chars(SoftwareSerial& esp_obj)
{
    while( esp_obj.available() )
    {
      // The esp has data so display its output to the serial window
      char c = esp_obj.read(); // read the next character.
      Serial.write(c);
    }
}

void trace(char* message)
{
   Serial.println(message);
}


bool send_request(SoftwareSerial& device, char* szRequest, String& response, long timeout, char* szSuccessMarker, char* szFailureMarker, bool verbose)
{
    bool result = false;

    // Clear response
    response = "";

    // Sent request to remote device
    if (verbose) {
        trace("Sending request:");
        trace(szRequest);
    }
    device.println(szRequest);

    // wait for complete response
    int n = 1000;
    long dt = timeout / n;
    for (int i=0; i<n; i++)
    {
        // Receive new chars from remote device, if any,
        // and append to 'response' buffer
          bool new_chars_received = false;

            while (device.available())
            {
                char ch = device.read();
                response += ch;
                //trace(response.c_str());
                new_chars_received = true;
            }

          // Check for complete response, and in case return either true (for success)
          // or false (for error)
          if (new_chars_received)
          {
            if (szSuccessMarker && strstr(response.c_str(), szSuccessMarker)) {
              result = true;
              break;
            }
            if (szFailureMarker && strstr(response.c_str(), szFailureMarker)) {
              result = false;
              break;
            }
          }

          // Otherwise, keep on receiving response

        delay(dt);
    }

    // Fail for timeout elapsed
    if (verbose)
    {
        trace(result ? "SUCCESS" : "FAILURE");
        trace("Response:");
        trace(response.c_str());
    }
    return result;
}

// end of Helpers
/////////////////////////////////////////////////////////////////////////////////////

bool wifi_connect()
{
    Serial.println("Establishing wifi connection ...");

    String response;
    bool verbose = true;

    send_request(esp8266, "AT+RST", response, 3000, "\r\nOK\r\n", "\r\nERROR\r\n", verbose);
    delay(10000);

    send_request(esp8266, "AT+CWMODE_CUR=1", response, 3000, "\r\nOK\r\n", "\r\nERROR\r\n", verbose);

    return send_request(esp8266, wifi_connection_string.c_str(), response, 10000, "\r\nOK\r\n", "\r\nERROR\r\n", verbose);

}

bool http_post(SoftwareSerial& device, char* text)
{
    String request = "AT+CIPSTART=\"TCP\",\"" + HOST + "\"," + PORT;
    String response;
    bool verbose = true;

    send_request(esp8266, request.c_str(), response, 10000, "\r\nOK\r\n", "\r\nERROR\r\n", verbose);

    String str_value = text;
    int length = 6 + str_value.length();
    request = "POST /samples/ HTTP/1.0\r\nHost: " + HOST + "\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";
    request += String(length);
    request += "\r\n\r\nvalue=";
    request += str_value;


    trace("Sending: ");
    trace(request.c_str());

    device.print("AT+CIPSEND=");
    device.println(request.length());
    delay(500);
    device.print(request);

    trace(request.c_str());

    send_request(esp8266, "AT+CIPCLOSE", response, 10000, "\r\nOK\r\n", "\r\nERROR\r\n", verbose);
}

/////////////////////////////////////////////////////////////////////////////////////
int pushButton = 12;
int ledPin = 13;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    esp8266.begin(9600); // your esp's baud rate might be different


    pinMode(pushButton, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    digitalWrite(ledPin, HIGH);
    unsigned long t0 = millis();
    bool connected = wifi_connect();
    unsigned long t1 = millis();
    Serial.println("elapsed time [s]:");
    Serial.println((t1 - t0)/1000.0);
    Serial.println(connected ? "Esp8266 connected at 9600 baudrate and waiting for AT commands ..." : "Connection failure");

    blink(connected ? 10 : 2);
}

void blink(int n)
{
    int i = 0;
    for (i=0; i<n; i++) {
        digitalWrite(ledPin, HIGH);
        delay(200);
        digitalWrite(ledPin, LOW);
        delay(200);
    }
}


int i = 0;

void loop()
{
    int buttonState = digitalRead(pushButton);

    // Button press ?
    if (buttonState == LOW) {
        blink(1);
        int r, g, b;
        if (read_color(r,g,b)) {
          blink(1);
          char buffer[16];
          sprintf(buffer, "#%02x%02x%02x", r, g, b);
          http_post(esp8266, buffer);
          blink(5);
        }
        else {
          blink(2);
        }
    }
}

bool read_color(int &red, int &green, int &blue)
{
    GroveColorSensor colorSensor;
    colorSensor.ledStatus = 1;

    colorSensor.readRGB(&red, &green, &blue);       //Read RGB values to variables.
    delay(300);
    Serial.print("The RGB value are: RGB( ");
    Serial.print(red,DEC);
    Serial.print(", ");
    Serial.print(green,DEC);
    Serial.print(", ");
    Serial.print(blue,DEC);
    Serial.println(" )");
    colorSensor.clearInterrupt();

    return true;
}

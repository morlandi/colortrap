
#include <string.h>

void setup() {                
    Serial.begin(9600);
}

void trace(char* message)
{
   Serial.println(message);
}


bool send_command(char* szCommand, char* szSuccessMarker, char* szFailureMarker, long timeout, String& response)
{
    // Clear response
    response = "";
  
    // Sent command to remote device
    Serial.println(szCommand);

    // wait for complete response
    int n = 100;
    long dt = timeout / n;
    for (int i=0; i<n; i++) 
    {
        // Receive new chars from remote device, if any, 
        // and append to 'response' buffer
          bool new_chars_received = false;
            while (Serial.available()) 
            {
                char ch = Serial.read();
                response += ch;
                trace(response.c_str());
                new_chars_received = true;
            }

          // Check for complete response, and in case return either true (for success)
          // or false (for error)
          if (new_chars_received) 
          {
            if (strstr(response.c_str(), szSuccessMarker)) {
              return true;
            }
            if (strstr(response.c_str(), szFailureMarker)) {
              return false;
            }
          }

          // Otherwise, keep on receiving response

        delay(dt);
    }

    // Fail for timeout elapsed
    return false;
}



void loop() 
{
    String response;
    char* request = "prova";
  
    trace("<-- send new command");
    if (send_command(request, "OK", "ERROR", 10000, response))
    {
        trace("--> success");
    }
      else
    {
        trace("--> failure");
    }
    trace("Response was:");
    trace(response.c_str());
    
    delay(1000);
}

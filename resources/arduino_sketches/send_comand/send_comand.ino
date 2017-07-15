

void setup() {                
    Serial.begin(9600);
}

void trace(char* message)
{
   Serial.println(message);
}


bool send_command(char* szCommand, char* szSuccessMarker, char* szFailureMarker, long timeout)
{
    String response;

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
            if (strstr(szSuccessMarker, response.c_str())) {
              return true;
            }
            if (strstr(szFailureMarker, response.c_str())) {
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
    trace("<-- send new command");
    if (send_command("prova", "OK", "ERROR", 10000))
    {
            trace("--> success");
    }
      else
    {
            trace("--> failure");
    }
    
    delay(1000);
}

#include <ESP32Servo.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "AIS 8/3_2.4G";
const char* password = "0863925696";
Servo myservo;  //ประกาศตัวแปรแทน Servo
int pos = 90;   // variable to store the servo position
String payload = "";
void setup() {
  Serial.begin(9600);
  myservo.attach(12);  // attaches the servo on pin 9 to the servo object// attaches the servo on pin 6 to the servo object
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {  //Check the current connection status

    HTTPClient http;

    http.begin("https://cod9000.pspgun.com/");  //Specify the URL
    int httpCode = http.GET();                  //Make the request

    if (httpCode > 0) {  //Check for the returning code
      payload = http.getString();
      Serial.println(payload);
      if (payload.charAt(1) == 'C') {
        pos = 90;
        myservo.write(90);
      }
      if (payload.charAt(1) == 'R') {
        for (pos; pos <= 180; pos += 1)  // goes from 0 degrees to 90 degrees in steps of 1 degree
        {
          myservo.write(pos);
          http.GET();
          payload = http.getString();
          if (payload.charAt(1) == 'S')
            break;
        }
      }
      if (payload.charAt(1) == 'L') {
        {
          for (pos; pos >= 0; pos -= 1)  // goes from 0 degrees to 90 degrees in steps of 1 degree
          {
            // payload = http.getString();
            myservo.write(pos);
            http.GET();
            payload = http.getString();
            if (payload.charAt(1) == 'S')
              break;
            delay(25);
          }
        }
      }
    }

    else {
      Serial.println("Error on HTTP request");
    }  //Free the resources
  }
}
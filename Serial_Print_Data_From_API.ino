#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // http web access library
#include <ArduinoJson.h>        // JSON 5.10.0 decoding library
 
// set Wi-Fi SSID and password
const char *ssid     = "SSID";///////////////////////////////////////ADD/////////////////////////////////////////
const char *password = "Password";//////////////////////////////////////ADD////////////////////////////////////////
 
// set location and API key
String Location = "Chandigarh, IN";;////////////Sample//////////////////////////ADD//NEW//Location////////////////////////////////////
String API_Key  = "API Key from OpenWeather";//////////////////////////////////////ADD////////////////////////////////////////
 
void setup(void)
{
  Serial.begin(9600);
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  Serial.print("Connecting.");
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
  delay(1000);
 
}
 
void loop()
{
  if (WiFi.status() == WL_CONNECTED)  //Check WiFi connection status
  {
    HTTPClient http;  //Declare an object of class HTTPClient
 
    // specify request destination
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key);  // !!
    Serial.println("http://api.openweathermap.org/data/2.5/weather?q=" + Location + "&APPID=" + API_Key);  
    int httpCode = http.GET();  // send the request
    Serial.println(httpCode);
    if (httpCode > 0)  // check the returning code
    {
      String payload = http.getString();   //Get the request response payload
 
      DynamicJsonBuffer jsonBuffer(512);
 
      // Parse JSON object
      JsonObject& root = jsonBuffer.parseObject(payload);
      if (!root.success()) {
        Serial.println(F("Parsing JSON failed!"));
        return;
      }
 
      float temp = (float)(root["main"]["temp"]) - 273.15;        // get temperature in °C from kelvin
     
      // print data
      Serial.printf("Temperature = %.2f°C\r\n", temp);

    }
 
    http.end();   //Close connection
 
  }
 
  delay(120000);   // wait 2 minute for next data
 
}
// End of code.

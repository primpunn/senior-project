#include <WiFi.h>
 
const char* ssid = "primpunn.p";
const char* password =  "Hpsb_8741";
 
const uint16_t port = 8093;
const char * host = "172.20.10.5";

//long s = 4;
 
void setup()
{
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP()); 
 
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
    client.print("Hello from ESP32!");
    //client.print(s);
    Serial.println("Disconnecting...");
    client.stop();
 
    delay(10000);
}

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

byte ledPin = 2;
char ssid[] = "paya1";           // SSID of your home WiFi
char pass[] = "billu12345";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192, 168, 29, 83);       // the fix IP address of the server
WiFiClient client;
//WiFiServer server(80);

void setup() {
    Serial.begin(115200);               // only for debug
    WiFi.begin(ssid, pass);             // connects to the WiFi router
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    /*  Serial.println("Connected to wifi");
      Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
      Serial.print("IP: ");     Serial.println(WiFi.localIP());
      Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
      Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
      Serial.print("SSID: "); Serial.println(WiFi.SSID());
      Serial.print("Signal: "); Serial.println(WiFi.RSSI());*/
    pinMode(ledPin, OUTPUT);
    Wire.begin(D1, D2);

}

void loop() {
    client.connect(server, 80);   // Connection to the server
    digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
    //Serial.println(".");
    client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
    String answer = client.readStringUntil('\r');   // receives the answer from the sever
    //Serial.println("from server: " + answer);
    Serial.println(answer);
    
    int val = answer.toInt();

    byte buffer[10];
    buffer[0] = lowByte(val);
    buffer[1] = highByte(val);
    
    Wire.beginTransmission(8);
    Wire.write(buffer, 2);
    Wire.endTransmission();

    client.flush();
    digitalWrite(ledPin, HIGH);
    //delay(100);                  // client will trigger the communication after two seconds
}
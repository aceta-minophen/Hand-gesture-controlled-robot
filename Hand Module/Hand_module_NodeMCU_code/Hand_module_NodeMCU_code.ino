#include <SPI.h>                             //Library for SPI 
#include <ESP8266WiFi.h>


int x;

byte ledPin = 2;
char ssid[] = "paya1";
char pass[] = "billu12345";
WiFiServer server(80);

IPAddress ip(192, 168, 29, 83);            // IP address of the server
IPAddress gateway(192, 168, 29, 1);           // gateway of your network
IPAddress subnet(255, 255, 255, 0);          // subnet mask of your network


void setup(void) {
    Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200 

    pinMode(D1, INPUT);

    SPI.begin();                            //Begins the SPI commnuication
    SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
    digitalWrite(SS, HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)

    WiFi.config(ip, gateway, subnet);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
    pinMode(ledPin, OUTPUT);
}

void loop(void)
{
    int Mastersend;
    float Mastereceive;

    Mastersend = x;
    Mastereceive = SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave

    String values = String(Mastereceive, 2);
    //Serial.println(Mastereceive);
    delay(50);

    if (Mastereceive >= 0) {
        digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
        digitalWrite(LED_BUILTIN, HIGH);
    }

    Serial.println(values);

    //delay(100);

    WiFiClient client = server.available();
    if (client) {
        if (client.connected()) {
            digitalWrite(ledPin, LOW);
            Serial.println(".");
            String request = client.readStringUntil('\r');
            //Serial.print("From client: ");
            //Serial.print(request);
            client.flush();
            //client.println("Hi client! No, I am listening.\r");
            client.println(values);
            /*if (button == LOW) {
                int a = 10000;
                client.println(a);
                Serial.println(a);
            }*/
            digitalWrite(ledPin, HIGH);
        }
        client.stop();
    }
}
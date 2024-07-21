#define BLYNK_TEMPLATE_ID "TMPL6I8OIU2lY"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "d3ztTRx3_vreGIWozrytn0Fz0isc1Gcx"

#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

String URL = "http://ipaddress/fuelfusion/test_data.php";
const char* ssid = "namawifi";
const char* password = "passwordwifi";
double volume = 0.0;

const int relayPin = D2; // Define the digital pin for the relay

BLYNK_WRITE(V1) {
  int relayState = param.asInt(); // Get the value from the Blynk app (0 or 1)
  digitalWrite(relayPin, relayState); // Control the relay
}

void setup() {
  Serial.begin(9600);
  connectWiFi();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
}

void loop() {
  Blynk.run();

  if (WiFi.status() == WL_CONNECTED) {
    if (Serial.available() > 0) {
      String data = Serial.readStringUntil('\n');
      volume = data.toFloat();
      Serial.print("Received volume data: ");
      Serial.println(volume, 2);
    }

    String postData = "volume=" + String(volume);

    HTTPClient http;
    WiFiClient client;

    http.begin(client, URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST(postData);
    String payload = http.getString();

    Serial.print("URL : ");       Serial.println(URL);
    Serial.print(" Data : ");     Serial.println(postData);
    Serial.print(" httpCode : "); Serial.println(httpCode);
    Serial.print(" payload : ");  Serial.println(payload);
    Serial.println("--------------------------------------------------------------");

    http.end();
  }

  delay(5000);
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

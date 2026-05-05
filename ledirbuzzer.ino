#define BLYNK_TEMPLATE_ID "TMPL3r0nGpxLa"
#define BLYNK_TEMPLATE_NAME "Parking System"
#define BLYNK_AUTH_TOKEN "W3XBqvz8OTgcwKPbSHDFWOULQ60Dh4XJ"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Airtel_Kishore mahal";
char pass[] = "nhibtana";

#define IR D2
#define LED D1

BlynkTimer timer;

// Sensor function
void checkSensor() {
  int value = digitalRead(IR);

  Serial.print("IR Value: ");
  Serial.println(value);

  if (value == 0) {
    digitalWrite(LED, HIGH);
    Blynk.virtualWrite(V0, 1);
  } else {
    digitalWrite(LED, LOW);
    Blynk.virtualWrite(V0, 0);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(IR, INPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, LOW);

  WiFi.begin(ssid, pass);

  timer.setInterval(500L, checkSensor);
}

void loop() {
  // try connecting Blynk safely
  if (WiFi.status() == WL_CONNECTED) {
    if (!Blynk.connected()) {
      Blynk.config(BLYNK_AUTH_TOKEN);
      Blynk.connect();
    }
    Blynk.run();
  }

  timer.run();
}
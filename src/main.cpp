#include <Arduino.h>
#include "Fuzzy.h"

#define TRIG_PIN  33
#define ECHO_PIN  32
#define BUZZER    14
#define LED_R     25
#define LED_G     26
#define LED_B     27

void setLED(bool r, bool g, bool b) {
  digitalWrite(LED_R, r ? LOW : HIGH);
  digitalWrite(LED_G, g ? LOW : HIGH);
  digitalWrite(LED_B, b ? LOW : HIGH);
}

float bacaJarak() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long durasi = pulseIn(ECHO_PIN, HIGH, 30000);
  if (durasi == 0) return 400;

  return durasi * 0.034 / 2;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(BUZZER, LOW);
  setLED(0, 0, 0);
}

void loop() {
  float jarak = bacaJarak();
  float danger = Fuzzy::tingkatBahaya(jarak);

  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.print(" cm, Bahaya: ");
  Serial.println(danger);

  if (danger > 60) {
    setLED(1, 0, 0);
    digitalWrite(BUZZER, HIGH);
  } else if (danger > 30) {
    setLED(1, 1, 0);
    digitalWrite(BUZZER, (millis() / 500) % 2);
  } else {
    setLED(0, 1, 0);
    digitalWrite(BUZZER, LOW);
  }

  delay(1000);
}

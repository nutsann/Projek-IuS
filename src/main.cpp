#include <Arduino.h>

// Sistem Pendeteksi Banjir Berbasis ESP32
// Input  : Sensor Ultrasonik HC-SR04
// Output : RGB LED dan Buzzer Active Module

#define TRIG_PIN 5
#define ECHO_PIN 18
#define BUZZER_PIN 19
#define LED_R 25
#define LED_G 26
#define LED_B 27

const float BATAS_WASPADA = 20.0;
const float BATAS_BAHAYA  = 10.0;

unsigned long lastBeepTime = 0;
bool buzzerState = false;

float bacaJarakCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long durasi = pulseIn(ECHO_PIN, HIGH, 30000);
  if (durasi == 0) return -1;
  return durasi * 0.0343 / 2.0;
}

void setRGB(bool r, bool g, bool b) {
  digitalWrite(LED_R, r ? HIGH : LOW);
  digitalWrite(LED_G, g ? HIGH : LOW);
  digitalWrite(LED_B, b ? HIGH : LOW);
}

void buzzerMati() {
  digitalWrite(BUZZER_PIN, LOW);
  buzzerState = false;
}

void buzzerBeep(unsigned long intervalMs) {
  unsigned long now = millis();
  if (now - lastBeepTime >= intervalMs) {
    lastBeepTime = now;
    buzzerState = !buzzerState;
    digitalWrite(BUZZER_PIN, buzzerState ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setRGB(false, false, false);
  buzzerMati();
  Serial.println("Sistem Pendeteksi Banjir ESP32 siap");
}

void loop() {
  float jarak = bacaJarakCm();
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.print(" cm | Status: ");

  if (jarak < 0 || jarak > 400) {
    setRGB(false, false, true);
    buzzerMati();
    Serial.println("ERROR SENSOR");
  } else if (jarak <= BATAS_BAHAYA) {
    setRGB(true, false, false);
    buzzerBeep(150);
    Serial.println("BAHAYA");
  } else if (jarak <= BATAS_WASPADA) {
    setRGB(true, true, false);
    buzzerBeep(500);
    Serial.println("WASPADA");
  } else {
    setRGB(false, true, false);
    buzzerMati();
    Serial.println("AMAN");
  }

  delay(100);
}
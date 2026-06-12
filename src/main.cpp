#include <Arduino.h>
#include "Fuzzy.h"

// =====================================================
// SISTEM PENDETEKSI BANJIR BERBASIS ESP32
// Komponen:
// - ESP32
// - HC-SR04
// - 1 RGB LED Module Common Cathode
// - Buzzer Active Module
// =====================================================

// Pin final satu sisi ESP32
const int TRIG_PIN = 33;
const int ECHO_PIN = 32;

const int LED_R = 25;
const int LED_G = 26;
const int LED_B = 27;

const int BUZZER_PIN = 14;

// Ambang jarak untuk demo alat fisik
// Sensor berada di atas permukaan air.
// Semakin kecil jarak, berarti air semakin tinggi.
const float BATAS_AMAN = 25.0;
const float BATAS_WASPADA = 12.0;

// Interval buzzer
const unsigned long INTERVAL_WASPADA = 700;
const unsigned long INTERVAL_BAHAYA = 200;
const unsigned long INTERVAL_ERROR = 500;

// Variabel buzzer
unsigned long waktuBuzzerSebelumnya = 0;
bool buzzerNyala = false;

// Variabel Serial Monitor
unsigned long waktuSerialSebelumnya = 0;

enum StatusBanjir {
  AMAN,
  WASPADA,
  BAHAYA,
  ERROR_SENSOR
};

// =====================================================
// FUNCTION PROTOTYPES
// Wajib di PlatformIO agar fungsi dikenali sebelum dipakai
// =====================================================
float bacaJarakCM();
StatusBanjir tentukanStatus(float jarak);
void setRGB(bool merah, bool hijau, bool biru);
void matikanRGB();
void tampilkanStatusLED(StatusBanjir status);
void kontrolBuzzer(StatusBanjir status);
void bunyiBuzzerBerkedip(unsigned long interval, int frekuensi);
void tampilkanSerial(float jarak, float nilaiBahaya, StatusBanjir status);
String teksStatus(StatusBanjir status);
String teksLED(StatusBanjir status);
String teksBuzzer(StatusBanjir status);

// =====================================================
// SETUP
// =====================================================
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  matikanRGB();
  noTone(BUZZER_PIN);

  Serial.println();
  Serial.println("=======================================");
  Serial.println("SISTEM PENDETEKSI BANJIR BERBASIS ESP32");
  Serial.println("Sensor : HC-SR04");
  Serial.println("Output : 1 RGB LED + Buzzer Active");
  Serial.println("Pin    : TRIG 33, ECHO 32, R 25, G 26, B 27, BUZZER 14");
  Serial.println("=======================================");
}

// =====================================================
// LOOP
// =====================================================
void loop() {
  float jarak = bacaJarakCM();
  float nilaiBahaya = Fuzzy::tingkatBahaya(jarak);
  StatusBanjir status = tentukanStatus(jarak);

  tampilkanStatusLED(status);
  kontrolBuzzer(status);
  tampilkanSerial(jarak, nilaiBahaya, status);

  delay(50);
}

// =====================================================
// BACA JARAK HC-SR04
// =====================================================
float bacaJarakCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long durasi = pulseIn(ECHO_PIN, HIGH, 30000);

  if (durasi == 0) {
    return -1.0;
  }

  float jarak = durasi / 58.0;
  return jarak;
}

// =====================================================
// TENTUKAN STATUS
// =====================================================
StatusBanjir tentukanStatus(float jarak) {
  if (jarak <= 0 || jarak > 400) {
    return ERROR_SENSOR;
  }

  if (jarak > BATAS_AMAN) {
    return AMAN;
  }

  if (jarak > BATAS_WASPADA) {
    return WASPADA;
  }

  return BAHAYA;
}

// =====================================================
// KONTROL RGB LED
// Modul RGB pada foto bertuliskan B G R -
// Sambungan fisik:
// B -> GPIO27
// G -> GPIO26
// R -> GPIO25
// - -> GND
//
// Common cathode:
// HIGH = nyala
// LOW  = mati
// =====================================================
void setRGB(bool merah, bool hijau, bool biru) {
  digitalWrite(LED_R, merah ? HIGH : LOW);
  digitalWrite(LED_G, hijau ? HIGH : LOW);
  digitalWrite(LED_B, biru ? HIGH : LOW);
}

void matikanRGB() {
  setRGB(false, false, false);
}

void tampilkanStatusLED(StatusBanjir status) {
  switch (status) {
    case AMAN:
      // Hijau
      setRGB(false, true, false);
      break;

    case WASPADA:
      // Kuning = merah + hijau
      setRGB(true, true, false);
      break;

    case BAHAYA:
      // Merah
      setRGB(true, false, false);
      break;

    case ERROR_SENSOR:
      // Biru
      setRGB(false, false, true);
      break;
  }
}

// =====================================================
// KONTROL BUZZER
// AMAN    : mati
// WASPADA : beep lambat
// BAHAYA  : beep cepat
// ERROR   : beep sedang
// =====================================================
void kontrolBuzzer(StatusBanjir status) {
  switch (status) {
    case AMAN:
      noTone(BUZZER_PIN);
      buzzerNyala = false;
      break;

    case WASPADA:
      bunyiBuzzerBerkedip(INTERVAL_WASPADA, 1000);
      break;

    case BAHAYA:
      bunyiBuzzerBerkedip(INTERVAL_BAHAYA, 1600);
      break;

    case ERROR_SENSOR:
      bunyiBuzzerBerkedip(INTERVAL_ERROR, 700);
      break;
  }
}

void bunyiBuzzerBerkedip(unsigned long interval, int frekuensi) {
  unsigned long waktuSekarang = millis();

  if (waktuSekarang - waktuBuzzerSebelumnya >= interval) {
    waktuBuzzerSebelumnya = waktuSekarang;
    buzzerNyala = !buzzerNyala;

    if (buzzerNyala) {
      tone(BUZZER_PIN, frekuensi);
    } else {
      noTone(BUZZER_PIN);
    }
  }
}

// =====================================================
// SERIAL MONITOR
// =====================================================
void tampilkanSerial(float jarak, float nilaiBahaya, StatusBanjir status) {
  unsigned long waktuSekarang = millis();

  if (waktuSekarang - waktuSerialSebelumnya >= 1000) {
    waktuSerialSebelumnya = waktuSekarang;

    Serial.print("Jarak: ");

    if (jarak <= 0) {
      Serial.print("Tidak terbaca");
    } else {
      Serial.print(jarak, 1);
      Serial.print(" cm");
    }

    Serial.print(" | Fuzzy: ");
    Serial.print(nilaiBahaya, 1);

    Serial.print(" | Status: ");
    Serial.print(teksStatus(status));

    Serial.print(" | LED: ");
    Serial.print(teksLED(status));

    Serial.print(" | Buzzer: ");
    Serial.println(teksBuzzer(status));
  }
}

String teksStatus(StatusBanjir status) {
  switch (status) {
    case AMAN:
      return "AMAN";
    case WASPADA:
      return "WASPADA";
    case BAHAYA:
      return "BAHAYA";
    case ERROR_SENSOR:
      return "ERROR SENSOR";
    default:
      return "TIDAK DIKETAHUI";
  }
}

String teksLED(StatusBanjir status) {
  switch (status) {
    case AMAN:
      return "Hijau";
    case WASPADA:
      return "Kuning";
    case BAHAYA:
      return "Merah";
    case ERROR_SENSOR:
      return "Biru";
    default:
      return "-";
  }
}

String teksBuzzer(StatusBanjir status) {
  switch (status) {
    case AMAN:
      return "Mati";
    case WASPADA:
      return "Beep lambat";
    case BAHAYA:
      return "Beep cepat";
    case ERROR_SENSOR:
      return "Beep sedang";
    default:
      return "-";
  }
}

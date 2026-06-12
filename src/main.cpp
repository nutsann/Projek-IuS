#include <Arduino.h>

/*
  Sistem Pendeteksi Banjir Berbasis ESP32
  Mata Kuliah IUS

  Input  : Sensor Ultrasonik HC-SR04
  Output : 3 RGB LED Module paralel dan Buzzer Active Module

  Catatan:
  - Tidak menggunakan WiFi, web dashboard, database, atau relay.
  - RGB LED dianggap common cathode, jadi HIGH = menyala dan LOW = mati.
  - Buzzer pada simulasi Wokwi menggunakan tone() dan noTone().
*/

const int PIN_TRIG = 5;
const int PIN_ECHO = 18;

const int PIN_BUZZER = 14;

const int PIN_LED_R = 25;
const int PIN_LED_G = 26;
const int PIN_LED_B = 27;

const float BATAS_AMAN_CM = 25.0;
const float BATAS_WASPADA_CM = 12.0;
const float JARAK_MAKSIMAL_VALID_CM = 400.0;

const unsigned long TIMEOUT_ECHO_US = 30000UL;
const unsigned long INTERVAL_BACA_SENSOR_MS = 200;

enum StatusBanjir {
  AMAN,
  WASPADA,
  BAHAYA,
  ERROR_SENSOR
};

float bacaJarakCM();
StatusBanjir tentukanStatus(float jarak);
void setRGB(bool merah, bool hijau, bool biru);
void matikanRGB();
void tampilkanStatusLED(StatusBanjir status);
void kontrolBuzzer(StatusBanjir status);
void tampilkanSerial(float jarak, StatusBanjir status);
String teksStatus(StatusBanjir status);
String teksLED(StatusBanjir status);
String teksBuzzer(StatusBanjir status);

float jarakTerakhir = -1.0;
StatusBanjir statusTerakhir = ERROR_SENSOR;
unsigned long waktuBacaSensorTerakhir = 0;

void setup() {
  Serial.begin(115200);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(PIN_BUZZER, OUTPUT);

  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  digitalWrite(PIN_TRIG, LOW);
  matikanRGB();
  noTone(PIN_BUZZER);

  Serial.println();
  Serial.println("Sistem Pendeteksi Banjir Berbasis ESP32");
  Serial.println("Sensor: HC-SR04 | Output: 3 RGB LED paralel dan buzzer");
  Serial.println("Baudrate Serial Monitor: 115200");
  Serial.println();
}

void loop() {
  unsigned long waktuSekarang = millis();

  // Pembacaan sensor dibuat berkala agar HC-SR04 lebih stabil.
  if (waktuSekarang - waktuBacaSensorTerakhir >= INTERVAL_BACA_SENSOR_MS) {
    waktuBacaSensorTerakhir = waktuSekarang;
    jarakTerakhir = bacaJarakCM();
    statusTerakhir = tentukanStatus(jarakTerakhir);
  }

  tampilkanStatusLED(statusTerakhir);
  kontrolBuzzer(statusTerakhir);
  tampilkanSerial(jarakTerakhir, statusTerakhir);
}

float bacaJarakCM() {
  // Kirim pulsa trigger 10 mikrodetik ke sensor HC-SR04.
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // pulseIn membaca lama pulsa HIGH dari pin ECHO dalam mikrodetik.
  unsigned long durasi = pulseIn(PIN_ECHO, HIGH, TIMEOUT_ECHO_US);

  if (durasi == 0) {
    return -1.0;
  }

  float jarak = durasi / 58.0;

  if (jarak <= 0 || jarak > JARAK_MAKSIMAL_VALID_CM) {
    return -1.0;
  }

  return jarak;
}

StatusBanjir tentukanStatus(float jarak) {
  if (jarak <= 0) {
    return ERROR_SENSOR;
  }

  if (jarak > BATAS_AMAN_CM) {
    return AMAN;
  }

  if (jarak > BATAS_WASPADA_CM) {
    return WASPADA;
  }

  return BAHAYA;
}

void setRGB(bool merah, bool hijau, bool biru) {
  // Ketiga RGB LED dipasang paralel pada pin yang sama.
  digitalWrite(PIN_LED_R, merah ? HIGH : LOW);
  digitalWrite(PIN_LED_G, hijau ? HIGH : LOW);
  digitalWrite(PIN_LED_B, biru ? HIGH : LOW);
}

void matikanRGB() {
  setRGB(false, false, false);
}

void tampilkanStatusLED(StatusBanjir status) {
  switch (status) {
    case AMAN:
      setRGB(false, true, false);   // Hijau
      break;

    case WASPADA:
      setRGB(true, true, false);    // Kuning
      break;

    case BAHAYA:
      setRGB(true, false, false);   // Merah
      break;

    case ERROR_SENSOR:
    default:
      setRGB(false, false, true);   // Biru
      break;
  }
}

void kontrolBuzzer(StatusBanjir status) {
  static bool buzzerNyala = false;
  static unsigned long waktuPerubahan = 0;
  static StatusBanjir statusSebelumnya = ERROR_SENSOR;

  unsigned long waktuSekarang = millis();

  if (status == AMAN) {
    noTone(PIN_BUZZER);
    buzzerNyala = false;
    statusSebelumnya = status;
    return;
  }

  int frekuensi = 1000;
  unsigned long durasiNyala = 200;
  unsigned long durasiMati = 800;

  if (status == WASPADA) {
    frekuensi = 1000;
    durasiNyala = 200;
    durasiMati = 800;
  } else if (status == BAHAYA) {
    frekuensi = 1500;
    durasiNyala = 150;
    durasiMati = 150;
  } else if (status == ERROR_SENSOR) {
    frekuensi = 700;
    durasiNyala = 250;
    durasiMati = 250;
  }

  // Saat status berubah, bunyi langsung dimulai agar respons terasa cepat.
  if (status != statusSebelumnya) {
    statusSebelumnya = status;
    buzzerNyala = true;
    waktuPerubahan = waktuSekarang;
    tone(PIN_BUZZER, frekuensi);
    return;
  }

  unsigned long interval = buzzerNyala ? durasiNyala : durasiMati;

  if (waktuSekarang - waktuPerubahan >= interval) {
    waktuPerubahan = waktuSekarang;
    buzzerNyala = !buzzerNyala;

    if (buzzerNyala) {
      tone(PIN_BUZZER, frekuensi);
    } else {
      noTone(PIN_BUZZER);
    }
  }
}

void tampilkanSerial(float jarak, StatusBanjir status) {
  static unsigned long waktuSerialTerakhir = 0;
  unsigned long waktuSekarang = millis();

  if (waktuSekarang - waktuSerialTerakhir < 1000) {
    return;
  }

  waktuSerialTerakhir = waktuSekarang;

  Serial.print("Jarak: ");
  if (status == ERROR_SENSOR) {
    Serial.print("Tidak valid");
  } else {
    Serial.print(jarak, 1);
    Serial.print(" cm");
  }

  Serial.print(" | Status: ");
  Serial.print(teksStatus(status));
  Serial.print(" | LED: ");
  Serial.print(teksLED(status));
  Serial.print(" | Buzzer: ");
  Serial.println(teksBuzzer(status));
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
    default:
      return "ERROR SENSOR";
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
    default:
      return "Biru";
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
    default:
      return "Beep sedang";
  }
}

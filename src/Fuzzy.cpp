#include "Fuzzy.h"

// Fungsi keanggotaan segitiga
float Fuzzy::triMF(float x, float a, float b, float c) {
  if (x <= a || x >= c) return 0.0;
  if (x == b) return 1.0;
  if (x < b) return (x - a) / (b - a);
  return (c - x) / (c - b);
}

// Fungsi keanggotaan trapesium
float Fuzzy::trapMF(float x, float a, float b, float c, float d) {
  if (x <= a || x >= d) return 0.0;
  if (x >= b && x <= c) return 1.0;
  if (x < b) return (x - a) / (b - a);
  return (d - x) / (d - c);
}

// Catatan:
// Sensor dipasang di atas air.
// Jarak besar = air rendah = aman.
// Jarak kecil = air tinggi = bahaya.
//
// Ambang disesuaikan untuk demo jarak pendek:
// > 25 cm       = aman
// 12 - 25 cm    = waspada
// <= 12 cm      = bahaya

float Fuzzy::jarakAman(float jarak) {
  // Mulai aman setelah 20 cm, penuh aman mulai 25 cm.
  // Batas atas dibuat 400 cm untuk jangkauan HC-SR04.
  return trapMF(jarak, 20, 25, 400, 401);
}

float Fuzzy::jarakWaspada(float jarak) {
  // Puncak waspada sekitar 18 cm.
  return triMF(jarak, 10, 18, 26);
}

float Fuzzy::jarakBahaya(float jarak) {
  // Penuh bahaya pada 0-10 cm, turun sampai 15 cm.
  return trapMF(jarak, 0, 0.1, 10, 15);
}

float Fuzzy::tingkatBahaya(float jarak) {
  if (jarak <= 0 || jarak > 400) {
    return 0.0;
  }

  float aman = jarakAman(jarak);
  float waspada = jarakWaspada(jarak);
  float bahaya = jarakBahaya(jarak);

  float total = aman + waspada + bahaya;
  if (total == 0) return 0.0;

  // Nilai 10 = aman, 50 = waspada, 90 = bahaya
  return (aman * 10 + waspada * 50 + bahaya * 90) / total;
}

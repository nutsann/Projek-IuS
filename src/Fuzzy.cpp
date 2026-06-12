#include "Fuzzy.h"

float Fuzzy::triMF(float x, float a, float b, float c) {
  if (x <= a || x >= c) return 0;
  if (x == b) return 1;
  if (x < b) return (x - a) / (b - a);
  return (c - x) / (c - b);
}

float Fuzzy::trapMF(float x, float a, float b, float c, float d) {
  if (x <= a || x >= d) return 0;
  if (x >= b && x <= c) return 1;
  if (x < b) return (x - a) / (b - a);
  return (d - x) / (d - c);
}

float Fuzzy::jarakAman(float jarak) {
  return trapMF(jarak, 80, 100, 400, 400);
}

float Fuzzy::jarakWaspada(float jarak) {
  return triMF(jarak, 30, 65, 100);
}

float Fuzzy::jarakBahaya(float jarak) {
  return trapMF(jarak, 0, 0, 30, 60);
}

float Fuzzy::tingkatBahaya(float jarak) {
  float aman = jarakAman(jarak);
  float waspada = jarakWaspada(jarak);
  float bahaya = jarakBahaya(jarak);

  float total = aman + waspada + bahaya;
  if (total == 0) return 0;

  return (aman * 10 + waspada * 50 + bahaya * 90) / total;
}

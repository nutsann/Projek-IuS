# Panduan Wiring Sistem Pendeteksi Banjir

Dokumen ini menjelaskan sambungan komponen untuk project pendeteksi banjir berbasis ESP32, HC-SR04, 3 RGB LED module, dan buzzer active module.

## Wiring HC-SR04 ke ESP32

| HC-SR04 | ESP32 | Keterangan |
| --- | --- | --- |
| VCC | 5V / VIN | Sumber tegangan sensor |
| GND | GND | Ground |
| TRIG | GPIO 5 | Pin trigger dari ESP32 |
| ECHO | GPIO 18 | Pin echo ke ESP32 |

Sensor HC-SR04 diletakkan di atas wadah air dan menghadap ke permukaan air. Semakin kecil jarak yang terbaca, semakin tinggi permukaan air.

## Wiring Buzzer ke ESP32

| Buzzer Active Module | ESP32 | Keterangan |
| --- | --- | --- |
| SIG / positif | GPIO 14 | Sinyal kontrol buzzer |
| GND / negatif | GND | Ground |

Pada simulasi Wokwi, buzzer dikendalikan dengan `tone()` dan `noTone()`. Pada alat asli, beberapa buzzer active module lebih cocok dikendalikan dengan `digitalWrite(HIGH/LOW)`.

## Wiring 3 RGB LED ke ESP32

Ketiga RGB LED dipasang paralel sehingga semuanya menampilkan warna status yang sama.

| Pin RGB LED | ESP32 | Keterangan |
| --- | --- | --- |
| R LED 1, R LED 2, R LED 3 | GPIO 25 | Kanal merah |
| G LED 1, G LED 2, G LED 3 | GPIO 26 | Kanal hijau |
| B LED 1, B LED 2, B LED 3 | GPIO 27 | Kanal biru |
| COM / GND semua RGB LED | GND | Common cathode |

RGB LED dianggap common cathode, sehingga logika program adalah:

| Nilai Output | Kondisi LED |
| --- | --- |
| HIGH | Menyala |
| LOW | Mati |

## Catatan Penggunaan Breadboard

- Gunakan rail merah breadboard untuk jalur 5V atau VIN.
- Gunakan rail biru atau hitam breadboard untuk jalur GND.
- Hubungkan GND ESP32 ke rail GND breadboard.
- Sambungkan semua GND komponen ke rail GND yang sama.
- Rapikan kabel berdasarkan fungsi agar mudah dijelaskan saat presentasi.
- Untuk RGB LED paralel, satukan jalur R, jalur G, jalur B, dan jalur COM masing-masing pada baris atau rail yang sesuai.

## Catatan Pembagi Tegangan ECHO HC-SR04

Pada alat asli, HC-SR04 umumnya memakai tegangan 5V. Pin ECHO dapat mengeluarkan sinyal 5V, sedangkan GPIO ESP32 bekerja pada logika 3.3V.

Karena itu, jalur ECHO sebaiknya diberi pembagi tegangan sebelum masuk ke GPIO 18 ESP32. Contoh konsep:

- ECHO HC-SR04 masuk ke resistor pertama.
- Titik tengah resistor masuk ke GPIO 18 ESP32.
- Resistor kedua dari titik tengah menuju GND.

Tujuannya adalah menurunkan level sinyal ECHO agar lebih aman untuk ESP32.

## Catatan Jika Warna RGB LED Tertukar

Jika warna LED tidak sesuai dengan status:

- Cek ulang pin R, G, dan B pada modul RGB LED.
- Tukar kabel R, G, dan B sesuai label modul.
- Pastikan modul yang dipakai benar-benar common cathode.
- Pastikan COM RGB LED terhubung ke GND, bukan ke 3.3V atau 5V.

## Catatan Keamanan Saat Merakit

- Cabut kabel USB ESP32 saat mengubah wiring.
- Periksa kembali jalur 5V, 3.3V, dan GND sebelum menyalakan alat.
- Jangan menghubungkan pin ECHO HC-SR04 5V langsung ke ESP32 tanpa pembagi tegangan pada implementasi alat asli.
- Pastikan tidak ada kabel yang saling bersentuhan dan menyebabkan short circuit.
- Gunakan kabel USB Type-C data agar upload program ke ESP32 berjalan normal.
- Relay tidak digunakan pada versi final, jadi tidak perlu dipasang pada breadboard.

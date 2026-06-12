# Sistem Pendeteksi Banjir Berbasis ESP32 Menggunakan Sensor Ultrasonik HC-SR04, 3 RGB LED Module, dan Buzzer Active

Project ini dibuat untuk project akhir mata kuliah IUS. Sistem membaca jarak antara sensor ultrasonik HC-SR04 dan permukaan air. Semakin kecil jarak yang terbaca, semakin tinggi permukaan air. ESP32 kemudian menampilkan status melalui 3 RGB LED module yang dipasang paralel dan sebuah buzzer active module.

Project ini fokus pada pendeteksi banjir lokal. Tidak ada WiFi, web dashboard, database, relay, LCD, OLED, atau fitur tambahan lain.

## Tujuan Project

- Membuat simulasi pendeteksi banjir menggunakan Wokwi.
- Menyiapkan kode yang bisa di-build dengan PlatformIO menggunakan Arduino Framework.
- Menampilkan status banjir secara lokal melalui RGB LED dan buzzer.
- Menyediakan dokumentasi wiring dan skenario pengujian untuk laporan akhir.

## Daftar Komponen

| No | Komponen | Jumlah |
| --- | --- | --- |
| 1 | ESP32 Development Board Type-C | 1 |
| 2 | Sensor Ultrasonik HC-SR04 | 1 |
| 3 | RGB LED Module common cathode | 3 |
| 4 | Buzzer Active Module | 1 |
| 5 | Breadboard 830 titik | 1 |
| 6 | Kabel jumper male-to-male | Secukupnya |
| 7 | Kabel jumper male-to-female | Secukupnya |
| 8 | Kabel USB Type-C data | 1 |

## Tabel Pin dan Wiring

| Komponen | Pin Komponen | Pin ESP32 | Keterangan |
| --- | --- | --- | --- |
| HC-SR04 | VCC | 5V / VIN | Sumber tegangan sensor |
| HC-SR04 | GND | GND | Ground |
| HC-SR04 | TRIG | GPIO 5 | Pulsa trigger |
| HC-SR04 | ECHO | GPIO 18 | Pulsa echo |
| Buzzer Active | SIG / positif | GPIO 14 | Sinyal buzzer |
| Buzzer Active | GND / negatif | GND | Ground |
| RGB LED 1 | R | GPIO 25 | Kanal merah |
| RGB LED 1 | G | GPIO 26 | Kanal hijau |
| RGB LED 1 | B | GPIO 27 | Kanal biru |
| RGB LED 1 | COM / GND | GND | Common cathode |
| RGB LED 2 | R | GPIO 25 | Dipasang paralel dengan RGB LED 1 |
| RGB LED 2 | G | GPIO 26 | Dipasang paralel dengan RGB LED 1 |
| RGB LED 2 | B | GPIO 27 | Dipasang paralel dengan RGB LED 1 |
| RGB LED 2 | COM / GND | GND | Common cathode |
| RGB LED 3 | R | GPIO 25 | Dipasang paralel dengan RGB LED 1 |
| RGB LED 3 | G | GPIO 26 | Dipasang paralel dengan RGB LED 1 |
| RGB LED 3 | B | GPIO 27 | Dipasang paralel dengan RGB LED 1 |
| RGB LED 3 | COM / GND | GND | Common cathode |

## Struktur Folder

```text
Projek-IuS/
|-- .vscode/
|   |-- extensions.json
|   `-- settings.json
|-- docs/
|   |-- wiring.md
|   |-- skenario_pengujian.md
|   `-- catatan_presentasi.md
|-- include/
|-- lib/
|-- src/
|   `-- main.cpp
|-- test/
|-- .gitignore
|-- diagram.json
|-- platformio.ini
|-- README.md
`-- wokwi.toml
```

## Cara Kerja Sistem

1. ESP32 mengirim sinyal trigger ke HC-SR04 melalui GPIO 5.
2. HC-SR04 mengirim sinyal echo ke ESP32 melalui GPIO 18.
3. ESP32 membaca durasi echo menggunakan `pulseIn()`.
4. Jarak dihitung dengan rumus `jarak = durasi / 58.0`.
5. ESP32 menentukan status berdasarkan jarak sensor ke permukaan air.
6. Status ditampilkan melalui warna RGB LED dan pola bunyi buzzer.
7. Jarak, status, kondisi LED, dan kondisi buzzer ditampilkan ke Serial Monitor setiap 1 detik.

## Tabel Status

| Status | Kondisi Jarak | Warna RGB LED | Kondisi Buzzer |
| --- | --- | --- | --- |
| AMAN | Jarak lebih dari 25 cm | Hijau | Mati |
| WASPADA | Jarak lebih dari 12 cm sampai 25 cm | Kuning | Bunyi lambat |
| BAHAYA | Jarak 12 cm atau kurang | Merah | Bunyi cepat |
| ERROR SENSOR | Sensor tidak terbaca atau jarak tidak valid | Biru | Bunyi sedang |

## Cara Build di PlatformIO

1. Buka folder project ini menggunakan Visual Studio Code.
2. Pastikan extension PlatformIO IDE sudah terpasang.
3. Buka file `src/main.cpp` jika ingin melihat atau mengubah kode.
4. Klik menu PlatformIO.
5. Klik `Build`.
6. Jika build berhasil, file firmware akan dibuat di `.pio/build/esp32dev/`.

## Cara Menjalankan Simulasi Wokwi

1. Pastikan extension Wokwi for VS Code sudah terpasang.
2. Build project terlebih dahulu menggunakan PlatformIO.
3. Tekan `Ctrl + Shift + P`.
4. Pilih `Wokwi: Start Simulator`.
5. Simulasi akan memakai `diagram.json` dan firmware dari `.pio/build/esp32dev/firmware.bin`.
6. Buka Serial Monitor dengan baudrate `115200`.

## Cara Menguji Jarak di Wokwi

| Pengujian | Distance HC-SR04 | Status yang Diharapkan |
| --- | --- | --- |
| 1 | 30 cm | AMAN |
| 2 | 20 cm | WASPADA |
| 3 | 8 cm | BAHAYA |

Langkah uji:

1. Jalankan simulator Wokwi.
2. Klik komponen HC-SR04.
3. Ubah nilai `Distance`.
4. Amati warna RGB LED, bunyi buzzer, dan teks pada Serial Monitor.

## Catatan Implementasi ke Alat Asli

- Jika HC-SR04 diberi tegangan 5V, jalur ECHO sebaiknya diberi pembagi tegangan sebelum masuk ke GPIO ESP32.
- Ketiga RGB LED dipasang paralel agar semua menampilkan warna status yang sama.
- Jika warna RGB LED tidak sesuai, cek ulang pin R, G, dan B pada modul.
- Jika buzzer active module asli tidak cocok dengan `tone()`, pola buzzer bisa diganti memakai `digitalWrite(HIGH/LOW)`.
- Gunakan kabel USB Type-C data, bukan kabel charge-only.
- Pastikan semua ground komponen terhubung ke GND ESP32 yang sama.
- Relay memang ada di daftar barang, tetapi tidak digunakan pada versi final project ini.
- Web dashboard, WiFi, database, LCD, dan OLED juga tidak digunakan.

## Dokumentasi yang Perlu Difoto untuk Laporan Akhir

- Foto rangkaian ESP32, HC-SR04, RGB LED, dan buzzer di breadboard.
- Foto koneksi pin ESP32 yang terlihat jelas.
- Screenshot simulasi Wokwi saat status AMAN.
- Screenshot simulasi Wokwi saat status WASPADA.
- Screenshot simulasi Wokwi saat status BAHAYA.
- Screenshot Serial Monitor yang menampilkan jarak dan status.
- Foto proses pengujian alat asli jika sudah dirakit.

# Skenario Pengujian Sistem

Dokumen ini berisi skenario pengujian untuk memastikan sistem pendeteksi banjir bekerja sesuai rancangan.

## Tujuan Pengujian

- Memastikan sensor HC-SR04 dapat membaca jarak.
- Memastikan ESP32 dapat menentukan status AMAN, WASPADA, BAHAYA, dan ERROR SENSOR.
- Memastikan RGB LED menampilkan warna sesuai status.
- Memastikan buzzer menghasilkan pola bunyi sesuai status.
- Menyiapkan tabel hasil pengujian untuk laporan akhir.

## Pengujian Status AMAN

| Item | Nilai |
| --- | --- |
| Distance HC-SR04 | 30 cm |
| Status yang diharapkan | AMAN |
| Warna LED | Hijau |
| Kondisi buzzer | Mati |
| Serial Monitor | Menampilkan jarak sekitar 30 cm dan status AMAN |

Langkah:

1. Jalankan simulasi Wokwi.
2. Klik komponen HC-SR04.
3. Ubah `Distance` menjadi `30`.
4. Perhatikan warna LED, buzzer, dan Serial Monitor.

## Pengujian Status WASPADA

| Item | Nilai |
| --- | --- |
| Distance HC-SR04 | 20 cm |
| Status yang diharapkan | WASPADA |
| Warna LED | Kuning |
| Kondisi buzzer | Bunyi lambat |
| Serial Monitor | Menampilkan jarak sekitar 20 cm dan status WASPADA |

Langkah:

1. Jalankan simulasi Wokwi.
2. Klik komponen HC-SR04.
3. Ubah `Distance` menjadi `20`.
4. Perhatikan warna LED, buzzer, dan Serial Monitor.

## Pengujian Status BAHAYA

| Item | Nilai |
| --- | --- |
| Distance HC-SR04 | 8 cm |
| Status yang diharapkan | BAHAYA |
| Warna LED | Merah |
| Kondisi buzzer | Bunyi cepat |
| Serial Monitor | Menampilkan jarak sekitar 8 cm dan status BAHAYA |

Langkah:

1. Jalankan simulasi Wokwi.
2. Klik komponen HC-SR04.
3. Ubah `Distance` menjadi `8`.
4. Perhatikan warna LED, buzzer, dan Serial Monitor.

## Pengujian ERROR SENSOR

| Item | Nilai |
| --- | --- |
| Kondisi | Sensor tidak terbaca atau nilai jarak tidak valid |
| Status yang diharapkan | ERROR SENSOR |
| Warna LED | Biru |
| Kondisi buzzer | Bunyi sedang |
| Serial Monitor | Menampilkan jarak tidak valid dan status ERROR SENSOR |

Contoh cara uji di simulasi:

1. Hentikan simulasi.
2. Putuskan sementara kabel ECHO pada `diagram.json` atau di editor diagram Wokwi.
3. Jalankan simulasi lagi.
4. Amati perubahan status menjadi ERROR SENSOR.

## Format Tabel Hasil Pengujian untuk Laporan Akhir

| No | Jarak sensor | Status yang Diharapkan | Warna LED | Kondisi Buzzer | Hasil Pengujian | Keterangan |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 30 cm | AMAN | Hijau | Mati | Sesuai / Tidak sesuai | Isi saat pengujian |
| 2 | 20 cm | WASPADA | Kuning | Bunyi lambat | Sesuai / Tidak sesuai | Isi saat pengujian |
| 3 | 8 cm | BAHAYA | Merah | Bunyi cepat | Sesuai / Tidak sesuai | Isi saat pengujian |
| 4 | Tidak valid | ERROR SENSOR | Biru | Bunyi sedang | Sesuai / Tidak sesuai | Isi saat pengujian |

## Catatan Pengamatan

- Catat nilai jarak yang muncul pada Serial Monitor.
- Ambil screenshot tiap status di Wokwi.
- Untuk alat asli, catat jika ada selisih pembacaan jarak karena posisi sensor atau permukaan air tidak rata.

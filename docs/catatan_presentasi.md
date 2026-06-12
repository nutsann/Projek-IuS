# Catatan Presentasi Project

Dokumen ini berisi alur presentasi dan contoh kalimat yang bisa dibacakan saat menjelaskan project akhir mata kuliah IUS.

## Pembukaan Presentasi

Contoh kalimat:

"Selamat pagi/siang. Kami akan mempresentasikan project akhir mata kuliah IUS dengan judul Sistem Pendeteksi Banjir Berbasis ESP32 Menggunakan Sensor Ultrasonik HC-SR04, RGB LED, dan Buzzer."

"Project ini dibuat untuk memberikan peringatan lokal berdasarkan ketinggian air yang dibaca melalui sensor ultrasonik."

## Penjelasan Latar Belakang

Contoh kalimat:

"Banjir dapat terjadi ketika permukaan air naik melewati batas aman. Karena itu, dibutuhkan sistem sederhana yang dapat membaca perubahan tinggi air dan memberikan peringatan secara langsung."

"Pada project ini, kami tidak menggunakan WiFi, web dashboard, database, atau relay. Sistem dibuat fokus sebagai alat pendeteksi banjir lokal dengan indikator LED dan buzzer."

## Tujuan Project

Contoh kalimat:

"Tujuan project ini adalah membuat sistem sederhana yang dapat membaca perubahan permukaan air, menentukan status banjir, dan memberikan peringatan lokal melalui LED serta buzzer."

"Project ini juga disiapkan agar bisa diuji melalui simulasi Wokwi dan diimplementasikan ke ESP32 asli menggunakan PlatformIO."

## Penjelasan Komponen

Komponen utama:

- ESP32 Development Board Type-C sebagai mikrokontroler.
- Sensor HC-SR04 untuk membaca jarak sensor ke permukaan air.
- 3 RGB LED module sebagai indikator visual.
- Buzzer active module sebagai indikator suara.
- Breadboard dan kabel jumper sebagai media perakitan.

Contoh kalimat:

"ESP32 berfungsi sebagai otak sistem. Sensor HC-SR04 membaca jarak ke permukaan air. RGB LED menampilkan warna status, sedangkan buzzer memberikan peringatan suara."

"Ketiga RGB LED dipasang paralel, sehingga ketiganya selalu menampilkan warna status yang sama."

## Penjelasan Cara Kerja

Contoh kalimat:

"Sensor HC-SR04 ditempatkan di atas wadah air. Sensor membaca jarak dari sensor ke permukaan air. Jika jarak semakin kecil, maka permukaan air semakin tinggi."

"ESP32 menentukan status berdasarkan jarak. Jika jarak lebih dari 25 cm, status AMAN. Jika jarak lebih dari 12 cm sampai 25 cm, status WASPADA. Jika jarak 12 cm atau kurang, status BAHAYA."

"Jika sensor tidak terbaca atau nilainya tidak valid, sistem masuk ke status ERROR SENSOR."

## Penjelasan Indikator Status

Contoh kalimat:

"Pada status AMAN, RGB LED berwarna hijau dan buzzer mati."

"Pada status WASPADA, RGB LED berwarna kuning dan buzzer berbunyi lambat."

"Pada status BAHAYA, RGB LED berwarna merah dan buzzer berbunyi cepat."

"Pada status ERROR SENSOR, RGB LED berwarna biru dan buzzer berbunyi sedang."

## Penjelasan Simulasi Wokwi

Contoh kalimat:

"Simulasi dibuat menggunakan Wokwi for VS Code. Project ini menggunakan PlatformIO, sehingga kode utama berada di folder src dengan nama file main.cpp."

"Untuk menjalankan simulasi, project di-build terlebih dahulu melalui PlatformIO. Setelah itu, simulator Wokwi dijalankan menggunakan perintah Wokwi: Start Simulator."

"Nilai jarak dapat diuji dengan mengubah parameter Distance pada komponen HC-SR04."

## Penjelasan Hasil Pengujian

Contoh kalimat:

"Pada pengujian pertama, distance diatur menjadi 30 cm. Sistem menampilkan status AMAN, LED hijau menyala, dan buzzer mati."

"Pada pengujian kedua, distance diatur menjadi 20 cm. Sistem menampilkan status WASPADA, LED kuning menyala, dan buzzer berbunyi lambat."

"Pada pengujian ketiga, distance diatur menjadi 8 cm. Sistem menampilkan status BAHAYA, LED merah menyala, dan buzzer berbunyi cepat."

"Pengujian error sensor dilakukan dengan membuat sensor tidak terbaca. Sistem menampilkan status ERROR SENSOR, LED biru menyala, dan buzzer berbunyi sedang."

## Penjelasan Implementasi Alat Asli

Contoh kalimat:

"Pada alat asli, sensor HC-SR04 dapat diberi tegangan 5V melalui VIN ESP32. Namun, pin ECHO sebaiknya diberi pembagi tegangan sebelum masuk ke GPIO ESP32 karena ESP32 bekerja pada level logika 3.3V."

"Jika buzzer active module tidak cocok menggunakan fungsi tone, program dapat disesuaikan dengan digitalWrite HIGH dan LOW."

"Jika warna RGB LED tidak sesuai, kabel R, G, dan B perlu dicek kembali karena urutan pin pada modul dapat berbeda."

## Penutup

Contoh kalimat:

"Kesimpulannya, sistem ini dapat membaca jarak permukaan air dan memberikan status peringatan secara lokal menggunakan RGB LED dan buzzer."

"Project ini masih dapat dikembangkan, misalnya dengan menambahkan casing, kalibrasi tinggi wadah, atau sumber daya mandiri. Namun, untuk versi final mata kuliah ini, sistem sengaja difokuskan pada pendeteksi banjir lokal tanpa WiFi, web dashboard, database, atau relay."

"Sekian presentasi dari kami. Terima kasih."

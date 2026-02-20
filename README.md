# TensorProject

## Proje Açıklaması
Bu proje, C dilinde yazılmış bir dinamik Tensor yapısı ve Quantization demo uygulamasıdır. 
Amaç, RAM’i sınırlı cihazlarda (mikrodenetleyici, TinyML vb.) çalışacak bir veri yapısı tasarlamaktır. 
Tensor, duruma göre 32-bit Float, 16-bit Float (Half-precision) veya 8-bit Integer (Quantized) değerleri saklayabilir.  

Projede kullanılan teknikler:
- **Union ve Enum** ile dinamik veri tipi yönetimi
- **Memory management** ile dinamik bellek kullanımı
- **Quantization ve Dequantization** demo
- C dilinde primitive tensor implementasyonu

## Kullanım
1. Visual Studio Community 2022 veya üstü ile açın
2. `main.c` dosyasını **Startup Item** olarak seçin
3. `Ctrl + F5` ile çalıştırın
4. Konsolda tensor değerleri ve hafıza kullanımı görüntülenecek

```text
=== FLOAT32 Tensor ===
0.12
-0.45
1.20
0.33
-0.78
Memory Usage Float32: 20 bytes

=== Quantized INT8 Tensor ===
12
-45
120
33
-78
Memory Usage INT8: 5 bytes

=== Dequantized Back to FLOAT32 ===
0.12
-0.45
1.20
0.33
-0.78

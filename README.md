
# Filozofların Yemek Problemi Simülasyonu

Bu proje, klasik "Yemek Yiyen Filozoflar" probleminin bir uygulamasıdır. Projede, bir grup filozofun yemek yeme, düşünme ve uyuma döngüsü simüle edilmektedir. Filozoflar, sınırlı sayıda çatal paylaşarak yemek yerler. Program, deadlock önlemenin ve doğru davranışı sağlamanın yollarını gösteren, çoklu iş parçacığı (multithreading) ve mutex kullanımı ile yazılmıştır.

## İçindekiler
- [Genel Bakış](#genel-bakış)
- [Özellikler](#özellikler)
- [Dosya Yapısı](#dosya-yapısı)
- [Derleme](#derleme)
- [Kullanım](#kullanım)
- [Argümanlar](#argümanlar)

## Genel Bakış

Bu program, pthread'ler ve mutex'ler kullanarak bir yuvarlak masa etrafında yemek yemeye çalışan filozofları simüle eder. Filozoflar yemek yemek için iki çatal almak zorundadır, ancak çatallar filozof sayısı kadar olduğundan, bu durum bir yarışa neden olabilir. Amaç deadlock ve açlık durumlarından kaçınarak tüm filozofların yemek yiyebilmesini sağlamaktır.

## Özellikler

- `pthread` kullanılarak çoklu iş parçacıklı simülasyon.
- datarace durumlarını ve deadlock'u önlemek için mutex kullanımı.
- Filozofların yaşam döngüsünü simüle eder: **yemek**, **düşünme** ve **uyuma**.
- Hatalı girişler için argüman kontrolü.

## Dosya Yapısı

- `main.c`: Ana fonksiyon içerir ve simülasyonu başlatır.
- `init.c`: Veri yapılarının, mutex'lerin ve filozofların başlatılmasından sorumludur.
- `simulation.c`: Filozofların eylemlerini (yemek, uyuma, düşünme) içeren temel mantığı içerir.
- `situation.c`: Simülasyonu yönetir, filozofların ölüm gibi durumlarını kontrol eder.
- `utils.c`: Argüman doğrulama için yardımcı fonksiyonları içerir.
- `utils1.c`: Uyku ve yazdırma gibi ek yardımcı fonksiyonlar içerir.
- `free.c`: Bellek temizliği ve mutexlerin yok edilmesini yönetir.
- `philo.h`: Yapı tanımları ve fonksiyon prototiplerini içeren başlık dosyası.

## Derleme

Projeyi derlemek için aşağıdaki komutu kullanın:

```bash
make
```

## Kullanım

Derlendikten sonra programı şu şekilde çalıştırabilirsiniz:

```bash
./philo [filozof_sayısı] [ölüm_süresi] [yeme_süresi] [uyuma_süresi] [isteğe_bağlı_yemek_yeme_sayısı]
```

Örnek:

```bash
./philo 5 800 200 200
```

Bu, şu parametrelerle bir simülasyon başlatacaktır:
- 5 filozof.
- Bir filozofun yemek yemeden önce ölmeden geçebileceği süre: 800 ms.
- Yemek yeme ve uyuma süresi: 200 ms.

Opsiyonel olarak, her bir filozofun kaç kez yemek yemesi gerektiğini belirleyebilirsiniz:

```bash
./philo 5 800 200 200 3
```

## Argümanlar

1. `filozof_sayısı`: Filozof ve çatal sayısı (1'den büyük olmalıdır).
2. `ölüm_süresi`: Bir filozofun yemek yemeden önce ölmeden dayanabileceği süre (ms cinsinden).
3. `yeme_süresi`: Bir filozofun yemek yerken harcadığı süre (ms cinsinden).
4. `uyuma_süresi`: Bir filozofun uyurken harcadığı süre (ms cinsinden).
5. `isteğe_bağlı_yemek_yeme_sayısı`: (Opsiyonel) Eğer tüm filozoflar bu kadar kez yemek yerse, simülasyon sona erer. Belirtilmezse, simülasyon sonsuza dek sürer.

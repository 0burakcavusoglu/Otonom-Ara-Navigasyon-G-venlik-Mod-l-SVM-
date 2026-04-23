# Otonom Araç Navigasyon Güvenlik Modülü (SVM)

Bu proje, 2 boyutlu bir düzlemde tanımlanmış iki farklı engel sınıfını, aralarında **maksimum güvenlik koridoru (margin)** bırakacak şekilde ayıran matematiksel bir model ve algoritma içermektedir.

##  Proje Hakkında
Otonom araçların güvenliği için sadece engelleri ayırmak yeterli değildir; sistemin ölçüm hatalarına ve gürültüye karşı dayanıklı olması için engellere olan uzaklığın maksimize edilmesi gerekir. Bu projede, bu problemi çözmek için **Destek Vektör Makineleri (Support Vector Machines - SVM)** algoritması kullanılmıştır.

### Temel Özellikler
* **Maksimum Marj Ayrıştırıcısı:** En yakın engel koordinatlarına olan uzaklığı maksimize eden optimum sınırı bulur.
* **Modern C++ Mimari:** Nesne yönelimli (OOP) ve katmanlı yazılım mimarisi kullanılarak geliştirilmiştir.
* **Güvenli Bellek Yönetimi:** `std::unique_ptr` ve RAII prensipleri ile sıfır bellek sızıntısı hedeflenmiştir.
* **Yüksek Verimlilik:** Eğitim aşaması O(n), karar verme (tahmin) aşaması O(1) zaman karmaşıklığına sahiptir.

##  Matematiksel Model
Algoritma, **Hinge Loss (Menteşe Kaybı)** fonksiyonunu **Stochastic Gradient Descent (SGD)** yöntemiyle optimize ederek çalışır.

[Image of Support Vector Machine margin and hyperplane]

* **Karar Sınırı:** w * x + b = 0
* **Marj Genişliği:** 2 / ||w||

## Yazılım Mimarisi
Proje, sorumlulukların ayrılması prensibine uygun olarak 3 ana katmandan oluşmaktadır:
1. **Veri Modeli (Point):** Engel koordinatlarını ve etiketlerini tutan veri yapısı.
2. **İş Mantığı (SVMSolver):** SVM algoritmasının ve gradyan inişi optimizasyonunun yapıldığı motor.
3. **Analiz Katmanı (SafetyModule):** Hesaplanan sonuçları raporlayan ve güvenlik marjını analiz eden birim.

##  Zaman Karmaşıklığı Analizi
- **Eğitim (Training):** O(n) - Veri seti boyutuyla doğru orantılıdır.
- **Tahmin (Prediction):** O(1) - Gerçek zamanlı navigasyon için anlık karar verir.

---
**Geliştiren:** Burak Çavuşoğlu
**Öğrenci No:** 5230505068
**Bölüm:** Yazılım Mühendisliği (3. Sınıf)

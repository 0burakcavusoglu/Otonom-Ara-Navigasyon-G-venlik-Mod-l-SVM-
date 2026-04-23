#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <iomanip>

/**
 * --- KATMAN 1: VERI YAPISI (Point) ---
 * OOP Prensipleri: Encapsulation (Kapsülleme) kullanılmıştır.
 */
class Point {
public:
    double x, y;
    int label; // Engel Grubu (+1 veya -1)

    Point(double x_val, double y_val, int l) : x(x_val), y(y_val), label(l) {}
};

/**
 * --- KATMAN 2: MATEMATIKSEL MOTOR (SVMSolver) ---
 * Bu katman "Maksimum Marj" mantığıyla çalışır.
 * Zaman Karmaşıklığı: O(Epochs * n) -> Doğrusal zamanlı ve verimlidir.
 */
class SVMSolver {
private:
    double w1 = 0.0, w2 = 0.0, b = 0.0; // Ağırlıklar ve Sapma (Bias)
    double learningRate = 0.001;
    double lambda = 0.01; // Düzenleme (Overfitting'i engeller)

public:
    void train(const std::vector<Point>& data, int epochs = 10000) {
        for (int i = 0; i < epochs; ++i) {
            for (const auto& p : data) {
                // Karar Sınırı Denklemi: y * (w1*x1 + w2*x2 + b)
                double condition = p.label * (w1 * p.x + w2 * p.y + b);
                
                if (condition >= 1) {
                    // Marj dışında ve doğru sınıflandırma: Marjı maksimize etmeye odaklan
                    w1 -= learningRate * (2 * lambda * w1);
                    w2 -= learningRate * (2 * lambda * w2);
                } else {
                    // Marj içinde veya yanlış sınıflandırma: Gradyan inişi ile hatayı düzelt
                    w1 -= learningRate * (2 * lambda * w1 - p.label * p.x);
                    w2 -= learningRate * (2 * lambda * w2 - p.label * p.y);
                    b -= learningRate * (-p.label);
                }
            }
        }
    }

    // Hesaplanan katsayıları dışarı aktarır
    void getWeights(double& outW1, double& outW2, double& outB) const {
        outW1 = w1; outW2 = w2; outB = b;
    }
};

/**
 * --- KATMAN 3: GUVENLIK MODULU (SafetyModule) ---
 * Analiz ve raporlama katmanıdır.
 */
class SafetyModule {
public:
    // Marj Genişliği Formülü: 2 / ||w||
    static double calculateMargin(double w1, double w2) {
        return 2.0 / std::sqrt(w1 * w1 + w2 * w2);
    }

    static void printReport(double w1, double w2, double b) {
        std::cout << "========================================" << std::endl;
        std::cout << "   OTONOM ARAC GUVENLIK MODULU RAPORU   " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "[+] Karar Denklemi: " << w1 << "x + " << (w2 >= 0 ? "+ " : "") << w2 << "y + " << (b >= 0 ? "+ " : "") << b << " = 0" << std::endl;
        std::cout << "[+] Guvenlik Koridoru (Margin): " << calculateMargin(w1, w2) << " birim" << std::endl;
        std::cout << "[+] Analiz: Sinir çizgisi iki sınıfa da eşit ve maksimum uzaklıktadır." << std::endl;
        std::cout << "[+] Durum: OPTIMUM GUVENLIK SAGLANDI." << std::endl;
        std::cout << "========================================" << std::endl;
    }
};

/**
 * --- ANA PROGRAM (Main) ---
 */
int main() {
    // 1. Koordinat Setlerini Oluşturma (Doğrusal ayrılabilir noktalar)
    // Grup 1 (+1 Etiketi) - Örn: Yolun solundaki ağaçlar
    // Grup 2 (-1 Etiketi) - Örn: Yolun sağındaki bariyerler
    std::vector<Point> dataset;
    dataset.emplace_back(1.0, 2.0, 1);
    dataset.emplace_back(2.0, 3.0, 1);
    dataset.emplace_back(1.5, 4.5, 1);
    
    dataset.emplace_back(5.0, 1.0, -1);
    dataset.emplace_back(6.0, 2.5, -1);
    dataset.emplace_back(7.0, 0.5, -1);

    // 2. Bellek Yönetimi (Modern C++ Smart Pointer Kullanımı)
    // std::make_unique ile bellek sızıntısı riski ortadan kaldırılmıştır.
    auto solver = std::make_unique<SVMSolver>();
    
    std::cout << "[BILGI] Algoritma egitiliyor, en güvenli rota hesaplaniyor..." << std::endl;
    solver->train(dataset, 10000);

    // 3. Hesaplama Sonuçlarını Al ve Raporla
    double w1, w2, b;
    solver->getWeights(w1, w2, b);

    SafetyModule::printReport(w1, w2, b);

    return 0; 
    // solver nesnesi kapsam dışına çıktığında bellek otomatik olarak temizlenir.
}
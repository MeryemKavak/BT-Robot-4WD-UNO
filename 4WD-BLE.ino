//BLUETOOTH KONTROLLÜ PROJE KODLARI
// -------------------------------------------------------------
// Bluetooth Kontrollü Robot Kodu
// -------------------------------------------------------------
// Platform: Arduino UNO + Sensor Shield V5
// Kontrol: Bluetooth Modülü (HC-05/HC-06)
// Motor Sürücü: L298N
// -------------------------------------------------------------
#include <SoftwareSerial.h>  // Yazılımsal seri iletişim için kütüphane
// --- Pin Tanımlamaları ---
// L298N Motor Sürücü Pinleri
#define ENA 9   // Sol motor hız kontrolü (PWM) - S9
#define ENB 10  // Sağ motor hız kontrolü (PWM) - S10
#define IN1 7   // Sol motor yön 1 - S7
#define IN2 6   // Sol motor yön 2 - S6
#define IN3 5   // Sağ motor yön 1 - S5
#define IN4 4   // Sağ motor yön 2 - S4
// Bluetooth Modülü Pinleri (SoftwareSerial için)
#define BT_RX_PIN 11  // Arduino RX pini (Bluetooth TX'e bağlanır) - S11
#define BT_TX_PIN 12  // Arduino TX pini (Bluetooth RX'e bağlanır) - S12
// --- Ayarlanabilir Parametreler ---
int MOTOR_HIZI = 255;        // Motorların genel hızı (0-255 arası)
#define BLUETOOTH_BAUD 9600  // Bluetooth modülünün baud hızı (Genellikle 9600)
// --- SoftwareSerial Nesnesi ---
SoftwareSerial BTserial(BT_RX_PIN, BT_TX_PIN);  // RX, TX
// --- Değişkenler ---
char komut;  // Bluetooth'tan gelen komutu saklamak için
void setup() {
  // Pin modlarını ayarla
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // Başlangıçta motorları durdur
  motorlariDurdur();
  // Seri iletişimi başlat (Hata ayıklama için - Arduino IDE Seri Monitör)
  Serial.begin(9600);
  Serial.println("Arduino Hazır.");
  Serial.println("Bluetooth Kontrollü Robot");
  // SoftwareSerial (Bluetooth) iletişimini başlat
  BTserial.begin(BLUETOOTH_BAUD);
  Serial.print("Bluetooth Modülü Başlatıldı (Baud: ");
  Serial.print(BLUETOOTH_BAUD);
  Serial.println(")");
  BTserial.println("Robot Kontrole Hazir!");  // Telefona mesaj gönder (opsiyonel)
  ileriGit(MOTOR_HIZI);
  delay(500);
  geriGit(MOTOR_HIZI);
  delay(500);
  ileriGit(MOTOR_HIZI);
  delay(500);
  motorlariDurdur();

}
void loop() {
  // Bluetooth'tan veri gelip gelmediğini kontrol et
  if (BTserial.available() > 0) {
    // Gelen veriyi oku
    komut = BTserial.read();
    // Gelen komutu Seri Monitör'e yazdır (Hata ayıklama için)
    Serial.print("Alinan Komut: ");
    Serial.println(komut);
    // Komuta göre işlem yap
    switch (komut) {
      case 'F':  // İleri (Forward)
      case 'f':
        Serial.println("Hareket: İleri");
        BTserial.println("Hareket: Ileri");  // Telefona geri bildirim
        ileriGit(MOTOR_HIZI);
        break;
      case 'B':  // Geri (Backward)
      case 'b':
        Serial.println("Hareket: Geri");
        BTserial.println("Hareket: Geri");
        geriGit(MOTOR_HIZI);
        break;
      case 'L':  // Sol (Left)
      case 'l':
        Serial.println("Hareket: Sol");
        BTserial.println("Hareket: Sol");
        solaDon(MOTOR_HIZI);
        break;
      case 'R':  // Sağ (Right)
      case 'r':
        Serial.println("Hareket: Sağ");
        BTserial.println("Hareket: Sag");
        sagaDon(MOTOR_HIZI);
        break;
      case 'S':  // Dur (Stop)
      case 's':
        Serial.println("Hareket: Dur");
        BTserial.println("Hareket: Dur");
        motorlariDurdur();
        break;
      case '1': motorHiziniAyarla(25); break;
      case '2': motorHiziniAyarla(50); break;
      case '3': motorHiziniAyarla(75); break;
      case '4': motorHiziniAyarla(100); break;
      case '5': motorHiziniAyarla(125); break;
      case '6': motorHiziniAyarla(150); break;
      case '7': motorHiziniAyarla(175); break;
      case '8': motorHiziniAyarla(200); break;
      case '9': motorHiziniAyarla(225); break;
      case '10': motorHiziniAyarla(255); break;

      default:
        Serial.println("Bilinmeyen Komut!");
        BTserial.println("Bilinmeyen Komut!");
        // Bilinmeyen komut geldiğinde durmak daha güvenli olabilir
         motorlariDurdur();
        break;
    }
  }
  // Başka görevler buraya eklenebilir (eğer gerekirse)
}
// --- Motor Kontrol Fonksiyonları ---
// Motorları ileri yönde hareket ettiren fonksiyon
void ileriGit(int hiz) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, hiz);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, hiz);
}
// Motorları geri yönde hareket ettiren fonksiyon
void geriGit(int hiz) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, hiz);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, hiz);
}
// Robotu sola döndüren fonksiyon (Sağ ileri, Sol geri - Keskin dönüş)
void solaDon(int hiz) {
  digitalWrite(IN1, LOW);  // Sol motor geri
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, hiz);
  digitalWrite(IN3, HIGH);  // Sağ motor ileri
  digitalWrite(IN4, LOW);
  analogWrite(ENB, hiz);
}
// Robotu sağa döndüren fonksiyon (Sol ileri, Sağ geri - Keskin dönüş)
void sagaDon(int hiz) {
  digitalWrite(IN1, HIGH);  // Sol motor ileri
  digitalWrite(IN2, LOW);
  analogWrite(ENA, hiz);
  digitalWrite(IN3, LOW);  // Sağ motor geri
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, hiz);
}
// Motorları durduran fonksiyon
void motorlariDurdur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
// İsteğe bağlı: Hız ayarı için fonksiyon
void motorHiziniAyarla(int yeniHiz) {
  MOTOR_HIZI = yeniHiz;
  Serial.print("Yeni Hız: ");
  Serial.println(MOTOR_HIZI);
  BTserial.print("Yeni Hiz: ");
  BTserial.println(MOTOR_HIZI);
}

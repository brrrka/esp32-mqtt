#include <WiFi.h>
#include <PubSubClient.h>

// Wajib, masukkan ssid dan password wifi yang digunakan dan terhubung ke Raspi
const char* ssid = "ssid";
const char* password = "password";

// IP Server Raspi 
const char* mqtt_server = "RASPI_SERVER_IP"; 

// Jika ada tambahkan
const char* mqtt_username = "username"; 
const char* mqtt_password = "password"; 

// Pin untuk sensor HC-SR04
const int trigPin = 5;
const int echoPin = 18;

WiFiClient espClient;
PubSubClient client(espClient);

// Fungsi callback yang dipanggil saat menerima pesan dari server MQTT
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Pesan diterima di topic: ");
  Serial.print(topic);
  Serial.print(". Pesan: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();
}

// Fungsi untuk menghubungkan ke server MQTT
void connectToMQTT() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke server MQTT...");
    if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
      Serial.println("Terhubung!");
      client.subscribe("test/topic");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" Coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Memulai koneksi Wi-Fi
  Serial.println("Menghubungkan ke Wi-Fi...");
  WiFi.begin(ssid, password);

  // Menunggu hingga ESP32 terhubung ke Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan...");
  }

  // Menampilkan alamat IP setelah berhasil terhubung
  Serial.println("Terhubung ke Wi-Fi!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  // Mengatur server MQTT dan callback
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // Menghubungkan ke server MQTT
  connectToMQTT();

  // Inisialisasi pin sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // handler ESP32
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();

  // Program Utama HCSR 04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2.0) * 0.0344; 

  // Menampilkan hasil di serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Mengirimkan data ke topik MQTT
  String message = String(distance);
  Serial.print("Mengirim pesan: ");
  Serial.println(message);
  client.publish("sensor/distance", message.c_str());

  // Delay sebelum pengukuran berikutnya
  delay(2000);
}

#include <AntaresESP32MQTT.h>

#define ACCESSKEY "******************"       // Ganti dengan access key akun Antares anda
#define WIFISSID "Www"         // Ganti dengan SSID WiFi anda
#define PASSWORD "xyz123456"     // Ganti dengan password WiFi anda

#define applicationName "SmartHome101"   // Ganti dengan application name Antares yang telah dibuat
#define deviceName "Temperature"     // Ganti dengan device Antares yang telah dibuat

AntaresESP32MQTT antares(ACCESSKEY);    // Buat objek antares

void callback(char topic[], byte payload[], unsigned int length) {

  antares.get(topic, payload, length);  // Menyimpan topic dan payload ke penampungan data sementara

  Serial.println("New Message!");
  Serial.println("Topic: " + antares.getTopic());     // Print topic
  Serial.println("Payload: " + antares.getPayload()); // Print payload

  // Print data-data yang telah didapatkan
  Serial.println("Temperature: " + String(antares.getInt("temperature")));
  Serial.println("Humidity: " + String(antares.getInt("humidity")));
  Serial.println("Wind speed: " + String(antares.getFloat("wind_speed")));
  Serial.println("Rain level: " + String(antares.getFloat("rain_level")));
  Serial.println("Latitude: " + antares.getString("latitude"));
  Serial.println("Longitude: " + antares.getString("longitude"));
}

void setup() {
  Serial.begin(115200);     // Buka komunikasi serial dengan baudrate 115200
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);  // Mencoba untuk menyambungkan ke WiFi
  antares.setMqttServer();  // Inisiasi server MQTT Antares
  antares.setCallback(callback);  // Set fungsi callback menjadi fungsi callback seperti di atas
}
void loop() {
  /*
    Cek koneksi ke broker MQTT Antares. Jika disconnect,
    akan dicoba untuk menyambungkan lagi
   */
  antares.checkMqttConnection();
}

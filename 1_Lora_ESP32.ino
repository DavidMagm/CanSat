#include <SPI.h>
#include <LoRa.h>

// Pines sugeridos para ESP32
#define NSS 5
#define RST 14
#define DIO0 2

int counter = 0;

void setup() {
  Serial.begin(115200);
  LoRa.setPins(NSS, RST, DIO0);
  
  if (!LoRa.begin(433E6)) { // Ajusta a la frecuencia de tu módulo (433E6, 868E6, 915E6)
    Serial.println("Error al iniciar LoRa!");
    while (1);
  }
  Serial.println("LoRa Emisor listo.");
}

void loop() {
  Serial.print("Enviando paquete: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("Hola LoRa ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  delay(2000);
}

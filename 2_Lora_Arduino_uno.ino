#include <SPI.h>
#include <LoRa.h>

// Pines para Arduino Uno
#define NSS 10
#define RST 9
#define DIO0 2

const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  LoRa.setPins(NSS, RST, DIO0);
  
  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa!");
    while (1);
  }
  Serial.println("LoRa Receptor listo.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    digitalWrite(ledPin, HIGH); // Enciende LED al recibir
    
    Serial.print("Recibido: '");
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.print("' con RSSI: ");
    Serial.println(LoRa.packetRssi());
    
    delay(200);
    digitalWrite(ledPin, LOW);
  }
}

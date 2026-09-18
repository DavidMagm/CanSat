#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

float presionSuelo = 0.0;  // hPa (referencia para altitud relativa)

void setup() {
  Serial.begin(115200);

  // Paso 1: Forzar comunicación I2C en los pines del ESP32 (SDA=21, SCL=22)
  Wire.begin(21, 22);

  delay(1000);  // Pausa para estabilización de energía
  Serial.println("\n----------------------------------------------");
  Serial.println("MONITOR CONECTADO.");

  // Paso 2: Inicializar AHT20 (humedad y temperatura), dirección 0x38
  if (!aht.begin()) {
    Serial.println("¡ERROR! AHT20 no encontrado en I2C.");
    Serial.println("Verifica la dirección 0x38 y las conexiones SDA/SCL.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("AHT20 Encontrado.");

  // Paso 3: Inicializar BMP280 (presión). Combos baratos suelen usar 0x76; Adafruit 0x77
  if (!bmp.begin(0x76) && !bmp.begin(0x77)) {
    Serial.println("¡ERROR! BMP280 no encontrado en I2C.");
    Serial.println("Verifica si la dirección es 0x76 o 0x77 y las conexiones.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("BMP280 Encontrado.");

  Serial.println("Coloca el CanSat en el suelo. Calibrando en 3 segundos...");
  delay(3000);

  // Paso 4: Promedio de 20 lecturas para fijar la presión de referencia (Pa -> hPa)
  float suma = 0;
  for (int i = 0; i < 20; i++) {
    suma += bmp.readPressure();
    delay(50);
  }
  presionSuelo = (suma / 20.0) / 100.0;

  Serial.print("Presión de referencia guardada: ");
  Serial.print(presionSuelo);
  Serial.println(" hPa");
  Serial.println("INICIANDO REGISTRO DE VUELO...");
  Serial.println("----------------------------------------------");
  delay(1000);
}

void loop() {
  sensors_event_t humedad, temperatura;
  aht.getEvent(&humedad, &temperatura);

  float presionActual = bmp.readPressure();  // Pa
  float alturaActual = bmp.readAltitude(presionSuelo);

  // Filtro básico para lecturas cercanas a cero en el suelo
  if (alturaActual > -0.5 && alturaActual < 0.5) {
    alturaActual = 0.0;
  }

  Serial.print("ALTURA_RELATIVA: ");
  Serial.print(alturaActual, 2);
  Serial.print(" m | PRESION: ");
  Serial.print(presionActual, 0);
  Serial.print(" Pa | TEMP: ");
  Serial.print(temperatura.temperature, 1);
  Serial.print(" °C | HUMEDAD: ");
  Serial.print(humedad.relative_humidity, 1);
  Serial.println(" %");

  delay(200);  // Muestra lecturas 5 veces por segundo
}

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

// Intentaremos con la dirección estándar 0x68 primero. 
// Si falla, cambia el 0x68 por 0x69 abajo.
MPU6050 sensor(0x68);

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  Serial.begin(115200);
  
  // Paso 1: Iniciar I2C con pines específicos para ESP32
  Wire.begin(21, 22); 
  Wire.setClock(400000); // 400kHz para comunicación rápida
  
  delay(2000); // Pausa para que el voltaje se estabilice (evita el Brownout)
  Serial.println("\n--- INICIANDO SISTEMA DE PRUEBA ---");
  
  // Paso 2: Inicializar y FORZAR el encendido
  sensor.initialize();
  sensor.setSleepEnabled(false); // <--- ESTO ES VITAL
  
  // Paso 3: Verificación real
  if (sensor.testConnection()) {
    Serial.println("EXITO: MPU6050 encontrado y despertado");
  } else {
    Serial.println("ERROR: El sensor no responde. Revisar:");
    Serial.println("- ¿AD0 está a GND? (Usa 0x68)");
    Serial.println("- ¿AD0 está a 3.3V? (Usa 0x69)");
    Serial.println("- ¿Los cables SDA/SCL están cruzados?");
  }
}

void loop() {
  // Usamos getMotion6 para leer todo en un solo viaje del bus I2C (más eficiente)
  sensor.getAcceleration(&ax, &ay, &az);

  // Convertir valores en bruto a Fuerzas G (dividiendo por la escala 16384.0)
  float gX = ax / 16384.0;
  float gY = ay / 16384.0;
  float gZ = az / 16384.0;

  // Imprimir únicamente los 3 datos requeridos
  Serial.print("G-X: "); Serial.print(gX, 2); Serial.print(" G | ");
  Serial.print("G-Y: "); Serial.print(gY, 2); Serial.print(" G | ");
  Serial.print("G-Z: "); Serial.print(gZ, 2); Serial.println(" G");

  delay(200); 
}
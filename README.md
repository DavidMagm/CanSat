# Proyecto CanSat

Satélite en botella (CanSat) del **Proyecto Integrador 2026-2**, Programa de Tecnología en Electrónica Industrial, Institución Universitaria Antonio José Camacho.

El prototipo se libera desde un drone, mide variables físicas durante el descenso, transmite la telemetría y despliega el paracaídas de forma autónoma antes del aterrizaje. En cuarto semestre se evoluciona ese sistema con interfaz de usuario, modos de operación, indicadores y acondicionamiento electrónico, sin perder las funciones del semestre anterior.

## Qué se quiere lograr

**Objetivo general:** evolucionar el CanSat con interacción, visualización, automatización y acondicionamiento electrónico, de modo que sea un sistema más completo e integrado.

**Objetivos específicos:**

1. Interfaz de usuario para elegir modos de operación y ver variables y estados (entradas y salidas).
2. Lógica secuencial que automatice el comportamiento según el modo seleccionado.
3. Circuitos de acondicionamiento, protección y adaptación para los dispositivos nuevos, con pruebas de funcionamiento.

## Variables a medir

Durante el vuelo y en tierra se adquieren, como mínimo:

| Variable    | Uso típico                                      |
| ----------- | ----------------------------------------------- |
| Temperatura | Ambiente / interior del CanSat                  |
| Presión     | Ambiente; base para altitud relativa            |
| Humedad     | Ambiente                                        |

El firmware actual usa el combo **AHT20 + BMP280** (humedad y temperatura en el AHT20; presión y altitud relativa en el BMP280). Otras magnitudes del prototipo previo (por ejemplo aceleración con MPU6050) pueden seguir presentes según el hardware montado.

## Modos de operación

La selección se hace con teclado matricial o pulsadores. Hay **cinco modos**:

1. Medición y visualización de **temperatura**.
2. Medición y visualización de **presión**.
3. Medición y visualización de **humedad**.
4. Visualización **simultánea** de todas las variables medidas.
5. **Diagnóstico** o prueba: sensores, visualización e indicadores.

Además se exigen indicadores luminosos y sonoros, circuitos de protección/adaptación y, en la demostración final, liberación desde drone, telemetría en descenso y despliegue autónomo del paracaídas.

## Nota técnica: ubicación de la pantalla

La pantalla LCD (o equivalente) **no es obligatorio que vaya a bordo del satélite**. Puede ir:

- **En el CanSat**, si el peso, el volumen y la alimentación lo permiten.
- **En la estación de tierra**, mostrando lo que llega por radio (LoRa u otro enlace), que es la opción más práctica en vuelo.

Lo que sí debe cumplirse es que el usuario pueda ver variables, mensajes y estados según el modo elegido. La interfaz (teclado/pulsadores y pantalla) puede residir total o parcialmente en tierra, siempre que los cinco modos y el diagnóstico queden demostrables.

## Firmware en este repositorio

Sketches Arduino independientes (cada `.ino` debe estar en una carpeta con el mismo nombre para `arduino-cli`):

- `1_Barometro_calibracion_AHT20BMP280.ino` — calibración de presión de suelo y lectura de humedad, temperatura, presión y altitud relativa.
- `1_Medidas_sin_procesar.ino` — aceleración cruda MPU6050.
- `1_Lora_ESP32.ino` — transmisor LoRa (ESP32).
- `2_Lora_Arduino_uno.ino` — receptor LoRa (Arduino Uno), imprime RSSI.

Comentarios y salida Serial en español. I2C del ESP32: SDA = GPIO21, SCL = GPIO22.

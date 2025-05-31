# Sistema de Aquisição de Dados com ESP32

Este projeto implementa um sistema de aquisição de dados utilizando um **ESP32**, integrando sensores ambientais e de movimento, além de GPS e armazenamento em cartão SD. É ideal para aplicações embarcadas em foguetes, drones ou sistemas móveis que exigem coleta e registro de dados em tempo real.

---

## Arquitetura do Sistema

### Sensores Utilizados

| Sensor         | Função                            | Interface | Pino(s)         |
|----------------|------------------------------------|-----------|-----------------|
| **BME280**     | Temperatura, umidade, pressão     | I2C       | GPIO 21 (SDA), GPIO 22 (SCL) |
| **ADXL375**    | Aceleração 3 eixos                | I2C       | GPIO 21 (SDA), GPIO 22 (SCL) |
| **GPS (TinyGPS++)** | Localização via satélite    | UART      | RX: GPIO 16, TX: GPIO 17     |
| **Botão de Start** | Inicialização manual do sistema | Digital   | GPIO 4           |
| **Buzzer**     | Sinal sonoro de feedback          | Digital   | (definir no `initPorts`)    |
| **Cartão SD**  | Armazenamento dos dados           | SPI       | (definir pinos no hardware) |

---

## Funcionalidades

### Inicialização
- **Calibração automática** do acelerômetro ADXL375.
- Leitura da altitude de referência com o BME280.

### Loop Principal
- Leitura de dados dos sensores (aceleração, pressão, temperatura, umidade e GPS).
- Cálculo da aceleração absoluta para detectar eventos com base em threshold.
- Escrita contínua em arquivo de texto no cartão SD: `/data_Clustril.txt`.

---

## Estrutura de Código

### `main.cpp`
- Inicializa sensores e interfaces.
- Realiza a lógica principal de coleta e gravação dos dados.

### `sensors.h` e `sensors.cpp`
- Funções auxiliares para leitura e calibração de sensores.
- Cálculo da aceleração corrigida.
- Interação com o GPS (TinyGPSPlus).

### `general_use.h`
- Definições gerais, estruturas de dados e pinos utilizados.

---

## Formato dos Dados no SD

Os dados são gravados no formato texto com separação entre os campos, contendo:

- Aceleração (X, Y, Z)
- Temperatura (°C)
- Pressão (Pa)
- Umidade (%)
- Latitude e Longitude (GPS)

---

## Compilação com PlatformIO

Utilize o seguinte `platformio.ini` para configurar corretamente o ambiente de desenvolvimento com PlatformIO:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_speed = 921600

lib_deps =
    adafruit/Adafruit BME280 Library@^2.2.2
    adafruit/Adafruit Unified Sensor@^1.1.9
    adafruit/Adafruit ADXL375 Library@^1.0.5
    mikalhart/TinyGPSPlus@^1.0.3

build_flags =
    -DCORE_DEBUG_LEVEL=0
    -DDEBUG_DISABLED

board_build.flash_mode = dio
board_build.partitions = default_16MB.csv

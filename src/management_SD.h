#ifndef MANAGEMENT_SD_H
#define MANAGEMENT_SD_H

// Bibliotecas para SD
#include "FS.h"
#include "SD.h"


// Definições do SD
#define SD_CS 5
// SD_MOSI 11
// SD_SCLK 12
// SD_MISO 13


/**
 * @brief Estrutura de dados para armazenar informações de sensores e status para o SD e enviar pelo LoRa.
 *
 * Esta estrutura é usada para coletar e armazenar vários tipos de dados de diferentes sensores e 
 * indicadores de status. Destina-se ao uso para registro de dados em um cartão SD e envio via LoRa.
 * 
 * A estrutura contém os seguintes campos:
 * 
 * - **Dados do BME280**:
 *   - `temperature`: Leitura de temperatura do sensor BMP390 (em graus Celsius).
 *   - `pressure`: Leitura de pressão do sensor BMP390 (em Pascal).
 *   - `altitude`: Altitude calculada a partir do sensor BMP390 (em metros).
 *  - `humidity`: Leitura de umidade do sensor BME280 (em %).
 * 
 * - **Dados do ADXL375**:
 *   - `adxl_ax`: Aceleração no eixo X do sensor ADXL375 (em m/s²).
 *   - `adxl_ay`: Aceleração no eixo Y do sensor ADXL375 (em m/s²).
 *   - `adxl_az`: Aceleração no eixo Z do sensor ADXL375 (em m/s²).
 * 
 * - **Dados do GPS**:
 *   - `latitude`: Leitura de latitude do sensor GPS (em graus).
 *   - `longitude`: Leitura de longitude do sensor GPS (em graus).
 */
#pragma pack(1)
typedef struct ClustrilData {
    // Dados do BME_1
    float temperature_1;
    float pressure_1;
    float altitude_1;
    float humidity_1;

    // Dados do Acelerômetro
    float accel_ax;
    float accel_ay;
    float accel_az;

    // Dados do GPS
    double lat;
    double lon;
} clustril_data_t;
#pragma pack()


void WriteToSD(fs::FS &fs, clustril_data_t *SDdata, const char *path, bool SDstatus);

bool checkSD(fs::FS &fs);


#endif // MANAGEMENT_SD_H
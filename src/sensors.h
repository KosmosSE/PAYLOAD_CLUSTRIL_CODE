#ifndef SENSORS_H
#define SENSORS_H

// Bibliotecas para os sensores
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <TinyGPSPlus.h>
#include <Adafruit_ADXL375.h>
#include "general_use.h"
#include "management_SD.h"
#include <Adafruit_BME280.h>

//Conexoes adxl375 3.3v -> vs ; 3.3 -> cs ; sdo -> gnd ;

// Endereços I2C dos sensores

#define ADXL_I2C 0x53

#define BME_I2C 0x76

// Constantes de Baudrate
#define GPS_BAUD 9600

//Função de Inicialização sensores I2C
bool initI2CSensors(Adafruit_BME280 &bme_1, Adafruit_ADXL375 &adxl);

//Função de Inicialização sensores UART
bool InitUARTSensors(HardwareSerial &gpsSerial);

//Leitura dos dados de Pressão e Temperatura dos BME'S
void readPressureAndTemperatureAndHumidityBME(Adafruit_BME280 *bme_1 , clustril_data_t *SDdata) ;

//Leitura dos dados de altitude dos BME'S
void readAltitudeBarometers(Adafruit_BME280 *bmp_1, clustril_data_t *SDdata);

//Leitura dos dados da aceleração do ADXL375
void readAcceleration(Adafruit_ADXL375 *adxl, clustril_data_t *SDdata,float calibAdxl[3]);

//Função de calibração da aceleração do ADXL375
void AccelCalibration(Adafruit_ADXL375 *adxl, float adxl_calib[3], int n);

//Leitura dos dados do GPS
void readGPS(TinyGPSPlus &gps, clustril_data_t *SDdata, HardwareSerial &SerialGPS);

#endif // SENSOR_H
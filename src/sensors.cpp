#include "sensors.h"
#include "general_use.h"

bool initI2CSensors(Adafruit_BME280 &bme_1, Adafruit_ADXL375 &adxl) {
    // Inicializa os Barômetros
    if (!bme_1.begin(BME_I2C)) {
        Serial.println("Erro: Falha ao iniciar BME280");
        return false;
    }

    bme_1.setSampling(
        Adafruit_BME280::MODE_NORMAL,          // Modo de operação contínuo
        Adafruit_BME280::SAMPLING_X2,          // Oversampling da temperatura (2X)
        Adafruit_BME280::SAMPLING_X16,         // Oversampling da pressão (16X)
        Adafruit_BME280::SAMPLING_X16,         // Oversampling da umidade (16X)
        Adafruit_BME280::FILTER_X16,           // Coeficiente do filtro IIR
        Adafruit_BME280::STANDBY_MS_0_5        // Taxa de atualização (aproximadamente 200 Hz)
    );

    // Inicializa o Acelerômetro
    if (!adxl.begin(ADXL_I2C)) {
        Serial.println("Erro: Falha ao iniciar ADXL375");
        return false;
    }

    return true;
}

bool InitUARTSensors(HardwareSerial &gpsSerial) {
    // Inicializa o GPS
    gpsSerial.begin(GPS_BAUD);

    while (!gpsSerial){
        //    Serial.println("Erro: Falha ao iniciar GPS");
        delay(10);
    }
   
    return true;
}

void readPressureAndTemperatureAndHumidityBME(Adafruit_BME280 *bme_1 , clustril_data_t *SDdata) {

    SDdata->pressure_1 = bme_1->readPressure();
    SDdata->temperature_1 = bme_1->readTemperature();
    SDdata->humidity_1 = bme_1->readHumidity();
}

void readAltitudeBarometers(Adafruit_BME280 *bme_1, clustril_data_t *SDdata) {

    SDdata->altitude_1 = bme_1->readAltitude(SeaLevelHpa);
}

void readGPS(TinyGPSPlus &gps, clustril_data_t *SDdata, HardwareSerial &SerialGPS){
      // Lê os dados do GPS
    while (SerialGPS.available() > 0) {
        gps.encode(SerialGPS.read());
      }
    
      if (gps.location.isUpdated()) {
        SDdata->lat = gps.location.lat();
        SDdata->lon = gps.location.lng();
        Serial.print("Lat: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Lng: ");
        Serial.println(gps.location.lng(), 6);
        Serial.print("Satélites: ");
        Serial.println(gps.satellites.value());
        Serial.println("-----");
      }

}

void readAcceleration(Adafruit_ADXL375 *adxl, clustril_data_t *SDdata,float calibAdxl[3]) {
  
    sensors_event_t adxlEvent;

    adxl->getEvent(&adxlEvent);
    
    //Accelerometer data from ADXL375
    SDdata->accel_ax = adxlEvent.acceleration.x - calibAdxl[0];
    SDdata->accel_ay = adxlEvent.acceleration.y - calibAdxl[1];
    SDdata->accel_az = adxlEvent.acceleration.z - calibAdxl[2];

}

void AccelCalibration(Adafruit_ADXL375 *adxl,float adxl_calib[3], int n) {
   
  float sumx = 0;
  float sumy = 0;
  float sumz = 0;
 
  sensors_event_t event;

  for(int i = 0; i<n; i++) {

    adxl->getEvent(&event);
    
    sumx += event.acceleration.x;
    sumy += event.acceleration.y;
    sumz += event.acceleration.z;
    
    }

    float calib_x = sumx/n;
    float calib_y = sumy/n;
    float calib_z = sumz/n;

    adxl_calib[0] = calib_x;
    adxl_calib[1] = calib_y;
    adxl_calib[2] = calib_z;
    
}
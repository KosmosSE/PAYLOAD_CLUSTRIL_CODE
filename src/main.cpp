// Biblioteca Para Uso Geral
#include "general_use.h"
#include "sensors.h"

// Variáveis Globais

Altitude altBar1(0, 0, 0); // Estrutura para manipular e calibrar dados de altitude do BME 1

bool systemStarted = false;

clustril_data_t SDdata; // Estrutura para armazenar dados de sensores e status
bool FirstTime = true;  // Flag para verificar se é o primeira parada no timelock
// Intanciando objetos dos sensores

Adafruit_BME280 bme_1; // Barometro 1

Adafruit_ADXL375 adxl(ADXL_I2C); // ADXL375

TinyGPSPlus gps; // GPS

HardwareSerial gpsSerial(2); // Serial para o GPS

// dados de aceleração
float adxl_ax, adxl_ay, adxl_az; // aceleração em x, y e z do ADXL375p
float adxl_calib[3] = {0, 0, 0}; // valores de calibração da aceleração do ADXL375
double adxl_abs_accel;           // aceleração absoluta

static unsigned long previousMillisBME = millis(), currentMillis;

void setup()
{
  Serial.begin(BAUDRATE); // Inicializa a comunicação serial para o monitor serial
  while (!Serial)
    delay(10); // Aguarda o monitor serial ser conectado

  initI2CSensors(bme_1, adxl); // Inicializa todos os sensores I2C

  pinMode(buttonPin, INPUT_PULLUP);

  InitUARTSensors(gpsSerial); // Inicializa todos os sensores UART
  initPorts();                // Inicializa todos os pinos usados no sistema

  // BuzzerSound(); //Toca o buzzer para indicar que o sistema iniciou com sucesso

  AccelCalibration(&adxl, adxl_calib, 1000); // Calibra o ADXL375

  // Calibra a altitude do BME 1
  altBar1.setBarCalibration(bme_1.readAltitude(SeaLevelHpa)); // Calibra a altitude do barometro 1
}

void loop()
{

  if (!systemStarted)
  {
    if (digitalRead(buttonPin) == LOW)
    { // Pressionado (com PULLUP)
      systemStarted = true;
      Serial.println("Botão pressionado. Sistema iniciado.");
      delay(500); // Debounce
    }
    else
    {
      return; // Sai do loop até botão ser pressionado
    }
  }

  // Parte da utilização dos dados do adxl375 para possível TimeLock-----------------------------------------------------

  readAcceleration(&adxl, &SDdata, adxl_calib); // Leitura dos dados de aceleração do ADXL375

  adxl_abs_accel = sqrt(SDdata.accel_ax * SDdata.accel_ax + SDdata.accel_ay * SDdata.accel_ay + SDdata.accel_az * SDdata.accel_az); // Cálculo da aceleração absoluta para o TimeLock

  bool checkAdxlLockReturn = AdxlLock(adxl_abs_accel); // Verificação da aceleração para o AdxlLock

  if (checkAdxlLockReturn)
  { // Se a aceleração for maior que o limite, o AdxlLock será ativado
  }
  //-------------------------------------------------------------------------------------------------------------------
  // Parte do SD--------------------------------------------------------------------------------------------------------

  readPressureAndTemperatureAndHumidityBME(&bme_1, &SDdata); // Leitura da pressão e temperatura do barometro 1

  bool CheckSDReturn = checkSD(SD); // Verifica se o cartão SD está conectado

  readGPS(gps, &SDdata, gpsSerial); // Leitura dos dados de GPS

  WriteToSD(SD, &SDdata, "/data.txt", CheckSDReturn); // Escreve os dados no cartão SD7
  delay(40);

  //-------------------------------------------------------------------------------------------------------------------
}
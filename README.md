Clustril - Sistema de Aquisição de Dados com ESP32
Este projeto implementa um sistema embarcado com ESP32 para aquisição e registro de dados ambientais e de movimento. Os sensores utilizados são o barômetro BME280, o acelerômetro ADXL375 e um módulo GPS. Os dados são processados e salvos em um cartão SD para posterior análise.

Pinos Utilizados
Função	Componente	Pino ESP32
SDA (I2C)	BME280, ADXL375	GPIO 21
SCL (I2C)	BME280, ADXL375	GPIO 22
RX (UART2)	GPS	GPIO 16
TX (UART2)	GPS	GPIO 17
Botão de inicialização	Entrada digital	GPIO 4 (exemplo)
SPI (SD Card)	Cartão SD	Definido na biblioteca SD (ex: GPIO 5, 18, 19, 23)*

*A configuração exata dos pinos do cartão SD depende do modelo de placa e da biblioteca utilizada. Ajuste conforme seu hardware.

Componentes Principais
ESP32

Barômetro BME280

Acelerômetro ADXL375

Módulo GPS (compatível com TinyGPS++)

Cartão SD

Botão físico (start manual)

Funcionalidades
Inicialização de sensores I2C e UART

Calibração automática do acelerômetro

Cálculo da aceleração absoluta (norma do vetor aceleração)

Cálculo e calibração de altitude via BME280

Leitura de dados de GPS

TimeLock baseado em aceleração (evento de alta aceleração)

Escrita de dados estruturados no cartão SD

Sistema inicia apenas após acionamento do botão

Fluxo de Execução
Sistema aguarda o pressionamento do botão de inicialização.

Ao iniciar:

Calibra o acelerômetro (média de 1000 leituras).

Lê altitude inicial e define como referência.

No loop principal:

Leitura de aceleração (com compensação de calibração).

Verificação de evento por aceleração absoluta (TimeLock).

Leitura de pressão, temperatura e umidade.

Leitura de dados GPS (se disponíveis).

Escrita dos dados no cartão SD.

Estrutura dos Arquivos
main.cpp: lógica principal do sistema.

sensors.h/.cpp: funções para manipulação e leitura dos sensores.

general_use.h: definições gerais, tipos de dados e macros.

Formato de Dados Gravados
Os dados são salvos no arquivo /data_Clustril.txt, com formato estruturado. Exemplo de colunas:

sql
Copiar
Editar
timestamp, pressure_1, temperature_1, humidity_1, altitude_1, accel_ax, accel_ay, accel_az, accel_abs, lat, lon
Dependências
Adafruit BME280

Adafruit Sensor

Adafruit ADXL375

TinyGPS++

Biblioteca SD padrão do ESP32/Arduino

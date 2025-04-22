#include "management_SD.h"

void WriteToSD(fs::FS &fs, clustril_data_t *SDdata, const char *path, bool SDstatus) {
    if (!SDstatus) {
        Serial.println("Failed to connect to the SD card");
        return;
    }
    
    File file = fs.open(path, FILE_APPEND);
    if (!file) {
        Serial.println("Failed to open file for appending");
        return;
    }
    
    // Check if file is empty and write headers if needed
    if (file.size() == 0) {
        file.println("Temperatura_1 (°C),Pressão_1 (Pa),Altitude_1 (m), Umidade_1 (%), accel_ax (m/s^2), accel_ay (m/s^2), accel_az (m/s^2), Latitude, Longitude");
    }
    
    // Write sensor data in CSV format
    file.print(SDdata->temperature_1);
    file.print(",");
    file.print(SDdata->pressure_1);
    file.print(",");
    file.print(SDdata->altitude_1);
    file.print(",");
    file.print(SDdata->humidity_1);
    file.print(",");

    file.print(SDdata->accel_ax);
    file.print(",");
    file.print(SDdata->accel_ay);
    file.print(",");
    file.print(SDdata->accel_az);
    file.print(",");

    file.print(SDdata->lat);
    file.print(",");
    file.print(SDdata->lon);
    file.print(",");

    file.print("\n");
    
    file.close();
  }

  bool checkSD(fs::FS &fs){
    Serial.println("SD CARD Test");               // Print a message indicating the start of the SD card test

    if (!SD.begin(SD_CS)){                       // Attempt to initialize the SD card
        Serial.println("Card Mount Failed");      // Print an error message if the card mount fails
        return false;
    }
    else {
        Serial.println("SD module found");        // Print a success message if the SD module is found
    }

    uint8_t cardType = SD.cardType();             // Get the type of the SD card

    Serial.print("SD Card Type: ");               // Print a message indicating the type of SD card

    if (cardType == CARD_NONE) {                  // Check if no SD card is attached
        Serial.println("No SD card attached");    // Print an error message if no card is attached
        return false;
    }

    else if (cardType == CARD_MMC) {
        Serial.println("MMC");                    // Print "MMC" if the card type is MMC
    } 
    
    else if (cardType == CARD_SD) {
        Serial.println("SDSC");                   // Print "SDSC" if the card type is SDSC
    } 
    
    else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");                   // Print "SDHC" if the card type is SDHC
    } 
    
    else {
        Serial.println("UNKNOWN");                // Print "UNKNOWN" if the card type is unknown
    }
    return true;
}
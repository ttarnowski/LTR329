#include "LTR329ALS01.h"
#include <stdio.h>

#define I2C_SDA 25
#define I2C_SCL 26

LTR329ALS01 ltr329(I2C_SDA, I2C_SCL); 

void setup()
{
    Serial.begin(115200); 

    // Start LTR329
    ltr329.begin(); 
    Serial.println("[LTR329] begin. "); 

    char tempString[64] = {}; 
    Serial.print(""); 
    sprintf(tempString, "[LTR329] MANUFAC ID: 0x%02x", ltr329.readManufacturerId()); 
    Serial.println(tempString); 
    sprintf(tempString, "[LTR329] PART NUMBER: 0x%02x", ltr329.readPartNumber()); 
    Serial.println(tempString); 
    Serial.print("[LTR329] STATUS REG: 0b"); 
    Serial.println(ltr329.readStatus().raw, BIN); 

    ltr329.writetControl(true, LTR329ALS01_ALS_GAIN_x8); 
    Serial.print("[LTR329] CTRL REG: 0b"); 
    Serial.println(ltr329.readControl().raw, BIN); 

    ltr329.writeMeasRate(LTR329ALS01_ALS_INT_100ms, LTR329ALS01_ALS_RATE_500ms); 
    Serial.print("[LTR329] MEAS REG: 0b"); 
    Serial.println(ltr329.readMeasRate().raw, BIN); 
}

void loop()
{
    float lux; 
    lux = ltr329.readLux(); 
    Serial.print("[LTR329] Lux: "); 
    Serial.println(lux); 
}

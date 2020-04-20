//RF TX - ATTiny85
#define DHTPIN 4
#define DHTTYPE DHT11
#define READINGS_INTERVAL 10000

#include <ArduinoUniqueID.h>
#include "DHT.h"

DHT dht(DHTPIN, DHTTYPE);
int LAST_READ=0;

typedef struct RFData{
  byte id[9];
  byte timestamp;
  byte temperature;
  byte umidity;
}RFData;

RFData PKG;
RFData LAST_PKG;
int PKG_SIZE=sizeof(struct RFData);

void loadID(){
  for (size_t i = 0; i < UniqueIDsize; i++){
    PKG.id[i]=UniqueID[i];
  }  
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  loadID();
}
void loop() {
  if(((int)millis()-LAST_READ) > READINGS_INTERVAL){
    PKG.timestamp=(uint8_t)millis();
    PKG.temperature=(uint8_t)dht.readTemperature(); 
    PKG.umidity=(uint8_t)dht.readHumidity();
    Serial.write((const char*)&PKG, PKG_SIZE);  
    LAST_READ=(int)millis();     
  }
/* ADICIONAR RX NO SENSOR
  RFData inputPKG;
  if(Serial.available()){
    Serial.readBytes((char*)&input, sizeof(RFData));
    for(int i=0; i < 9; i++){ 
      if(input.id[i] < 0x10)
        Serial.print("0");
      Serial.print(input.id[i],HEX);
      if(i < 8)
        Serial.print(":"); 
    }
*/
}

  

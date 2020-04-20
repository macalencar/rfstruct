//RF RX - Arduino UNO
#include<SoftwareSerial.h>
SoftwareSerial HC12 = SoftwareSerial(2,3);

typedef struct RFData{
  byte id[9];
  byte timestamp;
  byte temperature;
  byte umidity;
}RFData;

RFData PKG;
int PKG_SIZE=sizeof(struct RFData);

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
}
void loop() {
  RFData input;
  if(HC12.available()){
    HC12.readBytes((char*)&input, sizeof(RFData));
    for(int i=0; i < 9; i++){ 
      if(input.id[i] < 0x10)
        Serial.print("0");
      Serial.print(input.id[i],HEX);
      if(i < 8)
        Serial.print(":"); 
    }
    Serial.print(";");
    Serial.print(input.timestamp);
    Serial.print(";");
    Serial.print(input.temperature,DEC);
    Serial.print(";");
    Serial.print(input.umidity,DEC);
    Serial.println(";");
  }
}  

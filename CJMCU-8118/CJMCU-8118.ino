#include "HDC1080JS.h"
#include "Wire.h"
HDC1080JS tempsensor;

#include "Adafruit_CCS811.h"
Adafruit_CCS811 ccs;

void setup() {
  if (!ccs.begin()) {
    Serial.println("Failed to start sensor! Please check your wiring.");
    while (1);
  }

  // Wait for the sensor to be ready
  while (!ccs.available());


  Wire.begin();
  Wire.setClock(400000); //set clock speed for I2C bus to maximum allowed for HDC1080
  Serial.begin(9600);  // start serial for output

  tempsensor = HDC1080JS();
  tempsensor.config();


}

void loop() {
  if (ccs.available()) {
    if (!ccs.readData()) {
      Serial.print("CO2: ");
      Serial.println(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
      tempsensor.readTempHumid();
      float temp = tempsensor.getTemp();
      float humid = tempsensor.getRelativeHumidity();

      Serial.print("T=");
      Serial.print(temp);
      Serial.print("C, RH=");
      Serial.print(humid);
      Serial.println("%");
    }
    else {
      Serial.println("ERROR!");
      while (1);
    }
  }
  delay(500);
  // put your main code here, to run repeatedly:

}

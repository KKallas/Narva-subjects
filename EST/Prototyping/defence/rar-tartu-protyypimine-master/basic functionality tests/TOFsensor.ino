#include <Wire.h>
#include <VL53L1X.h>

#define I2C_SDA 23
#define I2C_SCL 21

VL53L1X sensor;

void scanI2C()
{
  Serial.println();
  Serial.println("Scanning I2C bus...");

  int found = 0;

  for (uint8_t address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Found I2C device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      found++;
    }
  }

  if (found == 0)
  {
    Serial.println("No I2C devices found.");
  }

  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("VL53L1X standalone TOF test");
  Serial.print("SDA = G");
  Serial.println(I2C_SDA);
  Serial.print("SCL = G");
  Serial.println(I2C_SCL);

  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);

  scanI2C();

  sensor.setTimeout(500);

  if (!sensor.init())
  {
    Serial.println("VL53L1X init FAILED.");
    Serial.println("Expected sensor at I2C address 0x29.");
    Serial.println("Check SDA/SCL order, common GND, power, and pullups/level shifting.");
    while (true)
    {
      delay(1000);
    }
  }

  Serial.println("VL53L1X init OK.");

  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000); // 50 ms
  sensor.startContinuous(50);               // read every ~50 ms

  Serial.println("Starting distance readings...");
}

void loop()
{
  uint16_t distance_mm = sensor.read();

  if (sensor.timeoutOccurred())
  {
    Serial.println("Sensor timeout.");
  }
  else
  {
    Serial.print("Distance: ");
    Serial.print(distance_mm);
    Serial.println(" mm");
  }

  delay(100);
}
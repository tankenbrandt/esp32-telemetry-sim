/*
 transmitter  -> ESP32 + MPU6050 + BME280 + LoRa
 1. Reads accel, gyro from MPU6050
 2. reads temp, pressure, humidity from BME280
 3. Sends CSV string via LoRa @ 915 MHz
 *  ▸ Prints everything to Serial for local debug
 */

#include <Wire.h>
#include <SPI.h>    // i2c and spi comms
#include <LoRa.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>    //sensor setup
#include <Adafruit_BME280.h>

Adafruit_MPU6050  mpu;    //create sensor objecst
Adafruit_BME280   bme;

constexpr uint8_t I2C_SDA = 21; // GPIO 21 data line 
constexpr uint8_t I2C_SCL = 22; // GPIO 22 clock

constexpr uint8_t LORA_CS   = 4;   // chip select
constexpr uint8_t LORA_RST  = 25;   // reset 
constexpr uint8_t LORA_IRQ  = 26;   // interrupt
constexpr uint8_t LORA_SCK  = 18;   
constexpr uint8_t LORA_MISO = 19;
constexpr uint8_t LORA_MOSI = 23;
constexpr long    LORA_FREQ_HZ = 915E6;

void setup()
{
  Serial.begin(115200); //begin serial transmission
  delay(200);
  Serial.println("\nLoRa TX booting... ");

  Wire.begin(I2C_SDA, I2C_SCL);

  if (!mpu.begin(0x68)) {
    Serial.println("MPU6050 NOT FOUND"); //mpu initialize
    while (true) { delay(10); }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);      //configure range for accel, gyro
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // reduce noise with filter
  Serial.println("MPU6050 ready.");

  if (!bme.begin(0x77)) {
    Serial.println("BME280 NOT FOUND");
    while (true) { delay(10); } 
  }
  Serial.println("BME280 ready.");

  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);  // LoRa init
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);           // CS, RST, DIO0
  if (!LoRa.begin(LORA_FREQ_HZ)) {
    Serial.println("LoRa init failed. Check wiring & freq.");
    while (true) { delay(10); }
  }
  Serial.println("LoRa radio up.\n");
}

void loop()
{
  sensors_event_t a, g, t_mpu; // get sensor data
  mpu.getEvent(&a, &g, &t_mpu);

  float temp_bme = bme.readTemperature();       // °C temp
  float pres_hPa = bme.readPressure() / 100.0;  // convert Pa to hPa
  float hum      = bme.readHumidity();          

  // build csv
  String pkt =
    String(a.acceleration.x, 2) + "," +
    String(a.acceleration.y, 2) + "," +
    String(a.acceleration.z, 2) + "," +
    String(temp_bme,          2) + "," +
    String(pres_hPa,          2) + "," +
    String(hum,               2);

  // send LoRa
  LoRa.beginPacket();
  LoRa.print(pkt);
  LoRa.endPacket();

  Serial.printf(
    "TX ▸ ACC(%.2f,%.2f,%.2f)  |  T=%.2f°C  P=%.2fhPa  H=%.2f%%\n",
    a.acceleration.x, a.acceleration.y, a.acceleration.z,   // serial debug
    temp_bme, pres_hPa, hum);
  delay(500);   // 2 updates / sec
}

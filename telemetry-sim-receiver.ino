/*
 LoRa reciever / ground station
 1. listens on 915 MHz
 2. Parses CSV payload from transmitter
 3. Prints all fields to Serial
 4. Displays Acc-Z on a tiny SSD1306 OLED
*/

#include <SPI.h> //communication with lora
#include <LoRa.h>

// LoRa pins
constexpr uint8_t LORA_CS   = 5;   // D5 chip select
constexpr uint8_t LORA_RST  = 4;   // D4 reset
constexpr uint8_t LORA_IRQ  = 15;  // D15 interrupt
constexpr long    LORA_FREQ_HZ = 915E6; //915 MHz

// oled
#define USE_OLED  1
#if USE_OLED
#include <Wire.h>
#include <Adafruit_GFX.h> //use adafruit oled graphics library
#include <Adafruit_SSD1306.h>
//i2c pins
constexpr uint8_t OLED_SDA = 21;   // D21 data 
constexpr uint8_t OLED_SCL = 22;   // D22 clock
Adafruit_SSD1306 oled(128, 64, &Wire, -1);// initialize oled
#endif

void setup()
{
  Serial.begin(115200); //begin serial 
  delay(200); // allow stabilize
  Serial.println("\n--- LoRa RX booting ---");

#if USE_OLED
  Wire.begin(OLED_SDA, OLED_SCL); //start i2c 
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // make sure OLED is connected by searching for address
    Serial.println("OLED not found; continuing without display.");
  } else {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);                   // initial message
    oled.println("LoRa RX ready");
    oled.display();
  }
#endif

  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
  if (!LoRa.begin(LORA_FREQ_HZ)) {
    Serial.println("LoRa init failed. Check wiring & freq.");   // start LoRa,  stop if fails
    while (true) { delay(10); }
  }
  Serial.println("LoRa radio up.\n");
}

void loop()
{
  int pktSize = LoRa.parsePacket(); // look for LoRa packet from transmit
  if (pktSize == 0) return;          // nothing received yet
  String csv = "";
  while (LoRa.available()) csv += (char)LoRa.read(); // add new characters to string

  float ax, ay, az, temp, pres, hum;
  sscanf(csv.c_str(), "%f,%f,%f,%f,%f,%f",      // take values from csv and format as floats
         &ax, &ay, &az, &temp, &pres, &hum);

  Serial.printf("RX ▸ ACC(%.2f, %.2f, %.2f)  |  T = %.2f °C  P = %.2f hPa  H = %.2f %%\n",
                ax, ay, az, temp, pres, hum);   // formatting by chatgpt for printing 

#if USE_OLED
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Acc Z: "); oled.println(az, 2);     // print acceleration with 2 decimal, temp with 1 on oled
  oled.print("Temp : "); oled.println(temp, 1);
  oled.display();
#endif
}

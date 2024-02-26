
// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3D
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

int right_led = 6;
int left_led = 8;
int forward_led = 4;
int backward_led = 5;

void setup(void) {
  Serial.begin(115200);
  pinMode(forward_led, OUTPUT);
  pinMode(backward_led, OUTPUT);
  pinMode(left_led, OUTPUT);
  pinMode(right_led, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Failed"));
    for(;;);
  }
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    while (1) yield();
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Hello, world");
  display.display();
}

void loop() {

  lis.read();      // get X Y and Z data at once

  /* Or....get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  int x_dir = event.acceleration.x;
  int y_dir = event.acceleration.y;
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.println(String(event.acceleration.x) + "," + String(event.acceleration.y));

  if(x_dir < -2) {
    digitalWrite(left_led, !digitalRead(left_led));
    digitalWrite(right_led, LOW);
  } else if (x_dir > 2) {
    digitalWrite(right_led, !digitalRead(right_led));
    digitalWrite(left_led, LOW);
  } else {
    digitalWrite(right_led, LOW);
    digitalWrite(left_led, LOW);
  }
  if(y_dir > 4) {
    digitalWrite(forward_led, HIGH);
    digitalWrite(backward_led, LOW);
  } else if(y_dir < -4) {
    digitalWrite(forward_led, LOW);
    digitalWrite(backward_led, HIGH);
  } else {
    digitalWrite(forward_led, LOW);
    digitalWrite(backward_led, LOW);
  }
  if(Serial.available()) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print(Serial.readString());
    display.display();
  }
    delay(200); 
}

#include <FastLED.h>
#define RED_LED 5
#define GREEN_LED 10
#define BLUE_LED 11
//int brightness = 100;
int rBright = 0;
int gBright = 0;
int bBright = 0;
int fadeSpeed = 50;
const long interval = 500;
unsigned long previousMillis = 0; // the value of the previous days millis(), so we can reset each day
String data = ""; // bluetooth store
void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  showAnalogRGB( CRGB::Red );   delay(500);
  showAnalogRGB( CRGB::Green ); delay(500);
  showAnalogRGB( CRGB::Blue );  delay(500);
  showAnalogRGB( CRGB::Black ); delay(500);
  Serial.begin(9600);
}


void loop() {
  unsigned long currentMillis = millis();
  while (Serial.available() > 0) {
    data = Serial.readString();
    Serial.println(data);
  }
    if (data == "manual") {
      if (data > 0 && data < 100) {
		 rBright = data.toInt();
        analogWrite(RED_LED, rBright);
      }
      if (data > 200 && data < 300) {
		 gBright = data.toInt();
        analogWrite(GREEN_LED, gBright);
      }
      if (data > 400 && data < 500) {
		 bBright = data.toInt();
        analogWrite(BLUE_LED, bBright);
      }
    }


  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;



    if ( data == "red") // Forward
    {
      showAnalogRGB( CRGB::Red );
      delay(500);
    }
    if ( data == "green") // Forward
    {
      showAnalogRGB( CRGB::Green );
      delay(500);
    }
    if ( data == "blue") // Forward

      showAnalogRGB( CRGB::Blue );
    delay(500);
  }
  if ( data == "pink") // Forward
  {
    showAnalogRGB( CRGB::Red );
    showAnalogRGB( CRGB::Blue );
    delay(500);
  }
  if ( data == "light") // Forward
  {
    showAnalogRGB( CRGB::Green );
    showAnalogRGB( CRGB::Blue );
    delay(500);
  }

  if ( data == "off" ) // Forward
  {
    analogWrite(RED_LED, 0);
    analogWrite(GREEN_LED, 0);
    analogWrite(BLUE_LED, 0);
  }
  if ( data == "random") // Forward
  {
    static uint8_t a;
    a = a + 2;
    // Use FastLED automatic HSV->RGB conversion
    showAnalogRGB( CHSV( a, 255, 255) ); delay(500);

    delay(20);
  }

}
void showAnalogRGB( const CRGB& rgb)
{
  analogWrite(RED_LED,   rgb.r );
  analogWrite(GREEN_LED, rgb.g );
  analogWrite(BLUE_LED,  rgb.b );
}

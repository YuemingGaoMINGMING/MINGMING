#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define LED_PIN    6

#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int lightSensorPin = A0;
int lightSensorVal;

int LED_PINVal;

int ANALOG_THRESHOLD = 400;

void setup(){
  Serial.begin(9600);
  pinMode(lightSensorPin, INPUT);
  pinMode(LED_PIN, OUTPUT);

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
    strip.begin();          
    strip.show();           
    strip.setBrightness(50);
}

void loop(){
  lightSensorVal = analogRead(lightSensorPin);
  Serial.println(lightSensorVal);

  if(lightSensorVal < ANALOG_THRESHOLD){
    colorWipe(strip.Color(255,   0,   0), 50); 
    colorWipe(strip.Color(  0, 255,   0), 50); 
    colorWipe(strip.Color(  0,   0, 255), 50); 

    theaterChase(strip.Color(127, 127, 127), 50); 
    theaterChase(strip.Color(127,   0,   0), 50); 
    theaterChase(strip.Color(  0,   0, 127), 50); 

    rainbow(10);             
    theaterChaseRainbow(50); 
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) { 
    for(int b=0; b<3; b++) { 
      strip.clear(); 
      
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); 
      }
      strip.show(); 
      delay(wait);  
    }
  }
}


void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {

    strip.rainbow(firstPixelHue);
    strip.show(); 
    delay(wait); 
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     
  for(int a=0; a<30; a++) {  
    for(int b=0; b<3; b++) { 
      strip.clear(); 
      
      for(int c=b; c<strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));
        strip.setPixelColor(c, color);
      }
      strip.show();
      delay(wait); 
      firstPixelHue += 65536 / 90; 
    }
  }
}
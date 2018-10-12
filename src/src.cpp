#include "mbed.h"

AnalogIn analog_value(A0);
DigitalOut led(LED1);

#define LED_ON {led = 1;}
#define LED_OFF {led = 0;}

#define PRINT(msg) {\
  printf("%s\r\n",msg);\
}
#define PRINT_F(num) {\
  printf("%0.20f\r\n",num);\
}
#define PRINT_I(num) {\
  printf("%d\r\n",(int)num);\
}
#define delay(ms) { \
    wait(ms/1000); \
}

int delayTime = 10; // 9 Maybe algorithm change needed (was 60)

bool measurement(){
/*    double alpha = 0.90;
    int period = 100;
    static double oldValue = 0;*/
    unsigned short rawValue;
    rawValue = analog_value.read_u16(); // Value from 0 to 65535
    rawValue = rawValue >> 6; // DIV 64 -> change to 0 - 1023
    //PRINT_I(rawValue);
    //double value = alpha * oldValue + (1 - alpha) * rawValue;
    //PRINT_F(value);
    //PRINT("\r\n");
    //pin_value = analog_value.read(); // Converts and read the analog input value (value from 0.0 to 1.0)    
    
    static int maxHodnota = 0;
  static bool SpickovaHodnota = false;
     int analogHodnota;
  bool vysledek = false;
 analogHodnota = rawValue;
  // přepočet analogové hodnoty pro další výpočty
  analogHodnota *= (1000 / delayTime);
  // upravení maximální hodnoty
  if (analogHodnota * 4L < maxHodnota) {
    maxHodnota = analogHodnota * 0.8;
  }
  // detekce špičkové hodnoty
  if (analogHodnota > maxHodnota - (1000 / delayTime)) {
    // nastavení nového maxima při detekované špičce
    if (analogHodnota > maxHodnota) {
      maxHodnota = analogHodnota;
    }
    // nastavení platnosti výsledku, když
    // nebyla detekována špička
    if (SpickovaHodnota == false) {
      vysledek = true;
    }
    SpickovaHodnota = true;
  } else if (analogHodnota < maxHodnota - (3000 / delayTime)) {
    SpickovaHodnota = false;
    // upravení maximální hodnoty při změně měřených hodnot
    maxHodnota -= (1000 / delayTime);
  }
  // vrácení výsledku podprogramu
  return vysledek;

}

int main() {
    int beatFrequency;
    static int beatsPerMin = 0;
    while(1) {
        if (measurement()){
            LED_ON;
            beatFrequency = 60000 / beatsPerMin;
            PRINT_I(beatsPerMin);
            PRINT_I(beatFrequency);
            PRINT("\r\n");
            if (beatFrequency > 50 & beatFrequency < 200) {
              printf("Heart beat frequency: %d BPM\r\n", beatFrequency);
              //delay(1000);
            }
            
            beatsPerMin = 0;
        }else{
            LED_OFF;
            }
        delay(delayTime);
        beatsPerMin += delayTime;
    }
}
#include "mbed.h"

AnalogIn analog_value(A0);
DigitalOut led(LED1);

#define LED_ON {led = 1;}
#define LED_OFF {led = 1;}

#define PRINT(msg) {\
  printf("%s\r\n",msg);\
}
#define PRINT_F(num) {\
  printf("%0.20f\r\n",num);\
}
#define delay(ms) { \
    wait(ms/1000); \
}

int main() {
   double pin_value, value;
    while(1) {
        pin_value = analog_value.read(); // Converts and read the analog input value (value from 0.0 to 1.0)
        value = pin_value;
        PRINT_F(value);
        LED_OFF;
        delay(300);
        LED_ON;
    }
}

#include "mbed.h"

AnalogIn analog_value(A0);
DigitalOut led(LED1);
int delayTime = 10;

#define LED_ON {led = 1;}
#define LED_OFF {led = 0;}

bool measurement(){
    static int maxValue = 0;
    static bool spikeDetected = false;
    int analogValue;
    bool result = false;
    
    analogValue = analog_value.read_u16(); // analogValue from 0 to 65535
    
    // Voltage measurement transformation
    analogValue = analogValue >> 6; // DIV 64 -> change to 0 - 1023
    analogValue *= (1000 / delayTime);
    
    // The last maxValue will be detected as a peak.
    if (analogValue * 4L < maxValue) {
        maxValue = analogValue * 0.8;
    }
    
    // Beat detection
    if (analogValue > maxValue - (1000 / delayTime)) {
    
        // Change maximum value for next measurement
        if (analogValue > maxValue) {
            maxValue = analogValue;
        }
    
        // Allocate only one heartbeat to a peak.
        if (spikeDetected == false) {
            result = true;
        }
    
        spikeDetected = true;
    } else if (analogValue < maxValue - (3000 / delayTime)) {
        spikeDetected = false;
        
        // Change maximum value for remove fake beats
        maxValue -= (1000 / delayTime);
    }
 
    return result;

}

int main() {
    int beatFrequency;
    int beatsPerMin = 0;
    
    while(1) {
        if (measurement()){
            LED_ON;
            
            // Count beats per minute
            beatFrequency = 60000 / beatsPerMin;
            
            if (beatFrequency > 50 & beatFrequency < 200) {
              printf("Heart beat frequency: %d BPM\r\n", beatFrequency);
            }
            
            beatsPerMin = 0;
        }else{
            LED_OFF;
            }
            
        wait_ms(delayTime);
        beatsPerMin += delayTime;
    }
}
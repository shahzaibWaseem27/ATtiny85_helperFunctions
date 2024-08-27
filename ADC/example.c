#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

uint8_t i = 0;

int main(){


  DDRB |= (1 << PB0);

  TCCR0B &= ~(1 << WGM02);
  TCCR0A |= (1 << WGM01) | (1 << WGM00);

  TCCR0A |= (1 << COM0A1);
  TCCR0A &= ~(1 << COM0A0);

  TCCR0B &= ~(1 << CS02);
  TCCR0B |= (1 << CS01) | (1 << CS00);


  while(1){

    for(i = 0; i < 256; i++){

      OCR0A = i;
      _delay_ms(30);

    }

    _delay_ms(1000);

    for(i = 255; i >= 0; i--){

      OCR0A = i;
      _delay_ms(30);

    }

    _delay_ms(1000);

  }

}


// int main(void) {
//     // Set the ADC prescaler to 64 (suitable for an 8 MHz clock)
//     //setClockPrescalarADC(64);

//     // Enable the ADC on channel 2 (ADC2)
//     //enableADCOnChannel(2);

//     // Variable to store ADC result
//     //int adcResult = 0;

//     while (1) {
//         // Measure the ADC value from channel 2, right-adjusted
//         adcResult = measureADCVal(2, 'n');

//         // You can now use the adcResult variable, e.g., send it via UART, control an LED, etc.
        
//         // For demonstration purposes, we'll just add a delay
//         _delay_ms(1000);  // Wait 1 second before the next reading
//     }

//     // Optional: Disable the ADC on channel 2 if you no longer need it
//     disableADCOnChannel(2);

//     return 0;
// }

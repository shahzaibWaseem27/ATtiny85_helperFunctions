#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

int main(void) {
    // Set the ADC prescaler to 64 (suitable for an 8 MHz clock)
    setClockPrescalarADC(64);

    // Enable the ADC on channel 2 (ADC2)
    enableADCOnChannel(2);

    // Variable to store ADC result
    int adcResult = 0;

    while (1) {
        // Measure the ADC value from channel 2, right-adjusted
        adcResult = measureADCVal(2, 'n');

        // You can now use the adcResult variable, e.g., send it via UART, control an LED, etc.
        
        // For demonstration purposes, we'll just add a delay
        _delay_ms(1000);  // Wait 1 second before the next reading
    }

    // Optional: Disable the ADC on channel 2 if you no longer need it
    disableADCOnChannel(2);

    return 0;
}

#include <avr/io.h>


int measureADCVal(uint8_t channel, char isLeftAdjusted){

    // Adjust result alignment
    if(isLeftAdjusted == 'y'){
        ADMUX |= (1 << ADLAR);
    } else {
        ADMUX &= ~(1 << ADLAR);
    }

    // Clear the older channel selection
    ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));

    // Set the channel selection
    switch(channel){
        case 0: break;  // Already cleared above
        case 1: ADMUX |= (1 << MUX0); break;
        case 2: ADMUX |= (1 << MUX1); break;
        case 3: ADMUX |= (1 << MUX1) | (1 << MUX0); break;
        default: return -1; // Invalid channel
    }

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while(ADCSRA & (1 << ADSC)){}

    // Read the result
    uint8_t ADCResultLower8bits = ADCL;
    uint8_t ADCResultHigher8bits = ADCH;

    if(isLeftAdjusted == 'y'){
        return (ADCResultHigher8bits << 2) | (ADCResultLower8bits >> 6);
    } else {
        return (ADCResultHigher8bits << 8) | ADCResultLower8bits;
    }
}



void setClockPrescalarADC(int prescalar){

    switch(prescalar){
        case 2:
            ADCSRA &= ~((1 << ADPS2) | (1 << ADPS1));
            ADCSRA |= (1 << ADPS0);
            break;

        case 4:
            ADCSRA &= ~((1 << ADPS2) | (1 << ADPS0));
            ADCSRA |= (1 << ADPS1);
            break;

        case 8:
            ADCSRA &= ~(1 << ADPS2);
            ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
            break;

        case 16:
            ADCSRA &= ~((1 << ADPS1) | (1 << ADPS0));
            ADCSRA |= (1 << ADPS2);
            break;

        case 32:
            ADCSRA &= ~(1 << ADPS1);
            ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
            break;

        case 64:
            ADCSRA &= ~(1 << ADPS0);
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
            break;

        case 128:
            ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
            break;
    }
}


void enableADCOnChannel(int channel){
    ADCSRA |= (1 << ADEN);

    switch(channel){
        case 0: DIDR0 |= (1 << ADC0D); break;
        case 1: DIDR0 |= (1 << ADC1D); break;
        case 2: DIDR0 |= (1 << ADC2D); break;
        case 3: DIDR0 |= (1 << ADC3D); break;
    }
}

void disableADCOnChannel(uint8_t channel){
    switch(channel){
        case 0: DIDR0 &= ~(1 << ADC0D); break;
        case 1: DIDR0 &= ~(1 << ADC1D); break;
        case 2: DIDR0 &= ~(1 << ADC2D); break;
        case 3: DIDR0 &= ~(1 << ADC3D); break;
    }
}

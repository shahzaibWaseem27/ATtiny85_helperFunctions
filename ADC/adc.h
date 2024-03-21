#include <avr/io.h>


int measureADCVal(uint8_t channel, char isLeftAdjusted){

    if(isLeftAdjusted == 'y'){
        ADMUX |= (1 << ADLAR);
    } else {
        ADMUX &= ~(1 << ADLAR);
    }

    uint8_t ADCResultLower8bits = 0;
    uint8_t ADCResultHigher8bits = 0;

    switch(channel){

        case 0:
            ADMUX &= ~((1 << MUX3) & (1 << MUX2) & (1 << MUX1) & (1 << MUX0));
            ADCSRA |= (1 << ADSC);
            while(ADCSRA & (1 << ADSC)){}
            ADCResultLower8bits = ADCL;
            ADCResultHigher8bits = ADCH;
            if(isLeftAdjusted == 'y'){
                return (ADCResultHigher8bits << 2) | (ADCResultLower8bits >> 6);
            } else {
                return (ADCResultHigher8bits << 8) | ADCResultLower8bits;
            }
            break;

        case 1:
            ADMUX &= ~((1 << MUX3) & (1 << MUX2) & (1 << MUX1));
            ADMUX |= (1 << MUX0);
            ADCSRA |= (1 << ADSC);
            while(ADCSRA & (1 << ADSC)){}
            ADCResultLower8bits = ADCL;
            ADCResultHigher8bits = ADCH;
            if(isLeftAdjusted == 'y'){
                return (ADCResultHigher8bits << 2) | (ADCResultLower8bits >> 6);
            } else {
                return (ADCResultHigher8bits << 8) | ADCResultLower8bits;
            }
            break;

        case 2:
            ADMUX &= ~((1 << MUX3) & (1 << MUX2) & (1 << MUX0));
            ADMUX |= (1 << MUX1);
            ADCSRA |= (1 << ADSC);
            while(ADCSRA & (1 << ADSC)){}
            ADCResultLower8bits = ADCL;
            ADCResultHigher8bits = ADCH;
            if(isLeftAdjusted == 'y'){
                return (ADCResultHigher8bits << 2) | (ADCResultLower8bits >> 6);
            } else {
                return (ADCResultHigher8bits << 8) | ADCResultLower8bits;
            }
            break;

        case 3:
            ADMUX &= ~((1 << MUX3) & (1 << MUX2));
            ADMUX |= (1 << MUX1) | (1 << MUX0);
            ADCSRA |= (1 << ADSC);
            while(ADCSRA & (1 << ADSC)){}
            ADCResultLower8bits = ADCL;
            ADCResultHigher8bits = ADCH;
            if(isLeftAdjusted == 'y'){
                return (ADCResultHigher8bits << 2) | (ADCResultLower8bits >> 6);
            } else {
                return (ADCResultHigher8bits << 8) | ADCResultLower8bits;
            }
            break;
        
    }

}


void setClockPrescalarADC(int prescalar){

    switch(prescalar){

        case 2:
            ADCSRA &= ~((1 << ADPS2) & (1 << ADPS1));
            ADCSRA |= (1 << ADPS0);
            break;

        case 4:
            ADCSRA &= ~((1 << ADPS2) & (1 << ADPS0));
            ADCSRA |= (1 << ADPS1);
            break;
        
        case 8:
            ADCSRA &= ~(1 << ADPS2);
            ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
            break;

        case 16:
            ADCSRA &= ~((1 << ADPS1) & (1 << ADPS0));
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

        case 0:

            DIDR0 |= (1 << ADC0D);
            break;

        case 1:

            DIDR0 |= (1 << ADC1D);
            break;

        case 2:

            DIDR0 |= (1 << ADC2D);
            break;

        case 3:

            DIDR0 |= (1 << ADC3D);
            break;

    }

}

void disableADCOnChannel(uint8_t channel){

    ADCSRA &= ~(1 << ADEN);

    switch(channel){

    case 0:

        DIDR0 &= ~(1 << ADC0D);
        break;

    case 1:

        DIDR0 &= ~(1 << ADC1D);
        break;

    case 2:

        DIDR0 &= ~(1 << ADC2D);
        break;

    case 3:

        DIDR0 &= ~(1 << ADC3D);
        break;

    }

}

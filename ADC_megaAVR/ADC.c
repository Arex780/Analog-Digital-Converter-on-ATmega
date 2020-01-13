#include <avr/io.h>
#include <avr/interrupt.h>
#include "deklara.h"

void init_ADC(void);
int multiply_with_round(unsigned int arg1, unsigned long arg2);
int multiply_with_round2(unsigned char arg1, unsigned int arg2);


int multiply_with_round(unsigned int arg1, unsigned long arg2){
	union {
		unsigned int bits16[2];
		unsigned long bits32;
	} temp_union;
	temp_union.bits32=arg1*arg2;
	if(temp_union.bits16[0]&0x8000)
		temp_union.bits16[1]++;
	return temp_union.bits16[1];
};




void init_ADC (void) {
    //ADMUX =_BV(MUX1);   // wewn�trzne napi�cie odniesienia wy��czone, 
                        // korzystamy z pod��czonego do AREF
                        // uaktywniono kana� ADC2 z pomiarem napi�cia zadawanego potencjometrem
    ADCSRA= _BV(ADEN)|	// w��czenie przetwornika ADC
			_BV(ADSC)|	// pierwsze uruchomienie konwersji (trwa ona 25 cykli zegara)
			_BV(ADIF)|	// skasowanie flagi przerwa� od ADC
			_BV(ADIE)|	// zezwolenie na przerwania od ko�ca konwersji ADC
			_BV(ADPS2)|	// ustawienie dzielnika cz�stotliwo�ci na 128
			_BV(ADPS1)|	// cz�stotliwo�� zegara ADC wynosi 16MHz/128=125 kHz
			_BV(ADPS0);	// spe�niono w ten spos�b wymagania dla najwy�szej dok�adno�ci ADC                           
						// cz�stotliwo�� powinna zawiera� si� z granicach od 50kHz do 200 kHz
};



ISR (ADC_vect) {
unsigned int wartosc_cyfrowa;
unsigned long int zmienna;
unsigned long int max;
        wartosc_cyfrowa=(ADC&0x03FF);
		napiecie=wartosc_cyfrowa<<1;
		prad=wartosc_cyfrowa;
		wsp_wypelnienia=digits_to_int(3, cyfry);
		zmienna=(unsigned long int)1023*wsp_wypelnienia;
		zmienna=zmienna/100;
		OCR1A=zmienna;
};
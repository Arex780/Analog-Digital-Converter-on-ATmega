#include <avr/io.h>	
#include <avr/interrupt.h>
#include "deklara.h"
void init_TIMER1(void);
void init_TIMER1 (void) {
	TCCR1A = _BV(COM1A1)| 	// po zrównaniu wartoœci zliczonej przez licznik1 w TCNT1 
							// i wartoœci porównywanej zapisanej w rejestrze OCR1A 
							// nastêpuje wyzerowanie wyjœcia OC1A
	_BV(WGM11)|_BV(WGM10); // ustawienie trybu dziesiêciobitowego PWM licznika1 z poprawna faz¹ 					 
	TCCR1B = _BV(CS10); //brak podzia³u czêstotliwoœci PWM Ÿród³o zegara = clk_IO
	TCNT1=0x0000;  	//wyzerowanie zliczonej wartoœci
	OCR1A=0x00;		//wyzerowanie rejestru z wartoœci¹ porównywan¹
	TIMSK |= _BV(TOIE1);	// zezwolenie na zg³aszanie przerwañ przez licznik1 przy doliczeniu do 0
	TIFR = 0xFF;       		// wyzerowanie flag przerwañ od liczników
};

ISR (TIMER1_OVF_vect) {
	ADCSRA |= _BV(ADSC); //start konwersji ADC
};							

	


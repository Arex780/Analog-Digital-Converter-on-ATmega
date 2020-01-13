#include <avr/io.h>	
#include <avr/interrupt.h>
#include "deklara.h"
void init_TIMER1(void);
void init_TIMER1 (void) {
	TCCR1A = _BV(COM1A1)| 	// po zr�wnaniu warto�ci zliczonej przez licznik1 w TCNT1 
							// i warto�ci por�wnywanej zapisanej w rejestrze OCR1A 
							// nast�puje wyzerowanie wyj�cia OC1A
	_BV(WGM11)|_BV(WGM10); // ustawienie trybu dziesi�ciobitowego PWM licznika1 z poprawna faz� 					 
	TCCR1B = _BV(CS10); //brak podzia�u cz�stotliwo�ci PWM �r�d�o zegara = clk_IO
	TCNT1=0x0000;  	//wyzerowanie zliczonej warto�ci
	OCR1A=0x00;		//wyzerowanie rejestru z warto�ci� por�wnywan�
	TIMSK |= _BV(TOIE1);	// zezwolenie na zg�aszanie przerwa� przez licznik1 przy doliczeniu do 0
	TIFR = 0xFF;       		// wyzerowanie flag przerwa� od licznik�w
};

ISR (TIMER1_OVF_vect) {
	ADCSRA |= _BV(ADSC); //start konwersji ADC
};							

	


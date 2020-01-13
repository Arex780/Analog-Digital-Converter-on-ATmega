#include <avr/pgmspace.h>
#include "IN_OUT.h"
#define VMLAB 1

extern unsigned int napiecie;   //wartosc napiêcia
extern unsigned char wsp_wypelnienia;
extern signed int prad;
extern signed char cyfry[3];   	 //wartoœci modyfikowane s¹ przyciskami
extern volatile unsigned char miganie;
extern volatile signed char menu;


extern void init_pins (void);
extern void define_char(void);
extern void init_LCD (void);
extern void init_ADC (void);
extern void init_TIMER1(void);
extern void window_1(void);
extern void window_2(void);
extern unsigned int digits_to_int (unsigned char liczba_cyfr, signed char *pcyfry);

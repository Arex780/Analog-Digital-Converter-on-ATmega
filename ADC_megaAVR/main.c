#include <avr/interrupt.h>	
#include <util/delay.h>
#include "deklara.h"
#include <math.h>
#define VMLAB 0
volatile unsigned char kl_ENTER = 0;	//przycisk ENTER (KEY0)
volatile unsigned char kl_UP = 0;		//przycisk UP (KEY1)
volatile unsigned char kl_DOWN = 0;		//przycisk DOWN (KEY2) 
volatile unsigned char kl_CANCEL = 0;	//przycisk CANCELv(KEY3)

volatile signed char menu=0;		//zmienna przechowujaca aktualna ilosc klikniec przycisku ENTER % 5
volatile int dzielnik_f=0; 	//zmienna regulujaca czestotliwosc zapalania sie i wylaczania modyfikowanej diody
volatile unsigned char miganie=0;	//zmienna bezposrednio wskazujaca na zapalenie lub nie modyfikowanej diody	

signed char cyfry[3];	//warto�ci tablicy modyfikowane s� przyciskami
signed char cyfry_kopia[3];   //kopia wartosci, uzyta pozniej w przyadku przycisku CANCEL

//deklaracje funkcji
//void init_TIMER1 (void);
void init_TIMER0 (void);
void init_pins (void);
void send_LCDinstr(unsigned char LCDinstr);
int main(void);


//Timer0 jest zainicjalizowany w celu generowania przerwa� od jego przepe�nienia.
void init_TIMER0 (void) {
#if VMLAB
	TCCR0 = _BV(CS00); //fclk/1, 
#else
	TCCR0 = _BV(CS00)|_BV(CS01)|_BV(CS02); //fclk/1024, 
#endif	
	TCNT0 = 0x00; //warto�� zliczona przez dzielnik_f
	TIMSK = _BV(TOIE0); //selektywne zezwolenie na przerwania od przepe�nienia dzielnik_fa0 TOIE0=1, przepe�nienie co 256*64us=16,38ms, dla HAPSIM co 0,128ms
};

union {		//do obs�ugi przycisk�w -> w przerwaniu ISR
 struct {
  unsigned char ENTER:1;	//LSB
  unsigned char UP:1;
  unsigned char DOWN:1;
  unsigned char CANCEL:1;
  unsigned char ENTER_PREV:1;
  unsigned char UP_PREV:1;
  unsigned char DOWN_PREV:1;
  unsigned char CANCEL_PREV:1; //MSB
 } flags;
  char byte;
} key;

union {		//do obs�ugi przycisk�w -> w przerwaniu ISR
 struct {
  unsigned char ENTER:1;	   //LSB
  unsigned char UP:1;
  unsigned char DOWN:1;
  unsigned char CANCEL:1;
  unsigned char ENTER_PREV:1;
  unsigned char UP_PREV:1;
  unsigned char DOWN_PREV:1;
  unsigned char CANCEL_PREV:1; 
  unsigned char ENTER_PREV1:1;
  unsigned char UP_PREV1:1;
  unsigned char DOWN_PREV1:1;
  unsigned char CANCEL_PREV1:1;
  unsigned char ENTER_PREV2:1;
  unsigned char UP_PREV2:1;
  unsigned char DOWN_PREV2:1;
  unsigned char CANCEL_PREV2:1; //MSB
  } flags; 
  int word;
} falling_slope;  

ISR (TIMER0_OVF_vect) {	//przerwanie wywo�ywane co ok. 16,4 ms
	sei();
	key.byte=(key.byte<<4);// przesuwaj�c w lew� stron� bity z do�u uzupe�niane s� zerami
//ustawienie jedynek na pozycjach od 0 do 3 w przypadku odczytania zer z odpowiednich wej�� KEYx
	key.byte|=((bit_is_clear(PINKEY,KEY0))|(bit_is_clear(PINKEY,KEY1) << 1)|(bit_is_clear(PINKEY,KEY2) << 2)|(bit_is_clear(PINKEY,KEY3) << 3)); 
	falling_slope.word=(falling_slope.word<<4);
	
	if(key.flags.ENTER){  //czy wci�ni�ty jest przycisk ENTER?
		if(!key.flags.ENTER_PREV) falling_slope.flags.ENTER=1; //Czy wykryto zbocze opadaj�ce
		if(falling_slope.flags.ENTER_PREV2) { kl_ENTER = 1; //Czy od chwili wykrycia zbocza opadaj�cego up�yn�y 3 przerwania z wci�ni�tym przyciskiem
			if(bit_is_clear(PINSWITCH, SW0))
				menu--;
			if(bit_is_set(PINSWITCH, SW0))
				menu++;	
		}
	}
	else{
		falling_slope.word&=0xEEEE;  //wyzerowanie flag dla przycisku ENTER potwierdzaj�cych wykrycie zbocza opadaj�cego
	};	
	
		
	if(key.flags.UP){  //czy wci�ni�ty jest przycisk UP?
		if(!key.flags.UP_PREV) falling_slope.flags.UP=1; //Czy wykryto zbocze opadaj�ce
		if(falling_slope.flags.UP_PREV2) kl_UP = 1; //Czy od chwili wykrycia zbocza opadaj�cego up�yn�y 3 przerwania z wci�ni�tym przyciskiem
	}
	else{
		falling_slope.word&=0xDDDD;  //wyzerowanie flag dla przycisku UP potwierdzaj�cych wykrycie zbocza opadaj�cego
	};		
		
	if(key.flags.DOWN){  //czy wci�ni�ty jest przycisk DOWN?
		if(!key.flags.DOWN_PREV) falling_slope.flags.DOWN=1; //Czy wykryto zbocze opadaj�ce
		if(falling_slope.flags.DOWN_PREV2) kl_DOWN = 1; //Czy od chwili wykrycia zbocza opadaj�cego up�yn�y 3 przerwania z wci�ni�tym przyciskiem
	}
	else{
		falling_slope.word&=0xBBBB;  //wyzerowanie flag dla przycisku DOWN potwierdzaj�cych wykrycie zbocza opadaj�cego
	};	
		
	if(key.flags.CANCEL){  //czy wci�ni�ty jest przycisk CANCEL?
		if(!key.flags.CANCEL_PREV) falling_slope.flags.CANCEL=1;  //Czy wykryto zbocze opadaj�ce
		if(falling_slope.flags.CANCEL_PREV2) kl_CANCEL = 1;  //Czy od chwili wykrycia zbocza opadaj�cego up�yn�y 3 przerwania z wci�ni�tym przyciskiem
	}
	else{
		falling_slope.word&=0x7777;  //wyzerowanie flag dla przycisku CANCEL potwierdzaj�cych wykrycie zbocza opadaj�cego
	};
	if(dzielnik_f==61)	//czy minela okolo sekunda?
	{
		dzielnik_f=0;		//reset dzielnik_fa
		miganie++;		//zmiana stanu modyfikowanej cyfry
	}
	if(miganie>1)
	{
		miganie=0;
	}
	dzielnik_f++;
};

unsigned int digits_to_int (unsigned char liczba_cyfr, signed char *pcyfry)
{
	unsigned int wypelnienie;
	unsigned char i;
	wypelnienie=0;
	for (i=0;i<liczba_cyfr;i++)
	{
			wypelnienie=wypelnienie+(pow(10.0,(liczba_cyfr-i-1))*(*(pcyfry+i)));			
	};
	return wypelnienie;
};

//unsigned int digits_to_int (unsigned char liczba_cyfr, signed char *pcyfry);
unsigned char wsp_wypelnienia=0;
signed int prad=0;
unsigned int napiecie=0;

int main (void)
{
	key.byte=0xFF;   //inicjalizacja flag stanami nieaktywnymi 
	falling_slope.word=0x0000; //inicjalizacja flag stanami nieaktywnymi
	init_pins();
	init_ADC();//inicjalizacja kierunkowo�ci wyprowadze�
	init_TIMER0();				//inicjalizacja Timera0
	init_TIMER1(); 				//inicjalizacja timera1			//IN_OUT
	init_LCD ();
	define_char();
	sei();
	window_1();
while (1)
	{
		if(menu<0)
			menu=3;
		if(menu>3)
		{
			//wsp_wypelnienia=digits_to_int(3, cyfry);
			menu=0;
		}
		if(menu==0)		//zrob kopie aktualnego stanu cyfr
		{
			cyfry_kopia[0]=cyfry[0];
			cyfry_kopia[1]=cyfry[1];
			cyfry_kopia[2]=cyfry[2];
		}
		switch (menu)
		{
			case 0:
				window_2();
				break;
			case 1:
				if(kl_UP == 1){
					cyfry[0]++;
					if (cyfry[0] > 1) cyfry[0] = 0;
					kl_UP =0;
				};
				if(kl_DOWN == 1){
					cyfry[0]--;
					if (cyfry[0] < 0) cyfry[0] = 1;
					kl_DOWN = 0;
				};
				if(cyfry[0]==1)
				{
					cyfry[1]=0;
					cyfry[2]=0;
				};
				window_2();
				break;
			case 2:
				if(kl_UP == 1 && cyfry[0]==0){
					cyfry[1]++;
					if (cyfry[1] > 9) 
						cyfry[1] = 0;
					kl_UP =0;
				};
				if(kl_DOWN == 1 && cyfry[0]==0){
					cyfry[1]--;
					if (cyfry[1] < 0) cyfry[1] = 9;
					kl_DOWN = 0;
				};
				window_2();
				break;
			case 3:
				if(kl_UP == 1 && cyfry[0]==0){
					cyfry[2]++;
					if (cyfry[2] > 9) cyfry[2] = 0;
					kl_UP =0;
				};
				if(kl_DOWN == 1 && cyfry[0]==0){
					cyfry[2]--;
					if (cyfry[2] < 0) cyfry[2] = 9;
					kl_DOWN = 0;
				};
				window_2();
				break;
			}
		if(kl_CANCEL==1)		//powrot do stanu przed modyfikacja
		{
			menu=0;
			cyfry[0]=cyfry_kopia[0];
			cyfry[1]=cyfry_kopia[1];
			cyfry[2]=cyfry_kopia[2];
			kl_CANCEL=0;
		}
	};
	return 0;
};



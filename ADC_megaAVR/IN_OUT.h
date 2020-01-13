	#include <avr/io.h>		
/* do��czenie do projektu pliku nag��wkowego avr/io.h z biblioteki avr-libc
   pozwala na korzystanie z nazw rejestr�w i flag bitowych oraz poni�szych makrorozwini��*/
void init_pins (void);
//przyporz�dkowanie diodom LED, prze��cznikom SW i przyciskom KEY odpowiednich port�w mikrokontrolera
#define PORTLED 	PORTB	//diody LED pod��czono do portu B
#define DIRLED		DDRB	//diody LED pod��czono do portu B
#define PINKEY		PINC	//przyciski KEY pod��czono do portu C
#define DIRKEY		DDRC	//przyciski KEY pod��czono do portu C
#define	PINSWITCH	PINC	//prze��czniki SW pod��czono do portu C
#define DIRSWITCH	DDRC	//prze��czniki SW pod��czono do portu C

//przyporz�dkowanie sygna�om wy�wietlacza LCD odpowiednich port�w mikrokontrolera
#define	LCD_DATA_OUT	PORTD	//magistral� danych wy�wietlacza LCD pod��czono do portu D
#define	LCD_DATA_IN		PIND	//magistral� danych wy�wietlacza LCD pod��czono do portu D
#define LCD_DIR_DATA	DDRD	//magistral� danych wy�wietlacza LCD pod��czono do portu D
#define	LCD_CONTROL		PORTE	//sygna�y steruj�ce wy�wietlacza LCD pod��czono do portu E
#define LCD_DIR_CONTROL	DDRE	//sygna�y steruj�ce wy�wietlacza LCD pod��czono do portu E

/* przyporz�dkowanie poszczeg�lnym diodom LED, prze��cznikom SW i przyciskom KEY 
   odpowiednich pin�w z okre�lonych port�w mikrokontrolera */
#define	LED0		PB4		//dioda LED0 pod��czona jest do pinu PB4
#define	LED1		PB5		//dioda LED1 pod��czona jest do pinu PB5
#define	LED2		PB6		//dioda LED2 pod��czona jest do pinu PB6
#define	LED3		PB7		//dioda LED3 pod��czona jest do pinu PB7
#define KEY0        PC0		//przycisk KEY0 pod��czony jest do pinu PC0
#define KEY1        PC1		//przycisk KEY1 pod��czony jest do pinu PC1
#define KEY2        PC2		//przycisk KEY2 pod��czony jest do pinu PC2
#define KEY3        PC3		//przycisk KEY3 pod��czony jest do pinu PC3
#define SW0         PC4		//prze��cznik SW0 pod��czony jest do pinu PC4
#define SW1         PC5		//prze��cznik SW1 pod��czony jest do pinu PC5
#define SW2         PC6		//prze��cznik SW2 pod��czony jest do pinu PC6
#define SW3         PC7		//prze��cznik SW3 pod��czony jest do pinu PC7
/* przyporz�dkowanie wyprowadze� wy�wietlacza LCD do pin�w z okre�lonych port�w mikrokontrolera */
#define LCD_D0      PD0		//lini� danych D0 LCD pod��czono do pinu PD0
#define LCD_D1      PD1		//lini� danych D1 LCD pod��czono do pinu PD1
#define LCD_D2      PD2		//lini� danych D2 LCD pod��czono do pinu PD2
#define LCD_D3      PD3		//lini� danych D3 LCD pod��czono do pinu PD3
#define LCD_D4      PD4		//lini� danych D4 LCD pod��czono do pinu PD4
#define LCD_D5      PD5		//lini� danych D5 LCD pod��czono do pinu PD5
#define LCD_D6      PD6		//lini� danych D6 LCD pod��czono do pinu PD6
#define LCD_D7      PD7		//lini� danych D7 LCD pod��czono do pinu PD7
#define LCD_RS      PE2		//sygna� steruj�cy RS LCD pod��czono do pinu PE2
#define LCD_EN      PE3		//sygna� steruj�cy EN LCD pod��czono do pinu PE3
#define LCD_R_W     PE4		//sygna� steruj�cy R_W LCD pod��czono do pinu PE4


	#include <avr/io.h>		
/* do³¹czenie do projektu pliku nag³ówkowego avr/io.h z biblioteki avr-libc
   pozwala na korzystanie z nazw rejestrów i flag bitowych oraz poni¿szych makrorozwiniêæ*/
void init_pins (void);
//przyporz¹dkowanie diodom LED, prze³¹cznikom SW i przyciskom KEY odpowiednich portów mikrokontrolera
#define PORTLED 	PORTB	//diody LED pod³¹czono do portu B
#define DIRLED		DDRB	//diody LED pod³¹czono do portu B
#define PINKEY		PINC	//przyciski KEY pod³¹czono do portu C
#define DIRKEY		DDRC	//przyciski KEY pod³¹czono do portu C
#define	PINSWITCH	PINC	//prze³¹czniki SW pod³¹czono do portu C
#define DIRSWITCH	DDRC	//prze³¹czniki SW pod³¹czono do portu C

//przyporz¹dkowanie sygna³om wyœwietlacza LCD odpowiednich portów mikrokontrolera
#define	LCD_DATA_OUT	PORTD	//magistralê danych wyœwietlacza LCD pod³¹czono do portu D
#define	LCD_DATA_IN		PIND	//magistralê danych wyœwietlacza LCD pod³¹czono do portu D
#define LCD_DIR_DATA	DDRD	//magistralê danych wyœwietlacza LCD pod³¹czono do portu D
#define	LCD_CONTROL		PORTE	//sygna³y steruj¹ce wyœwietlacza LCD pod³¹czono do portu E
#define LCD_DIR_CONTROL	DDRE	//sygna³y steruj¹ce wyœwietlacza LCD pod³¹czono do portu E

/* przyporz¹dkowanie poszczególnym diodom LED, prze³¹cznikom SW i przyciskom KEY 
   odpowiednich pinów z okreœlonych portów mikrokontrolera */
#define	LED0		PB4		//dioda LED0 pod³¹czona jest do pinu PB4
#define	LED1		PB5		//dioda LED1 pod³¹czona jest do pinu PB5
#define	LED2		PB6		//dioda LED2 pod³¹czona jest do pinu PB6
#define	LED3		PB7		//dioda LED3 pod³¹czona jest do pinu PB7
#define KEY0        PC0		//przycisk KEY0 pod³¹czony jest do pinu PC0
#define KEY1        PC1		//przycisk KEY1 pod³¹czony jest do pinu PC1
#define KEY2        PC2		//przycisk KEY2 pod³¹czony jest do pinu PC2
#define KEY3        PC3		//przycisk KEY3 pod³¹czony jest do pinu PC3
#define SW0         PC4		//prze³¹cznik SW0 pod³¹czony jest do pinu PC4
#define SW1         PC5		//prze³¹cznik SW1 pod³¹czony jest do pinu PC5
#define SW2         PC6		//prze³¹cznik SW2 pod³¹czony jest do pinu PC6
#define SW3         PC7		//prze³¹cznik SW3 pod³¹czony jest do pinu PC7
/* przyporz¹dkowanie wyprowadzeñ wyœwietlacza LCD do pinów z okreœlonych portów mikrokontrolera */
#define LCD_D0      PD0		//liniê danych D0 LCD pod³¹czono do pinu PD0
#define LCD_D1      PD1		//liniê danych D1 LCD pod³¹czono do pinu PD1
#define LCD_D2      PD2		//liniê danych D2 LCD pod³¹czono do pinu PD2
#define LCD_D3      PD3		//liniê danych D3 LCD pod³¹czono do pinu PD3
#define LCD_D4      PD4		//liniê danych D4 LCD pod³¹czono do pinu PD4
#define LCD_D5      PD5		//liniê danych D5 LCD pod³¹czono do pinu PD5
#define LCD_D6      PD6		//liniê danych D6 LCD pod³¹czono do pinu PD6
#define LCD_D7      PD7		//liniê danych D7 LCD pod³¹czono do pinu PD7
#define LCD_RS      PE2		//sygna³ steruj¹cy RS LCD pod³¹czono do pinu PE2
#define LCD_EN      PE3		//sygna³ steruj¹cy EN LCD pod³¹czono do pinu PE3
#define LCD_R_W     PE4		//sygna³ steruj¹cy R_W LCD pod³¹czono do pinu PE4


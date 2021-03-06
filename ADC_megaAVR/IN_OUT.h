	#include <avr/io.h>		
/* dołączenie do projektu pliku nagłówkowego avr/io.h z biblioteki avr-libc
   pozwala na korzystanie z nazw rejestrów i flag bitowych oraz poniższych makrorozwinięć*/
void init_pins (void);
//przyporządkowanie diodom LED, przełącznikom SW i przyciskom KEY odpowiednich portów mikrokontrolera
#define PORTLED 	PORTB	//diody LED podłączono do portu B
#define DIRLED		DDRB	//diody LED podłączono do portu B
#define PINKEY		PINC	//przyciski KEY podłączono do portu C
#define DIRKEY		DDRC	//przyciski KEY podłączono do portu C
#define	PINSWITCH	PINC	//przełączniki SW podłączono do portu C
#define DIRSWITCH	DDRC	//przełączniki SW podłączono do portu C

//przyporządkowanie sygnałom wyświetlacza LCD odpowiednich portów mikrokontrolera
#define	LCD_DATA_OUT	PORTD	//magistralę danych wyświetlacza LCD podłączono do portu D
#define	LCD_DATA_IN		PIND	//magistralę danych wyświetlacza LCD podłączono do portu D
#define LCD_DIR_DATA	DDRD	//magistralę danych wyświetlacza LCD podłączono do portu D
#define	LCD_CONTROL		PORTE	//sygnały sterujące wyświetlacza LCD podłączono do portu E
#define LCD_DIR_CONTROL	DDRE	//sygnały sterujące wyświetlacza LCD podłączono do portu E

/* przyporządkowanie poszczególnym diodom LED, przełącznikom SW i przyciskom KEY 
   odpowiednich pinów z określonych portów mikrokontrolera */
#define	LED0		PB4		//dioda LED0 podłączona jest do pinu PB4
#define	LED1		PB5		//dioda LED1 podłączona jest do pinu PB5
#define	LED2		PB6		//dioda LED2 podłączona jest do pinu PB6
#define	LED3		PB7		//dioda LED3 podłączona jest do pinu PB7
#define KEY0        PC0		//przycisk KEY0 podłączony jest do pinu PC0
#define KEY1        PC1		//przycisk KEY1 podłączony jest do pinu PC1
#define KEY2        PC2		//przycisk KEY2 podłączony jest do pinu PC2
#define KEY3        PC3		//przycisk KEY3 podłączony jest do pinu PC3
#define SW0         PC4		//przełącznik SW0 podłączony jest do pinu PC4
#define SW1         PC5		//przełącznik SW1 podłączony jest do pinu PC5
#define SW2         PC6		//przełącznik SW2 podłączony jest do pinu PC6
#define SW3         PC7		//przełącznik SW3 podłączony jest do pinu PC7
/* przyporządkowanie wyprowadzeń wyświetlacza LCD do pinów z określonych portów mikrokontrolera */
#define LCD_D0      PD0		//linię danych D0 LCD podłączono do pinu PD0
#define LCD_D1      PD1		//linię danych D1 LCD podłączono do pinu PD1
#define LCD_D2      PD2		//linię danych D2 LCD podłączono do pinu PD2
#define LCD_D3      PD3		//linię danych D3 LCD podłączono do pinu PD3
#define LCD_D4      PD4		//linię danych D4 LCD podłączono do pinu PD4
#define LCD_D5      PD5		//linię danych D5 LCD podłączono do pinu PD5
#define LCD_D6      PD6		//linię danych D6 LCD podłączono do pinu PD6
#define LCD_D7      PD7		//linię danych D7 LCD podłączono do pinu PD7
#define LCD_RS      PE2		//sygnał sterujący RS LCD podłączono do pinu PE2
#define LCD_EN      PE3		//sygnał sterujący EN LCD podłączono do pinu PE3
#define LCD_R_W     PE4		//sygnał sterujący R_W LCD podłączono do pinu PE4


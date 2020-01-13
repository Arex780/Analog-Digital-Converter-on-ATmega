/***************************************************************/
/* LCD.c - sterowanie alfanumerycznym wy�wietlaczem LCD        */
/*         20x4 (20 znak�w, 4 wiersze) poprzez                 */
/*         osiem linii danych ze sprawdzaniem flagi gotowo�ci  */
/***************************************************************/
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "LCD.h"
#include "teksty.h"
#include "deklara.h"
/********************  zmienne globalne  *******************/
char chtab[8]={'�','�','�','�','�','�','�','�'}; //do obs�ugi polskich znak�w

void check_busy_flag (void)	{
char flag=0x80;
	LCD_RD_FLAG;			// ustawienie sygna��w steruj�cych dla rozpocz�cia odczytu flagi zaj�to�ci
	LCD_DIR_DATA=0x00;		// ustawienie wej�� dla portu, do kt�rego pod��czono linie danych LCD
	while (flag!=0){
		LCD_EN_SET;				// ustawienie linii EN	
		asm("nop");				//wymagane wyd�u�enie impulsu do 230ns 1/16MHz = 62,5ns 6*62,5ns = 375ns
		asm("nop");				//jednocze�nie wymagany odczyt po minimum 160 ns < 4*62,5ns = 250ns
		asm("nop");	
#if VMLAB
		asm("nop");				
		asm("nop");				
		asm("nop");	
#endif	
		flag=LCD_DATA_IN&_BV(7);	// wyzerowanie bit�w poza flag� zaj�to�ci
		LCD_EN_CLEAR;			// zerowanie linii EN
		asm("nop");				// wymagane wyd�u�enie cyklu do 500 ns < 14*62,5ns = 875ns
		asm("nop");
		asm("nop");
	};
	LCD_DIR_DATA=0xFF;		// ustawienie wyj�� dla portu, do kt�rego pod��czono linie danych LCD	
};

void send_LCDdata (unsigned char LCDdata) {	//wys�anie bajtu do LCD
	check_busy_flag();		// sprawdzenie flagi zaj�to�ci
	LCD_WR_DATA;			// ustawienie sygna��w steruj�cych dla rozpocz�cia zapisu danej
// po 1 cyklu zegarowym czyli 1/16MHz=62.5us > 40us (minimalny dopuszczalny czas)	
	LCD_EN_SET;				// ustawienie linii EN	
	LCD_DATA_OUT = LCDdata;	//przes�anie bajtu danych do LCD_DATA_OUT
	asm("nop");				//wymagane wyd�u�enie impulsu do 230 ns < 7*62,5ns = 437ns
	asm("nop");		
	asm("nop");	
	asm("nop");	
#if VMLAB
	asm("nop");				
	asm("nop");	
#endif	
	LCD_EN_CLEAR;			// zerowanie linii EN
};
void send_LCDinstr (unsigned char LCDinstr) {	//wys�anie bajtu do LCD
	check_busy_flag();		// sprawdzenie flagi zaj�to�ci
	LCD_WR_INST;			// ustawienie sygna��w steruj�cych dla rozpocz�cia zapisu instrukcji
// po 1 cyklu zegarowym czyli 1/16MHz=62.5us > 40us (minimalny dopuszczalny czas)	
	LCD_EN_SET;				// ustawienie linii EN	
	LCD_DATA_OUT = LCDinstr;//przes�anie instrukcji do LCD_DATA_OUT
	asm("nop");				//wymagane wyd�u�enie impulsu do 230 ns < 7*62,5ns = 437ns
	asm("nop");	
	asm("nop");	
	asm("nop");	
#if VMLAB
	asm("nop");				
	asm("nop");				
#endif		
	LCD_EN_CLEAR;			// zerowanie linii EN
};
void send_LCDinstr_without_check_flag (unsigned char LCDinstr) {	//wyslanie bajtu do LCD
	LCD_WR_INST;			// ustawienie sygna��w steruj�cych dla rozpocz�cia zapisu instrukcji
// po 1 cyklu zegarowym czyli 1/16MHz=62.5us > 40us (minimalny dopuszczalny czas)	
	LCD_EN_SET;				// ustawienie linii EN	
	LCD_DATA_OUT = LCDinstr;//przes�anie bajtu danych do LCD_DATA_OUT
	asm("nop");				//wymagane wyd�u�enie impulsu do 230 ns < 7*62,5ns = 437ns
	asm("nop");
	asm("nop");	
	asm("nop");	
#if VMLAB
	asm("nop");				
	asm("nop");	
#endif			
	LCD_EN_CLEAR;			// zerowanie linii EN
};
void define_char(void) { 		// Funkcja definiuje polskie znaki 
	unsigned char i;
for (i=0; i<8; i++) {
/* Niepotrzebne definicje mo�na wprowadzi� do komentarza, aby zaoszcz�dzi� oko�o 20 bajt�w programu na ka�dej definicji) */
   	send_LCDinstr (i*8+0x40);	  //Ustawianie adresu dla pami�ci CGRAM
	if 		  (chtab[i] == '�') {send_gcram(14,17,17,17,31,17,17,2);  }//�	
	else if   (chtab[i] == '�') {send_gcram(2,14,21,16,16,17,14,0);   }//�
	else if   (chtab[i] == '�') {send_gcram(31,16,16,30,16,16,31,2);  }//�	
	else if   (chtab[i] == '�') {send_gcram(16,16,18,20,24,16,31,0);  }//�
	else if   (chtab[i] == '�') {send_gcram(2,21,25,21,19,17,17,0);   }//�
	else if   (chtab[i] == '�') {send_gcram(2,14,21,17,17,17,14,0);   }//�
	else if   (chtab[i] == '�') {send_gcram(2,14,16,14,1,1,30,0);     }//�
	else if   (chtab[i] == '�') {send_gcram(31,1,2,31,8,16,31,0);     }//�
//	else if   (chtab[i] == '�') {send_gcram(0,0,14,1,15,17,15,2);     }//�
//	else if   (chtab[i] == '�') {send_gcram(2,4,14,16,16,17,14,0);    }//��
//	else if   (chtab[i] == '�') {send_gcram(0,0,14,17,31,16,14,2);	  }//�
//	else if   (chtab[i] == '�') {send_gcram(12,4,6,12,4,4,14,0);      }//�
//	else if   (chtab[i] == '�') {send_gcram(2,4,22,25,17,17,17,0);    }//��
//	else if   (chtab[i] == '�') {send_gcram(2,4,14,16,16,17,14,0);    }//��
//	else if   (chtab[i] == '�') {send_gcram(2,4,15,16,14,1,30,0);     }//��
// 	else if   (chtab[i] == '�') {send_gcram(2,4,31,2,4,8,31,0);       }//��
//	else if   (chtab[i] == '�') {send_gcram(4,0,31,2,4,8,31,0);       }//�
	else                        {send_gcram(21,10,21,10,21,10,21,10); //szachownica gdy nie ma takiego	znaku
	};
};	
};
void send_gcram	(unsigned char v0,unsigned char v1,unsigned char v2,unsigned char v3,
	 			unsigned char v4,unsigned char v5,unsigned char v6,unsigned char v7) {
		 send_LCDdata(v0);send_LCDdata(v1);send_LCDdata(v2);send_LCDdata(v3);
		 send_LCDdata(v4);send_LCDdata(v5);send_LCDdata(v6);send_LCDdata(v7);				
}	
void send_LCDdata_pol(char LCDdata) {	//wys�anie bajtu do LCD
unsigned char j;						//z uwzgl�dnieniem polskich znak�w
	if (LCDdata>127)		 //je�li kod ASCII znaku wyzszy ni� 127 
	{						 //oznacza to jeden z polskich znak�w
	    for (j=0;j<8;)
	    {
			if (LCDdata == chtab[j]){  // zmiana warto�ci argumentu LCDdata
				LCDdata = j;				   // z kodu ASCII znaku na adres
				break;						   // od 0 do 7 w pami�ci CGRAM
			};
		j++;
	    };
	};
	send_LCDdata(LCDdata);
};

void init_LCD (void) {		//inicjalizacja wy�wietlacza LCD
//maksymalna warto�� op�nienia generowanego przez funkcj� _delay_ms wynosi 6.5535s z rozdzielczo�ci� 0.1 ms, a do czasu (2^16-1)*4/fclk[kHz]=16.38375 ms z rozdzielczo�ci� 2.5e-4 ms
	_delay_ms(40); 	//odmierzenie 15ms po w��czeniu zasilania 
	send_LCDinstr_without_check_flag(LCD_8bit_data); //ustawia 8 bitow� magistral� danych 	
	_delay_ms(4.1); 	//odmierzenie 4.1 ms po pierwszym wywo�aniu instrukcji LCD_8bit_data
 	send_LCDinstr_without_check_flag(LCD_8bit_data); //ustawia 8 bitow� magistral� danych 
	_delay_us(100); 	//odmierzenie 100 us po drugim wywo�aniu instrukcji LCD_8bit_data
	send_LCDinstr_without_check_flag(LCD_8bit_data); //ustawia 8 bitow� magistral� danych
	_delay_us(37); 	//odmierzenie 37 us po drugim wywo�aniu instrukcji LCD_8bit_data
	send_LCDinstr(LCD_8bit_data); //ustawia 8 bitow� magistral� danych
	send_LCDinstr(LCD_OFF);	   // D=0 - wy��czenie wy�wietlacza, C=0 - wy��czenie kursora, B=0 - wy��czenie migania kursora
	send_LCDinstr(LCD_CLEAR); //czy�ci wy�wietlacz LCD i 'Entry mode set' przesuwa kursor +1
	send_LCDinstr(LCD_MODE);  // I/D=1 - inkrementacja, S=0 - brak przesuni�cia zawarto�ci DDRAM
	send_LCDinstr(LCD_ON);	   // D=1 - w��czenie wy�wietlacza, C=0 - wy��czenie kursora, B=0 - wy��czenie migania kursora
};

// adresy pamiecie DDRAM dla poszczeg�lnych pozycji wy�wietlanych znak�w
//		 1	 2	 3	 4	 5	 6	 7	 8	 9	10	11	12	13	14	15	16	17	18	19	20
//
//1		00	01	02	03	04	05	06	07	08	09	0A	0B	0C	0D	0E	0F	10	11	12	13
//2		40	41	42	43	44	45	46	47	48	49	4A	4B	4C	4D	4E	4F	50	51	52	53
//3		14	15	16	17	18	19	1A	1B	1C	1D	1E	1F	20	21	22	23	24	25	26	27
//4		54	55	56	57	58	59	5A	5B	5C	5D	5E	5F	60	61	62	63	64	65	66	67
unsigned char address_DDRAM (unsigned char x, unsigned char y){
unsigned char xy;
switch(x)
	{
			case 1: 	xy=y-1; 		break;
			case 2:		xy=0x40+y-1;	break;
			case 3:		xy=0x14+y-1;	break;
			case 4:		xy=0x54+y-1;	break;
			default:	xy=y-1;
	};
return xy;	
};

void write_string_xy(unsigned char x, unsigned char y, PGM_P text) {  //pisz tekst na LCD wskazywany wska�nikiem *text
unsigned char nr = 0;
unsigned char xy;
volatile unsigned char zn;	
	xy=address_DDRAM(x, y);
	send_LCDinstr((xy|0x80));	// ustalenie pocz�tku tekstu
	while ((zn = pgm_read_byte(&text[nr++])) > '\0') { //sprawdzenie czy nie odczytano ostatniego znaku z wprowdzanego ci�gu znak�w
		send_LCDdata_pol(zn);  // umie�� wskazany znak tekstu na LCD
	}; 
};
void print_integer (unsigned char x, unsigned char y,signed int liczba, unsigned char calkowite, unsigned char ulamkowe){
	unsigned char xy;
	unsigned char j;
	unsigned char znak=0;	//domy�lna warto�� znaku dla liczby dodatniej
	unsigned zero=1;		//domy�lnie nie znaleziono cyfry r�nej od zera	
	signed char cyfry[5]; 	//tablica cyfr odpowiadaj�cych wprowadzanej liczbie
	xy=address_DDRAM(x, y);
	send_LCDinstr((xy|0x80));	//ustalenie pocz�tku tekstu
	if(liczba<0){
		liczba=-liczba;
		znak=1;					//zapamietanie, i� liczba jest ujemna
	};	
	//zamiana liczby na odpowiadaj�cy jej zbi�r cyfr	
	int_to_digits(liczba, calkowite+ulamkowe, cyfry);
	for(j=1; j<calkowite;j++){				//p�tla od najbardziej znacz�cej cyfry 
											//cz�ci ca�kowitej do przedostatniej 
		if((zero)&&(cyfry[j-1]>0)){
			zero=0;							//znaleziono pierwsz� cyfr� wi�ksz� od zera
			if(znak)			
				send_LCDdata('-');			//je�eli liczba jest ujemna przed pierwsz� 
											//cyfr� ca�kowit� jest umieszczony znak "-"
			else							//je�eli liczba jest dodatnia przed pierwsz�
				send_LCDdata(' ');			//cyfr� ca�kowit� jest umieszczony znak " "		
			send_LCDdata(cyfry[j-1]+48);	//konwersja, a nast�pnie wizualizacja   
		}									//pierwszej z cz�ci calkowitej cyfry
		else if(!zero)
			send_LCDdata(cyfry[j-1]+48);	//wizualizacja kolejnych cyfr cz�ci
		else								//ca�kowitej po wykryciu pierwszej cyfry > 0
			send_LCDdata(' ');				//przed wykryciem pierwszej cyfry cz�ci
	};										//ca�kowitej > 0 jest umieszczany znak " "
	if(zero){
		if(znak)							//je�eli nie wykryto cyfry > 0 przed ostatni�
			send_LCDdata('-');				//z cz�ci ca�kowitej jest umieszczony znak "-"
		else								//je�eli liczba jest dodatnia przed pierwsz�
			send_LCDdata(' ');				//cyfr� ca�kowit� jest umieszczony znak " "	
	};
	send_LCDdata(cyfry[calkowite-1]+48);	//konwersja i wizualizacja ostatniej cyfry ca�kowitej
	if(ulamkowe>0){							//je�eli funkcja ma wizualizowa� cyfry u�amkowe
		send_LCDdata('.');					//nalezy przes�a� po cyfrach ca�kowitych znak "."
		for(j=calkowite+1; j<=calkowite+ulamkowe;j++)
			send_LCDdata(cyfry[j-1]+48);	//wizualizacja cyfr u�amkowych
	};
};									
void int_to_digits(unsigned int liczba, unsigned char liczba_cyfr, signed char *pcyfry){
	unsigned char i;
		for(i=liczba_cyfr; i>=1;i--){	//generowanie adres�w dla kolejnych cyfr od najmniej znacz�cej
			*(pcyfry+i-1)=liczba%10;	//dzielenie modulo 10
			liczba/=10;					//dzielenie przez 10
		};
};
void print_three_digits(unsigned char x, unsigned char y, signed char *pcyfry, unsigned char miganie)
{
	unsigned char xy;
	xy=address_DDRAM(x, y);
	switch(menu)
	{
		case 0:
		{
		 int_to_digits(wsp_wypelnienia, 3, pcyfry);
		 send_LCDinstr((xy|0x80));
		if (cyfry[0]!=0)
			send_LCDdata(cyfry[0]+48);
		else
			send_LCDdata(32);
		if (cyfry[0]==0 && cyfry[1]==0)
			send_LCDdata(32);
		else
			send_LCDdata(cyfry[1]+48);
		 send_LCDdata(cyfry[2]+48);	
		 break;
		};
		case 1:
		{
		 send_LCDinstr((xy|0x80));	    
		 if(miganie==1)
			send_LCDdata(cyfry[0]+48);	
		 else
			send_LCDdata(32);
		 send_LCDdata(cyfry[1]+48);	
		 send_LCDdata(cyfry[2]+48);	
		 break;
		};
		case 2:
		{
		 send_LCDinstr((xy|0x80));	    
		 send_LCDdata(cyfry[0]+48);	
		 if(miganie==1)
			send_LCDdata(cyfry[1]+48);	
		 else
			send_LCDdata(32);		    
		 send_LCDdata(cyfry[2]+48);	
		 break;
		};
		case 3:
		{
		 send_LCDinstr((xy|0x80));	    
		 send_LCDdata(cyfry[0]+48);	
		 send_LCDdata(cyfry[1]+48);	
		 if(miganie==1)
			send_LCDdata(cyfry[2]+48);
		 else
			send_LCDdata(32);	
		 break;
		};
	};
};	

	
void window_1(void) {
	send_LCDinstr(LCD_CLEAR); //czy�ci wyswietlacz LCD  
//	send_LCDinstr(LCD_OFF);	   // D=0 - wy��czenie wy�wietlacza, C=0 - wy��czenie kursora, B=0 - wy��czenie migania kursora
	write_string_xy(1,2,o1_1);
	print_integer(1, 5, napiecie, 3, 0);
	write_string_xy(1, 10, o1_1a);
	write_string_xy(2,2,o1_2);
	print_integer(2,5,wsp_wypelnienia, 3, 0);
	write_string_xy(2,10,o1_2a);
	write_string_xy(3,2,o1_3);
	print_integer(3, 5, prad, 3, 0);
	write_string_xy(3, 10, o1_3a);
	write_string_xy(4,2,o1_4);
	print_integer(4, 5, napiecie*prad, 3, 0);
	write_string_xy(4,10,o1_4a);
};
void window_2(void)
{
	print_three_digits(2,5,cyfry,miganie);
	print_integer(3,5,prad,3,0);
};

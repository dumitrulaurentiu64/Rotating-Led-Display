#include <avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t secventa =1; //variabila globala folosita in rutina de intrerupere a timer-ului 0

volatile uint8_t indexSecventa = 0; //variabila globala folosita in rutina de intrerupere a timer-ului 0

void timer1Init(){ // initializare timer1

  TCCR1B |= (1 << CS12) | (1 << CS10); //setare prescaler pe 1024 => frecventa este impartita la 1024
  
  sei(); // enable la intreruperi
  
}

void timer0Init(){

        TCCR0A |= (1 << WGM01); // punerea timer-ului 0 in modul CTC 

       TIMSK0 |= (1 << OCIE0A);  //enable timer compare interrupt,
        
        TCCR0B |= (1 << CS02) | (1 << CS00);  //setare prescaler pe 1024 => frecventa este impartita la 1024
     
}





ISR (INT0_vect) // rutina de intrerupere a intreruperii externe ( cea care vine de la senzorul Hall la fiecare rotatie a barii )
{               // Aceasta se activeaza la fiecare rotire facuta
 
   secventa = TCNT1/72; // TCNT1 este registrul in care se gaseste valoarea incrementata de timer-ul 1
   TCNT1=0; // se reseteaza valoarea din registrul
   OCR0A=secventa; // timer-ul 0 e in pus in mod ctc/compare, astfel registrul corespunzator timer-ului 0 ( adica TCNT0 ) 
                   // se reseteaza si va activa rutina de intrerupere a timer-ului 0 atunci cand va ajunge la valoarea din OCR0A
   indexSecventa=0; // senzorul a trecut pe langa magnet, asta inseamna ca se reseteaza indexul
  
}

ISR (TIMER0_COMPA_vect) //rutina de intrerupere a timer-ului 0
{ // o rotatie inseamna 360 de grade, in aceasta rotatie sunt 72 de secvente ( de asta mai sus in ... se imparte la 72, adica o secventa la fiecare 5 grade
  // Asta inseamna ca ledurile isi schimba valoarea la fiecare 5 grade parcurse in acea rotatie sau in timp la cateva milisecunde
  // "timpul a fost calculat cu ajutorul comunicatiei seriale intr-un pas anterior prezentat la laborator", asta in cazul in care te intreaba cum ai stiut timpul
 
  // in if-uri practic se aprind/sting ledurile in functie de index, pentru a afisa am avut nevoie doar de 38 de secvente din totalul de 72 de secvente
  if (indexSecventa == 0) ///////////// afisare P
  {
    afis_col(1, 1, 1, 1, 1, 1, 1);
  }
  else if (indexSecventa == 1)
  {
    afis_col(1, 0, 0, 1, 0, 0, 0);
  }
  else if (indexSecventa == 2)
  {
    afis_col(1, 0, 0, 1, 0, 0, 0);
  }
  else if (indexSecventa == 3)
  {
    afis_col(0, 1, 1, 0, 0, 0, 0);
  }
  else if (indexSecventa == 4)
  {
    afis_col(0, 0, 0, 0, 0, 0, 0);
  }
  else if (indexSecventa == 5)
  {
   afis_col(0, 0, 0, 0, 0, 0, 0);
  }
  else if (indexSecventa == 6) //////// afisare S
  {
  afis_col(0,1,1,0,0,0,1);
  }
  else if (indexSecventa == 7)
  {
  afis_col(1,0,0,1,0,0,1);
   }
  else if (indexSecventa == 8)
  {
  afis_col(1,0,0,1,0,0,1);
   }
  else if (indexSecventa == 9)
  {
  afis_col(1,0,0,1,0,0,1);
   }
  else if (indexSecventa == 10)
  {
  afis_col(1,0,0,0,1,1,0);
  }
   else if (indexSecventa == 11)
  {
   afis_col(0, 0, 0, 0, 0, 0, 0);
  }
  else if (indexSecventa == 12)
  {
   afis_col(0, 0, 0, 0, 0, 0, 0);
  }
  else if (indexSecventa == 13) //////// afisare 2
  {
  afis_col(0,1,1,0,0,0,1);
  }
  else if (indexSecventa == 14)
  {
  afis_col(1,0,0,1,0,0,1);
  }
  else if (indexSecventa == 15)
  {
   afis_col(1,0,0,0,1,0,1);
   }
  else if (indexSecventa == 16)
  {
  afis_col(1,0,0,0,1,0,1);
   }
  else if (indexSecventa == 17)
  {
  afis_col(0,1,0,0,0,1,1); 
  }
   else if (indexSecventa == 18)
  {
   afis_col(0,0,0,0,0,0,0);
  }
  else if (indexSecventa == 19)
  {
    afis_col(0,0,0,0,0,0,0);
  }
  else if ( indexSecventa == 20) ////////afisare  0
  {
     afis_col(0,1,1,1,1,1,0);
  }
  else if ( indexSecventa == 21) 
  {
  afis_col(1,0,0,0,0,0,1);
  }
  else if ( indexSecventa == 22) 
  {
  afis_col(1,0,0,0,0,0,1);
  }
  else if ( indexSecventa == 23) 
  {
  afis_col(1,0,0,0,0,0,1);
  }
  else if ( indexSecventa == 24) 
  {
  afis_col(0,1,1,1,1,1,0);
  }
  else if ( indexSecventa == 25) 
  {
    afis_col(0,0,0,0,0,0,0);
  }
  else if ( indexSecventa == 26) 
  {
  afis_col(0,0,0,0,0,0,0);
  }
  else if ( indexSecventa == 27) //////// afisare 1
  {
   afis_col(0,0,0,0,0,0,1);
  }
  else if ( indexSecventa == 28)
  {
  afis_col(0,0,0,0,0,0,1);
  }
  else if ( indexSecventa == 29)
  {
     afis_col(1,1,1,1,1,1,1);
  }
  else if ( indexSecventa == 30) 
{
    afis_col(0,1,0,0,0,0,1);
  }
  else if ( indexSecventa == 31) 
  {
    afis_col(0,0,1,0,0,0,1);
  }
    else if ( indexSecventa == 32) 
  {
  afis_col(0,0,0,0,0,0,0);
  }
    else if ( indexSecventa == 33) 
  {
    afis_col(0,0,0,0,0,0,0);
  }
  else if ( indexSecventa == 34) ////// afisare 9
  {
    afis_col(0,1,1,1,1,1,0);
  }
  else if ( indexSecventa == 35)
  {
    afis_col(1,0,0,1,0,0,1);
  }
  else if ( indexSecventa == 36)
  {
    afis_col(1,0,0,1,0,0,1);  
  }
  else if ( indexSecventa == 37) 
  {
    afis_col(1,0,0,1,0,0,1);  
  }
  else if ( indexSecventa == 38) 
  {
     afis_col(0,1,1,0,0,0,1);    
  }
    else
  {
     afis_col(0,0,0,0,0,0,0);
  }
  

  indexSecventa++; // dupa fiecare apelare de functie ( afis_col ) indexul trece la urmatoarea secventa
  indexSecventa=indexSecventa%72; // cand indexul ajunge la 72, acesta se reseteaza, asta inseamna ca bara teoretic a facut o rotatie
   
}

int main()
{
  DDRB= 0x01; //setare pini pentru led-uri
  DDRD|=0xBB; //setare pini pentru led-uri
  DDRC |= (1<< 5) | ( 1<< 4); //setare pini pentru led-uri
  DDRD &= ~(1 << DDD2);     // Clear the PD2 pin/Pune pe 0 pinul PD2
  

  PORTD |= (1 << PORTD2); //Activeaza pinul PD2 pentru a primi intrerupere de la senzor, intreruperea 
                          // externa poate sa vina doar la pinul acela
                          // turn On the Pull-up
                          // PD2 is now an input with pull-up enabled
  
  
  EICRA |= (1 << ISC01)|(1<<ISC00);    // set INT0 to trigger on Rising  edge, intreruperea externa este "trigger-uita"
                                       // doar pe front coborator ( adica doar cand senzorul se departeaza de magnet )
                                       // Pe front coborator nu se activeaza intreruperea ( adica cand se aproprie )
                                       
  EIMSK |= (1 << INT0);     // Turns on INT0
  
  sei();     // Enable global interrupts by setting global interrupt enable bit in SREG
  
  timer1Init(); // setup timer1, initializeaza timerele
  timer0Init(); // setup timer0, initializeaza timerele(vezi functiile de mai sus)

  while(1) // Un loop infinit in care nu se intampla nimic, este folosit ca sa nu fie oprita rularea programului
           // totul se face doar din intreruperi
  {
 
  }
}

void afis_col(int led1, int led2, int led3, int led4, int led5, int led6, int led7){ //Functia aceasta primeste ca parametrii 0 sau 1, in functie de aceste valori se aprind
                                                                                     // sau se sting ledurile, 0 - stins, 1 - aprins
  if (led1==0) {PORTD &= ~0x08;} else {PORTD |= 0x08;} //setare bit pe 0 respectiv pe 1 in else
  if (led2==0) {PORTD &= ~0x10;} else {PORTD |= 0x10;}
  if (led3==0) {PORTD &= ~0x20;} else {PORTD |= 0x20;}//aprindere leduri corespunzator cu parametrii functiei 
  if (led4==0) {PORTC &= ~0x20;} else {PORTC |= 0x20;}
  if (led5==0) {PORTB &= ~0x01;} else {PORTB |= 0x01;}//led 1 = cel din capatul barii
  if (led6==0) {PORTC &= ~0x10;} else {PORTC |= 0x10;}//led7 = penultimul led ( langa suportul de baterie )
  if (led7==0) {PORTD &= ~0x80;} else {PORTD |= 0x80;}
                                                      //ledul 8 exista dar nu l-am folosit, este ledul chiar de langa suportul de baterie
}

void P(){ // aici este modelul pentru fiecare caracter folosit, nu folosim direct functia ci se copiaza valorile de aici si se pun
          // in rutina de intrerupere a timer-ului 0 ( la fel si pentru celelalte caractere de mai jos )
  afis_col(1,1,1,1,1,1,1);
  afis_col(1,0,0,1,0,0,0);
  afis_col(1,0,0,1,0,0,0);
  afis_col(0,1,1,0,0,0,0);

}

void S(){
  afis_col(0,1,1,0,0,0,1);
  afis_col(1,0,0,1,0,0,1);
  afis_col(1,0,0,1,0,0,1);
  afis_col(1,0,0,1,0,0,1);
  afis_col(1,0,0,0,1,1,0);
}

void doi(){
  afis_col(0,1,1,0,0,0,1);
  afis_col(1,0,0,1,0,0,1);
  afis_col(1,0,0,0,1,0,1);
  afis_col(1,0,0,0,1,0,1);
  afis_col(0,1,0,0,0,1,1);
}

void zero(){
  afis_col(0,1,1,1,1,1,0);
  afis_col(1,0,0,0,0,0,1);
  afis_col(1,0,0,0,0,0,1);
  afis_col(1,0,0,0,0,0,1);
  afis_col(0,1,1,1,1,1,0);
}

void noua(){
  afis_col(0,1,1,1,1,1,0);
  afis_col(1,0,0,1,0,0,1);
  afis_col(1,0,0,1,0,0,1);
  afis_col(1,0,0,1,0,0,1);
  afis_col(0,1,1,0,0,0,1);
}

void unu(){
  afis_col(0,0,0,0,0,0,1);
  afis_col(0,0,0,0,0,0,1);
  afis_col(1,1,1,1,1,1,1);
  afis_col(0,1,0,0,0,0,1);
  afis_col(0,0,1,0,0,0,1);
}

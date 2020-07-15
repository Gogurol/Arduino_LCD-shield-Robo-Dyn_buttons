#include <LiquidCrystal.h> //biblioteka do obsługi LCD

LiquidCrystal lcd (8,9,4,5,6,7); //piny pod ktory jest podpiety wyswietlacz
   int numRows = 2;
   int numCols = 16;
   //^ "opis" wyswietlacza: wiersze; kolumny;
   
   char* buttons[] ={"Gora", "W dol", "W lewo", "W prawo", "Wybierz"};
   //^tablica/wskaznik do przechowywania napisow wyswielanych po nacisniecu przyciskow

  unsigned long tap_time = 0UL;   //zmienna na czas wduszenia klawisza (w mils)
  unsigned long wait_time = 100UL ; //zmienna na odczekanie do stabilizacji przycisku
  // ^ bieda debouncing
  int buttons_pin = A0; // tutaj, bo mi funkcje nie widza :(
  
void setup() {
   
   lcd.begin(numRows,numCols);
   lcd.clear();
   
   pinMode(buttons_pin, INPUT); //pod A0 jest piec przyciskow na shield'zie
   Serial.begin(9600); //by dzialala funkcja podlgad
   lcd.print("Tap button");
   }

void loop() {
  
  //int Volt (analogRead(A0));
  

  if (analogRead(buttons_pin) <1021) button_decode();  
    
  
   
}

void podglad(int x) { //do odczytu zmiennych przez interfejs UART

    Serial.println(x);
}

 byte przyciski (int Volt){

  tap_time = millis();

  if ((Volt ==0 && Volt <140) && (millis() + tap_time > wait_time)) {//przycsk prawo

   return 3;
   
   }
   
  else if ((Volt >144 && Volt <323) && (millis() + tap_time > wait_time)){//przycsk gora
    
   return 0;
  }
  else if ((Volt > 327 && Volt <500) && (millis() + tap_time > wait_time)){//przycsk dol
    
   return 1;
  }
 else if ((Volt > 504 && Volt <740) && (millis() + tap_time > wait_time)){//przycsk lewo
    return 2;
  }
  else if ((Volt > 741 && Volt <1000) && (millis() + tap_time > wait_time)){//przycsk select
    return 4;
  }
  
 }

 void button_decode(){

  int Volt (analogRead(buttons_pin));

  byte button_state = 5;
  button_state = przyciski(Volt);

  podglad(button_state);


    switch (przyciski(Volt)) {
    case 3:
      
      podglad(Volt);
      podglad(button_state);
      
      
      lcd.clear();
      lcd.print(buttons[3]);
       
    break;
      
    case  0:
      podglad(Volt);
      lcd.clear();
      lcd.print(buttons[0]);
      break;

    case 1:
      podglad(Volt);
      lcd.clear();
      lcd.print(buttons[1]);
      break;
      
    case 2:
      podglad(Volt);
      lcd.clear();
      lcd.print(buttons[2]);      
      break;
      
    case 4:
      podglad(Volt);
      lcd.clear();
      lcd.print(buttons[4]);      
      break;
    
    default:
      // if nothing else matches, do the default
      // default is optional
    break;
  }
  
  
 }

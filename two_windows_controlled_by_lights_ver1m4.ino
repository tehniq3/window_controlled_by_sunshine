/*
- sketch pentru deschidere automata 2 fereastra (control independent)
cand este lumina si inchidere cand e noapte
- sketch scris de Nicu Florica pentru Dan Olaru
- versine 1.4 din 10.06.2016, Craiova
- vizitati http://www.tehnic.go.ro
- vizitati si http://www.arduinotehniq.com
- vizitati canalul de filmulete: https://www.youtube.com/channel/UCm-OQ7YTHGcRV6sMTY6mHHw
*/

#define lum1pin 6
#define lum11pin 2
#define lum12pin 3
#define sus1  4
#define jos1 5

#define lum2pin 11
#define lum21pin 7
#define lum22pin 8
#define sus2  9
#define jos2 10


int lum1;   // variabila pentru citire intensitate luminoasa la senzor 1
int lum2;   // variabila pentru citire intensitate luminoasa la senzor 2

unsigned long timp0;   // timp initial masurare intensitate luminoasa
unsigned long timp1;   // timp curent
unsigned long timp11;  // timp initial comenzi motor 1
unsigned long timp21;  // timp initial comenzi motor 2
unsigned long timp2;   // timp initial masurare intensitate luminoasa


long asteptare = 5000; // interval intre masuratori (3sec)
long stopmotor = 5000; // timp ignoare comenzi de schimbare directie rotatie motor
byte sens1 = 0;        // directie motor 1 (0 - oprit, 1 - stanga, 2 - dreapta 
byte sens2 = 0;        // directie motor 2 (0 - oprit, 1 - stanga, 2 - dreapta 
byte inchis1 = 0;      // variabila pentru depistare ajungere la capat sau pe traseu (0 = nu e la capat, 1 e la capat) 
byte inchis2 = 0;      // variabila pentru depistare ajungere la capat sau pe traseu (0 = nu e la capat, 1 e la capat) 
byte deschis1 = 0;
byte deschis2 = 0;

void setup() {
  
Serial.begin(9600);       // pornesc monitorizarea seriala
Serial.println("");
Serial.println("");
Serial.println("");
Serial.println("");
Serial.println("Sistem pentru deschiderea/inchiderea a 2 ferestre functie de intensitatea luminoasa");
Serial.println("Automatic system for independent control at two windows according sunlight..");
delay(1000);
Serial.println("proiect original al lui Nicu FLORICA (niq_ro)");
Serial.println("original project by Nicu FLORICA (niq_ro)");
delay(1000);
Serial.println("06.2016 - Craiova, Romania, Europa ;)");

   pinMode(lum1pin, INPUT);  // pinul pentru foto rezistenta 1
   pinMode(lum11pin, INPUT);  // pinul pentru limitatorul 1 pentru sus la circuitul 1
   pinMode(lum12pin, INPUT);  // pinul pentru limitatorul 2 pentru jos la circuitul 1
   digitalWrite(lum11pin, HIGH);  // in repaus (fara contact)   
   digitalWrite(lum12pin, HIGH);  // in repaus (fara contact)   

   pinMode(lum2pin, INPUT);  // pinul pentru foto rezistenta 2
   pinMode(lum21pin, INPUT);  // pinul pentru limitatorul 1 pentru sus la circuitul 2
   pinMode(lum22pin, INPUT);  // pinul pentru limitatorul 2 pentru jos la circuitul 2
   digitalWrite(lum21pin, HIGH);  // in repaus (fara contact)   
   digitalWrite(lum22pin, HIGH);  // in repaus (fara contact)   

  pinMode(sus1, OUTPUT); // control releu 1 de la canal 1
  pinMode(jos1, OUTPUT); // control releu 2 de la canal 1
  pinMode(sus2, OUTPUT); // control releu 1 de la canal 2
  pinMode(jos2, OUTPUT); // control releu 2 de la canal 2
   digitalWrite(sus1, LOW);  // in repaus (fara contact)   
   digitalWrite(jos1, LOW);  // in repaus (fara contact)   
   digitalWrite(sus2, LOW);  // in repaus (fara contact)   
   digitalWrite(jos2, LOW);  // in repaus (fara contact)   

timp0 = millis();
timp11 = timp0;

lum1 = digitalRead(lum1pin);  // se citeste valoarea intenstatii luminoase pe senzorul 1  
lum2 = digitalRead(lum1pin);  // se citeste valoarea intenstatii luminoase pe senzorul 2  
delay(1000);
}

void loop () {

timp1 = millis(); //timp curent 

if (timp1 - timp0 > asteptare) {
Serial.println("");
Serial.println("Se masoara intensitatea luminoasa !!!");
Serial.println("Now, Arduino measure the light..");
timp0 = timp1;   // timpul vechi se inoieste
Serial.println("---------------------------");
Serial.print("Intensitate lumininoasa zona 1 = ");
Serial.print("Light in first zone = ");
Serial.println(1-digitalRead(lum1pin));
Serial.print("Intensitate lumininoasa zona 2 = ");
Serial.print("Light in second zone = ");
Serial.println(1-digitalRead(lum2pin));
Serial.println("---------------------------");
}

// circuit 1
if (digitalRead(lum1pin) == LOW)   // daca e soare puternic
  {
  Serial.print(" 1* ");
  digitalWrite(jos1, LOW);  
    if (digitalRead(lum11pin) == HIGH) // daca fereastra e intredeschisa
    {
    sens1 = 1;
    }   // sfarsit de conditie de cap de cursa

    if (digitalRead(lum11pin) == LOW) // daca fereastra s-a deschis complet
    {
    sens1 = 0;
    deschis1 = 1;
    inchis1 = 0;
    }  // sfarsit de conditie de cap de cursa
  }  // sfarsit de conditie de zi

if (digitalRead(lum1pin) == HIGH)   // daca e aprope de apus
  {
    Serial.print(" 1) ");
 
  digitalWrite(sus1, LOW);  
    if (digitalRead(lum12pin) == HIGH) // daca fereastra e intredeschisa
    {
    sens1 = 2;
    }   // sfarsit de conditie de cap de cursa

    if (digitalRead(lum12pin) == LOW) // daca fereastra s-a inchis complet
    {
    sens1 = 0;
    inchis1 = 1;
    deschis1 = 0;
    }  // sfarsit de conditie de cap de cursa
  }  // sfarsit de conditie de zi


// circuit 2
if (digitalRead(lum2pin) == LOW)   // daca e soare puternic
  {
  Serial.print(" 2* ");
  digitalWrite(jos2, LOW);  
    if (digitalRead(lum21pin) == HIGH) // daca fereastra e intredeschisa
    {
    sens2 = 1;
    }   // sfarsit de conditie de cap de cursa

    if (digitalRead(lum21pin) == LOW) // daca fereastra s-a deschis complet
    {
    sens2 = 0;
    deschis2 = 1;
    inchis2 = 0;
    }  // sfarsit de conditie de cap de cursa
  }  // sfarsit de conditie de zi

if (digitalRead(lum2pin) == HIGH)   // daca e aprope de apus
  {
    Serial.print(" 2) ");
 
  digitalWrite(sus2, LOW);  
    if (digitalRead(lum22pin) == HIGH) // daca fereastra e intredeschisa
    {
    sens2 = 2;
    }   // sfarsit de conditie de cap de cursa

    if (digitalRead(lum22pin) == LOW) // daca fereastra s-a inchis complet
    {
    sens2 = 0;
    inchis2 = 1;
    deschis2 = 0;
    }  // sfarsit de conditie de cap de cursa
  }  // sfarsit de conditie de zi


// decizii control motor 1
if (sens1 == 0) // motor1 oprit
    {
    digitalWrite(jos1, LOW);   
    digitalWrite(sus1, LOW);
   Serial.println("===="); 
    }
if (timp11 - timp0 > stopmotor) {
 
if ((sens1 == 1) and (deschis1 == 0)) // motor1 pornit in sensul 1
    {
    digitalWrite(jos1, LOW);   
    digitalWrite(sus1, HIGH); 
      Serial.println(""); 
      Serial.println("Fereastra 1 nu s-a deschis complet !!!"); 
      Serial.println("Window no.1 is not open !!!"); 
      Serial.println(">>>"); 
    timp11 = timp0;
    }
if ((sens1 == 1) and (deschis1 == 1)) // motor1 pornit in sensul 1
    {
    digitalWrite(jos1, LOW);   
    digitalWrite(sus1, LOW); 
      Serial.println("");
      Serial.println("Fereastra 1 s-a deschis complet !!!"); 
      Serial.println("Window no.1 is open !!!"); 
      Serial.println(">|"); 
   // timp11 = timp0;
    }

if ((sens1 == 2) and (inchis1 == 0)) // motor1 pornit in sensul opus (2)
    {
    digitalWrite(jos1, HIGH);   
    digitalWrite(sus1, LOW);
      Serial.println(""); 
      Serial.println("Fereastra 1 nu s-a inchis complet !!!");  
      Serial.println("Window no.1 is not close !!!"); 
      Serial.println("<<<<");
    timp11 = timp0;  
  }
if ((sens1 == 2) and (inchis1 == 1)) // motor1 pornit in sensul opus (2)
    {
    digitalWrite(jos1, LOW);   
    digitalWrite(sus1, LOW);
      Serial.println(""); 
      Serial.println("Fereastra 1 s-a inchis complet !!!");  
      Serial.println("Window no.1 is close !!!"); 
      Serial.println("|<");
    timp11 = timp0;  
  }
}

// decizii control motor 2
if (sens2 == 0) // motor 2 oprit
    {
    digitalWrite(jos2, LOW);   
    digitalWrite(sus2, LOW);
   Serial.println("===="); 
    
    }
if (timp21 - timp0 > stopmotor) {
 
if ((sens2 == 1) and (deschis2 == 0)) // motor 2 pornit in sensul 1
    {
    digitalWrite(jos2, LOW);   
    digitalWrite(sus2, HIGH); 
      Serial.println(""); 
      Serial.println("Fereastra 2 nu s-a deschis complet !!!"); 
      Serial.println("Window no.2 is not open !!!"); 
      Serial.println(">>>"); 
    timp21 = timp0;
    }
if ((sens2 == 1) and (deschis2 == 1)) // motor 2 pornit in sensul 1
    {
    digitalWrite(jos2, LOW);   
    digitalWrite(sus2, LOW); 
      Serial.println("");
      Serial.println("Fereastra 2 s-a deschis complet !!!"); 
      Serial.println("Window no.2 is open !!!"); 
      Serial.println(">|"); 
    }

if ((sens2 == 2) and (inchis2 == 0)) // motor 2 pornit in sensul opus (2)
    {
    digitalWrite(jos2, HIGH);   
    digitalWrite(sus2, LOW);
      Serial.println(""); 
      Serial.println("Fereastra 2 nu s-a inchis complet !!!");  
      Serial.println("Window no.2 is not close !!!"); 
      Serial.println("<<<<");
    timp21 = timp0;  
  }
if ((sens2 == 2) and (inchis2 == 1)) // motor 2 pornit in sensul opus (2)
    {
    digitalWrite(jos2, LOW);   
    digitalWrite(sus2, LOW);
      Serial.println(""); 
      Serial.println("Fereastra 2 s-a inchis complet !!!");  
      Serial.println("Window no.2 is close !!!"); 
      Serial.println("|<");
    timp21 = timp0;  
  }


}  




delay(500);  // se asteapta putin  
}  // sfarsit de program principal


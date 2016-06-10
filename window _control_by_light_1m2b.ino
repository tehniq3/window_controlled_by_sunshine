/*
- sketch pentru deschidere automata fereastra
cand este lumina si inchidere cand e noapte
- sketch scris de Nicu Florica pentru Dan Olaru
- versine 1.2b din 06.0.6.2016, Craiova
- vizitati http://www.tehnic.go.ro
- vizitati si http://www.arduinotehniq.com
- vizitati canalul de filmulete: https://www.youtube.com/channel/UCm-OQ7YTHGcRV6sMTY6mHHw
*/

#define lum1pin 7
#define lum11pin 2
#define lum12pin 3
#define sus1  4
#define jos1 5

int lum1;   // variabila pentru citire intensitate luminoasa la senzor 1
//int lum1min = 100; // valoare pentru lumina de seara
//int lum1max = 500; // valoare pentru lumina de zi

unsigned long timp0;   // timp initial masurare intensitate luminoasa
unsigned long timp1;   // timp curent
unsigned long timp11;  // timp initial comenzi motor

long asteptare = 5000; // interval intre masuratori (3sec)
long stopmotor = 5000; // timp ignoare comenzi de schimbare directie rotatie motor
byte sens1 = 0;        // directie motor1 (0 - oprit, 1 - stanga, 2 - dreapta 
byte inchis1 = 0;      // variabila pentru depistare ajungere la capat sau pe traseu (0 = nu e la capat, 1 e la capat) 
byte deschis1 = 0;

void setup() {
  
   Serial.begin(9600);       // pornesc monitorizarea seriala
Serial.println("");
Serial.println("");
Serial.println("");
Serial.println("");
Serial.println("Sistem pentru deschiderea/inchiderea unei ferestre functie de intensitatea luminoasa");
Serial.println("Automatic system for control window according sunlight..");
delay(1000);
Serial.println("proiect original al lui Nicu FLORICA (niq_ro)");
Serial.println("original project by Nicu FLORICA (niq_ro)");
delay(1000);
Serial.println("06.2016 - Craiova, Romania, Europa ;)");

   pinMode(lum1pin, INPUT);  // pinul pentru foto rezistenta 1
   pinMode(lum11pin, INPUT);  // pinul pentru limitatorul 1 pentru sus la circuitul 1
   pinMode(lum12pin, INPUT);  // pinul pentru limitatorul 2 pentru jos la circuitul 1
   digitalWrite(lum11pin, HIGH);  // in repaus (fara conact)   
   digitalWrite(lum12pin, HIGH);  // in repaus (fara conact)   

  pinMode(sus1, OUTPUT);
  pinMode(jos1, OUTPUT);
   digitalWrite(sus1, LOW);  // in repaus (fara conact)   
   digitalWrite(jos1, LOW);  // in repaus (fara conact)   

timp0 = millis();
timp11 = timp0;

lum1 = digitalRead(lum1pin);  // se citeste valoarea intenstatii luminoase pe senzorul 1  
delay(1000);
}

void loop () {

timp1 = millis(); //timp curent 

if (timp1 - timp0 > asteptare) {
Serial.println("");
Serial.println("Se masoara intensitatea luminoasa !!!");
Serial.println("Now, Arduino measure the light..");
timp0 = timp1;   // timpul vechi se inoieste
//lum1 = digitalRead(lum1pin);  // se citeste valoarea intenstatii luminoase pe senzorul 1  
//lum1 = lum1min/2;    // intuneric
//lum1 = (lum1min + lum1max)/2;  // lunima ok
//lum1 = lum1max + lum1min/2; // lumina puternica
Serial.println("---------------------------");
Serial.print("Intensitate lumininoasa = ");
Serial.print("Light = ");
Serial.println(1-digitalRead(lum1pin));
Serial.println("---------------------------");
}

if (digitalRead(lum1pin) == LOW)   // daca e soare puternic
  {
//  Serial.println("Lumina de zi !!!");
  Serial.print("*");
  digitalWrite(jos1, LOW);  
    if (digitalRead(lum11pin) == HIGH) // daca fereastra e intredeschisa
    {
//    Serial.println("Fereastra nu e deschisa complet !!!");  
//    Serial.println(">>");  
//    digitalWrite(sus1, HIGH); 
    sens1 = 1;
    }   // sfarsit de conditie de cap de cursa

    if (digitalRead(lum11pin) == LOW) // daca fereastra s-a deschis complet
    {
//    Serial.println("Fereastra s-a deschis complet !!!"); 
//    Serial.println("Motoras oprit !!!"); 
    sens1 = 0;
    deschis1 = 1;
    inchis1 = 0;
//    digitalWrite(sus1, LOW); 
    }  // sfarsit de conditie de cap de cursa
  }  // sfarsit de conditie de zi

if (digitalRead(lum1pin) == HIGH)   // daca e aprope de apus
  {
  //Serial.println("Lumina de noapte !!!");
    Serial.print(")");
  
  digitalWrite(sus1, LOW);  
    if (digitalRead(lum12pin) == HIGH) // daca fereastra e intredeschisa
    {
//    Serial.println("Fereastra nu e deschisa complet !!!");  
//    Serial.println("<<");
//    digitalWrite(jos1, HIGH); 
    sens1 = 2;
    }   // sfarsit de conditie de cap de cursa

    if (digitalRead(lum12pin) == LOW) // daca fereastra s-a inchis complet
    {
//    Serial.println("Fereastra s-a inchis complet !!!");  
//    Serial.println("Motoras oprit !!!");
//    digitalWrite(jos1, LOW); 
    sens1 = 0;
    inchis1 = 1;
    deschis1 = 0;
    }  // sfarsit de conditie de cap de cursa
  }  // sfarsit de conditie de zi

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
      Serial.println("Fereastra nu s-a deschis complet !!!"); 
      Serial.println("Window is not open !!!"); 
      Serial.println(">>>"); 
    timp11 = timp0;
    }
if ((sens1 == 1) and (deschis1 == 1)) // motor1 pornit in sensul 1
    {
    digitalWrite(jos1, LOW);   
    digitalWrite(sus1, LOW); 
      Serial.println("");
      Serial.println("Fereastra s-a deschis complet !!!"); 
      Serial.println("Window is open !!!"); 
      Serial.println(">|"); 
   // timp11 = timp0;
    }

if ((sens1 == 2) and (inchis1 == 0)) // motor1 pornit in sensul opus (2)
    {
    digitalWrite(jos1, HIGH);   
    digitalWrite(sus1, LOW);
      Serial.println(""); 
      Serial.println("Fereastra nu s-a inchis complet !!!");  
      Serial.println("Window is not close !!!"); 
      Serial.println("<<<<");
    timp11 = timp0;  
  }
if ((sens1 == 2) and (inchis1 == 1)) // motor1 pornit in sensul opus (2)
    {
    digitalWrite(jos1, LOW);   
    digitalWrite(sus1, LOW);
      Serial.println(""); 
      Serial.println("Fereastra s-a inchis complet !!!");  
      Serial.println("Window is close !!!"); 
      Serial.println("|<");
    timp11 = timp0;  
  }



}  




delay(500);  // se asteapta putin  
}  // sfarsit de program principal


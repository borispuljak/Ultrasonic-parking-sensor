//LCD library
#include <LiquidCrystal.h> 
//LED diode
int zelena=1;
int zuta=2;
int crvena=3;
//SENZOR UDALJENOSTI
int echo=4;
int trig=5;
//vrijeme potrebno pulsu da se vrati natrag
float trajanje;
//jednosmjerna udaljenost prijeđena od strane pulsa
float udaljenost;
//LCD ZASLON //lcd(RS,EN,D4,D5,D6,D7)
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
//ZUJALICA
int zujalica = 12;
void setup()
{
 lcd.begin(16, 2);
 
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
 
 pinMode(crvena, OUTPUT);
 pinMode(zelena, OUTPUT);
 pinMode(zuta, OUTPUT);
 
 pinMode(zujalica, OUTPUT);
}
void loop()
{
 mjerenje_vremena();
 
 //udaljenost u cm izražena preko brzine zvuka i vremena
 //potrebno da impuls napravi put dva puta(naprijed i natrag)
 
 udaljenost = trajanje * (0.0343) / 2; 
 pokazi_udaljenost(); 
 
 ledice();
 delay(100);
}
//funkcija za mjerenje vremena potrebnog impulsu da se vrati natrag
void mjerenje_vremena()
{ 
 
 digitalWrite(trig, LOW);
 delayMicroseconds(2);
 
 digitalWrite(trig, HIGH);
 delayMicroseconds(10);
 digitalWrite(trig, LOW);
 
 trajanje = pulseIn(echo, HIGH);
}
//funckija koja pali ledice,
//ispisuje na lcd zaslon je li sigurno još voziti ili se auto treba zaustaviti
//i zujalica ispusta frekvenciju
//u ovisnosti kolika je udaljenost
void ledice() 
{
 
 if (udaljenost>=120)
 {
 digitalWrite(zelena, LOW);
 digitalWrite(crvena, LOW);
 digitalWrite(zuta, LOW);
 
 lcd.setCursor(0, 1);
 lcd.print("SIGURNO");
 
 
 }
 else if(udaljenost >= 75 && udaljenost<120 )
 {
 digitalWrite(zelena, HIGH);
 delay(300);
 digitalWrite(zelena, LOW);
 delay(100);
 
 digitalWrite(crvena, LOW);
 digitalWrite(zuta, LOW);
 
 lcd.setCursor(0, 1);
 lcd.print("SIGURNO");
 
 tone(zujalica, 500);
 delay(400);
 noTone(zujalica);
 delay(400);
 }
 else if (udaljenost>50 && udaljenost < 75)
 {
 digitalWrite(zelena, HIGH);
 
 digitalWrite(zuta, HIGH);
 delay(200);
 digitalWrite(zuta, LOW);
 delay(100);
 
 digitalWrite(crvena, LOW);
 
 lcd.setCursor(0, 1);
 lcd.print("USPORI");
 
 tone(zujalica, 500);
 delay(200);
 noTone(zujalica);
 delay(200);
 }
 else if (udaljenost>=0 && udaljenost<50)
 {
 digitalWrite(zelena, HIGH);
 digitalWrite(zuta, HIGH);
 
 digitalWrite(crvena, HIGH);
 delay(200);
 digitalWrite(crvena, LOW);
 delay(100);
 
 lcd.setCursor(4, 1);
 lcd.print("STOP!!!");
 
 tone(zujalica, 500);
 
 }
}
//funkcija za prikaz udaljenosti na LCD monitoru
void pokazi_udaljenost()
{ 
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Udaljenost: ");
 lcd.setCursor(11, 0);
 lcd.print(udaljenost);
 
}
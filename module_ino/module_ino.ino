#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
 

const int bouton = 3;
const int relay = 2;
 
int etatBouton;
boolean etat, statu;

void setup(){
  
  /*** Initialisation de la connexion sans-fil à base de NRF24L01 ***/
  /*** VERSION DE TEST
   ***Absence du code pour vérifier que celui ci fonctionne ...
   
   Serial.begin(9600);

  Mirf.cePin = 8; // CE
  Mirf.csnPin = 7; // CSN
  Mirf.spi = &MirfHardwareSpi; 
  Mirf.init(); 

  Mirf.channel = 42; // On utilise le canal 42 parceque c'est fun ... 
  Mirf.payload = sizeof(unsigned long); //ici il faut déclarer la taille du "payload" soit du message qu'on va transmettre, au max 32 octets
  Mirf.config(); //on configure ce joyeux bordel :)
   
  Mirf.setTADDR((byte *)"modu1"); // Le 2eme module va envoyer ses info au 1er module MOI
  Mirf.setRADDR((byte *)"serve"); // On définit ici l'adresse du 2eme module LUI
  ***/
  
  /*** Initialisation des sorties pour le relai et le bouton ***/
  pinMode(relay, OUTPUT); 
  pinMode(bouton, INPUT); 
  etatBouton = HIGH; 
  etat = false; 
  statu = false;
  
}
 
void loop(){
  /* Version de test
  
  byte data[Mirf.payload]; // Tableau de byte qui va stocker le message recu
  
  if(!Mirf.isSending() && Mirf.dataReady()){ // Si un message a été recu et qu'un autre n'est pas en cours d'emission
    Serial.println("Réception");
    Mirf.getData(data); // on récupére le message
    if(data == '1')
    {
      digitalWrite(relay, LOW); 
      etat = !etat; 
    }
    if(data == '0')
    {
      digitalWrite(relay, HIGH); 
      etat = !etat; 
    }
    //Mirf.send(data);
    
    Serial.println("Change l'état du Relai");
  }*/
  
  
  if(digitalRead(bouton)==HIGH and statu == false ) // bouton poussé, on rentre uniquement à la première detection de l'appui
  { 
    if(etat == true)
    {
      etat = false;
      statu = true; 
      digitalWrite(relay, LOW); 
    }
    if(etat == false)
    {
      etat = true; 
      statu = true; 
      digitalWrite(relay, HIGH);
    }
  }
  else if(digitalRead(bouton)==LOW and statu == true) // cette ligne permet de bloqué le changement d'état du relay x fois quand on appui sur le bouton 
  {
    statu = false;
  }
    
}

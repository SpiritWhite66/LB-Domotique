#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
 

const int bouton = 2;
const int led = 3;
const int relay = 4;
 
int etatBouton;
boolean etat, statu,access;

void setup(){
  Serial.begin(115200);
  /*** Initialisation de la connexion sans-fil à base de NRF24L01 ***/
  /*** VERSION DE TEST
   ***Absence du code pour vérifier que celui ci fonctionne ...
   
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
  pinMode(led, OUTPUT);
  pinMode(bouton, INPUT); 
  etatBouton = HIGH; 
  etat=true;
  statu=true;
  access=false; //jeton d'accès de la connexion sans fils
  
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
 /*if(!Mirf.isSending() && Mirf.dataReady())
 {
   Mirf.getData(data); // on récupére le message
   access=true; //j'active le jeton
   statu = true
 }*/
      char data = 0; //variable contenant le caractère à lire
      int reception = 0; //variable contenant le nombre de caractère disponibles dans le buffer
    
      reception = Serial.available();
    
      while(reception > 0) //tant qu'il y a des caractères à lire
      {
          access = true;
          data = Serial.read(); //on lit le caractère
          reception = Serial.available(); //on relit le nombre de caractères dispo
      }
      Serial.println(statu); 
      if(digitalRead(bouton)==LOW or access==true) // bouton poussé, on rentre uniquement à la première detection de l'appui
      {
      
        if(statu==true)
        {
          if((etat == true or data=='1')and data!='0')
          {
            Serial.println("j'allume"); 
            digitalWrite(relay, HIGH);
            digitalWrite(led, LOW);
            etat=false;
          }
          else if(etat==false or data=='0')
          {
            Serial.println("j'éteins"); 
            digitalWrite(relay, LOW);
            digitalWrite(led, HIGH);
            etat=true;
          }
                      
        }
        statu=false;   //je bloque les actions tant que le bouton n'a pas était relaché
        access=false; //on rebloque l'accès par la connexion sans fils
       }
     
     else
     {
       statu = true; 
     }
    
    //fin du programme
 
 
}

//#include <SPI.h>
//#include <Mirf.h>
//#include <nRF24L01.h>
//#include <MirfHardwareSpiDriver.h>
 
 

const int bouton = 2;
const int led = 3;
const int relay = 4;
const char identifiant = 'R'; //identifiant du module
 
int etatBouton;
boolean etat, statu,access;
char * commande;
boolean presse;
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
  presse = false;
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
      commande = ReadCommande(&access);
      if(digitalRead(bouton)==LOW or access==true) // bouton poussé, on rentre uniquement à la première detection de l'appui
      {
        if(digitalRead(bouton) == LOW)
        {
          presse = true;
          }
        if(statu==true)
        {
          if((etat == true and commande[4]=='1')or (etat==true and presse == true))
          {
            Serial.println("j'allume"); 
            digitalWrite(relay, HIGH);
            digitalWrite(led, LOW);
            etat=false;
          }
          else if((etat==false and commande[4]=='0')or (etat==false and presse==true) )
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

char * WriteCommande(char * commande)
{
  /*****
  [0] => caractère de début de commande - Non important
  [1] => caractère de début de commande - Non important
  [2] => expéditeur - Important
  [3] => destinataire - Important
  [4] => commande - Important
  [5] => caractère de fin de commande - Non important
  [6] => caractère de fin de commande - Non important
  *****/
  Serial.println(commande[4]);     
}

char * ReadCommande(bool *access)
{
  /*****
  [0] => caractère de début de commande - Non important
  [1] => caractère de début de commande - Non important
  [2] => expéditeur - Important
  [3] => destinataire - Important
  [4] => commande - Important
  [5] => caractère de fin de commande - Non important
  [6] => caractère de fin de commande - Non important
  *****/
      char data[7]; //variable contenant le caractère à lire
      int reception = 0; //variable contenant le nombre de caractère disponibles dans le buffer
      int i = 0;
      reception = Serial.available();
      if(reception !=0)
      {
        char save[] = {'0','0'}; // sauvegarde des deux dernier caractères
        while(reception > 0 && (save[0]!='\\' || save[1]!='1') ) //tant qu'il y a des caractères à lire
        {            
            data[i] = Serial.read(); //on lit le caractère
            save[0] = save[1]; //on déplace les caractères pour faire la bonne sauvegarde
            save[1] = data[i];
            Serial.print(i); 
            Serial.print('-');         
            Serial.println(data[i]);     
            reception = Serial.available(); //on relit le nombre de caractères dispo
            i++;
        } 
        if(data[3]==identifiant && i==7)
        {
          *access = true;
          WriteCommande(commande);
          return data;
        }
      }
}

  

#include "protocol.h"



protocol::protocol(Token_gestion* gest)
{
    gestion = gest;
    //on essaie de faire la connection avec la carte Arduino
    port = new QextSerialPort;
    port->setPortName("/dev/ttyACM0"); // Uniquement Linux | à modifier | "COM3" ou "/ dev/ttyACM0".
    port->setBaudRate(BAUD19200);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setDataBits(DATA_8);
    port->setFlowControl(FLOW_OFF);
    port->open(QextSerialPort::ReadWrite);
    if(!port->isOpen())
    {
       cout << "Probème d'ouverture du port";
    }
}
bool protocol::Verification(char * commande)
{
    if((sizeof(commande)==7) && (commande[2]=='L') && (gestion->Get_Token(commande[3])==true)) // on verifie que la commande contient bien 7 octet, que l'expediteur est bien le localhost (L), et que le destinataire existe bien en tant que module
    {
        return true;
    }
}
bool protocol::Verification_commande(char * commande)
{
    switch (commande[5]) {
      case 'A':
      case 'E':
        return true;
        break;
      case'T':
        //Envoi 'ok'
        //Allocation du token
        return true;
        break;
      default:
        return false;
    }
}


char* protocol::Compoze()
{
    char commandes[7] = {'\\','0',exp,dest,com,'\\','1'};
    if(Verification_commande(commandes) and Verification(commandes))
    {
       return commandes;
    }
}

void protocol::Send_Authorization(char* commande)
{
    if(gestion->Get_Token(commande[3])) // Vérification que le module existe
    {
        step=1;
        //Utiliser la librairie QextSerialPort
    }
}
void protocol::Send_Commande()
{
    //Utiliser la librairie QextSerialPort
}
void protocol::Send_Response()
{
    //Utiliser la librairie QextSerialPort
}
bool protocol::End_Communication()
{
    if(step==2)
    {
        step=0;
        return true;
    }
    else
    {
        return false;
    }
    //Effectuer la vérification de fin d'échange
    //Désactive le token pour le module
}
void protocol::Allocation_Token(char * commande)
{
    if(End_Communication())
    {
        gestion->Get_Token(commande[3]);
        cout<<"Token est alloué au module"<<commande[3]<<endl;
        Send_Authorization(commande);//Le token viens de lui être envoyé
    }
    else
    {
        //ajout dans la liste d'attente
    }
    //Verification de fin d'échange
    //Passage du token à true pour le module
}

void protocol::SendData(char commande) {
    QString str(commande);
    if(port!=NULL) //on test si le port es bien ouvert
    {
        cout<<"envoi"<<endl;
        port->write(str.toLatin1());
    }

}

void protocol::ReadData() {
    cout<<"reception"<<endl;
    QByteArray array = port->readAll();
    QString str(array);
    cout<<"recept "<<str.toStdString()<<endl; //on affiche la commande
}

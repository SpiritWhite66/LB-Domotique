#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <iostream>
#include <QString>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include "token_gestion.h"
#include <QWidget>
#include <QApplication>
using namespace std;

class protocol
{
public:
    protocol(Token_gestion *gest);
    bool Verification(char *commande); // vérifie que la chaine de bit est valide
    bool Verification_commande(char *commande);
    void Send_Commande();
    void Allocation_Token(char *commande);
    void Send_Authorization(char *commande);
    void Send_Response();
    char* Compoze();
    void Decompoze();
    bool End_Communication();
    void SendData(char commande);
    void ReadData();

private:
    QextSerialPort *port;
    Token_gestion *gestion;
    char dest, exp, com; //information sur la communication en cours
    int step;
};

#endif // PROTOCOL_H


#include <iostream>
using namespace std;
#include "windows.h"
#include "token_gestion.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Token_gestion * gestionnaire = new Token_gestion; //on initialise la gestion du token
    gestionnaire -> New_Module(); //on rentre le nouveau module, il va ajouté à la liste des modules utilisé et l'enregistrer dans le fichier binaire

    protocol * proto=new protocol(gestionnaire); //on initialise la classe gérant le protocole de communication

    windows win(proto); // j'ouvre mon programme
    win.show();

    return a.exec();
}

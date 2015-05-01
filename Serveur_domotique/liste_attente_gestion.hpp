#include <iostream>
#include <string.h>
using namespace std;


#ifndef GESTION_LISTE_H
#define GESTION_LISTE_H

class gestion_liste
{

public:
    struct scommande;
    typedef struct scommande commande;
    gestion_liste(); //Initialise la gestion !
	void saisir_commande(commande **head);
    commande* Create_Commande(char com[]); //Créer la structure
	void Add_Commande(commande* com, commande **head); //insérer en fin
    commande Recupere_Commande(commande **head);
	void Affichage_Commande(commande * head); 

private:
    void InsererDebut(commande *com, commande** head);
    void InsererFin(commande *com, commande** head);

    commande **head;
    int nb_com;
};

#endif // GESTION_LISTE_H

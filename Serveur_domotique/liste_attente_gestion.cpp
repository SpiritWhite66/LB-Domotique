#include "liste_attente_gestion.hpp"

typedef struct gestion_liste::scommande
{
    char com[8];
    struct scommande *next;
}commande;


gestion_liste::gestion_liste()
{
    *head = NULL;
    nb_com = 0;
}

void gestion_liste::saisir_commande(commande **head)
{
	bool boucle = true;
	while(boucle)
	{
		char com[7];
		cout<<"Rentrez la commande"<<endl;
		cin>>com;
		commande* cell = Create_Commande(com);
		Add_Commande(cell, head);
		cout<<"Voulez-vous rentrez une autre commande ? "<<endl;
		cin>>boucle;
	}
}
commande* gestion_liste::Create_Commande(char* c) //Créer la structure
{
	commande *cell = new commande; 
	strcpy (cell->com,c);
    return cell;

}
void gestion_liste::InsererDebut(commande* com,commande** head) //avec tete qui est l'adresse du bloc d'entête
{
	com->next = *head;
	*head = com; 	
}
void gestion_liste::InsererFin(commande *com, commande** head)
{
	commande* adress = *head;
	while(adress->next != NULL)
	{			
		adress = adress->next;
	}
	com->next = NULL;
	adress->next = com;
	
}
void gestion_liste::Add_Commande(commande* com, commande **head) //insérer en fin
{

	if(*head!=NULL)
	{
        InsererFin(com, head);
	}
	else
	{
        InsererDebut(com, head);
	}
	nb_com++;
}

void gestion_liste::Affichage_Commande(commande *head)
{
	cout<<"Liste des commandes en attentes : "<<endl;
	while(head != NULL)
	{
		cout<<"--"<<head->com<<"--"<<endl;
		head=head->next;
	}
} 

commande gestion_liste::Recupere_Commande(commande **head)
{
	if(head!=NULL)
	{
		commande retour = **head;
		commande* save = *head;
		save=save->next;
		delete(*head);
		*head=save;
		nb_com--;  
		return retour;

	}
}

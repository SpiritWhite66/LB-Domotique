#include "liste_attente_gestion.hpp"
int main(void)
{
	commande*head=NULL;
	saisir_commande(&head);
	Affichage_Commande(head);
	commande test = Recupere_Commande(&head);
	cout<<test.com<<endl;
		Affichage_Commande(head);
	test = Recupere_Commande(&head);
	cout<<test.com<<endl;
		Affichage_Commande(head);
	test = Recupere_Commande(&head);
	cout<<test.com<<endl;
	Affichage_Commande(head);
	return 0;
}
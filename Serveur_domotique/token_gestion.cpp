#include "token_gestion.h"


/********----------Définition des structures de chaque module-----------********/

typedef struct Token_gestion::Module_structure
{
    char id;
    bool token = false;
    Module * next;
}Module;

typedef struct Token_gestion::switch_structure : Module
{

    QPushButton * bouton;
    bool etat;

}m_switch;

/********---------------------------------------------------------------********/

Token_gestion::Token_gestion()
{
    temps = 1;
    head = NULL;
    save_file = new char[12];
    save_file = "module.save";
}
Module* Token_gestion::New_Module()
{
    char type;
    cout<<"Rentrez le type du nouveau module : ";
    cin >> type;
    if(type == 'i')
    {
        m_switch * mod = new m_switch;
        cout<<"Rentrez l'identifiant du nouveau module : ";
        cin >> mod->id;
        mod->etat = false;
        mod->bouton = new QPushButton;
        return mod;
    }
}

void Token_gestion::Add_Module(Module *nModule)
{
    nModule->next = head;
    head = nModule;
    Token_gestion::Save_Module(head);
}

void Token_gestion::Remove_Module()
{
    Module * save = head->next;
    delete (head);
    head=save;
}

void Token_gestion::Affichage_Module()
{
    Module * save = head; //Pour éviter de modifier la variable privée
    if(save!=NULL)
    {
        do
        {
            cout<<"ID : "<<save->id<<endl;
            save = save->next;
        }while(save != NULL and save!=head );
    }
}

void Token_gestion::Move_Token() //Obsolète
{
    Module * save = head;
    bool tok = true;
    if(save!=NULL)
    {
        while(save !=NULL and tok)
        {
            if(save->token==true)
            {
                tok = false; // on sort de la boucle
            }
        }
        save->token=false;
        save->next
                ->token = true;
    }
}
void Token_gestion::Update_Token(char id, bool action)
{
    Module * save = head;
    bool tok = true;
    if(save!=NULL)
    {
        while(save !=NULL and tok)
        {
            if(save->id == id)
            {
                tok = false; // on sort de la boucle
                if(action)
                {
                    save->token=true;
                }
                else
                {
                    save->token=false;
                }
            }
            else
            {
                save=save->next;
            }
        }
    }
}

void Token_gestion::Get_FileSave()
{
    cout<<"Etes-vous sur de vouloir changer de fichier de sauvegarde des modules ?"<<endl;
    char response;  //variable uniquement temporaire
    cin>>response;
    if(response == 'y')
    {
        cout<<"Rentrez le nom du nouveau fichier"<<endl;
        cin>>save_file;
    }
    else
    {
        cout<<"Commande annulé"<<endl;
    }
    delete(&response); // on supprime la variable temporaire de la mémoire
}
void Token_gestion::Open_File()
{
    F=fopen(save_file,"a");
}
void Token_gestion::Close_File()
{
    fclose(F);
}


void Token_gestion::Save_Module(Module *module)
{
    if(module != NULL)
    {
        if(F !=NULL)
        {
            fwrite(module, sizeof(Module), 1, F);
        }
    }
}
void Token_gestion::Load_Module() //On doit reconstruire la liste chainée
{
    if(F!=NULL)
    {
        if(!feof(F))
        {
            /*** Gestion cas de la première lecture***/
            Module * mod = new Module;
            fread(mod, sizeof(Module), 1, F);
            mod->next = NULL;
            head=mod;
            while(!feof(F))
            {
                mod = new Module;
                fread(mod, sizeof(Module), 1, F);
                mod->next=head;
                head=mod;
            }
        }

    }

}
bool Token_gestion::Get_Token(char id)
{
    Module * save = head;
    bool tok = true;
    if(save!=NULL)
    {
        while(save !=NULL and tok)
        {
            if(save->id==id)
            {
                tok = false; // on sort de la boucle
                return true;
            }
        }

    }
}


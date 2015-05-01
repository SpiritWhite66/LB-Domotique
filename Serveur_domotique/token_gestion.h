#ifndef TOKEN_GESTION_H
#define TOKEN_GESTION_H
#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <stdio.h>

using namespace std;

class Token_gestion
{
private:
    struct Module_structure;
    typedef struct Module_structure Module;
    struct switch_structure;
    typedef struct switch_structure m_switch;
    Module* head; //Sommet de la pile
    int temps;
    void Save_Module(Module *module);
    void Load_Module();
    void Get_FileSave();
    char * save_file;
    FILE * F;


public:
    Token_gestion();
    Module* New_Module();
    void Add_Module(Module* nModule);
    void Remove_Module();
    void Affichage_Module();
    void Move_Token();//Obsolète
    void Update_Token(char id, bool action); //remplace Move_Token()
    void Get_Temporisation();
    void Search_Module();
    bool Get_Token(char id);
    void Open_File();
    void Close_File();


};

#endif // TOKEN_GESTION_H

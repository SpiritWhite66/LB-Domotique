#include "windows.h"

windows::windows(protocol *prot) :  QWidget()
{
    test = prot;
    setFixedSize(300,150);

    m_bouton = new QPushButton("Allumer", this);
    QObject::connect(m_bouton, SIGNAL(clicked()), this, SLOT(envoi()));

}
void windows::envoi() //Code de TEST
{
    if(m_bouton->text()=="Eteindre")
    {
        m_bouton->setText("Allumer");
        test->SendData('0');
    }
    else
    {
        m_bouton->setText("Eteindre");
        test->SendData('1');
    }
}
windows::~windows()
{

}

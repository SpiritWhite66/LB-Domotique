#ifndef WINDOWS_H
#define WINDOWS_H

#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include "protocol.h"

class windows : public QWidget
{
    Q_OBJECT

    public:
        windows(protocol * prot);

        ~windows();
    public slots:
        void envoi();

    private:
        QPushButton *m_bouton;
        protocol *test;
};

#endif // WINDOWS_H

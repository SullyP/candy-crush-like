#include "controleur.h"

Controleur::Controleur(QObject *parent) :
    QObject(parent)
{
}

int Controleur::getTailleBonbon() const{
    return tailleBonbon;
}

void Controleur::setTailleBonbon(int taille){
    tailleBonbon=taille;
    emit tailleBonbonChanged();
}

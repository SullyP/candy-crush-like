#include "bonbon.h"


Bonbon::Bonbon(QQuickItem *parent) :
    QQuickItem(parent)
{
    setType(Normal);
    setCouleur(Rouge);
}


Bonbon::Bonbon(Bonbon::Couleur c,Bonbon::Type t){
    couleur=c;
    type=t;
}
Bonbon::Couleur Bonbon::getCouleur() const{
    return couleur;
}

Bonbon::Type Bonbon::getType() const{
    return type;
}

void Bonbon::setType(Bonbon::Type type){
    this->type=type;
    emit typeChanged();
}

void Bonbon::setCouleur(Bonbon::Couleur couleur){
    this->couleur=couleur;
    emit couleurChanged();
}

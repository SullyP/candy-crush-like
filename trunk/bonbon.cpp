#include "bonbon.h"

Bonbon::Bonbon(QObject *parent=0): QObject (parent){
    couleur=Aucune;
    type=Normal;
}

Bonbon::Bonbon(QObject *parent,Bonbon::Couleur c,Bonbon::Type t){
    couleur=c;
    type=t;
}

Bonbon::Couleur Bonbon::getCouleur() const{
    return couleur;
}

Bonbon::Type Bonbon::getType() const{
    return type;
}

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
QString Bonbon::getCouleur() const{
    return "Rouge";
}

QString Bonbon::getType() const{
    return "Normal";
}

void Bonbon::setType(Bonbon::Type type){
    this->type=type;
    emit typeChanged();
}

void Bonbon::setCouleur(Bonbon::Couleur couleur){
    this->couleur=couleur;
    emit couleurChanged();
}

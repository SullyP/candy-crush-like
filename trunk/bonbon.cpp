#include "bonbon.h"

Bonbon::Bonbon(){
    couleur=Rouge;
    type=Normal;
}

Bonbon::Bonbon(Bonbon& bonbon){
    Bonbon(bonbon.couleur, bonbon.type);
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

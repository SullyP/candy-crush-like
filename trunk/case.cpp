#include "case.h"


Case::Case(QQuickItem *parent) :
    QQuickItem(parent)
{
    this->debut=false;
    this->fin=false;
    this->franchissable=false;
    this->bonbon=NULL;
}

Case::Case(bool debut, bool fin, bool franchissable,Bonbon* bonbon){
    this->debut=debut;
    this->fin=fin;
    this->franchissable=franchissable;
    this->bonbon=bonbon;
}


bool Case::estVide() const{
    return (NULL==bonbon);
}

Bonbon* Case::getBonbon(){
    return bonbon;
}

bool Case::estDebut() const{
    return debut;
}

bool Case::estFin() const{
    return fin;
}

bool Case::estFranchissable() const{
    return franchissable;
}

void Case::setBonbon(Bonbon* bonbon){
    this->bonbon=bonbon;

}

void Case::setFin(bool fin){
    this->fin=fin;
}

void Case::setDebut(bool debut){
    this->debut=debut;
}

void Case::setFranchissable(bool franchissable){
    this->franchissable=franchissable;
}

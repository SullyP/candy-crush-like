#include "case.h"


Case::Case(QQuickItem *parent) :
    QQuickItem(parent)
{
    this->debut=false;
    this->fin=false;
    this->franchissable=true;
    this->bonbon=NULL;
    this->niveauGelatine=0;
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
    if(fin!=this->fin){
        this->fin=fin;
        emit finChanged();
    }
}

void Case::setDebut(bool debut){
    if(debut!=this->debut){
        this->debut=debut;
        emit debutChanged();
    }
}

void Case::setFranchissable(bool franchissable){
    if(franchissable!=this->franchissable){
        this->franchissable=franchissable;
        emit franchissableChanged();
    }
}

void Case::setNiveauGelatine(int num){
    if(niveauGelatine!=num){
        niveauGelatine=num;
        emit niveauGelatineChanged();
    }
}

int Case::getNiveauGelatine(){
  return niveauGelatine;
}

#include "case.h"

Case::Case(){
    this->debut=false;
    this->fin=false;
    this->franchissable=false;
    this->bonbon=NULL;
}

Case::Case (Case& c){
    Case(c.debut, c.fin, c.franchissable, c.bonbon);
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

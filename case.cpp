#include "case.h"



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

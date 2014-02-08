#ifndef CASE_H
#define CASE_H

#include"bonbon.h"

class Case
{

public:
    Case ();
    Case(bool debut, bool fin, bool franchissable,Bonbon* bonbon);
    bool estVide() const;
    Bonbon* getBonbon();
    bool estDebut() const;
    bool estFin() const;
    bool estFranchissable() const;

private:
    Bonbon* bonbon;
    bool debut;
    bool fin;
    bool franchissable;
};

#endif // CASE_H

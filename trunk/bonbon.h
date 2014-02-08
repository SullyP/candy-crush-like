#ifndef BONBON_H
#define BONBON_H
#include "stdlib.h"

class Bonbon
{

public:
    typedef enum{
        Rouge,
        Jaune,
        Vert,
        Bleu,
        Violet,
        Rose,
        Aucune
    }Couleur;
    typedef enum{
        Normal,
        Bombe,
        RayureH,
        RayureV,
        Sucre
    }Type;
    Bonbon();
    Bonbon(Couleur c,Type t);
    Couleur getCouleur() const;
    Type getType() const;

private:
    Couleur couleur;
    Type type;
};
#endif // BONBON_H

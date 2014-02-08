#ifndef BONBON_H
#define BONBON_H

#include<QObject>

class Bonbon : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(Couleur)
    Q_PROPERTY(Couleur couleur READ getCouleur)
    Q_PROPERTY(Type type READ getType)

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
    Bonbon(Bonbon& bonbon);
    Bonbon(Couleur c,Type t);
    Couleur getCouleur() const;
    Type getType() const;

private:
    Couleur couleur;
    Type type;
};
#endif // BONBON_H

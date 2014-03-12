#ifndef BONBON_H
#define BONBON_H

#include <QQuickItem>

class Bonbon : public QQuickItem
{
    friend class Niveau;
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(Couleur)
    Q_PROPERTY(Couleur couleur READ getCouleur NOTIFY couleurChanged)
    Q_PROPERTY(Type type READ getType NOTIFY typeChanged)

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
    Bonbon(QQuickItem *parent = 0);
    Bonbon(Couleur c,Type t);
    //GET
    Couleur getCouleur() const;
    Type getType() const;
private:
    Couleur couleur;
    Type type;
    //Fonctions accesible par la classe amie (niveau)
    //SET
    void setType(Type type);
    void setCouleur(Couleur couleur);
signals:
    void couleurChanged();
    void typeChanged();
public slots:
};
#endif // BONBON_H

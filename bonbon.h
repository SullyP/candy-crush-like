#ifndef BONBON_H
#define BONBON_H

#include <QQuickItem>

class Bonbon : public QQuickItem

{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_ENUMS(Couleur)
    Q_PROPERTY(QString couleur READ getCouleur NOTIFY couleurChanged)
    Q_PROPERTY(QString type READ getType NOTIFY typeChanged)

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
    QString getCouleur() const;
    QString getType() const;
    void setType(Type type);
    void setCouleur(Couleur couleur);

private:
    Couleur couleur;
    Type type;
signals:
    void couleurChanged();
    void typeChanged();
public slots:
};
#endif // BONBON_H

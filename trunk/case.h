#ifndef CASE_H
#define CASE_H

#include <QQuickItem>
#include"bonbon.h"

class Case : public QQuickItem
{
    friend class Niveau;
    Q_OBJECT
    Q_PROPERTY(bool debut READ estDebut NOTIFY debutChanged)
    Q_PROPERTY(bool fin READ estFin NOTIFY finChanged)
    Q_PROPERTY(bool franchissable READ estFranchissable NOTIFY franchissableChanged)
    Q_PROPERTY(bool vide READ estVide)
    Q_PROPERTY(int niveauGelatine READ getNiveauGelatine NOTIFY niveauGelatineChanged)
public:
    explicit Case (QQuickItem *parent = 0);
    //GET
    Bonbon* getBonbon();
    int getNiveauGelatine();
    //Tests sur la case
    bool estVide() const;
    bool estDebut() const;
    bool estFin() const;
    bool estFranchissable() const;
private:
    Bonbon* bonbon;
    bool debut;
    bool fin;
    bool franchissable;
    int niveauGelatine;
    //Fonctions accesible par la classe amie (niveau)
    //SET
    void setBonbon(Bonbon* bonbon);
    void setFin(bool fin);
    void setDebut(bool debut);
    void setFranchissable(bool franchissable);
    void setNiveauGelatine(int num);
signals:
    void franchissableChanged();
    void finChanged();
    void debutChanged();
    void niveauGelatineChanged();
public slots:

};

#endif // CASE_H

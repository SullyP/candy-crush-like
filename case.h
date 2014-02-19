#ifndef CASE_H
#define CASE_H

#include <QQuickItem>
#include"bonbon.h"

class Case : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(Bonbon* bonbon READ getBonbon)
    Q_PROPERTY(bool debut READ estDebut)
    Q_PROPERTY(bool fin READ estFin)
    Q_PROPERTY(bool franchissable READ estFranchissable)
    Q_PROPERTY(bool vide READ estVide)

public:
    explicit Case (QQuickItem *parent = 0);
    Case(bool debut, bool fin, bool franchissable,Bonbon* bonbon);
    bool estVide() const;
    Bonbon* getBonbon();
    bool estDebut() const;
    bool estFin() const;
    bool estFranchissable() const;
    void setBonbon(Bonbon* bonbon);
    void setFin(bool fin);
    void setDebut(bool debut);
    void setFranchissable(bool franchissable);

private:
    Bonbon* bonbon;
    bool debut;
    bool fin;
    bool franchissable;
};

#endif // CASE_H

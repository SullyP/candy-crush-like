#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include "qtquick2applicationviewer.h"
#include "case.h"
#include "bonbon.h"
#include "niveau.h"
#include "vue.h"
#include "global.h"

class Controleur : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int tailleBonbon READ getTailleBonbon WRITE setTailleBonbon NOTIFY tailleBonbonChanged)
    Q_PROPERTY(int nbColonne READ getNbColonne)
public:
    explicit Controleur(QObject *parent = 0);
    int getTailleBonbon() const;
    void setTailleBonbon(int taille);
    int getNbColonne() const;
    void newNiveau();
private:
    int tailleBonbon;
    Niveau niveau;
signals:
    void tailleBonbonChanged();
public slots:

};

#endif // CONTROLEUR_H

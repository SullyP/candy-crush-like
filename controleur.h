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
    Q_PROPERTY(int resolutionBonbon READ getResolutionBonbon NOTIFY resolutionBonbonChanged)
    Q_PROPERTY(int nbColonne READ getNbColonne)
public:
    explicit Controleur(QObject *parent = 0);
    int getResolutionBonbon() const;
    int getTailleBonbon() const;
    void setTailleBonbon(int taille);
    int getNbColonne() const;
    void newNiveau();
private:
    int resolutionBonbon;
    int tailleBonbon;
    Niveau niveau;
signals:
    void tailleBonbonChanged();
    void resolutionBonbonChanged();
public slots:

};

#endif // CONTROLEUR_H

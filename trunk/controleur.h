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
    Q_PROPERTY(int nbColonne READ getNbColonne NOTIFY nbColonneChanged)
    Q_PROPERTY(int score READ getScore NOTIFY scoreChanged)
    Q_PROPERTY(int scoreObjectif READ getScoreObjectif NOTIFY scoreObjectifChanged)
    Q_PROPERTY(int numNiveau READ getNumNiveau NOTIFY numNiveauChanged)
    Q_PROPERTY(int nbMvt READ getNbMvt NOTIFY nbMvtChanged)
    Q_PROPERTY(int behaviorDesactive READ getBehaviorDesactive WRITE setbehaviorDesactive NOTIFY behaviorDesactiveChanged)
    Q_PROPERTY(int nbTotalNiveau READ getNbTotalNiveau CONSTANT)
public:
    explicit Controleur(QObject *parent = 0);
    int getResolutionBonbon() const;
    int getTailleBonbon() const;
    void setTailleBonbon(int taille);
    int getNbColonne() const;
    int getScoreObjectif() const;
    int getScore() const;
    int getNumNiveau() const;
    int getNbMvt() const;
    int getNbTotalNiveau() const;
    bool getBehaviorDesactive() const;
    void setbehaviorDesactive(bool b);
    Q_INVOKABLE void chargerNiveau(int n);
    Q_INVOKABLE void selectionBonbon1(int x,int y);
    Q_INVOKABLE void selectionBonbon2(int x,int y);
private:
    int resolutionBonbon;
    int tailleBonbon;
    Niveau* niveau;
    //Désactivé les animations
    bool behaviorDesactive;
    //Coordonnées du premier bonbon sélectionné
    int xSelBonbon;
    int ySelBonbon;
signals:
    void tailleBonbonChanged();
    void resolutionBonbonChanged();
    void nbColonneChanged();
    void actualiserTailleBonbon();
    void scoreChanged();
    void numNiveauChanged();
    void scoreObjectifChanged();
    void nbMvtChanged();
    void behaviorDesactiveChanged();
public slots:

};

#endif // CONTROLEUR_H

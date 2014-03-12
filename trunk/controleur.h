#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include <QTimer>
#include "qtquick2applicationviewer.h"
#include "case.h"
#include "bonbon.h"
#include "niveau.h"

#define NB_TOTAL_NIVEAU 7
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
    Q_PROPERTY(int animationX READ getAnimationX WRITE setAnimationX NOTIFY animationXChanged)
    Q_PROPERTY(int animationY READ getAnimationY WRITE setAnimationY NOTIFY animationYChanged)
    Q_PROPERTY(int nbTotalNiveau READ getNbTotalNiveau CONSTANT)
public:
    explicit Controleur(QObject *parent = 0);
    //GET
    int getResolutionBonbon() const;
    int getTailleBonbon() const;
    int getNbColonne() const;
    int getScoreObjectif() const;
    int getScore() const;
    int getNumNiveau() const;
    int getNbMvt() const;
    int getNbTotalNiveau() const;
    bool getAnimationX() const;
    bool getAnimationY() const;

    //SET
    void setTailleBonbon(int taille);
    void setAnimationX(bool b);
    void setAnimationY(bool b);

    Q_INVOKABLE void chargerNiveau(int n);
    Q_INVOKABLE void selectionBonbon1(int x,int y);
    Q_INVOKABLE void selectionBonbon2(int x,int y);
private:
    //Taille et resolution des bonbons pour l'affichage
    int resolutionBonbon;
    int tailleBonbon;
    //Niveau en cours
    Niveau* niveau;
    //Timer permettant d'attendre la fin des animations avant de continuer le déroulement du jeu
    QTimer timer;
    //Désactive les animations
    bool animationX;
    bool animationY;
    //Coordonnées du premier bonbon sélectionné
    int x1SelBonbon;
    int y1SelBonbon;
    //Coordonnées du second bonbon sélectionné
    int x2SelBonbon;
    int y2SelBonbon;
    //Etape du déroulement du jeu
    int etape;
signals:
    void tailleBonbonChanged();
    void resolutionBonbonChanged();
    void nbColonneChanged();
    void actualiserTailleBonbon();
    void scoreChanged();
    void numNiveauChanged();
    void scoreObjectifChanged();
    void nbMvtChanged();
    void animationXChanged();
    void animationYChanged();
public slots:
    void deroulementJeu();
};

#endif // CONTROLEUR_H

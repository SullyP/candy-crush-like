#ifndef NIVEAU_H
#define NIVEAU_H

#include<QList>
#include "qtquick2applicationviewer.h"
#include"case.h"
#include"bonbon.h"
#include <sstream>

class Niveau
{
private:
    //viewer et grille pour la création des bonbons
    const static QtQuick2ApplicationViewer* viewer;
    static QQuickItem* grille;
public:
    //STATIC
    static void setViewer(QtQuick2ApplicationViewer* v);

    Niveau();
    Niveau(int nnbNiveau);
    ~Niveau();

    //Get and Set
    int getNum_niveau() const;
    int getScore() const;
    int getScore_objectif() const;
    int getNb_col() const;
    int getNb_lign() const;
    int getNb_mvt() const;
    Bonbon* getBonbon(int lign, int col) const;
    Bonbon* getBonbon(int id) const;
    Bonbon::Couleur getCouleur (int lign, int col);


    //Fonctions pour le déroulement du jeu (public)
    bool completer();
    bool estPossible(int x1, int y1, int x2, int y2);
    bool marquerDestruction();
    bool detruire();
    bool commuterBonbon(int lign1, int col1, int lign2, int col2);
    bool coupPossible() const;
    bool tomber();
    void compterScore(int coef);
    void redistribuer();

private:
    int num_niveau;
    int score;
    int score_objectif;
    QList<Case*> liste;
    QList<int> caseVide;
    QList<int> caseBloc;
    QList<int> caseDebut;
    QList<int> caseFin;
    int nb_col;
    int nb_lign;
    int nb_mvt;
    Bonbon::Couleur couleurHasard() const;

    //Fonction auxiliaire de tomber
    bool tomberDuDessus(int lign, int col);

    //Fonctions auxiliaire de marquerDetruire
    void marquerBonbon(int lign,int col);
    void marquerVertical(int lign, int col);
    void marquerHorizontal(int lign, int col);
    void marquerCombo(int lign, int col);

    //Ajout/Suppresion Bonbon/Case
    void ajouterBonbon(int lign, int col,Bonbon::Couleur couleur, Bonbon::Type type = Bonbon::Normal);
    void ajouterCase(int lign, int col, bool debut=false, bool fin=false, bool franchissable=true);
    void supprimerBonbon(int lign, int col);
    void supprimerCase(int lign, int col);

    //Fonctions auxiliaire de coupPossible
    bool comboPossible(int lign, int col) const;
    bool possibleHL(int lign, int col) const;
    bool possibleVL(int lign, int col) const;
    bool possibleHR(int lign, int col) const;
    bool possibleVR(int lign, int col) const;

    //Fonctions auxiliaire de combo
    bool comboHorizontal (int lign, int col);
    bool comboVertical (int lign, int col);

    //Fonctions de tests bonbon/case
    bool estVide (int lign, int col) const;
    bool estBloc (int lign, int col) const;
    bool sansBonbon (int lign, int col) const;
    int index(int lign, int col) const;
    bool estDebut(int lign, int col) const;
    bool estMarquer(int lign,int col) const;

    //Fonctions pour le déroulement du jeu (privé)
    void remplir();
    bool combo (int lign, int col);

};

#endif // NIVEAU_H

#ifndef NIVEAU_H
#define NIVEAU_H

#include<QList>
#include"case.h"
#include"bonbon.h"
#include"global.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Niveau
{

public:
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
    Bonbon::Couleur getCouleur (int lign, int col);


    bool estVide (int lign, int col) const;
    bool estBloc (int lign, int col) const;
    bool sansBonbon (int lign, int col) const;
    int index(int lign, int col) const;

    void remplir();

    //combo
    bool comboHorizontal (int lign, int col);
    bool comboVertical (int lign, int col);
    bool combo (int lign, int col);

    //Ajout/Suppresion Bonbon/Case
    void ajouterBonbon(int lign, int col,Bonbon::Couleur couleur, Bonbon::Type type = Bonbon::Normal);
    void ajouterCase(int lign, int col, bool debut=false, bool fin=false, bool franchissable=true);
    void supprimerBonbon(int lign, int col);
    void supprimerCase(int lign, int col);

    //detruire
    void detruireCombo(int lign, int col);
    void detruireHorizontal(int lign, int col);
    void detruireVertical(int lign, int col);
    void detruire();

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


};

#endif // NIVEAU_H

#ifndef NIVEAU_H
#define NIVEAU_H

#include<QList>
#include"case.h"

class Niveau
{

public:
    Niveau();
    Niveau(int num_niveau,int score_objectif, QList<Case> liste, int nb_col, int nb_lign, int nb_mvt);
    int getNum_niveau() const;
    int getScore() const;
    int getScore_objectif() const;
    int getNb_col() const;
    int getNb_lign() const;
    int getNb_mvt() const;

private:
    int num_niveau;
    int score;
    int score_objectif;
    QList<Case> liste;
    int nb_col;
    int nb_lign;
    int nb_mvt;


};

#endif // NIVEAU_H

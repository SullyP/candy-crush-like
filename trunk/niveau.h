#ifndef NIVEAU_H
#define NIVEAU_H

#include<QList>
#include"case.h"

class Niveau
{

public:
    Niveau();
    Niveau(int num_niveau,int score_objectif, QList<Case*> liste, int nb_col, int nb_lign, int nb_mvt);
    int getNum_niveau() const;
    int getScore() const;
    int getScore_objectif() const;
    int getNb_col() const;
    int getNb_lign() const;
    int getNb_mvt() const;
    bool estVide (int lign, int col);
    bool comboHorizontal (int lign, int col);
    bool comboVertical (int lign, int col);
    bool comboCoinHG (int lign, int col);
    bool comboCoinHD (int lign, int col);
    bool comboCoinBG (int lign, int col);
    bool comboCoinBD (int lign, int col);

private:
    int num_niveau;
    int score;
    int score_objectif;
    QList<Case*> liste;
    int nb_col;
    int nb_lign;
    int nb_mvt;


};

#endif // NIVEAU_H

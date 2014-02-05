#ifndef NIVEAU_H
#define NIVEAU_H

#include<QObject>
#include<QList>
#include"case.h"

class Niveau : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int num_niveau READ getNum_niveau)
    Q_PROPERTY(int score READ getScore)
    Q_PROPERTY(int score_objectif READ getScore_objectif)
    Q_PROPERTY(int nb_col READ getNb_col)
    Q_PROPERTY(int nb_lign READ getNb_lign)
    Q_PROPERTY(int nb_mvt READ getNb_mvt)

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

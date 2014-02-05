#include "niveau.h"

Niveau::Niveau(){
    this->score=0;
    this->num_niveau=0;
    this->score_objectif=0;
    this->nb_col=0;
    this->nb_lign=0;
    this->nb_mvt=0;
}

Niveau::Niveau(Niveau& niveau){
    Niveau(niveau.num_niveau,niveau.score_objectif,niveau.liste,niveau.nb_col,niveau.nb_lign,niveau.nb_mvt);
}

Niveau::Niveau(int num_niveau,int score_objectif, QList<Case> liste, int nb_col, int nb_lign, int nb_mvt){
    this->score=0;
    this->num_niveau=num_niveau;
    this->score_objectif=score_objectif;
    this->liste=liste;
    this->nb_col=nb_col;
    this->nb_lign=nb_lign;
    this->nb_mvt=nb_mvt;

}

int Niveau::getNum_niveau() const{
    return num_niveau;
}

int Niveau::getScore() const{
    return score;
}

int Niveau::getScore_objectif() const{
    return score_objectif;
}

int Niveau::getNb_col() const{
    return nb_col;
}

int Niveau::getNb_lign() const{
    return nb_lign;
}

int Niveau::getNb_mvt() const{
    return nb_mvt;
}

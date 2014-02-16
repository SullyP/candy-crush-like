#include "niveau.h"

Niveau::Niveau(){
    this->score=0;
    this->num_niveau=0;
    this->score_objectif=0;
    this->nb_col=0;
    this->nb_lign=0;
    this->nb_mvt=0;
}

Niveau::Niveau(int num_niveau,int score_objectif, QList<Case*> liste, int nb_col, int nb_lign, int nb_mvt){
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

//premiere case ling=0 col=0.
bool Niveau::estVide (int lign, int col){
    return (liste.at((lign*nb_col) + col) == NULL);
}

//Pour vérifier s'il y a combo sur le bonbon de la case et les 2 suivants sur la ligne.
bool Niveau::comboHorizontal (int lign, int col){
    int i=(lign*nb_col) + col;
    if (col+2<nb_col && col+1<nb_col){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i+1)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i+2)->getBonbon()->getCouleur()){
            return true;
        }
    }
    return false;
}

//Pour vérifier s'il y a combo sur le bonbon de la case et les 2 suivants sur la colonne.
bool Niveau::comboVertical(int lign, int col){
    int i=(lign*nb_col) + col;
    if (lign+2<nb_lign && lign+1<nb_lign){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i+nb_col)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i+nb_col*2)->getBonbon()->getCouleur()){
            return true;
        }
    }
    return false;
}

//combo en L
bool Niveau::comboCoinHG (int lign, int col){
    return (comboHorizontal(lign, col)+ comboVertical(lign, col));
}

bool Niveau::comboCoinHD(int lign, int col){
    if (col+2<nb_col && col+1<nb_col){
        return (comboHorizontal(lign, col)+ comboVertical(lign, col+2));
    }
    else return false;
}

bool Niveau::comboCoinBG(int lign, int col){
    if (lign+2<nb_lign && lign+1<nb_lign){
        return (comboHorizontal(lign+2, col)+ comboVertical(lign, col));
    }
    else return false;
}

bool Niveau::comboCoinBD(int lign, int col){
    if (2<=col){
        return (comboHorizontal(lign, col-2)+ comboVertical(lign, col));
    }
    else return false;
}

#include "controleur.h"

Controleur::Controleur(QObject *parent) :
    QObject(parent)
{
    QList<Case*> liste;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            liste.push_back(NULL);
        }
    }
    niveau=NULL;
}

int Controleur::getResolutionBonbon() const{
    return resolutionBonbon;
}

int Controleur::getTailleBonbon() const{
    return tailleBonbon;
}

int Controleur::getScore() const{
    if(niveau!=NULL)
        return niveau->getScore();
    else
        return 0;
}

int Controleur::getNbMvt() const{
    if(niveau!=NULL)
        return niveau->getNb_mvt();
    else
        return 0;
}

int Controleur::getNumNiveau() const{
    if(niveau!=NULL)
        return niveau->getNum_niveau();
    else
        return 0;
}

void Controleur::setTailleBonbon(int taille){
    if(taille!=tailleBonbon){
        tailleBonbon=taille;
        emit tailleBonbonChanged();

        //3 niveau de resolution 45 , 75 et 105 px
        if(taille<60 && resolutionBonbon!=45){
            resolutionBonbon=45;
            emit resolutionBonbonChanged();
        }else if(taille>90 && resolutionBonbon!=105){
            resolutionBonbon=105;
            emit resolutionBonbonChanged();
        }else if(resolutionBonbon!=75){
            resolutionBonbon=75;
            emit resolutionBonbonChanged();
        }
    }

}

int Controleur::getNbColonne() const{
    if(niveau!=NULL)
        return niveau->getNb_col();
    else
        return 1;
}

int Controleur::getScoreObjectif() const{
    if(niveau!=NULL)
        return niveau->getScore_objectif();
    else
        return 1;
}

int Controleur::getNbTotalNiveau() const{
    return NB_TOTAL_NIVEAU;
}

void Controleur::chargerNiveau(int n){
    delete niveau;
    niveau=new Niveau(n);
    emit nbColonneChanged();
    emit numNiveauChanged();
    emit scoreChanged();
    emit actualiserTailleBonbon();
    emit scoreObjectifChanged();
    emit nbMvtChanged();
}

void Controleur::selectionBonbon1(int x,int y){
    xSelBonbon = x/tailleBonbon;
    ySelBonbon = y/tailleBonbon;
}

void Controleur::selectionBonbon2(int x,int y){
    int xSelBonbon = x/tailleBonbon;
    int ySelBonbon = y/tailleBonbon;
    if(xSelBonbon==this->xSelBonbon){
        if(ySelBonbon>this->ySelBonbon){
            ySelBonbon= this->ySelBonbon+1;
        }else if(ySelBonbon<this->ySelBonbon){
            ySelBonbon= this->ySelBonbon-1;
        }
    }else if(ySelBonbon==this->ySelBonbon){
        if(xSelBonbon>this->xSelBonbon){
            xSelBonbon= this->xSelBonbon+1;
        }else if(xSelBonbon<this->xSelBonbon){
            xSelBonbon= this->xSelBonbon-1;
        }
    }

    //niveau->estPossible(niveau->index(this->xSelBonbon,this->ySelBonbon),niveau->index(xSelBonbon,ySelBonbon));
    //Puis reste du déroulement du jeu
}

bool Controleur::getAnimation() const{
    return animation;
}
void Controleur::setAnimation(bool b){
    if(b!=animation){
        animation=b;
        emit animationChanged();
    }
}

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

void Controleur::chargerNiveau(int n){
    if(niveau!=NULL)
        delete(niveau);
    niveau=new Niveau(n);
    emit nbColonneChanged();
    emit actualiserTailleBonbon();
}

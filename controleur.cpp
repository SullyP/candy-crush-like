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
    niveau=Niveau(1,10000,liste,9,9,30);
}

int Controleur::getTailleBonbon() const{
    return tailleBonbon;
}

void Controleur::setTailleBonbon(int taille){
    if(taille!=tailleBonbon){
        tailleBonbon=taille;
        emit tailleBonbonChanged();
    }
}

int Controleur::getNbColonne() const{
    return niveau.getNb_col();
}

void Controleur::newNiveau(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            niveau.ajouterCase(i,j);
            Bonbon::Couleur color;
            Bonbon::Type type;
            int temp = rand() % 4;
            switch(temp){
                case 0:
                    type=Bonbon::Normal;
                    break;
                case 1:
                    type=Bonbon::RayureH;
                    break;
                case 2:
                    type=Bonbon::RayureV;
                    break;
                default:
                    type=Bonbon::Sucre;
            }
            temp = rand() % 7;
            switch(temp){
                case 0:
                    color=Bonbon::Rouge;
                    break;
                case 1:
                    color=Bonbon::Jaune;
                    break;
                case 2:
                    color=Bonbon::Vert;
                    break;
                case 3:
                    color=Bonbon::Bleu;
                    break;
                case 4:
                    color=Bonbon::Violet;
                    break;
                case 5:
                    color=Bonbon::Rose;
                    break;
                default:
                    color=Bonbon::Aucune;
                    type=Bonbon::Bombe;
            }

            niveau.ajouterBonbon(i,j,color,type);

        }
    }
}

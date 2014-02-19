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

//Get and Set////////////////////////////////////////////////////////////////////////
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


//premiere case lign=0 col=0.
//Indique s'il n'y a pas de case définie
bool Niveau::estVide (int lign, int col){
    return (liste.at((lign*nb_col) + col) == NULL);
}

//Indique s'il y a un bonbon dans la case
bool Niveau::sansBonbon (int lign, int col){
    return (estVide(lign, col) || liste.at((lign*nb_col) + col)->getBonbon()==NULL);
}

// Retourne l'id de la case
int Niveau::index(int lign, int col){
    return (lign*nb_col) + col;
}

//Combo///////////////////////////////////////////////////////////////////////////////////////
//Pour vérifier s'il y a combo horizontal sur le bonbon.
bool Niveau::comboHorizontal (int lign, int col){
    int i=(lign*nb_col) + col;
    if (col+2<nb_col){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i+1)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i+2)->getBonbon()->getCouleur()){
            return true;
        }
    }
    if (col-1>=0 && col+1<nb_col){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i+1)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i-1)->getBonbon()->getCouleur()){
            return true;
        }
    }
    if (col-2>=0){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i-1)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i-2)->getBonbon()->getCouleur()){
            return true;
        }
    }
    return false;
}

//Pour vérifier s'il y a combo vertical sur le bonbon.
bool Niveau::comboVertical(int lign, int col){
    int i=(lign*nb_col) + col;
    if (lign+2<nb_lign){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i+nb_col)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i+nb_col*2)->getBonbon()->getCouleur()){
            return true;
        }
    }
    if (lign+1<nb_lign && lign-1>=0){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i+nb_col)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i-nb_col)->getBonbon()->getCouleur()){
            return true;
        }
    }
    if (lign-2>=0){
        if (liste.at(i)->getBonbon()->getCouleur()==liste.at(i-nb_col)->getBonbon()->getCouleur() && liste.at(i)->getBonbon()->getCouleur()==liste.at(i-nb_col*2)->getBonbon()->getCouleur()){
            return true;
        }
    }
    return false;
}

//Combo final
// vérifie horizontalement et verticalement si le bonbon indiqué fait parti d'un combo
bool Niveau::combo (int lign, int col){
    return (comboHorizontal(lign, col) || comboVertical(lign, col));
}

//Ajout/Suppresion Bonbon/Case //////////////////////////////////////////////////////////////////
void Niveau::ajouterBonbon(int ligne, int colonne,Bonbon::Couleur couleur, Bonbon::Type type){
    if(!estVide(ligne,colonne) && sansBonbon(ligne,colonne)){
        QQmlComponent component(GlobalViewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueBonbon.qml"));
        Bonbon* bonbec = qobject_cast<Bonbon *>(component.create());
        bonbec->setType(type);
        bonbec->setCouleur(couleur);
        bonbec->setProperty("ligne",QVariant(ligne));
        bonbec->setProperty("colonne",QVariant(colonne));
        bonbec->setParent(GlobalGrille);
        bonbec->setParentItem(GlobalGrille);
        liste.at(index(ligne,colonne))->setBonbon(bonbec);
    }
}

void Niveau::ajouterCase(int ligne, int colonne, bool debut, bool fin, bool franchissable){
    if(estVide(ligne,colonne)){
        QQmlComponent component(GlobalViewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueCase.qml"));
        Case *curCell = qobject_cast<Case *>(component.create());
        curCell->setDebut(debut);
        curCell->setFin(fin);
        curCell->setFranchissable(franchissable);
        curCell->setBonbon(NULL);
        curCell->setProperty("ligne",QVariant(ligne));
        curCell->setProperty("colonne",QVariant(colonne));
        curCell->setParent(GlobalGrille);
        curCell->setParentItem(GlobalGrille);
        liste[index(ligne,colonne)]=curCell;
    }
}

void Niveau::supprimerBonbon(int ligne, int colonne){
    if(!estVide(ligne,colonne) && !sansBonbon(ligne,colonne)){
        liste.at(index(ligne,colonne))->getBonbon()->destroyed();
        liste.at(index(ligne,colonne))->setBonbon(NULL);
    }
}

void Niveau::supprimerCase(int ligne, int colonne){
    if(!estVide(ligne,colonne)){
        supprimerBonbon(ligne,colonne);
        liste.at(index(ligne,colonne))->destroyed();
        liste[index(ligne,colonne)]=NULL;
    }
}

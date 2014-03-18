#include "controleur.h"

#define TEMPS_TIMER_ANIMATION 405
#define TEMPS_TIMER_SANS_ANIMATION 1
Controleur::Controleur(QObject *parent) :
    QObject(parent)
{
    niveau=NULL;
    animationX=false;
    animationY=true;
    etape=0;
    timer.setInterval(TEMPS_TIMER_ANIMATION);
    connect(&timer, SIGNAL(timeout()), this, SLOT(deroulementJeu()));

    //Initialisation sélecteur de bonbon
    x1SelBonbon=-1;
    y1SelBonbon=-1;
    x2SelBonbon=-1;
    y2SelBonbon=-1;
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

    //Initialisation etape et timer et coefScrore
    etape=0;
    coefScore=1;
    timer.stop();
}

void Controleur::selectionBonbon1(int x,int y){
    if(etape==0){
        x1SelBonbon = x/tailleBonbon;
        y1SelBonbon = y/tailleBonbon;
    }
}

void Controleur::selectionBonbon2(int x,int y){
    if(etape == 0){
        int xSel = x/tailleBonbon;
        int ySel = y/tailleBonbon;
        if(xSel == x1SelBonbon){
            x2SelBonbon = x1SelBonbon;
            if(ySel > y1SelBonbon){
                y2SelBonbon = y1SelBonbon+1;
            }else if(ySel < y1SelBonbon){
                y2SelBonbon = y1SelBonbon-1;
            }
        }else if(ySel == y1SelBonbon){
            y2SelBonbon = y1SelBonbon;
            if(xSel > x1SelBonbon){
                x2SelBonbon = x1SelBonbon+1;
            }else if(xSel < x1SelBonbon){
                x2SelBonbon= x1SelBonbon-1;
            }
        }

        //Si la commutation à bien été effectuée
        if(niveau->commuterBonbon(x1SelBonbon,y1SelBonbon,x2SelBonbon,y2SelBonbon)){
            etape++;
            timer.start(TEMPS_TIMER_ANIMATION);
        }
    }
}

bool Controleur::getAnimationY() const{
    return animationY;
}
void Controleur::setAnimationY(bool b){
    if(b!=animationY){
        animationY=b;
        emit animationYChanged();
    }
}

bool Controleur::getAnimationX() const{
    return animationX;
}
void Controleur::setAnimationX(bool b){
    if(b!=animationX){
        animationX=b;
        emit animationXChanged();
    }
}

void Controleur::deroulementJeu(){
    QString msg;
    switch(etape){
    case -1:
        //ETAPE -1: Vérification et réinistialisation avant etape 0
        x1SelBonbon=-1;
        y1SelBonbon=-1;
        x2SelBonbon=-1;
        y2SelBonbon=-1;
        coefScore=1;
        //Si le niveau est terminé.
        msg = niveau->estFini();
        if(msg!=""){
            emit msgFinNiveau(msg);
            timer.stop();
            break;
        }
        if(!niveau->coupPossible()){
            emit redistributionJeux();
            //niveau->redistribuer();
            etape=2;
            timer.start(TEMPS_TIMER_ANIMATION);
            break;
        }
        timer.stop();
        etape=0;
        break;
    case 0:
        //ETAPE 0: Le joueur peut jouer
        timer.stop();
        break;
    case 1:
        //ETAPE 1: Commutation des bonbons
        //Si le déplacement est possible
        if(niveau->estPossible(x1SelBonbon,y1SelBonbon,x2SelBonbon,y2SelBonbon)){
            etape++;
            emit nbMvtChanged();
            //Si l'un des deux bonbons est une bombe, alors animations.
            if(niveau->estBombe(x1SelBonbon,y1SelBonbon) || niveau->estBombe(x2SelBonbon,y2SelBonbon)){
                timer.start(TEMPS_TIMER_ANIMATION/2);
            }else{
                timer.start(TEMPS_TIMER_SANS_ANIMATION);
            }
        }else{
            etape=-1;
            timer.start(TEMPS_TIMER_ANIMATION);
        }
        break;
    case 2:
        //ETAPE 2: 'Marquage' des bonbons
        //Si des bonbons sont marqués
        if(niveau->marquerDestruction()){
            niveau->compterScore(coefScore);
            coefScore=coefScore+0.5;
            emit scoreChanged();
            etape++;
            timer.start(TEMPS_TIMER_ANIMATION);
        }else{
            etape=-1;
            timer.start(TEMPS_TIMER_SANS_ANIMATION);
        }
        break;
    case 3:
        //ETAPE 3: Destruction des bonbons
        if(niveau->detruire()){
            etape++;
        }else{
            etape=-1;
        }
        timer.start(TEMPS_TIMER_SANS_ANIMATION);
        break;
    case 4:
        //ETAPE 4: Générer et tomber les bonbons
        //Générer les bonbons dans les cases de début
        niveau->completer();
        //Si des bonbons sont tombés
        if(niveau->tomber()){
            timer.start(TEMPS_TIMER_SANS_ANIMATION);
        }else{
            etape=2;
            timer.start(TEMPS_TIMER_ANIMATION);
        }
        break;
    }
}

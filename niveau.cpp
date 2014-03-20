#include "niveau.h"

using namespace std;

const QtQuick2ApplicationViewer* Niveau::viewer;
QQuickItem* Niveau::grille;

Niveau::Niveau(){

}

Niveau::~Niveau(){
    for(int i=0;i<nb_col;i++){
        for(int j=0;j<nb_lign;j++){
            supprimerCase(i,j);
        }
    }
}

Niveau::Niveau(int nbNiveau){
    ostringstream nomFichier;
    nomFichier << ":/levels/" << nbNiveau;

    QFile file((nomFichier.str()).c_str());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int etape =0;
    num_niveau=nbNiveau;
    score=0;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString ligne = in.readLine();
        switch(etape){
        case 0:
            if(ligne=="score_objectif:")
                etape++;
            break;
        case 1:
            score_objectif=ligne.toInt();
            etape++;
            break;
        case 2:
            if(ligne=="nb_col:")
                etape++;
            break;
        case 3:
            nb_col=ligne.toInt();
            etape++;
            break;
        case 4:
            if(ligne=="nb_lign:")
                etape++;
            break;
        case 5:
            nb_lign=ligne.toInt();
            etape++;
            break;
        case 6:
            if(ligne=="nb_mvt:")
                etape++;
            break;
        case 7:
            nb_mvt=ligne.toInt();
            etape++;
            break;
        case 8:
            if(ligne=="case_vide:")
                etape++;
            break;
        case 9:
            if(ligne!="case_bloc:")
                caseVide.push_back(ligne.toInt());
            else
                etape++;
            break;
        case 10:
            if(ligne!="case_debut:")
                caseBloc.push_back(ligne.toInt());
            else
                etape++;
            break;
        case 11:
            if(ligne!="case_gelatine:")
                caseDebut.push_back(ligne.toInt());
            else
                etape++;
            break;
        case 12:
            if(ligne!="case_fin:")
                caseGelatine.push_back(ligne.toInt());
            else
                etape++;
            break;
        case 13:
            caseFin.push_back(ligne.toInt());

        }
    }

    //Création de la grille et des cases
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            liste.append(NULL);

            if(caseVide.contains(index(i,j))){
                //RIEN
            }else if(caseBloc.contains(index(i,j))){
                ajouterCase(i,j,false,false,false);
            }else {
                ajouterCase(i,j,caseDebut.contains(index(i,j)),caseFin.contains(index(i,j)),true,((caseGelatine.contains(index(i,j)))? 2 : 0));
            }
        }
    }

    //Remplissage de la grille par des bonbons
    remplir();
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
//Autres///////////////////////////////////////////////////////////////////////////////////////////

//premiere case lign=0 col=0.
//Indique s'il n'y a pas de case définie
bool Niveau::estVide (int lign, int col) const{
    return (index(lign,col) == -1 || liste.at(index(lign,col)) == NULL);
}

//Indique si la case est un Bloc (case non franchissable)
bool Niveau::estBloc (int lign, int col) const{
    return (!liste.at(index(lign,col))->estFranchissable());
}

//indique si la case est une case debut
bool Niveau::estDebut(int lign, int col) const{
    return (liste.at(index(lign,col))->estDebut());
}

//Indique s'il y a un bonbon dans la case
bool Niveau::sansBonbon (int lign, int col) const{
    return (estVide(lign, col) || liste.at(index(lign,col))->getBonbon()==NULL);
}

//Indique si le bonbon est marqué pour la destruction
bool Niveau::estMarquer(int lign,int col) const{
    if(index(lign,col)!=-1 && !sansBonbon(lign,col)){
        return getBonbon(lign,col)->property("etat")=="destruction";
    }
    return false;
}

// Retourne l'id de la case et retourne -1 s'il est en dehors de la liste
int Niveau::index(int lign, int col) const{
    if(lign>=0 && lign<nb_lign && col>=0 && col<nb_col)
        return (lign*nb_col) + col;
    else
        return -1;
}

//Remplissage de la grille de manière aléatoire, puis on change la couleur des bonbons qui forment un combo
//La grille obtenue a au moins un coup possible.
void Niveau::remplir(){
    while(!coupPossible()){
        for(int i=0;i<nb_lign;i++){
            for(int j=0;j<nb_col;j++){
                if(!estVide(i,j) && !estBloc(i,j)){
                    supprimerBonbon(i,j);
                    ajouterBonbon(i,j,couleurHasard());
                    Bonbon *b1,*b2,*b3,*b4;
                    bool comboColonne=false, comboLigne=false;
                    b1 = getBonbon(i, j - 1);
                    b2 = getBonbon(i, j - 2);
                    b3 = getBonbon(i-1,j);
                    b4 = getBonbon(i-2,j);
                    if(b1!=NULL && b2!=NULL)
                        comboColonne=(b1->getCouleur() == getBonbon(i,j)->getCouleur() && b2->getCouleur()==getBonbon(i,j)->getCouleur());
                    if(b3!=NULL && b4!=NULL)
                        comboLigne=(b3->getCouleur() == getBonbon(i,j)->getCouleur() && b4->getCouleur()==getBonbon(i,j)->getCouleur());

                    while(comboLigne || comboColonne){
                        Bonbon::Couleur newCouleur = couleurHasard();
                        if(newCouleur!=getBonbon(i,j)->getCouleur()){
                            getBonbon(i,j)->setCouleur(newCouleur);
                            if(b1!=NULL && b2!=NULL)
                                comboColonne=(b1->getCouleur() == newCouleur && b2->getCouleur()==newCouleur);
                            if(b3!=NULL && b4!=NULL)
                                comboLigne=(b3->getCouleur() == newCouleur && b4->getCouleur()==newCouleur);
                        }
                    }
                }
            }
        }
    }
}

//Renvoye vrai si le déplacement est possible, faux sinon.
//Re-commute les bonbons si le déplacement n'est pas possible.
//Marque les bonbons si les deux bonbons intervertis sont spéciaux
bool Niveau::estPossible(int x1, int y1, int x2, int y2){
    if(getBonbon(x1,y1)!=NULL && getBonbon(x2,y2)!=NULL){
        //Si le coup est possible entre deux bonbons spéciaux, ou s'il y a une bombe
        if((getBonbon(x1,y1)->getType() != Bonbon::Normal && getBonbon(x2,y2)->getType() != Bonbon::Normal)
                || (getBonbon(x1,y1)->getType() == Bonbon::Bombe || getBonbon(x2,y2)->getType() == Bonbon::Bombe)){
            //Si c'est deux bombes
            if(getBonbon(x1,y1)->getType() == Bonbon::Bombe && getBonbon(x2,y2)->getType() == Bonbon::Bombe){
                //On explose tout
                for(int i=0;i<nb_lign;i++){
                    for(int j=0;j<nb_col;j++){
                        if(getBonbon(i,j)!=NULL){
                            getBonbon(i,j)->setType(Bonbon::Bombe);
                            getBonbon(i,j)->setCouleur(Bonbon::Aucune);
                            getBonbon(i,j)->setProperty("etat",QVariant("aMarquer"));
                        }
                    }
                }
            }else{
                getBonbon(x1,y1)->setProperty("etat",QVariant("aMarquer"));
                getBonbon(x2,y2)->setProperty("etat",QVariant("aMarquer"));
                if(getBonbon(x1,y1)->getType() == Bonbon::Bombe){
                    Bonbon::Couleur couleur = getBonbon(x2,y2)->getCouleur();
                    Bonbon::Type type = getBonbon(x2,y2)->getType();
                    for(int i=0;i<nb_lign;i++){
                        for(int j=0;j<nb_col;j++){
                            if(getBonbon(i,j)!=NULL && getBonbon(i,j)->getCouleur()==couleur){
                                if(type!=Bonbon::Normal)
                                    getBonbon(i,j)->setType(type);
                                getBonbon(i,j)->setProperty("etat",QVariant("aMarquer"));
                            }
                        }
                    }
                }else if(getBonbon(x2,y2)->getType() == Bonbon::Bombe){
                    Bonbon::Couleur couleur = getBonbon(x1,y1)->getCouleur();
                    Bonbon::Type type = getBonbon(x1,y1)->getType();
                    for(int i=0;i<nb_lign;i++){
                        for(int j=0;j<nb_col;j++){
                            if(getBonbon(i,j)!=NULL && getBonbon(i,j)->getCouleur()==couleur){
                                if(type!=Bonbon::Normal)
                                    getBonbon(i,j)->setType(type);
                                getBonbon(i,j)->setProperty("etat",QVariant("aMarquer"));
                            }
                        }
                    }
                }
            }
            nb_mvt--;
            return true;
            //Si le coup est possible on renvoye vrai
        }else if(combo(x1,y1) || combo(x2,y2)){
            //et on décrémente les déplacements possibles
            nb_mvt--;
            return true;
        }else{
            //Sinon on remet les bonbons dans leur position initiale
            commuterBonbon(x1,y1,x2,y2);
            //et on renvoye faux
            return false;
        }
    }else{
        return false;
    }
}


//Retourne le bonbon à la case spécifié, s'il existe
Bonbon* Niveau::getBonbon(int lign, int col) const{
    if(index(lign,col)!=-1 && liste.at(index(lign,col))!=NULL)
        return liste.at(index(lign,col))->getBonbon();
    else
        return NULL;

}

Bonbon::Couleur Niveau::couleurHasard() const{
    Bonbon::Couleur couleur;
    int temp = rand() % 6;
    switch(temp){
    case 0:
        couleur=Bonbon::Rouge;
        break;
    case 1:
        couleur=Bonbon::Jaune;
        break;
    case 2:
        couleur=Bonbon::Vert;
        break;
    case 3:
        couleur=Bonbon::Bleu;
        break;
    case 4:
        couleur=Bonbon::Violet;
        break;
    default:
        couleur=Bonbon::Rose;
        break;
    }
    return couleur;
}

//retourne la couleur du bonbon spécifié, s'il existe
Bonbon::Couleur Niveau::getCouleur (int lign, int col){
    if (getBonbon(lign, col)!=NULL)
        return getBonbon(lign,col)->getCouleur();
    else
        return Bonbon::Aucune;
}

//Combo///////////////////////////////////////////////////////////////////////////////////////
//Pour vérifier s'il y a combo horizontal sur le bonbon.
bool Niveau::comboHorizontal (int lign, int col){
    if (col+2<nb_col){
        if (getCouleur(lign,col)==getCouleur(lign,col+1) && getCouleur(lign,col)==getCouleur(lign,col+2)){
            return true;
        }
    }
    if (col-1>=0 && col+1<nb_col){
        if (getCouleur(lign,col)==getCouleur(lign,col+1) && getCouleur(lign,col)==getCouleur(lign,col-1)){
            return true;
        }
    }
    if (col-2>=0){
        if (getCouleur(lign,col)==getCouleur(lign,col-1) && getCouleur(lign,col)==getCouleur(lign,col-2)){
            return true;
        }
    }
    return false;
}

//Pour vérifier s'il y a combo vertical sur le bonbon.
bool Niveau::comboVertical(int lign, int col){
    if (lign+2<nb_lign){
        if (getCouleur(lign,col)==getCouleur(lign+1,col) && getCouleur(lign,col)==getCouleur(lign+2,col)){
            return true;
        }
    }
    if (lign+1<nb_lign && lign-1>=0){
        if (getCouleur(lign,col)==getCouleur(lign+1,col) && getCouleur(lign,col)==getCouleur(lign-1,col)){
            return true;
        }
    }
    if (lign-2>=0){
        if (getCouleur(lign,col)==getCouleur(lign-1,col) && getCouleur(lign,col)==getCouleur(lign-2,col)){
            return true;
        }
    }
    return false;
}

//Combo final
// vérifie horizontalement et verticalement si le bonbon indiqué fait parti d'un combo
bool Niveau::combo(int lign, int col){
    return (comboHorizontal(lign, col) || comboVertical(lign, col));
}

//Coup possible
//vérifie s'il reste des coups possibles sur la grille actuelle
bool Niveau::coupPossible() const {
    for(int i = 0; i<nb_lign; i++){
        for(int j = 0; j<nb_col; j++){
            if(comboPossible(i,j)){
                return true;
            }
        }
    }
    return false;
}

bool Niveau::comboPossible(int lign, int col) const{
    if(sansBonbon(lign, col)){
        return false;
    }else if(!estVide(lign, col) && estBloc(lign, col)){
    }else if(getBonbon(lign, col)->getType()!=Bonbon::Normal){
        if(col+1<nb_col){
            if(!sansBonbon(lign, col+1)){
                if(getBonbon(lign, col+1)->getType()!=Bonbon::Normal){
                    return true;
                }
            }
        }
        if(lign+1<nb_lign){
            if(!sansBonbon(lign+1, col)){
                if(getBonbon(lign+1, col)->getType()!=Bonbon::Normal){
                    return true;
                }
            }
        }
    }
    if(col+3<nb_col){
        if(possibleHL(lign, col)){
            return true;
        }
    }
    if(lign+3<nb_lign){
        if(possibleVL(lign, col)){
            return true;
        }
    }
    if(col+2<nb_col && lign+1<nb_lign){
        if(possibleHR(lign, col)){
            return true;
        }
    }
    if(lign+2<nb_lign && col+1<nb_col){
        if(possibleVR(lign, col)){
            return true;
        }
    }
    return false;
}

//test sur rectangle 1x4 horizontal si 3 bonbon de la même couleur, un coup est possible
bool Niveau::possibleHL(int lign, int col) const{
    int rg=0,ja=0,ve=0,b=0,vi=0,rs=0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    for(int i=0;i<4;i++){
        if(sansBonbon(lign, col+i)){
            return false;
        }else if(!estVide(lign, col+i) && estBloc(lign, col+i)){
            return false;
        }
        else{
            tmpCouleur = getBonbon(lign, col+i)->getCouleur();
            switch(tmpCouleur) {
            case Bonbon::Rouge:
                rg++;
                break;
            case Bonbon::Jaune:
                ja++;
                break;
            case Bonbon::Vert:
                ve++;
                break;
            case Bonbon::Bleu:
                b++;
                break;
            case Bonbon::Violet:
                vi++;
                break;
            case Bonbon::Rose:
                rs++;
                break;
            case Bonbon::Aucune:
                if(getBonbon(lign, col+i)->getType() == Bonbon::Bombe){
                    return true;
                }
            }
        }
    }
    if(rg==3 || ja==3 || ve==3 || b==3 || vi==3 || rs==3){
        return true;
    }
    return false;
}

//test sur rectangle 1x4 vertical si 3 bonbon de la même couleur, un coup est possible
bool Niveau::possibleVL(int lign, int col) const{
    int rg=0,ja=0,ve=0,b=0,vi=0,rs=0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    for(int i=0;i<4;i++){
        if(sansBonbon(lign+i, col)){
            return false;
        }else if(!estVide(lign+i, col) && estBloc(lign+i, col)){
            return false;
        }else {
            tmpCouleur = getBonbon(lign+i, col)->getCouleur();
            switch(tmpCouleur) {
            case Bonbon::Rouge:
                rg++;
                break;
            case Bonbon::Jaune:
                ja++;
                break;
            case Bonbon::Vert:
                ve++;
                break;
            case Bonbon::Bleu:
                b++;
                break;
            case Bonbon::Violet:
                vi++;
                break;
            case Bonbon::Rose:
                rs++;
                break;
            case Bonbon::Aucune:
                if(getBonbon(lign+i, col)->getType() == Bonbon::Bombe){
                    return true;
                }
            }
        }
    }
    if(rg==3 || ja==3 || ve==3 || b==3 || vi==3 || rs==3){
        return true;
    }
    return false;
}

//test sur rectangle 2x3 horizontal si 3 ou 4 bonbons de la même couleur, il peut y avoir un coup possible
bool Niveau::possibleHR(int lign, int col) const{
    int rg=0,ja=0,ve=0,b=0,vi=0,rs=0,bloc=0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    //test sur rectangle 2x3 horizontal si 3 ou 4 bonbons de la même couleur, il peut y avoir un coup possible
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            if(sansBonbon(lign+i, col+j)){
                bloc++;
            }else if(!estVide(lign+i,col+j) && estBloc(lign+i, col+j)){
                bloc++;
            }else {
                tmpCouleur = getBonbon(lign+i, col+j)->getCouleur();
                switch(tmpCouleur) {
                case Bonbon::Rouge:
                    rg++;
                    break;
                case Bonbon::Jaune:
                    ja++;
                    break;
                case Bonbon::Vert:
                    ve++;
                    break;
                case Bonbon::Bleu:
                    b++;
                    break;
                case Bonbon::Violet:
                    vi++;
                    break;
                case Bonbon::Rose:
                    rs++;
                    break;
                case Bonbon::Aucune:
                    if(getBonbon(lign+i, col+j)->getType() == Bonbon::Bombe){
                        return true;
                    }
                }
            }
        }
    }
    if(rg>=3 || ja>=3 || ve>=3 || b>=3 || vi>=3 || rs>=3){
        if(rg==4 || ja==4 || ve==4 || b==4 || vi==4 || rs==4){
            if(rg==4){
                tmpCouleur = Bonbon::Rouge;
            }else if(ja==4){
                tmpCouleur = Bonbon::Jaune;
            }else if(ve==4){
                tmpCouleur = Bonbon::Vert;
            }else if(b==4){
                tmpCouleur = Bonbon::Bleu;
            }else if(vi==4){
                tmpCouleur = Bonbon::Violet;
            }else {
                tmpCouleur = Bonbon::Rose;
            }
            if(!sansBonbon(lign, col+1) && getBonbon(lign, col+1)->getCouleur() == tmpCouleur && !sansBonbon(lign+1, col+1) && getBonbon(lign+1, col+1)->getCouleur() == tmpCouleur){
                if(!sansBonbon(lign+1, col) && !sansBonbon(lign, col) &&(getBonbon(lign, col)->getCouleur() != getBonbon(lign+1, col)->getCouleur())
                        && ((getBonbon(lign, col)->getCouleur() == tmpCouleur) || (getBonbon(lign+1, col)->getCouleur() == tmpCouleur))){
                    return true;
                }
            }
            if((!sansBonbon(lign, col+1) && !sansBonbon(lign+1, col+1) && getBonbon(lign, col+1)->getCouleur() != getBonbon(lign+1, col+1)->getCouleur())
                    && ((getBonbon(lign, col+1)->getCouleur() == tmpCouleur) || (getBonbon(lign+1, col+1)->getCouleur() == tmpCouleur))){
                return true;
            }
        }else {
            int nbL1 = 0;
            int LBloc = 2;
            if(rg==3){
                tmpCouleur = Bonbon::Rouge;
            }else if(ja==3){
                tmpCouleur = Bonbon::Jaune;
            }else if(ve==3){
                tmpCouleur = Bonbon::Vert;
            }else if(b==3){
                tmpCouleur = Bonbon::Bleu;
            }else if(vi==3){
                tmpCouleur = Bonbon::Violet;
            }else {
                tmpCouleur = Bonbon::Rose;
            }
            for(int i=0;i<3;i++){
                if(sansBonbon(lign, col+i)){
                    LBloc = 1;
                }else if(!estVide(lign,col+i) && estBloc(lign, col+i)){
                    LBloc = 1;
                }else if(getBonbon(lign, col+i)->getCouleur() == tmpCouleur){
                    if(!estVide (lign+1, col+i) && !estBloc(lign+1, col+i)){
                        if(getBonbon(lign+1, col+i)->getCouleur() == tmpCouleur){
                            return false;
                        }
                    }
                    nbL1++;
                }
            }
            if((nbL1 == 2) && (LBloc == 2)){
                return true;
            }else if((nbL1 == 1) && (LBloc == 1)){
                return true;
            }
        }
    }
    return false;
}

//test sur rectangle 2x3 vertical si 3 ou 4 bonbons de la même couleur, il peut y avoir un coup possible
bool Niveau::possibleVR(int lign, int col) const{
    int rg=0,ja=0,ve=0,b=0,vi=0,rs=0,bloc=0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            if(sansBonbon(lign+i, col+j)){
                bloc++;
            }else if(!estVide(lign+i, col+j) && estBloc(lign+i, col+j)){
                bloc++;
            }else {
                tmpCouleur = getBonbon(lign+i, col+j)->getCouleur();
                switch(tmpCouleur) {
                case Bonbon::Rouge:
                    rg++;
                    break;
                case Bonbon::Jaune:
                    ja++;
                    break;
                case Bonbon::Vert:
                    ve++;
                    break;
                case Bonbon::Bleu:
                    b++;
                    break;
                case Bonbon::Violet:
                    vi++;
                    break;
                case Bonbon::Rose:
                    rs++;
                    break;
                case Bonbon::Aucune:
                    if(getBonbon(lign+i, col+j)->getType() == Bonbon::Bombe){
                        return true;
                    }
                }
            }
        }
    }
    if(rg>=3 || ja>=3 || ve>=3 || b>=3 || vi>=3 || rs>=3){
        if(rg==4 || ja==4 || ve==4 || b==4 || vi==4 || rs==4){
            if(rg==4){
                tmpCouleur = Bonbon::Rouge;
            }else if(ja==4){
                tmpCouleur = Bonbon::Jaune;
            }else if(ve==4){
                tmpCouleur = Bonbon::Vert;
            }else if(b==4){
                tmpCouleur = Bonbon::Bleu;
            }else if(vi==4){
                tmpCouleur = Bonbon::Violet;
            }else {
                tmpCouleur = Bonbon::Rose;
            }
            if(!sansBonbon(lign+1, col) &&  !sansBonbon(lign+1, col+1) && getBonbon(lign+1, col)->getCouleur() == tmpCouleur && getBonbon(lign+1, col+1)->getCouleur() == tmpCouleur){
                if(!sansBonbon(lign, col) && !sansBonbon(lign, col+1) && (getBonbon(lign, col)->getCouleur() != getBonbon(lign, col+1)->getCouleur())
                        && ((getBonbon(lign, col)->getCouleur() == tmpCouleur) || (getBonbon(lign, col+1)->getCouleur() == tmpCouleur))){
                    return true;
                }
            }
            if(!sansBonbon(lign+1, col) && !sansBonbon(lign+1, col+1) && (getBonbon(lign+1, col)->getCouleur() != getBonbon(lign+1, col+1)->getCouleur())
                    && ((getBonbon(lign+1, col)->getCouleur() == tmpCouleur) || (getBonbon(lign+1, col+1)->getCouleur() == tmpCouleur))){
                return true;
            }
        }else {
            int nbC1 = 0;
            int CBloc = 2;
            if(rg==3){
                tmpCouleur = Bonbon::Rouge;
            }else if(ja==3){
                tmpCouleur = Bonbon::Jaune;
            }else if(ve==3){
                tmpCouleur = Bonbon::Vert;
            }else if(b==3){
                tmpCouleur = Bonbon::Bleu;
            }else if(vi==3){
                tmpCouleur = Bonbon::Violet;
            }else {
                tmpCouleur = Bonbon::Rose;
            }
            for(int i=0;i<3;i++){
                if(sansBonbon(lign+i, col)){
                    CBloc = 1;
                }else if(!estVide(lign+i, col) && estBloc(lign+i, col)){
                    CBloc = 1;
                }else if(!sansBonbon(lign+i, col+i) && getBonbon(lign+i, col)->getCouleur() == tmpCouleur){
                    if(!estVide(lign+i, col+1) && !estBloc(lign+i, col+1)){
                        if(getBonbon(lign+i, col+1)->getCouleur() == tmpCouleur){
                            return false;
                        }
                    }
                    nbC1++;
                }
            }
            if((nbC1 == 2) && (CBloc == 2)){
                return true;
            }else if((nbC1 == 1) && (CBloc == 1)){
                return true;
            }
        }
    }
    return false;
}


//Ajout/Suppresion Bonbon/Case //////////////////////////////////////////////////////////////////
void Niveau::ajouterBonbon(int ligne, int colonne,Bonbon::Couleur couleur, Bonbon::Type type){
    if(!estVide(ligne,colonne) && !estBloc(ligne,colonne) && sansBonbon(ligne,colonne)){
        QQmlComponent component(viewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueBonbon.qml"));
        Bonbon* bonbec = qobject_cast<Bonbon *>(component.create());
        bonbec->setType(type);
        bonbec->setCouleur(couleur);
        bonbec->setProperty("ligne",QVariant(ligne));
        bonbec->setProperty("colonne",QVariant(colonne));
        bonbec->setParent(grille);
        bonbec->setParentItem(grille);
        bonbec->setProperty("etat",QVariant("normal"));
        liste.at(index(ligne,colonne))->setBonbon(bonbec);
    }
}

void Niveau::ajouterCase(int ligne, int colonne, bool debut, bool fin, bool franchissable, int niveauGelatine){
    if(estVide(ligne,colonne)){
        QQmlComponent component(viewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueCase.qml"));
        Case *curCell = qobject_cast<Case *>(component.create());
        curCell->setDebut(debut);
        curCell->setFin(fin);
        curCell->setFranchissable(franchissable);
        curCell->setNiveauGelatine(niveauGelatine);
        curCell->setBonbon(NULL);
        curCell->setProperty("ligne",QVariant(ligne));
        curCell->setProperty("colonne",QVariant(colonne));
        curCell->setParent(grille);
        curCell->setParentItem(grille);
        liste[index(ligne,colonne)]=curCell;
    }
}

void Niveau::supprimerBonbon(int ligne, int colonne){
    if (getBonbon(ligne,colonne)!=NULL){
        delete (getBonbon(ligne,colonne));
        liste[index(ligne,colonne)]->setBonbon(NULL);
    }
}

void Niveau::supprimerCase(int ligne, int colonne){
    supprimerBonbon(ligne,colonne);
    delete (liste[index(ligne,colonne)]);
    liste[index(ligne,colonne)]=NULL;
}

//detruire//////////////////////////////////////////////////////////////
//destruction des bonbons formant un combo avec le bonbon spécifié
void Niveau::marquerCombo(int lign, int col){
    if (comboHorizontal(lign, col)){
        marquerHorizontal(lign,col);
    }
    if (comboVertical(lign, col)){
        marquerVertical(lign,col);
    }
    marquerBonbon(lign,col);
}

void Niveau::marquerHorizontal(int lign, int col){
    Bonbon::Couleur c = getCouleur(lign,col) ;
    int j;
    //suppression des bonbons sur la gauche
    j=col-1;
    while (c==getCouleur(lign,j) && getCouleur(lign,j)!=Bonbon::Aucune){
        if (comboVertical(lign,j)){
            marquerVertical(lign,j);
        }
        marquerBonbon(lign,j);
        j=j-1;
    }
    //suppression des bonbons sur la droite
    j=col+1;
    while (c==getCouleur(lign,j)&& getCouleur(lign,j)!=Bonbon::Aucune) {
        if (comboVertical(lign,j)){
            marquerVertical(lign,j);
        }
        marquerBonbon(lign,j);
        j=j+1;
    }
}

void Niveau::marquerVertical(int lign, int col){
    Bonbon::Couleur c = getCouleur(lign,col) ;
    int i;
    //suppression des bonbons au dessus
    i=lign-1;
    while ( c==getCouleur(i,col)&& getCouleur(i,col)!=Bonbon::Aucune){
        if (comboHorizontal(i,col)){
            marquerHorizontal(i,col);
        }
        marquerBonbon(i,col);
        i=i-1;
    }
    //suppression des bonbons en dessous
    i=lign+1;
    while ( c==getCouleur(i,col)&& getCouleur(i,col)!=Bonbon::Aucune){
        if (comboHorizontal(i,col)){
            marquerHorizontal(i,col);
        }
        marquerBonbon(i,col);
        i=i+1;
    }
}

//Marque le bonbon à détruire et marque les autres bonbons si le bonbon en question est spécial
void Niveau::marquerBonbon(int lign,int col){
    if(index(lign,col)!=-1 && !estMarquer(lign,col) && !estVide(lign,col) && !estBloc(lign,col) && !sansBonbon(lign,col)){
        getBonbon(lign,col)->setProperty("etat",QVariant("destruction"));
        //Destruction de tous les bonbons sur un rectangle de 3*3
        if(getBonbon(lign,col)->getType()==Bonbon::Sucre){
            for(int i=lign-1;i<=lign+1;i++){
                for(int j=col-1;j<=col+1;j++){
                    marquerBonbon(i,j);
                }
            }
            //Destruction de tous les bonbons sur la colonne
        }else if(getBonbon(lign,col)->getType()==Bonbon::RayureV){
            for(int i=0;i<nb_lign;i++){
                marquerBonbon(i,col);
            }
            //Destruction de tous les bonbons sur la ligne
        }else if(getBonbon(lign,col)->getType()==Bonbon::RayureH){
            for(int i=0;i<nb_col;i++){
                marquerBonbon(lign,i);
            }
            //Destruction de tous les bonbons d'une couleur aléatoire
        }else if(getBonbon(lign,col)->getType()==Bonbon::Bombe){
            Bonbon::Couleur couleurDestruction = couleurHasard();
            for(int i=0;i<nb_lign;i++){
                for(int j=0;j<nb_col;j++){
                    if(!estVide(lign,col) && !estBloc(lign,col) && !sansBonbon(lign,col)){
                        if(getCouleur(i,j)==couleurDestruction){
                            marquerBonbon(i,j);
                        }
                    }
                }
            }
        }
    }
}

//Marque tous les combos à détruire. Renvoye vrai si des bonbons sont marqués, faux sinon.
bool Niveau::marquerDestruction(){
    bool bonbonMarquer = false;
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(!estVide(i,j) && !estBloc(i,j) && !sansBonbon(i,j) && getBonbon(i,j)->property("etat")=="aMarquer"){
                if(getBonbon(i,j)->getType()!=Bonbon::Bombe){
                    marquerBonbon(i,j);
                    bonbonMarquer = true;
                }else{
                    getBonbon(i,j)->setProperty("etat",QVariant("destruction"));
                    bonbonMarquer = true;
                }
            }
        }
    }
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(!estVide(i,j) && !estBloc(i,j) && !sansBonbon(i,j) && combo(i,j)){
                marquerCombo(i,j);
                bonbonMarquer = true;
            }
        }
    }
    return bonbonMarquer;
}

//Detruit tous les combos précédement marqués. Renvoye vrai s'il y a eu destruction, faux sinon.
bool Niveau::detruire(){
    bool destruction = false;
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(estMarquer(i,j)){
                supprimerBonbon(i,j);
                destruction = true;
            }
        }
    }
    return destruction;
}

//Commute les deux bonbons aux coordonées indiquées s'ils existent
//A condition qu'ils soient sur la même ligne ou colonne
//Renvoye vrai si le déplacement à été effectué, faux sinon
bool Niveau::commuterBonbon(int lign1, int col1, int lign2, int col2){
    Bonbon* b1 = getBonbon(lign1,col1);
    Bonbon* b2 = getBonbon(lign2,col2);
    if(b1!=NULL && b2!=NULL){
        if(lign1 == lign2){
            liste[index(lign1,col1)]->setBonbon(b2);
            liste[index(lign2,col2)]->setBonbon(b1);
            b2->setProperty("colonne",QVariant(col1));
            b1->setProperty("colonne",QVariant(col2));
            return true;
        }else if (col1 == col2){
            liste[index(lign1,col1)]->setBonbon(b2);
            liste[index(lign2,col2)]->setBonbon(b1);
            b2->setProperty("ligne",QVariant(lign1));
            b1->setProperty("ligne",QVariant(lign2));
            return true;
        }
    }
    return false;
}

//tomber//////////////////////////////////////////////////////////
//Renvoye vrai si des bonbons sont tombés, faux sinon
bool Niveau::tomber(){
    bool tombe=false;
    for(int i=nb_lign-1;i>-1;i--){
        for(int j=nb_col-1;j>-1;j--){
            if(sansBonbon(i,j) && !estVide(i,j) && !estBloc(i,j) && !estDebut(i,j)){
                tombe = tombe || tomberDuDessus(i,j);
            }
        }
    }
    return tombe;
}

//Renvoye vrai si le bonbon est bien tombé, faux sinon
bool Niveau::tomberDuDessus(int lign, int col){
    //Si la case du dessus est une case Vide
    //ou
    //Si la case du dessus est une case "normale"
    if(estVide(lign-1,col) ||
            (!estBloc(lign-1,col) && !estVide(lign-1,col))){
        //On cherche une case plus haut qui a un bonbon
        for(int curLign = lign-1; curLign>-1;curLign--){
            if(!estVide(curLign,col) && estBloc(curLign,col)){
                //Si on tombe sur un bloc on ne peut pas faire tomber de bonbon
                return false;
            }
            if(!sansBonbon(curLign,col)){
                Bonbon* b = getBonbon(curLign,col);
                liste[index(lign,col)]->setBonbon(b);
                b->setProperty("ligne",QVariant(lign));
                liste[index(curLign,col)]->setBonbon(NULL);
                return true;
            }
        }
    }
    //Si on arrive ici alors il n'y a pas de bonbon plus haut
    //Ou la case est un bloc

    //On regarde la case du dessus à droite
    if(index(lign-1,col+1)!=-1 && !sansBonbon(lign-1,col+1) &&!estBloc(lign-1,col+1)){
        Bonbon* b = getBonbon(lign-1,col+1);
        liste[index(lign,col)]->setBonbon(b);
        b->setProperty("ligne",QVariant(lign));
        b->setProperty("colonne",QVariant(col));
        liste[index(lign-1,col+1)]->setBonbon(NULL);
        return true;
    }
    //Sinon on regarde la case du dessus à gauche
    else if(index(lign-1,col-1)!=-1 &&!sansBonbon(lign-1,col-1) && !estBloc(lign-1,col-1)){
        Bonbon* b = getBonbon(lign-1,col-1);
        liste[index(lign,col)]->setBonbon(b);
        b->setProperty("ligne",QVariant(lign));
        b->setProperty("colonne",QVariant(col));
        liste[index(lign-1,col-1)]->setBonbon(NULL);
        return true;
    }

    return false;
}

//Génere des bonbons aléatoirement sur les cases de début
//Renvoye vrai si des bonbons ont été ajouté
bool Niveau::completer(){
    bool bonbonAjouter=false;
    for (int i = 0; i < caseDebut.size(); ++i) {
        int idBonbon = caseDebut.at(i);
        if((liste.at(idBonbon)->getBonbon())==NULL){
            ajouterBonbon(idBonbon/nb_col,idBonbon%nb_col,couleurHasard());
            bonbonAjouter=true;
        }
    }
    return bonbonAjouter;
}

void Niveau::setViewer(QtQuick2ApplicationViewer* v){
    viewer=v;
    grille = viewer->rootObject()->findChild<QQuickItem *>("grilleDeJeux");
}

void Niveau::compterScore(int coef){
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(estMarquer(i,j)){
                //Reduction de 1 niveau de gelatine si la case en avait
                int numGel=liste.at(index(i,j))->getNiveauGelatine();
                if(numGel>0){
                    score=score+20*numGel;
                    liste.at(index(i,j))->setNiveauGelatine(numGel-1);
                }
                if(getBonbon(i,j)->getType()==Bonbon::Normal){
                    score=score+60*coef;
                }else{
                    score=score+80*coef;
                }
            }
        }
    }
}

//Redistribue les bonbons sans créé de combos, et en gardant le même nombre et type de bonbons spéciaux
//De plus grâce à l'appel à remplir(), la grille obtenue a au moins un coup possible.
void Niveau::redistribuer(){
    QList<Bonbon*> bonus;
    int c=0;
    int iT, jT;
    for(int i=0; i<nb_lign; i++){
        for(int j=0; j<nb_col; j++){
            if(!sansBonbon(i, j)){
                if(getBonbon(i,j)->getType() != Bonbon::Normal){
                    bonus << getBonbon(i,j);
                    c++;
                }else {
                    supprimerBonbon(i,j);
                }
            }
        }
    }
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(getBonbon(i,j)!=NULL)
                liste.at(index(i,j))->setBonbon(NULL);
        }
    }
    remplir();
    while(c>0){
        iT = rand() % nb_lign-1;
        jT = rand() % nb_col-1;
        c--;
        if(!sansBonbon(iT,jT) && getBonbon(iT, jT)->getType() == Bonbon::Normal){
            getBonbon(iT,jT)->setType(bonus[c]->getType());
            if(bonus[c]->getType() == Bonbon::Bombe){
                getBonbon(iT,jT)->setCouleur(Bonbon::Aucune);
            }
            delete bonus[c];
        }else {
            c++;
        }
    }
}

bool Niveau::plusAucuneGelatine() const{
    for (int i = 0; i < caseGelatine.size(); i++) {
        int idBonbon = caseGelatine.at(i);
        if(idBonbon>=0 && idBonbon<=index(nb_lign-1,nb_col-1) &&
                liste.at(idBonbon)!=NULL && (liste.at(idBonbon)->getNiveauGelatine())!=0){
            return false;
        }
    }
    return true;
}

//Renvoye "" si le jeux n'est pas fini, le message à afficher sinon.
QString Niveau::estFini(){
    QString res="";
    if(score_objectif<=score && plusAucuneGelatine()){
        res="Bravo, vous avez gagné.";
    }else if(nb_mvt==0){
        if(score_objectif>score){
            res="Perdu. <br> Vous n'avez pas atteint l'objectif.";
        }else{
            res="Perdu. <br> Il reste de la gélatine.";
        }
    }
    return res;
}

//Indique si le bonbon de la case est une bombe
bool Niveau::estBombe(int lign,int col) const{
    if(getBonbon(lign,col)!=NULL){
        return (getBonbon(lign,col)->getType()==Bonbon::Bombe);
    }else{
        return false;
    }
}

//Indique si le bonbon de la case est spécial
bool Niveau::estSpecial(int lign, int col) const{
    if(getBonbon(lign,col)!=NULL){
        return (getBonbon(lign,col)->getType()!=Bonbon::Normal);
    }else{
        return false;
    }
}

//Combo Spéciaux////////////////////////////////////
//combo de 4 bonbons allignés formant un bonbon rayé(qui supprime toute la ligne ou la colonne)
//Horizontalement
bool Niveau::comboRayeH(int lign, int col){
    Bonbon::Couleur couleur=getCouleur(lign,col);
    if (couleur==getCouleur(lign,col+1) && couleur==getCouleur(lign,col+2) && couleur==getCouleur(lign,col+3)
            && !comboVertical(lign,col+1) && !comboVertical(lign,col+2) && !comboVertical(lign,col+3))
        return true;
    else
        return false;
}

//Verticalement
bool Niveau::comboRayeV(int lign, int col){
    Bonbon::Couleur couleur=getCouleur(lign,col);
    if ( couleur==getCouleur(lign+1,col) && couleur==getCouleur(lign+2,col) && couleur==getCouleur(lign+3,col)
         && !comboHorizontal(lign+1,col) && !comboHorizontal(lign+2,col) && !comboHorizontal(lign+3,col))
        return true;
    else
        return false;
}

//combo de 5 bonbons allignés formant un bonbon Bombe(qui supprime tous les bonbons de la même couleur que celui échangé)
//Horizontal
bool Niveau::comboBombeHori(int lign, int col){
    Bonbon::Couleur couleur=getCouleur(lign,col);
    if (comboRayeH(lign,col) && couleur==getCouleur(lign,col+4))
        return true;

    else
        return false;
}

//vertical
bool Niveau::comboBombeVerti(int lign, int col){
    Bonbon::Couleur couleur=getCouleur(lign,col);
    if (comboRayeV(lign,col) && couleur==getCouleur(lign+4,col))
        return true;

    else
        return false;
}

//combo vertical et horizontal formant un bonbon sucré(qui supprime tous les bonbons autour de lui)
bool Niveau::comboSucre(int lign, int col){
    if(comboHorizontal(lign,col) && comboVertical(lign,col))
        return true;
    else
        return false;
}

void Niveau::creerRayeH(int lign, int col){
    if(getBonbon(lign,col)!=NULL){
        getBonbon(lign,col)->setProperty("etat",QVariant("normal"));
        getBonbon(lign,col)->setType(Bonbon::RayureH);
    }
}

void Niveau::creerRayeV(int lign, int col){
    if(getBonbon(lign,col)!=NULL){
        getBonbon(lign,col)->setProperty("etat",QVariant("normal"));
        getBonbon(lign,col)->setType(Bonbon::RayureV);
    }
}

void Niveau::creerBombe(int lign, int col){
    if(getBonbon(lign,col)!=NULL){
        getBonbon(lign,col)->setProperty("etat",QVariant("normal"));
        getBonbon(lign,col)->setType(Bonbon::Bombe);
        getBonbon(lign,col)->setCouleur(Bonbon::Aucune);
    }
}

void Niveau::creerSucre(int lign, int col){
    if(getBonbon(lign,col)!=NULL){
        getBonbon(lign,col)->setProperty("etat",QVariant("normal"));
        getBonbon(lign,col)->setType(Bonbon::Sucre);
    }
}

void Niveau::ajouterBonbonSpeciaux(){
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(estMarquer(i,j)){
                if(comboBombeHori(i,j))
                    creerBombe(i,j+2);
                else if(comboBombeVerti(i,j))
                    creerBombe(i+2,j);
                else if(comboSucre(i,j))
                    creerSucre(i,j);
                else if(comboRayeH(i,j))
                    creerRayeH(i,j);
                else if(comboRayeV(i,j))
                    creerRayeV(i,j);
            }
        }
    }
}

//ajoute le bonbon spécial sur le bonbon déplacé sauf si celui-ci est déjà spécial
bool Niveau::ajouterSpecialDeplace(int lign, int col){
    bool creer=false;
    if (getBonbon(lign,col)->getType()==Bonbon::Normal){
        if (col-2>=0 && comboBombeHori(lign,col-2)){
            creerBombe(lign,col);
            creer=true;
        }
        else if (lign-2>=0 && comboBombeVerti(lign-2,col)){
            creerBombe(lign,col);
            creer=true;
        }
        else if (comboHorizontal(lign,col) && comboVertical(lign,col)){
            creerSucre(lign,col);
            creer=true;
        }
        else if (comboHorizontal(lign,col)){
            if(col-1>=0 && comboRayeH(lign,col-1)){
                creerRayeH(lign,col);
                creer=true;
            }
            else if(col-2>=0 && comboRayeH(lign,col-2)){
                creerRayeH(lign,col);
                creer=true;
            }
        }
        else if (comboVertical(lign,col)){
            if(lign-1>=0 && comboRayeV(lign-1,col)){
                creerRayeV(lign,col);
                creer=true;
            }
            else if (lign-2>=0 && comboRayeV(lign-2,col)){
                creerRayeV(lign,col);
                creer=true;
            }
        }
    }
    return creer;
}

bool Niveau::ajouterDeplace (int lign1, int col1, int lign2, int col2){
    return(ajouterSpecialDeplace(lign1,col1) || ajouterSpecialDeplace(lign2,col2));
}

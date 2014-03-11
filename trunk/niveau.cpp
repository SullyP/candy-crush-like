#include "niveau.h"

using namespace std;

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
            if(ligne!="case_fin:")
                caseDebut.push_back(ligne.toInt());
            else
                etape++;
            break;
        case 12:
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
                ajouterCase(i,j,caseDebut.contains(index(i,j)),caseFin.contains(index(i,j)));
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
    return (liste.at(index(lign,col)) == NULL);
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

// Retourne l'id de la case et retourne -1 s'il est en dehors de la liste
int Niveau::index(int lign, int col) const{
    if(lign>=0 && lign<nb_lign && col>=0 && col<nb_col)
        return (lign*nb_col) + col;
    else
        return -1;
}

//Remplissage de la grille de manière aléatoire, puis on change la couleur des bonbons qui forment un combo
void Niveau::remplir(){
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(!estVide(i,j) && !estBloc(i,j) && sansBonbon(i,j)){
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

//Renvoye vrai si le déplacement est possible, faux sinon.
//Re-commute les bonbons si le déplacment n'est pas possible.
bool Niveau::estPossible(int x1, int y1, int x2, int y2){
    if(getBonbon(x1,y1)!=NULL && getBonbon(x2,y2)!=NULL){
        //Si le coup est possible on renvoye vrai
        if(combo(x1,y1) || combo(x2,y2)){
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

//Retourne le bonbon à l'id spécifié, s'il existe
Bonbon* Niveau::getBonbon(int id) const{
    if(id!=-1 && liste.at(id)!=NULL)
        return liste.at(id)->getBonbon();
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
    case 5:
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
    }
    if(getBonbon(lign, col)->getType()!=Bonbon::Normal){
        if(!sansBonbon(lign, col+1)){
            if(getBonbon(lign, col+1)->getType()!=Bonbon::Normal){
                return true;
            }
        }
        if(!sansBonbon(lign+1, col)){
            if(getBonbon(lign+1, col)->getType()!=Bonbon::Normal){
                return true;
            }
        }
    }
    return(possibleHL(lign, col) || possibleVL(lign, col) || possibleHR(lign, col) || possibleVR(lign, col));
}

//test sur rectangle 1x4 horizontal si 3 bonbon de la même couleur, un coup est possible
bool Niveau::possibleHL(int lign, int col) const{
    int rg,ja,ve,b,vi,rs = 0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    for(int i=0;i<4;i++){
        if(sansBonbon(lign, col+i)){
            return false;
        }
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
    if(rg==3 || ja==3 || ve==3 || b==3 || vi==3 || rs==3){
        return true;
    }
    return false;
}

//test sur rectangle 1x4 vertical si 3 bonbon de la même couleur, un coup est possible
bool Niveau::possibleVL(int lign, int col) const{
    int rg,ja,ve,b,vi,rs = 0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    for(int i=0;i<4;i++){
        if(sansBonbon(lign+i, col)){
            return false;
        }
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
    if(rg==3 || ja==3 || ve==3 || b==3 || vi==3 || rs==3){
        return true;
    }
    return false;
}

//test sur rectangle 2x3 horizontal si 3 ou 4 bonbons de la même couleur, il peut y avoir un coup possible
bool Niveau::possibleHR(int lign, int col) const{
    int rg,ja,ve,b,vi,rs = 0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    //test sur rectangle 2x3 horizontal si 3 ou 4 bonbons de la même couleur, il peut y avoir un coup possible
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            if(sansBonbon(lign+i, col+j)){
                return false;
            }
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
            if(getBonbon(lign, col+1)->getCouleur() != getBonbon(lign+1, col+1)->getCouleur()){
                return true;
            }else if((getBonbon(lign, col)->getCouleur() == tmpCouleur) !=
                     (getBonbon(lign+1, col)->getCouleur() == tmpCouleur)){
                return true;
            }
        }
        else if(rg==3){
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
        if(getBonbon(lign, col)->getCouleur() != getBonbon(lign+1, col)->getCouleur() &&
                getBonbon(lign, col+1)->getCouleur() != getBonbon(lign+1, col+1)->getCouleur() &&
                getBonbon(lign, col+2)->getCouleur() != getBonbon(lign+1, col+2)->getCouleur()){
            return true;
        }
    }
    return false;
}

//test sur rectangle 2x3 vertical si 3 ou 4 bonbons de la même couleur, il peut y avoir un coup possible
bool Niveau::possibleVR(int lign, int col) const{
    int rg,ja,ve,b,vi,rs = 0;
    Bonbon::Couleur tmpCouleur = Bonbon::Aucune;
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            if(sansBonbon(lign+i, col+j)){
                return false;
            }
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
            if(getBonbon(lign+1, col)->getCouleur() != getBonbon(lign+1, col+1)->getCouleur()){
                return true;
            }else if((getBonbon(lign, col)->getCouleur() == tmpCouleur) !=
                     (getBonbon(lign, col+1)->getCouleur() == tmpCouleur)){
                return true;
            }
        }
        else if(rg==3){
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
        if(getBonbon(lign, col)->getCouleur() != getBonbon(lign, col+1)->getCouleur() &&
                getBonbon(lign+1, col)->getCouleur() != getBonbon(lign+1, col+1)->getCouleur() &&
                getBonbon(lign+2, col)->getCouleur() != getBonbon(lign+2, col+1)->getCouleur()){
            return true;
        }
    }
    return false;
}

//Ajout/Suppresion Bonbon/Case //////////////////////////////////////////////////////////////////
void Niveau::ajouterBonbon(int ligne, int colonne,Bonbon::Couleur couleur, Bonbon::Type type){
    if(!estVide(ligne,colonne) && !estBloc(ligne,colonne) && sansBonbon(ligne,colonne)){
        QQmlComponent component(GlobalViewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueBonbon.qml"));
        Bonbon* bonbec = qobject_cast<Bonbon *>(component.create());
        bonbec->setType(type);
        bonbec->setCouleur(couleur);
        bonbec->setProperty("ligne",QVariant(ligne));
        bonbec->setProperty("colonne",QVariant(colonne));
        bonbec->setParent(GlobalGrille);
        bonbec->setParentItem(GlobalGrille);
        bonbec->setProperty("creationTermine",QVariant(true));
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
void Niveau::detruireCombo(int lign, int col){
    if (comboHorizontal(lign, col)){
        detruireHorizontal(lign,col);
    }
    if (comboVertical(lign, col)){
        detruireVertical(lign,col);
    }
    supprimerBonbon(lign,col);
}

void Niveau::detruireHorizontal(int lign, int col){
    Bonbon::Couleur c = getCouleur(lign,col) ;
    int j;
    //suppression des bonbons sur la gauche
    j=col-1;
    while (c==getCouleur(lign,j) && getCouleur(lign,j)!=Bonbon::Aucune){
        if (comboVertical(lign,j)){
            detruireVertical(lign,j);
        }
        supprimerBonbon(lign,j);
        j=j-1;
    }
    //suppression des bonbons sur la droite
    j=col+1;
    while (c==getCouleur(lign,j)&& getCouleur(lign,j)!=Bonbon::Aucune) {
        if (comboVertical(lign,j)){
            detruireVertical(lign,j);
        }
        supprimerBonbon(lign,j);
        j=j+1;
    }
}

void Niveau::detruireVertical(int lign, int col){
    Bonbon::Couleur c = getCouleur(lign,col) ;
    int i;
    //suppression des bonbons au dessus
    i=lign-1;
    while ( c==getCouleur(i,col)&& getCouleur(i,col)!=Bonbon::Aucune){
        if (comboHorizontal(i,col)){
            detruireHorizontal(i,col);
        }
        supprimerBonbon(i,col);
        i=i-1;
    }
    //suppression des bonbons en dessous
    i=lign+1;
    while ( c==getCouleur(i,col)&& getCouleur(i,col)!=Bonbon::Aucune){
        if (comboHorizontal(i,col)){
            detruireHorizontal(i,col);
        }
        supprimerBonbon(i,col);
        i=i+1;
    }
}

//Detruit tous les combos. Renvoye vrai s'il y a eu destruction, faux sinon.
bool Niveau::detruire(){
    bool destruction = false;
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(!estVide(i,j) && !estBloc(i,j) && !sansBonbon(i,j) && combo(i,j)){
                detruireCombo(i,j);
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

//Indique s'il y a encore des cases vide où les bonbons devraient tomber
//USELESS
bool Niveau::caseEncoreVidePossible(){
    bool vide=false;
    for (int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(!estVide(i,j)){
                if(sansBonbon(i,j) && !estDebut(i,j)){
                    if(!sansBonbon(i-1,j) || (estBloc(i-1,j) && (!sansBonbon(i-1,j+1) || !sansBonbon(i-1,j-1) ))){
                        vide=true;
                    }
                }
            }
        }
    }
    return vide;
}

//USELESS
bool Niveau::caseDebutVide(){
    bool vide=false;
    for (int i = 0; i < caseDebut.size(); ++i) {
        if((liste.at(caseDebut.at(i))->getBonbon())==NULL){
            vide=true;
        }
    }
    return vide;
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

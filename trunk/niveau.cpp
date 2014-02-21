#include "niveau.h"

using namespace std;

Niveau::Niveau(){

}

Niveau::Niveau(int nbNiveau){
    ostringstream nomFichier;
    nomFichier << "./levels/" << nbNiveau << ".candy";

    // le constructeur de ifstream permet d'ouvrir un fichier en lecture
    ifstream fichier(nomFichier.str().c_str());

    if (fichier) // ce test échoue si le fichier n'est pas ouvert
    {
        string ligne; // variable contenant chaque ligne lue

        if (getline( fichier, ligne))
        {
            num_niveau=nbNiveau;
            score=0;
            if(ligne=="score_objectif:" && getline( fichier, ligne )){
                score_objectif=atoi(ligne.c_str());
                getline( fichier, ligne );

                if(ligne=="nb_col:" && getline( fichier, ligne )){
                    nb_col=atoi(ligne.c_str());
                    getline( fichier, ligne );

                    if(ligne=="nb_lign:" && getline( fichier, ligne )){
                        nb_lign=atoi(ligne.c_str());
                        getline( fichier, ligne );

                        if(ligne=="nb_mvt:" && getline( fichier, ligne )){
                            nb_mvt=atoi(ligne.c_str());
                            getline( fichier, ligne );
                            
                            if(ligne=="case_vide:"){
                                QList<int> caseVide;
                                while(getline( fichier, ligne ) && ligne!="case_bloc:"){
                                    caseVide.push_back(atoi(ligne.c_str()));
                                }

                                if(ligne=="case_bloc:"){
                                    QList<int> caseBloc;
                                    while(getline( fichier, ligne ) && ligne!="case_debut:"){
                                        caseBloc.push_back(atoi(ligne.c_str()));
                                    }

                                    if(ligne=="case_debut:"){
                                        QList<int> caseDebut;
                                        while(getline( fichier, ligne ) && ligne!="case_fin:"){
                                            caseDebut.push_back(atoi(ligne.c_str()));
                                        }

                                        if(ligne=="case_fin:"){
                                            QList<int> caseFin;
                                            while(getline( fichier, ligne ) && ligne!=""){
                                                caseFin.push_back(atoi(ligne.c_str()));
                                            }

                                            //Fermeture du fichier
                                            fichier.close();

                                            //Création de la grille
                                            for(int i=0;i<nb_lign;i++){
                                                for(int j=0;j<nb_col;j++){
                                                    liste.append(NULL);
                                                }
                                            }

                                            //Création des cases
                                            for(int i=0;i<nb_lign;i++){
                                                for(int j=0;j<nb_col;j++){
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
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
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

//Indique s'il y a un bonbon dans la case
bool Niveau::sansBonbon (int lign, int col) const{
    return (estVide(lign, col) || liste.at(index(lign,col))->getBonbon()==NULL);
}

// Retourne l'id de la case
int Niveau::index(int lign, int col) const{
    return (lign*nb_col) + col;
}

void Niveau::remplir(){
    for(int i=0;i<nb_lign;i++){
        for(int j=0;j<nb_col;j++){
            if(!estVide(i,j) && !estBloc(i,j) && sansBonbon(i,j)){
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
                ajouterBonbon(i,j,couleur);
            }
        }
    }
}

//Combo///////////////////////////////////////////////////////////////////////////////////////
//Pour vérifier s'il y a combo horizontal sur le bonbon.
bool Niveau::comboHorizontal (int lign, int col){
    int i=index(lign,col);
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
    int i=index(lign,col);
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
    if(!estVide(ligne,colonne) && !estBloc(ligne,colonne) && sansBonbon(ligne,colonne)){
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

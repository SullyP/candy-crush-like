#include "controleur.h"

Controleur::Controleur(QObject *parent) :
    QObject(parent)
{
    QList<Case*> liste;
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
    QList<Case*> liste;
    QQmlComponent component1(GlobalViewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueCase.qml"));
    QQmlComponent component2(GlobalViewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/VueBonbon.qml"));
   // QQuickItem* grille = GlobalViewer->rootObject()->findChild<QQuickItem *>("grilleDeJeux");
   // if(grille!=NULL){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                Case *curCell = qobject_cast<Case *>(component1.create());
                curCell->setProperty("ligne",QVariant(i));
                curCell->setProperty("colonne",QVariant(j));
                curCell->setParent(GlobalGrille);
                curCell->setParentItem(GlobalGrille);

                Bonbon* bonbec = qobject_cast<Bonbon *>(component2.create());
                bonbec->setType(Bonbon::Sucre);
                bonbec->setCouleur(Bonbon::Bleu);
                bonbec->setProperty("ligne",QVariant(i));
                bonbec->setProperty("colonne",QVariant(j));
                bonbec->setParent(GlobalGrille);
                bonbec->setParentItem(GlobalGrille);

                curCell->setBonbon(bonbec);
                liste.push_back(curCell);
            }
        }
    //}
    niveau=Niveau(1,10000,liste,9,9,30);
}

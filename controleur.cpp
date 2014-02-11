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
        tailleBonbon=taille/(niveau.getNb_col());
        emit tailleBonbonChanged();
}

void Controleur::newNiveau(){
    QList<Case*> liste;
    QQmlComponent component1(viewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/Caase.qml"));
    QQmlComponent component2(viewer->engine(),QUrl::fromLocalFile("qml/SweetCandy/Boonbon.qml"));
    QQuickItem* grille = viewer->findChild<QQuickItem*>("grilleJeux");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            Case *curCell = qobject_cast<Case *>(component1.create());
            curCell->setProperty("ligne",QVariant(i));
            curCell->setProperty("colonne",QVariant(j));
            curCell->setParent(viewer->rootObject());
            curCell->setParentItem(qobject_cast<QQuickItem *>(viewer->rootObject()));

            Bonbon* bonbec = qobject_cast<Bonbon *>(component2.create());
            bonbec->setType(Bonbon::Sucre);
            bonbec->setCouleur(Bonbon::Bleu);
            bonbec->setProperty("ligne",QVariant(i));
            bonbec->setProperty("colonne",QVariant(j));
            bonbec->setParent(viewer->rootObject());
            bonbec->setParentItem(qobject_cast<QQuickItem *>(viewer->rootObject()));

            curCell->setBonbon(bonbec);
            liste.push_back(curCell);
        }
    }
    niveau=Niveau(1,10000,liste,9,9,30);
}

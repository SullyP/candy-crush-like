#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include "case.h"
#include "bonbon.h"
#include "niveau.h"
#include "controleur.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //Ajout de nouveau type QML "CaseB" et "Bonbon" à partir de Case et Bonbon
    qmlRegisterType<Case>("sweetcandy.case", 1, 0, "CaseB");
    qmlRegisterType<Bonbon>("sweetcandy.bonbon", 1, 0, "Bonbon");
    //Instanciation du controleur
    Controleur controleur;

    QtQuick2ApplicationViewer viewer;
    //Définition de controleur comme une propriété réutilisable à partir de n'importe où en QML
    viewer.rootContext()->setContextProperty("controleur", &controleur);
    viewer.setMainQmlFile(QStringLiteral("qml/SweetCandy/main.qml"));
    viewer.showExpanded();
    //Taille Minimale de la fenêtre
    viewer.setMinimumSize(QSize(600,400));

    //Initialisation du viewer dans Niveau
    //Utile pour la création des bonbons et cases
    Niveau::setViewer(&viewer);

    return app.exec();
}

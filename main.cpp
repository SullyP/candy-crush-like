#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include "case.h"
#include "bonbon.h"
#include "niveau.h"
#include "controleur.h"
#include "vue.h"
#include "global.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Case>("sweetcandy.case", 1, 0, "CaseB");
    qmlRegisterType<Bonbon>("sweetcandy.bonbon", 1, 0, "Bonbon");
    Controleur controleur;

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("controleur", &controleur);
    viewer.setMainQmlFile(QStringLiteral("qml/SweetCandy/main.qml"));
    viewer.showExpanded();
    viewer.setMinimumSize(QSize(600,400));


    GlobalViewer=&viewer;
    GlobalGrille = GlobalViewer->rootObject()->findChild<QQuickItem *>("grilleDeJeux");
    controleur.chargerNiveau(1);

    return app.exec();
}

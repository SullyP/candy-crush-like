#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"
#include "case.h"
#include "bonbon.h"
#include "niveau.h"
#include "controleur.h"
#include "vue.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Controleur controleur;

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/SweetCandy/main.qml"));
    viewer.rootContext()->setContextProperty("controleur", &controleur);
    viewer.showExpanded();
    viewer.setMinimumSize(QSize(600,400));

    return app.exec();
}

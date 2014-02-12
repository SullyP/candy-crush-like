import QtQuick 2.0
import sweetcandy.case 1.0


CaseB{
    property int colonne : 0
    property int ligne : 0
    Rectangle{
        x:colonne*controleur.tailleBonbon
        y:ligne*controleur.tailleBonbon
        width: controleur.tailleBonbon
        height: controleur.tailleBonbon
        color: "grey"
        radius: controleur.tailleBonbon/6
    }
}

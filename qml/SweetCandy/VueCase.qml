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
        color:franchissable ? "#A3A3A3":"#616161"
        radius: controleur.tailleBonbon/6

        Item{
            //Indicateur de debut
            anchors.top: parent.top
            width: parent.width
            height: controleur.tailleBonbon/20

            Rectangle{
                visible: debut
                anchors.fill: parent
                anchors.rightMargin: controleur.tailleBonbon/6
                anchors.leftMargin: controleur.tailleBonbon/6
                color:"blue"
            }

        }

        Item{
            //Indicateur de fin
            anchors.bottom: parent.bottom
            width: parent.width
            height: controleur.tailleBonbon/20

            Rectangle{
                visible: fin
                anchors.fill: parent
                anchors.rightMargin: controleur.tailleBonbon/6
                anchors.leftMargin: controleur.tailleBonbon/6
                color:"black"
            }
        }

        Rectangle{
            //Gelatine
            opacity:niveauGelatine*0.5
            anchors.fill: parent
            anchors.margins: controleur.tailleBonbon/20
            radius: controleur.tailleBonbon/6
            color:"white"

            Behavior on opacity{
                PropertyAnimation {duration: 200}
            }
        }
    }
}

import QtQuick 2.0
import sweetcandy.bonbon 1.0

Bonbon{
    property int colonne: 0
    property int ligne: -1 // permet d'avoir un effet "tombé du ciel" lors de l'animation
    property string etat: "enCreation"

    x: colonne*controleur.tailleBonbon
    y: ligne*controleur.tailleBonbon
    width: controleur.tailleBonbon
    height: controleur.tailleBonbon

    Behavior on x {
        enabled: etat!="enCreation" && controleur.animationX
        PropertyAnimation { duration: 400; easing.type: Easing.OutBack }
    }

    Behavior on y {
        enabled: controleur.animationY
        PropertyAnimation { duration: 400; easing.type: Easing.OutBack}
    }


    Image{
        id:img
        source:{
            var couleurString;
            var typeString;

            switch(couleur){
            case Bonbon.Rouge:
                couleurString = "rouge";
                break;

            case Bonbon.Jaune:
                couleurString = "jaune";
                break;

            case Bonbon.Vert:
                couleurString = "vert";
                break;

            case Bonbon.Bleu:
                couleurString = "bleu";
                break;

            case Bonbon.Violet:
                couleurString = "violet";
                break;

            case Bonbon.Rose:
                couleurString = "rose";
                break;

            case Bonbon.Aucune:
                couleurString = "";
                break;
            }

            switch(type){
            case Bonbon.Normal:
                typeString = "";
                break;

            case Bonbon.Bombe:
                typeString = "bombe";
                break;

            case Bonbon.RayureH:
                typeString = "RayureH";
                break;

            case Bonbon.RayureV:
                typeString = "RayureV";
                break;

            case Bonbon.Sucre:
                typeString = "Sucre";
                break;
            }

            if(typeString === "bombe")
                return "qrc:/images/bombe";
            else
                return "qrc:/images/" + couleurString + typeString;
        }

        anchors.fill: parent
        anchors.margins: 2
        sourceSize.height: controleur.resolutionBonbon
    }

    Item{
        height: 1.25*controleur.tailleBonbon
        width: 1.25*controleur.tailleBonbon

        Image{
            id: imgExplosion
            opacity: 0
            source: "qrc:/images/explosion"+imgEnCours
            anchors.fill: parent
            anchors.centerIn: parent

            property int imgEnCours: 1

            ParallelAnimation{
                running:etat=="destruction"
                PropertyAction { target: imgExplosion; property: "opacity"; value:1 }
                NumberAnimation { target: img; property: "opacity"; to: 0; duration: 400 }
                NumberAnimation { target: imgExplosion; property: "imgEnCours"; to: 5; duration: 400 }
            }
        }
    }
}

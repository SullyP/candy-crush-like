import QtQuick 2.0
import sweetcandy.bonbon 1.0

Bonbon{
    property int colonne: 0
    property int ligne: -1 // permet d'avoir un effet "tombé du ciel" lors de l'animation
    property bool creationTermine: false

    x: colonne*controleur.tailleBonbon
    y: ligne*controleur.tailleBonbon
    width: controleur.tailleBonbon
    height: controleur.tailleBonbon

    Behavior on x {
        enabled: creationTermine && controleur.animation
        PropertyAnimation { duration: 400; easing.type: Easing.OutBack }
    }

    Behavior on y {
        PropertyAnimation { duration: 400; easing.type: Easing.OutBack}
    }

    Image{
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
                return "qrc:/images/bombe"
            else
                return "qrc:/images/" + couleurString + typeString
        }

        anchors.fill: parent
        anchors.margins: 2
        sourceSize.height: controleur.resolutionBonbon
    }
}

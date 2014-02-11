import QtQuick 2.0
import sweetcandy.bonbon 1.0

Bonbon{
    property int colonne: 0
    property int ligne: 0

    x: colonne*controleur.tailleBonbon
    y: ligne*controleur.tailleBonbon
    width: controleur.tailleBonbon
    height: controleur.tailleBonbon

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


            return "qrc:/images/" + couleurString + typeString
        }

        anchors.fill: parent
        sourceSize.height: this.height
        sourceSize.width: this.width
    }
}

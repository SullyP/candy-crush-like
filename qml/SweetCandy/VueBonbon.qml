import QtQuick 2.0
import sweetcandy.bonbon 1.0

Bonbon{
    property int colonne: 0
    property int ligne: 0

    /* Permet d'avoir une image nette à partir de l'image vectorielle,
    sans utiliser trop de ressources (couplé à 'onWidthChanged' et 'SourceSize', cf. plus bas) */
    property int niveauResolution: 0
    property int resolution: 37+niveauResolution

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

            if(typeString=="bombe")
                return "qrc:/images/bombe"
            else
                return "qrc:/images/" + couleurString + typeString
        }

        anchors.fill: parent
        sourceSize.height: resolution
        sourceSize.width: resolution

        onWidthChanged: {
            if(controleur.tailleBonbon!=resolution){
                var nivResol = Math.round((controleur.tailleBonbon/10)-(37/10))*10;
                if(nivResol!=niveauResolution){
                    niveauResolution=nivResol;
                }
            }
        }
    }
}

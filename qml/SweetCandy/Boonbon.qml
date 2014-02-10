import QtQuick 2.0
import sweetcandy.bonbon 1.0

Bonbon{
    property int colonne: 0
    property int ligne: 0
    property string type: String(Bonbon.type)
    property string couleur: String(Bonbon.couleur)

    x: colonne*controleur.tailleBonbon
    y: ligne*controleur.tailleBonbon
    width: controleur.tailleBonbon
    height: controleur.tailleBonbon
    Text{
        id:truc
        text:type+" "+couleur
        font.family: "Helvetica"
        font.pointSize: 7
        color: "red"
    }

    /*Image{
        source:{
            if(type == "Bombe" || couleur == "Aucune"){
                if(type=="Bombe" && couleur=="Aucune"){
                    return "qrc:/images/bombe"
                }
            }else if(type=="Normal"){
                return "qrc:/images/" + couleur.toLowerCase()
            }else{
                return "qrc:/images/" + couleur.toLowerCase() + type
            }

        }
        anchors.fill: parent
        sourceSize.height: this.height
        sourceSize.width: this.width
    }*/
}

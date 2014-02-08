import QtQuick 2.0
import sweetcandy.bonbon 1.0

Bonbon{
    id: bonbon
    property int colonne : 0
    property int ligne : 0
    property string type: Bonbon.type
    property string couleur: Bonbon.couleur

    x: colonne*controleur.tailleBonbon
    y: ligne*controleur.tailleBonbon
    width: controleur.tailleBonbon
    height: controleur.tailleBonbon
    Image{
        source:{
            if(bonbon.type=="Bombe" || bonbon.couleur=="Aucune"){
                if(bonbon.type==Bombe && bonbon.couleur==Aucune){
                    return "qrc:/images/bombe"
                }
            }else if(bonbon.type=="Normal"){
                return "qrc:/images/" + bonbon.couleur
            }else{
                return "qrc:/images/" + bonbon.couleur + bonbon.type
            }

        }
        anchors.fill: parent
        sourceSize.height: this.height
        sourceSize.width: this.width
    }
}

import QtQuick 2.0

Rectangle {
    id: ecran
    width: 600
    height: 400
    state: "mainMenu"
    property int margePixel: 30

    Image {
        id: background
        source:"qrc:/images/fondEcran"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        sourceSize.height: this.height

    }

    Rectangle {
        id: ecranGauche
        width: 200
        height: ecran.height
        color: "yellow"
        anchors.top: ecran.top
        anchors.left: ecran.left

    }


    Item {
        id: grilleJeux
        x: ((ecran.width-this.width-ecranGauche.width)/2)+ecranGauche.width //permet de centrer la grille de jeux
        y: (ecran.height-this.height)/2 //permet de centrer la grille de jeux
        width: Math.min(ecran.height,ecran.width-ecranGauche.width)-2*margePixel
        height: Math.min(ecran.height,ecran.width-ecranGauche.width)-2*margePixel

        onWidthChanged:{
            controleur.tailleBonbon=width;
        }

        Text{
            anchors.centerIn: parent
            text:controleur.tailleBonbon
        }

        /*MouseArea {
            anchors.fill: parent;
            onClicked: Game.handleClick(mouse.x,mouse.y);
        }*/



    }

}


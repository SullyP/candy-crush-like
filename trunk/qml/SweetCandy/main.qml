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
        sourceSize.height: 800
    }

    Item{
        id:jeux
        anchors.fill: parent
        anchors.margins: margePixel

        Item{
            anchors.centerIn: parent
            height: parent.height
            width: Math.min(parent.height+200,parent.width)

            Rectangle {
                id: infoJeux
                width: 200
                color: "yellow"
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
            }

            Item {
                id: grilleJeux
                objectName: "grilleDeJeux"
                height:this.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.left: infoJeux.right

                onWidthChanged:{
                    controleur.tailleBonbon=width/controleur.nbColonne;
                }

                /*MouseArea {
                    anchors.fill: parent;
                    onClicked: Game.handleClick(mouse.x,mouse.y);
                }*/
            }
        }
    }
}

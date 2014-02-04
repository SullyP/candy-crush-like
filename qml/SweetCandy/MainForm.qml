import QtQuick 2.0

Rectangle {
    id: ecran
    width: 600
    height: 400
    state: "mainMenu"
    property int margePixel: 30

    Rectangle {
        id: ecranGauche
        width: 200
        height: ecran.height
        color: "yellow"
        anchors.top: ecran.top
        anchors.left: ecran.left

    }
    Rectangle {
        id: ecranDroit
        width: ecran.width-ecranGauche.width
        height: ecran.height
        color: "black"
        anchors.top: ecran.top
        anchors.left: ecranGauche.right

        Rectangle {
            id: grilleJeux
            x: margePixel
            y: margePixel
            width: Math.min(parent.height,parent.width)-2*margePixel
            height: Math.min(parent.height,parent.width)-2*margePixel
            color: "red"
            property int nbColonne: 9

            MouseArea{
                anchors.fill: parent



                onClicked: {

                        grilleJeux.color="purple"

                        grilleJeux.color="yellow"
                }
            }
        }


    }

}

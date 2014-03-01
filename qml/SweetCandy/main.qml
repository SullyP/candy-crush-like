import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {
    id: ecran
    width: 600
    height: 400
    state: "mainMenu"
    property int margePixel: 30
    property int tailleInfoJeux: 200

    Image {
        id: background
        source:"qrc:/images/fondEcran"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        sourceSize.height: 800
    }

    Item{
        visible: ecran.state=="mainMenu"
        id:mainMenu
        anchors.fill: parent
        anchors.margins: margePixel

        Item{
            id: titre
            width:parent.width
            height: 30

            Text{
                text:"SweetCandy"
                font.pointSize: 25
                color: "black"
                anchors.centerIn: parent
            }
        }

        ScrollView{
            id:scroll
            width: parent.width-2*margePixel
            height: parent.height-4*margePixel
            anchors.centerIn: parent
            Grid{
                columns: scroll.width/66
                spacing: 5
                Repeater{
                    model: controleur.nbTotalNiveau
                    Rectangle {
                        width: 60
                        height: 60
                        radius: 10
                        color: "#616161"

                        Text{
                            text:String(index+1)
                            font.pointSize: 25
                            color: "white"
                            anchors.centerIn: parent
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                controleur.chargerNiveau(index+1);
                                ecran.state="jeux";
                            }
                        }
                    }
                }
            }
        }
    }

    Image{
        visible: ecran.state=="jeux"
        source: "qrc:/images/home"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        MouseArea{
            anchors.fill: parent
            onClicked: {
                ecran.state="mainMenu";
            }
        }
    }

    Item{
        visible: ecran.state=="jeux"
        id:jeux
        anchors.fill: parent
        anchors.margins: margePixel

        Item{
            anchors.centerIn: parent
            height: parent.height
            width: Math.min(parent.height+tailleInfoJeux,parent.width)

            Item {
                id: infoJeux
                width: tailleInfoJeux
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left

                Rectangle{
                    anchors.fill: parent
                    anchors.margins: 1
                    color: "#616161"
                    radius: controleur.tailleBonbon/6
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 2
                    anchors.topMargin: 2

                    Column {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 2

                        Rectangle{
                            width:parent.width
                            height: 20
                            color: "#A3A3A3"
                            radius: 5

                            Text{
                                text:"Niveau : "+String(controleur.numNiveau)
                                font.pointSize: 15
                                color: "black"
                                anchors.centerIn: parent
                            }
                        }

                        Rectangle{
                            width:parent.width
                            height: 20
                            color: "#A3A3A3"
                            radius: 5

                            Text{
                                text:"Mouvement(s) : "+String(controleur.nbMvt)
                                font.pointSize: 15
                                color: "black"
                                anchors.centerIn: parent
                            }
                        }

                        Rectangle{
                            width:parent.width
                            height: 20
                            color: "#A3A3A3"
                            radius: 5

                            Text{
                                text:"Objectif : "+String(controleur.scoreObjectif)
                                font.pointSize: 15
                                color: "black"
                                anchors.centerIn: parent
                            }
                        }

                        Rectangle{
                            width:parent.width
                            height: 20
                            color: "#A3A3A3"
                            radius: 5

                            Text{
                                text:"Score : "+String(controleur.score)
                                font.pointSize: 15
                                color: "black"
                                anchors.centerIn: parent
                            }
                        }
                        ProgressBar{
                            maximumValue: controleur.scoreObjectif
                            minimumValue: 0
                            orientation: 0
                            style: ProgressBarStyle {
                                background: Rectangle {
                                    radius: 2
                                    color: "lightgray"
                                    border.color: "gray"
                                    border.width: 1
                                    implicitWidth: 200
                                    implicitHeight: 24
                                }
                                progress: Rectangle {
                                    color: "lightsteelblue"
                                    border.color: "steelblue"
                                }
                            }

                            value: controleur.score
                        }
                    }
                }
            }

            Item {
                id: grilleJeux
                objectName: "grilleDeJeux"
                height:this.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.left: infoJeux.right

                Connections {
                    target: controleur
                    onActualiserTailleBonbon:{
                        controleur.tailleBonbon=grilleJeux.width/controleur.nbColonne;
                    }
                }

                MouseArea{
                    anchors.fill: parent;
                    onPressed: controleur.selectionBonbon1(mouse.x,mouse.y);
                    onReleased: controleur.selectionBonbon2(mouse.x,mouse.y);
                }

                onWidthChanged:{
                    controleur.tailleBonbon=width/controleur.nbColonne;
                }
            }
        }
    }
}


import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQuick.Dialogs 1.2
import MySimulator 1.0
import SimVis 1.0
import QMLPlot 1.0

Window {
    visible: true
    width: 1024
    height: 720

    MySimulator {
        id: simulator
    }

    Visualizer {
        id: visualizer
        anchors.fill: parent
        simulator: simulator
        camera: camera
        backgroundColor: "lightgray"

        Spheres {
            id: spheres
            color: "white"

            Light {
                id: spherelight
                ambientColor: "white"
                specularColor: "white"
                diffuseColor: "white"
                ambientIntensity: 0.4
                diffuseIntensity: 0.5
                specularIntensity: 0.4
                shininess: 10.0
                attenuation: 0.1
                position: camera.position
            }
        }

        TriangleCollection {
            id: triangles

            Light {
                id: trianglelight
                ambientColor: "white"
                specularColor: "white"
                diffuseColor: "white"
                ambientIntensity: 0.4
                diffuseIntensity: 0.5
                specularIntensity: 0.4
                shininess: 10.0
                attenuation: 0.1
                position: camera.position
            }

//            SkyBox {
//                id: skybox
//                camera: camera
//                texture: ":/1024.png"
//            }
//            SkyBoxReflection {
//                id: reflection
//                skybox: skybox
//                reflectivity: 0.5
//            }

//            SimplexBump {
//                id: simplexBump
//                enabled: true
//                intensity: 0.1
//                scale: 1.0
//            }

//            SimplexTexture {
//                id: simplexTexture
//                scale: 1.0
//                enabled: true
//                timeDependent: true
//            }
        }

        TrackballNavigator {
            id: navigator
            anchors.fill: parent
            camera: camera
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls)
            simulator.inputFileUrl = fileDialog.fileUrl
        }
        onRejected: {
            console.log("Canceled")
        }
        Component.onCompleted: visible = true
    }


    Slider {
        id: timeSlider
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        value: 19000
        minimumValue: 19000 //simulator.frameMin
        maximumValue: 22000 //simulator.frameMax
        stepSize: 100
        onValueChanged: {
            simulator.newStep = value
            simulator.nextStep = true
        }
        objectName: "slider"
        updateValueWhileDragging: true
    }



    Button {
        id: timestepButton
        anchors.left: parent.left
        text: timeSlider.value
    }

    Slider {
        id: xfacField
        anchors.top: timestepButton.bottom
        value: 0.3
        stepSize: 0.1
        onValueChanged: {
            simulator.xfac = value
            simulator.nextStep = true
        }
        updateValueWhileDragging: false

    }

    Slider {
        id: yfacField
        anchors.top: xfacField.bottom
        value: 0.3
        stepSize: 0.1
        onValueChanged: {
            simulator.yfac = value
            simulator.nextStep = true
        }
        updateValueWhileDragging: false

    }

    Slider {
        id: zfacField
        anchors.top: yfacField.bottom
        value: 0.3
        stepSize: 0.1
        onValueChanged: {
            simulator.zfac = value
            simulator.nextStep = true
        }
        updateValueWhileDragging: false
    }

    Button {
        id: preloadButton
        anchors.top: zfacField.bottom
        text: "Preload"
        onClicked: {
            simulator.frameStep = timeSlider.stepSize
            simulator.frameMin = timeSlider.minimumValue
            simulator.frameMax = timeSlider.maximumValue
            simulator.frameStep = timeSlider.stepSize
            simulator.isPreload = true
            timeSlider.updateValueWhileDragging = true
        }
    }

    CheckBox {
        id: spheresCheckbox
        anchors.top: preloadButton.bottom
        checked: true
        onCheckedChanged: {
            simulator.isPlotSpheres = checked
            simulator.nextStep = true
        }
        text: "Spheres"
    }

    CheckBox {
        id: trianglesCheckbox
        anchors.top:spheresCheckbox.bottom
        checked: true
        onCheckedChanged: {
            simulator.isPlotTriangles = checked
            simulator.nextStep = true
        }
        text: "Triangles"
    }

    Camera {
        id: camera
        farPlane: 1000000
        nearPlane: 0.1
    }

    Figure {
        id: figure
        width: 300
        height: 300
        //color: "red"
        xMin: timeSlider.minimumValue
        xMax: timeSlider.maximumValue
        yMin: simulator.areaMin
        yMax: simulator.areaMax
        xLabel: "timestep "
        yLabel: "area"
        title: "Surface area"
        LineGraph {
            id: graph
            dataSource: simulator.lineGraphDataSource
            width: 1
            style: Qt.DotLine
        }
        MouseArea {
            anchors.fill: parent
            drag.target: parent
        }
    }
}


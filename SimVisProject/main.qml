import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import MySimulator 1.0
//import MyWorker 1.0
import SimVis 1.0

Window {
    visible: true
    width: 1024
    height: 720

    MySimulator {
        id: simulator
    }

//    MyWorker {
//        id: worker
//
//    }



    Visualizer {
        id: visualizer
        anchors.fill: parent
        simulator: simulator
        camera: camera
        backgroundColor: "gray"



//        SkyBox {
//            id: skybox
//            camera: camera
//            texture: ":/cubemap.jpg"
//        }

        TriangleCollection {
            id: triangles

            Light {
                id: light
                ambientColor: "blue"
                specularColor: "white"
                diffuseColor: "green"
                ambientIntensity: 0.4
                diffuseIntensity: 0.5
                specularIntensity: 0.4
                shininess: 10.0
                attenuation: 0.1
                position: camera.position
            }

//            SkyBoxReflection {
//                id: reflection
//                skybox: skybox
//                reflectivity: 0.2
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

    Slider {
        id: slider
        anchors.left: timestepButton.right
        anchors.right: parent.right
        value: 0
        minimumValue: simulator.frameMin
        maximumValue: simulator.frameMax
        stepSize: 100
        onValueChanged: {
            simulator.newStep = value
            simulator.nextStep = true
        }
    }

    Button {
        id: timestepButton
        anchors.left: parent.left
        text: slider.value
    }

    Camera {
        id: camera
        farPlane: 1000000
        nearPlane: 0.1
    }
}


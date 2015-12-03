import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import MySimulator 1.0
import SimVis 1.0

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
        backgroundColor: "gray"





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

    Slider {
        id: timeSlider
        anchors.left: timestepButton.right
        anchors.right: parent.right
        value: 19000
        minimumValue: 20000 //simulator.frameMin
        maximumValue: 21000 //simulator.frameMax
        stepSize: 200
        onValueChanged: {
            simulator.newStep = value
            simulator.nextStep = true
        }
        objectName: "slider"
        updateValueWhileDragging: false
    }

    Button {
        id: timestepButton
        anchors.left: parent.left
        text: timeSlider.value
    }

    TextField {
        id: rSqThresholdField
        placeholderText: "rsq_threshold"
        anchors.top: timestepButton.bottom
        onEditingFinished: {
            simulator.rSqThreshold = text
            simulator.nextStep = true
        }
    }

    Slider {
        id: skewFactorField
        //placeholderText: "skewfactor"
        anchors.top: rSqThresholdField.bottom
        minimumValue: 0.0
        maximumValue: 1.0
        value: 0.2
        onValueChanged: {
            simulator.skewFactor = value
            simulator.nextStep = true
        }
        updateValueWhileDragging: true
    }
    Button {
        id: skewFactorButton
        anchors.left: skewFactorField.right
        anchors.top: timeSlider.bottom
        text: skewFactorField.value
    }

    Slider {
        id: xfacField
        anchors.top: skewFactorField.bottom
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
    }

    CheckBox {
        id: trianglesCheckbox
        anchors.top:spheresCheckbox.bottom
        checked: true
        onCheckedChanged: {
            simulator.isPlotTriangles = checked
            simulator.nextStep = true
        }
    }

    Camera {
        id: camera
        farPlane: 1000000
        nearPlane: 0.1
    }
}


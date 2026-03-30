import QtQuick
import Qt_ParticleSystem

Window {
    id: root
    minimumWidth: AppParameter.windowWidth
    maximumWidth: AppParameter.windowWidth
    minimumHeight: AppParameter.windowHeight
    maximumHeight: AppParameter.windowHeight
    property int particleCount: 0;
    visible: true
    title: qsTr("Particle System")

    Rectangle {
        id: screen
        anchors.fill: parent
        color: "black"

        Text {
            id: particleText
            text: "Particles: " + root.particleCount
            anchors.top: parent.top
            anchors.left: parent.left
            color: "white"
        }

        ParticleRenderer {
            id: renderer
            objectName: "renderer"
            anchors.fill: parent
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                if (root.particleCount <= 420) {
                    cppInterface.screenClicked(mouseX, mouseY)
                    root.particleCount += 30
                    AppParameter.particleRadius -= 1
                }
            }
        }
    }

    CppInterface {
        id: cppInterface
        objectName: "cppInterface"
    }
}

import QtQuick
import Qt_ParticleSystem

Window {
    id: root
    minimumWidth: Constants.windowWidth
    maximumWidth: Constants.windowWidth
    minimumHeight: Constants.windowHeight
    maximumHeight: Constants.windowHeight
    visible: true
    title: qsTr("Particle System")

    Rectangle {
        id: screen
        anchors.fill: parent
        color: "black"

        ParticleRenderer {
            id: renderer
            objectName: "renderer"
            anchors.fill: parent
        }
    }
}

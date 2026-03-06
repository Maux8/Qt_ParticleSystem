import QtQuick
import Qt_ParticleSystem

Window {
    id: root
    width: 640
    height: 480
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

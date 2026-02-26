import QtQuick
import Qt_ParticleSystem

Window {
    width: 640
    height: 480
    visible: true
    color: "black"
    title: qsTr("Particle System")

    MouseArea {
        id: wholeScreen
        anchors.fill: parent
        onClicked: { CppInterface.test(); }
    }
}

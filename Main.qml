import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    color: "black"
    title: qsTr("Particle System")

    Particle {
        centered_x: parent.width / 2
        centered_y: parent.height / 2
    }
}

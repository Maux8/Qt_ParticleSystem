import QtQuick
import Qt_ParticleSystem

Window {
    id: root
    width: 640
    height: 480
    visible: true
    color: "black"
    title: qsTr("Particle System")

    MouseArea {
        id: wholeScreen
        anchors.fill: parent
        onClicked: { spawnParticle(mouseX, mouseY); }
    }

    Particle {
        centered_x: root.width / 2
        centered_y: root.height / 2
    }

    function spawnParticle(mouseX, mouseY) {
        var particleComp = Qt.createComponent("Particle.qml");
        var particleSprite = particleComp.createObject(this, {centered_x: mouseX, centered_y: mouseY});
    }
}

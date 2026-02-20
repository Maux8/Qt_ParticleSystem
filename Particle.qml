import QtQuick

Item {
    id: container
    property alias particle_color: body.color
    property double centered_x: 0
    property double centered_y: 0

    width: Constants.particle_radius
    height: Constants.particle_radius
    antialiasing: true
    x: container.centered_x - (width / 2)
    y: container.centered_y + (height / 2)

    Rectangle {
        id: body
        anchors.fill: parent
        color: "white"
        radius: width / 2
    }
}

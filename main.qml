import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Particles 2.0
Item {
    id: root

    width: 640
    height: 480
    visible: true







    Button {
        text: "Button"
        style: ButtonStyle {
            background: BorderImage {
                source: control.pressed ? "images/button-pressed.png" : "images/button.png"
                border.left: 4 ; border.right: 4 ; border.top: 4 ; border.bottom: 4
            }
        }
        implicitWidth: window.width / columnFactor
    }


}


import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    model: calculatorModel
    delegate: RowLayout {
        width: parent.width
        Label {
            text: expression
            Layout.fillWidth: true
        }
        Label {
            text: "= " + result
            font.bold: true
        }
    }
    clip: true
}

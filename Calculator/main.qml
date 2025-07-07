import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    visible: true
    width: 400
    height: 600
    title: "Calculator"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        CalculatorDisplay {
            Layout.fillWidth: true
        }

        CalculatorButtons {
            Layout.fillWidth: true
        }

        HistoryView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}

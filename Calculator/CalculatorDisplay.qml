import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ColumnLayout {
    TextField {
        Layout.fillWidth: true
        text: viewModel.currentInput
        readOnly: true
        font.pixelSize: 24
        horizontalAlignment: Text.AlignRight
    }

    Label {
        Layout.fillWidth: true
        text: "Result: " + (viewModel.result !== 0 ? viewModel.result : "")
        font.pixelSize: 18
        horizontalAlignment: Text.AlignRight
    }
}

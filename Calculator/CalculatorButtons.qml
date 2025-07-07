import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

GridLayout {
    columns: 4
    rowSpacing: 5
    columnSpacing: 5

    Button { text: "7"; Layout.fillWidth: true; onClicked: viewModel.addDigit("7") }
    Button { text: "8"; Layout.fillWidth: true; onClicked: viewModel.addDigit("8") }
    Button { text: "9"; Layout.fillWidth: true; onClicked: viewModel.addDigit("9") }
    Button { text: "/"; Layout.fillWidth: true; onClicked: viewModel.setOperation("/") }
    Button { text: "4"; Layout.fillWidth: true; onClicked: viewModel.addDigit("4") }
    Button { text: "5"; Layout.fillWidth: true; onClicked: viewModel.addDigit("5") }
    Button { text: "6"; Layout.fillWidth: true; onClicked: viewModel.addDigit("6") }
    Button { text: "*"; Layout.fillWidth: true; onClicked: viewModel.setOperation("*") }
    Button { text: "1"; Layout.fillWidth: true; onClicked: viewModel.addDigit("1") }
    Button { text: "2"; Layout.fillWidth: true; onClicked: viewModel.addDigit("2") }
    Button { text: "3"; Layout.fillWidth: true; onClicked: viewModel.addDigit("3") }
    Button { text: "-"; Layout.fillWidth: true; onClicked: viewModel.setOperation("-") }
    Button { text: "0"; Layout.fillWidth: true; onClicked: viewModel.addDigit("0") }
    Button { text: "."; Layout.fillWidth: true; onClicked: viewModel.addDigit(".") }
    Button { text: "="; Layout.fillWidth: true; onClicked: viewModel.calculate() }
    Button { text: "+"; Layout.fillWidth: true; onClicked: viewModel.setOperation("+") }
    Button { text: "C"; Layout.fillWidth: true; onClicked: viewModel.clear() }
}

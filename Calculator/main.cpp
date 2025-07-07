
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calculatormodel.h"
#include "calculatorviewmodel.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    CalculatorModel model;
    CalculatorViewModel viewModel(&model);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("calculatorModel", &model);
    engine.rootContext()->setContextProperty("viewModel", &viewModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}

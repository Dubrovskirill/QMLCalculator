#ifndef CALCULATORVIEWMODEL_H
#define CALCULATORVIEWMODEL_H

#include <QObject>
#include "calculatormodel.h"

class CalculatorViewModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentInput READ currentInput NOTIFY currentInputChanged)
    Q_PROPERTY(double result READ result NOTIFY resultChanged)
public:
    explicit CalculatorViewModel(CalculatorModel* model, QObject* parent = nullptr);

    QString currentInput() const { return m_currentInput; }
    double result() const { return m_result; }

    Q_INVOKABLE void addDigit(const QString& digit);
    Q_INVOKABLE void setOperation(const QString& op);
    Q_INVOKABLE void calculate();
    Q_INVOKABLE void clear();

signals:
    void currentInputChanged();
    void resultChanged();

private:
    CalculatorModel* m_model;
    QString m_currentInput;
    double m_result = 0.0;
    double m_firstOperand = 0.0;
    QString m_operation;
};

#endif // CALCULATORVIEWMODEL_H

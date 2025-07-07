#include "calculatorviewmodel.h"
#include <QObject>
#include "calculatormodel.h"
#include <stdexcept>

CalculatorViewModel::CalculatorViewModel(CalculatorModel* model, QObject* parent)
    : QObject(parent), m_model(model) {}

void CalculatorViewModel::addDigit(const QString& digit) {
    m_currentInput += digit;
    emit currentInputChanged();
}

void CalculatorViewModel::setOperation(const QString& op) {
    if (!m_currentInput.isEmpty()) {
        m_firstOperand = m_currentInput.toDouble();
        m_currentInput.clear();
        m_operation = op;
        emit currentInputChanged();
    }
}

void CalculatorViewModel::calculate() {
    if (!m_currentInput.isEmpty() && !m_operation.isEmpty()) {
        double secondOperand = m_currentInput.toDouble();
        try {
            m_result = m_model->performOperation(m_firstOperand, secondOperand, m_operation);
            QString expression = QString("%1 %2 %3").arg(m_firstOperand).arg(m_operation).arg(secondOperand);
            m_model->addToHistory(expression, m_result);
            m_currentInput = QString::number(m_result);
            emit currentInputChanged();
            emit resultChanged();
        } catch (const std::runtime_error& e) {
            m_currentInput = "Error: " + QString(e.what());
            emit currentInputChanged();
        }
    }
}

void CalculatorViewModel::clear() {
    m_currentInput.clear();
    m_result = 0.0;
    m_firstOperand = 0.0;
    m_operation.clear();
    emit currentInputChanged();
    emit resultChanged();
}

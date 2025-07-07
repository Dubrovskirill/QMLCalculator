#include "calculatorviewmodel.h"
#include <QObject>
#include <QRegularExpression>
#include "calculatorviewmodel.h"
#include <stdexcept>
#include <QStack>
#include <QStringList>

CalculatorViewModel::CalculatorViewModel(CalculatorModel* model, QObject* parent)
    : QObject(parent), m_model(model) {}

void CalculatorViewModel::addDigit(const QString& digit) {
    if (m_currentInput.startsWith("Error:")) {
        m_currentInput.clear();
    }
    m_currentInput += digit;
    emit currentInputChanged();
}

void CalculatorViewModel::setOperation(const QString& op) {
    if (m_currentInput.startsWith("Error:")) {
        m_currentInput.clear();
    }
    if (!m_currentInput.isEmpty()) {
        m_currentInput += op;
        m_operation = op;
        emit currentInputChanged();
    }
}

QString toRPN(const QString& infix) {
    QString expression = infix;
    // Добавляем пробелы вокруг операций для корректного разбиения
    expression.replace(QRegularExpression("([+\\-*/])"), " \\1 ");
    QStack<QString> stack;
    QString output;
    QStringList tokens = expression.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QMap<QString, int> precedence = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};

    for (const QString& token : tokens) {
        if (token.isEmpty()) continue;
        if (precedence.contains(token)) {
            while (!stack.isEmpty() && precedence[stack.top()] >= precedence[token]) {
                output += stack.pop() + " ";
            }
            stack.push(token);
        } else {
            output += token + " ";
        }
    }
    while (!stack.isEmpty()) {
        output += stack.pop() + " ";
    }
    return output.trimmed();
}

void CalculatorViewModel::calculate() {
    if (m_currentInput.isEmpty()) {
        return;
    }

    QString rpn = toRPN(m_currentInput);

    QStack<double> stack;
    QStringList tokens = rpn.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    for (const QString& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                m_currentInput = "Error: Invalid expression";
                emit currentInputChanged();
                return;
            }
            double b = stack.pop();
            double a = stack.pop();
            try {
                stack.push(m_model->performOperation(a, b, token));
            } catch (const std::runtime_error& e) {
                m_currentInput = "Error: " + QString(e.what());
                emit currentInputChanged();
                return;
            }
        } else {
            bool ok;
            double value = token.toDouble(&ok);
            if (!ok) {
                m_currentInput = "Error: Invalid number";
                emit currentInputChanged();
                return;
            }
            stack.push(value);
        }
    }

    if (stack.size() != 1) {
        m_currentInput = "Error: Invalid expression";
        emit currentInputChanged();
        return;
    }

    m_result = stack.pop();
    m_model->addToHistory(m_currentInput, m_result);
    m_currentInput = QString::number(m_result);
    m_operation.clear();
    emit currentInputChanged();
    emit resultChanged();
}

void CalculatorViewModel::clear() {
    m_currentInput.clear();
    m_result = 0.0;
    m_firstOperand = 0.0;
    m_operation.clear();
    emit currentInputChanged();
    emit resultChanged();
}

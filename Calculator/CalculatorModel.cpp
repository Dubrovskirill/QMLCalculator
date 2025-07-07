#include "calculatormodel.h"
#include <stdexcept>
#include<QSharedPointer>



CalculatorModel::CalculatorModel(QObject* parent) : QAbstractListModel(parent) {
    // Инициализация операций (паттерн Strategy)
    m_operations.insert("+", std::make_shared<AddOperation>());
    m_operations.insert("-", std::make_shared<SubtractOperation>());
    m_operations.insert("*", std::make_shared<MultiplyOperation>());
    m_operations.insert("/", std::make_shared<DivideOperation>());
}

QHash<int, QByteArray> CalculatorModel::roleNames() const {
    return {{ExpressionRole, "expression"}, {ResultRole, "result"}};
}

int CalculatorModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : m_history.size();
}

QVariant CalculatorModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= m_history.size()) return {};
    const HistoryItem& item = m_history[index.row()];
    switch (role) {
    case ExpressionRole: return item.expression;
    case ResultRole: return item.result;
    default: return {};
    }
}

double CalculatorModel::performOperation(double a, double b, const QString& operation) {
    if (!m_operations.contains(operation)) throw std::runtime_error("Unknown operation");
    return m_operations[operation]->execute(a, b);
}

void CalculatorModel::addToHistory(const QString& expression, double result) {
    beginInsertRows({}, m_history.size(), m_history.size());
    m_history.append({expression, result});
    endInsertRows();
}

#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H
#include <QAbstractListModel>
#include <QMap>
#include <QHash>
#include <functional>
#include<QSharedPointer>

class IOperationStrategy{
public:
    virtual ~IOperationStrategy()=default;
    virtual double execute(double a, double b) const = 0;
};

class AddOperation:public IOperationStrategy {
    double execute(double a, double b) const override {return a+b;}
};

class SubtractOperation:public IOperationStrategy {
    double execute(double a, double b) const override {return a-b;}
};

class MultiplyOperation:public IOperationStrategy {
    double execute(double a, double b) const override {return a*b;}
};

class DivideOperation:public IOperationStrategy {
    double execute(double a, double b) const override {   if (b == 0) throw std::runtime_error("Division by zero"); return a / b;;}
};


class CalculatorModel : public QAbstractListModel
{
public:
   explicit CalculatorModel(QObject* parent = nullptr);
   enum Roles { ExpressionRole = Qt::UserRole + 1, ResultRole };
   QHash<int, QByteArray> roleNames() const override;
   int rowCount(const QModelIndex& parent = {}) const override;
   QVariant data(const QModelIndex& index, int role) const override;

   Q_INVOKABLE double performOperation(double a, double b, const QString& operation);
   Q_INVOKABLE void addToHistory(const QString& expression, double result);
private:
   struct HistoryItem {
       QString expression;
       double result;
   };

   QList<HistoryItem> m_history;
   QMap<QString, std::shared_ptr<IOperationStrategy>> m_operations;
};

#endif // CALCULATORMODEL_H

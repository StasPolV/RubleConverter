#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QVector>

struct Currency
{
	QString name;
	QString code;
	double rate;
};

class CurrencyModel : public QAbstractListModel
{
	Q_OBJECT

public slots:

public:
	enum Roles
	{
		NameRole = Qt::UserRole + 1,
		CodeRole
	};

	explicit CurrencyModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	void AddCurrency(const Currency& currency);
	void RemoveCurrency(int row);
	void SetCurrencies(QVector<Currency> currencies);

private:
	QVector<Currency> m_currencies;
};

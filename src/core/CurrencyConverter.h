#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

#include <CurrencyFetcher.h>

class CurrencyConverter : public QObject
{
	Q_OBJECT

public slots:
	void FillExchangeRate(const QVector<CurrencyRecord>& records = {});

public:
	explicit CurrencyConverter(QObject* parent = nullptr);

	double Convert(const QString& src_currency, const QString& dest_currency, double src_val);

private:
	QMap<QString, double> m_exchange_rate;
};

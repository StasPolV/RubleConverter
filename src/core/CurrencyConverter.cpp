#include "CurrencyConverter.h"

CurrencyConverter::CurrencyConverter(QObject* parent) : QObject(parent) {}

double CurrencyConverter::Convert(QString src_currency, QString dest_currency, double src_val)
{
	return m_exchange_rate[dest_currency] / m_exchange_rate[src_currency];
}

void CurrencyConverter::FillExchangeRate(QVector<CurrencyRecord> records)
{
	for (const CurrencyRecord& rec : records)
	{
		m_exchange_rate.insert(rec.quote, rec.rate);
	}
}

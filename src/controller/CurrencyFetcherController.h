#pragma once

#include <QObject>

class CurrencyFetcher;
class CurrencyModel;
class CurrencyConverter;

class CurrencyFetcherController : public QObject
{
public:
	explicit CurrencyFetcherController(CurrencyModel* model, CurrencyConverter* converter,
	                                   QObject* parent = nullptr);

private:
	CurrencyFetcher* m_fetcher;
	CurrencyModel* m_model;
};

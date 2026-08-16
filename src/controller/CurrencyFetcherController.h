#pragma once

#include <QObject>

class CurrencyFetcher;
class CurrencyModel;

class CurrencyFetcherController : public QObject
{
public:
	explicit CurrencyFetcherController(CurrencyModel* model, QObject* parent = nullptr);

private:
	CurrencyFetcher* m_fetcher;
	CurrencyModel* m_model;
};

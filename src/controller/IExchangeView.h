#pragma once

#include <QString>

class QObject;

class IExchangeView
{
public:
	virtual ~IExchangeView() = default;
	virtual QString CurrentCode() const = 0;
	virtual QString Amount() const = 0;
	virtual void SetAmount(const QString&) = 0;
	virtual QObject* AsQObject() = 0;
	virtual void SetCode(const QString&) = 0;
	virtual void SetLabel(const QString& src_currency, double src_val, const QString& dest_currency,
	                      double dest_val) = 0;
};

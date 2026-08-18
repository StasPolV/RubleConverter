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
};

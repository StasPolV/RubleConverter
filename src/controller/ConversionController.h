#pragma once

#include <QObject>

class IExchangeView;
class CurrencyConverter;

class ConversionController : public QObject
{
	Q_OBJECT
public:
	ConversionController(IExchangeView* panel_1, IExchangeView* panel_2,
	                     CurrencyConverter* converter, QObject* parent = nullptr);

private slots:
	void OnPanel1AmountEdited();
	void OnPanel2AmountEdited();

private:
	void RecalculateFrom(IExchangeView* src, IExchangeView* target);

	IExchangeView* m_panel_1;
	IExchangeView* m_panel_2;
	CurrencyConverter* m_converter;
};

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
	void OnPanel1Changed();
	void OnPanel2Changed();
	void UpdateRateLabels();

private:
	void RecalculateFrom(IExchangeView* src, IExchangeView* target);

	double ConvertAmount(IExchangeView* src, IExchangeView* target, double amount) const;
	double ConvertCurrentAmount(IExchangeView* src, IExchangeView* target) const;

	IExchangeView* m_panel_1;
	IExchangeView* m_panel_2;
	CurrencyConverter* m_converter;
};

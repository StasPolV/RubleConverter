#include "ConversionController.h"

#include "CurrencyConverter.h"
#include "IExchangeView.h"

ConversionController::ConversionController(IExchangeView* panel_1, IExchangeView* panel_2,
                                           CurrencyConverter* converter, QObject* parent)
    : QObject(parent), m_panel_1(panel_1), m_panel_2(panel_2), m_converter(converter)
{
	connect(m_panel_1->AsQObject(), SIGNAL(AmountEdited()), this, SLOT(OnPanel1AmountEdited()));
	connect(m_panel_2->AsQObject(), SIGNAL(AmountEdited()), this, SLOT(OnPanel2AmountEdited()));

	connect(m_panel_1->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(OnPanel1AmountEdited()));
	connect(m_panel_2->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(OnPanel2AmountEdited()));
}

void ConversionController::RecalculateFrom(IExchangeView* src, IExchangeView* target)
{
	const double amount = src->Amount().toDouble();
	const double result = m_converter->Convert(src->CurrentCode(), target->CurrentCode(), amount);
	target->SetAmount(QString::number(result, 'f', 2));
}

void ConversionController::OnPanel1AmountEdited()
{
	RecalculateFrom(m_panel_1, m_panel_2);
}

void ConversionController::OnPanel2AmountEdited()
{
	RecalculateFrom(m_panel_2, m_panel_1);
}

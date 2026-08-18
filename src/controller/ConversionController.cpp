#include "ConversionController.h"

#include "CurrencyConverter.h"
#include "IExchangeView.h"

namespace
{
	constexpr int kAmountPrecision = 2;  // TODO: move precision details into target implementation
}

ConversionController::ConversionController(IExchangeView* panel_1, IExchangeView* panel_2,
                                           CurrencyConverter* converter, QObject* parent)
    : QObject(parent), m_panel_1(panel_1), m_panel_2(panel_2), m_converter(converter)
{
	connect(m_panel_1->AsQObject(), SIGNAL(AmountEdited()), this, SLOT(OnPanel1Changed()));
	connect(m_panel_2->AsQObject(), SIGNAL(AmountEdited()), this, SLOT(OnPanel2Changed()));

	// When changing currency, the count goes from the left panel
	connect(m_panel_1->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(OnPanel1Changed()));
	connect(m_panel_2->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(OnPanel1Changed()));

	connect(m_panel_1->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(UpdateRateLabels()));
	connect(m_panel_2->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(UpdateRateLabels()));
}

void ConversionController::OnPanel1Changed()
{
	RecalculateFrom(m_panel_1, m_panel_2);
}

void ConversionController::OnPanel2Changed()
{
	RecalculateFrom(m_panel_2, m_panel_1);
}

void ConversionController::RecalculateFrom(IExchangeView* src, IExchangeView* target)
{
	const double result = ConvertCurrentAmount(src, target);
	target->SetAmount(QString::number(result, 'f', kAmountPrecision));
}

void ConversionController::UpdateRateLabels()
{
	const double rate_1_to_2 = ConvertAmount(m_panel_1, m_panel_2, 1.0);
	const double rate_2_to_1 = ConvertAmount(m_panel_2, m_panel_1, 1.0);

	m_panel_1->SetLabel(m_panel_1->CurrentCode(), 1, m_panel_2->CurrentCode(), rate_1_to_2);
	m_panel_2->SetLabel(m_panel_2->CurrentCode(), 1, m_panel_1->CurrentCode(), rate_2_to_1);
}

double ConversionController::ConvertAmount(IExchangeView* src, IExchangeView* target,
                                           double amount) const
{
	return m_converter->Convert(src->CurrentCode(), target->CurrentCode(), amount);
}

double ConversionController::ConvertCurrentAmount(IExchangeView* src, IExchangeView* target) const
{
	return ConvertAmount(src, target, src->Amount().toDouble());
}

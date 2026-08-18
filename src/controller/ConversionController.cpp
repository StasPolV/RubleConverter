#include "ConversionController.h"

#include "CurrencyConverter.h"
#include "IExchangeView.h"

ConversionController::ConversionController(IExchangeView* panel_1, IExchangeView* panel_2,
                                           CurrencyConverter* converter, QObject* parent)
    : QObject(parent), m_panel_1(panel_1), m_panel_2(panel_2), m_converter(converter)
{
	connect(m_panel_1->AsQObject(), SIGNAL(AmountEdited()), this, SLOT(OnPanelAmountEdited()));
	connect(m_panel_2->AsQObject(), SIGNAL(AmountEdited()), this, SLOT(OnPanelAmountEdited()));

	connect(m_panel_1->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(OnPanelAmountEdited()));
	connect(m_panel_2->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(OnPanelAmountEdited()));
	connect(m_panel_1->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(ChangeLabel()));
	connect(m_panel_2->AsQObject(), SIGNAL(CurrencyChanged()), this, SLOT(ChangeLabel()));
}

void ConversionController::RecalculateFrom(IExchangeView* src, IExchangeView* target)
{
	target->SetAmount(
	        QString::number(CalculateResult(src, target), 'f',
	                        2));  // TODO: move precision details into target implementation
}

void ConversionController::OnPanelAmountEdited()
{
	RecalculateFrom(m_panel_1, m_panel_2);
}

void ConversionController::ChangeLabel()
{
	double result_1 = CalculateResult(m_panel_1, m_panel_2, 1);
	double result_2 = CalculateResult(m_panel_2, m_panel_1, 1);
	m_panel_1->SetLabel(m_panel_1->CurrentCode(), 1, m_panel_2->CurrentCode(), result_1);
	m_panel_2->SetLabel(m_panel_2->CurrentCode(), 1, m_panel_1->CurrentCode(), result_2);
}

double ConversionController::CalculateResult(IExchangeView* src, IExchangeView* target,
                                             double amount)
{
	if (amount != -1)
	{
		return m_converter->Convert(src->CurrentCode(), target->CurrentCode(), amount);
	}

	const double src_amount = src->Amount().toDouble();
	const double result =
	        m_converter->Convert(src->CurrentCode(), target->CurrentCode(), src_amount);

	return result;
}

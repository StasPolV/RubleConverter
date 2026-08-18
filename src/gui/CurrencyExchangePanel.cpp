#include "CurrencyExchangePanel.h"

#include <QVBoxLayout>

CurrencyExchangePanel::CurrencyExchangePanel(CurrencyModel* model, QWidget* parent)
    : QWidget(parent)
{
	setAttribute(Qt::WA_StyledBackground, true);

	m_dropdown = new CurrencyDropdown(model, this);
	m_amount_input = new AmountInputWidget(this);

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->setContentsMargins(18, 16, 18, 18);
	main_layout->setSpacing(12);
	main_layout->addWidget(m_dropdown);
	main_layout->addWidget(m_amount_input);

	connect(m_dropdown, &CurrencyDropdown::CurrencyChanged, this,
	        &CurrencyExchangePanel::CurrencyChanged);
	connect(m_amount_input, &AmountInputWidget::TextEdited, this,
	        &CurrencyExchangePanel::AmountEdited);
}

void CurrencyExchangePanel::SetExchangeRateLabel(const QString& src_currency, double src_val,
                                                 const QString& dest_currency, double dest_val)
{
	m_amount_input->SetExchangeRateLabel(src_currency, src_val, dest_currency, dest_val);
}

QObject* CurrencyExchangePanel::AsQObject()
{
	return this;
}

QString CurrencyExchangePanel::CurrentCode() const
{
	return m_dropdown->CurrentCode();
}

QString CurrencyExchangePanel::Amount() const
{
	return m_amount_input->Amount();
}

void CurrencyExchangePanel::SetAmount(const QString& text)
{
	m_amount_input->SetAmount(text);
}

void CurrencyExchangePanel::SetCode(const QString& text)
{
	m_dropdown->SetCode(text);
}

#include "CurrencyExchangePanel.h"

#include <QVBoxLayout>

CurrencyExchangePanel::CurrencyExchangePanel(CurrencyModel* model, QWidget* parent)
    : QWidget(parent)
{
	CurrencyDropdown* dropdown = new CurrencyDropdown(model, this);
	AmountInputWidget* amount_input = new AmountInputWidget(this);

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(3);
	main_layout->addWidget(dropdown);
	main_layout->addWidget(amount_input);
}

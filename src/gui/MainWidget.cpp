#include "MainWidget.h"

#include "AmountInputWidget.h"
#include "CurrencyDropdown.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	CurrencyDropdown* dropdown_1 = new CurrencyDropdown(this);
	AmountInputWidget* amount_input = new AmountInputWidget(this);

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addWidget(dropdown_1);
	main_layout->addWidget(amount_input);
}

#include "MainWidget.h"

#include "CurrencyDropdown.h"

#include <QHBoxLayout>

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	CurrencyDropdown* dropdown_1 = new CurrencyDropdown(this);

	QHBoxLayout* main_layout = new QHBoxLayout(this);
	main_layout->addWidget(dropdown_1);
}

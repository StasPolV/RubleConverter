#include "MainWidget.h"

#include "ConversionController.h"
#include "CurrencyConverter.h"
#include "CurrencyExchangePanel.h"
#include "CurrencyFetcherController.h"
#include "CurrencyModel.h"
#include "MainController.h"

#include <QHBoxLayout>
#include <QToolButton>

namespace
{
	double kSwitchButtonRatio = 0.3;
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	m_currency_model = new CurrencyModel(this);
	CurrencyConverter* converter = new CurrencyConverter(this);

	CurrencyExchangePanel* panel_1 = new CurrencyExchangePanel(m_currency_model, this);
	CurrencyExchangePanel* panel_2 = new CurrencyExchangePanel(m_currency_model, this);
	QHBoxLayout* main_layout = new QHBoxLayout(this);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->addWidget(panel_1, 3);
	m_switch_button = new ScalableIconButton(this);
	m_switch_button->SetIconSource(":/images/arrows.png");
	m_switch_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_switch_button->setMinimumWidth(50);
	main_layout->addWidget(m_switch_button, 1);
	main_layout->addWidget(panel_2, 3);

	new CurrencyFetcherController(m_currency_model, converter, this);
	new ConversionController(panel_1, panel_2, converter, this);
	MainController* main_controller = new MainController(this);

	connect(m_switch_button, &ScalableIconButton::clicked, this,
	        [this, panel_1, panel_2]() { emit SwitchRequested(panel_1, panel_2); });
	connect(this, &MainWidget::SwitchRequested, main_controller, &MainController::SwitchPanels);
}

void MainWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	m_switch_button->setMaximumHeight(height() * kSwitchButtonRatio);
}

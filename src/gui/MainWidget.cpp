#include "MainWidget.h"

#include "CurrencyExchangePanel.h"

#include <QHBoxLayout>
#include <QToolButton>

namespace
{
	double kSwitchButtonRatio = 0.3;
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	CurrencyExchangePanel* panel_1 = new CurrencyExchangePanel(this);
	CurrencyExchangePanel* panel_2 = new CurrencyExchangePanel(this);

	QHBoxLayout* main_layout = new QHBoxLayout(this);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->addWidget(panel_1, 3);
	m_switch_button = new ScalableIconButton(this);
	m_switch_button->SetIconSource(":/images/arrows.png");
	m_switch_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_switch_button->setMinimumWidth(50);
	main_layout->addWidget(m_switch_button, 1);
	main_layout->addWidget(panel_2, 3);
}

void MainWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	m_switch_button->setMaximumHeight(height() * kSwitchButtonRatio);
}

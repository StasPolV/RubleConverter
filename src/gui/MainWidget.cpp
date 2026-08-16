#include "MainWidget.h"

#include "CurrencyExchangePanel.h"
#include "CurrencyFetcherController.h"
#include "CurrencyModel.h"

#include <QHBoxLayout>
#include <QToolButton>

namespace
{
	double kSwitchButtonRatio = 0.3;
}

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	m_currency_model = new CurrencyModel(this);

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

	new CurrencyFetcherController(m_currency_model, this);

	connect(m_switch_button, &ScalableIconButton::clicked, this,
	        [this, panel_1, panel_2, main_layout]()
	        {
		        int index_a = main_layout->indexOf(panel_1);
		        int index_b = main_layout->indexOf(panel_2);

		        main_layout->removeWidget(panel_1);
		        main_layout->removeWidget(panel_2);

		        if (index_a < index_b)
		        {
			        main_layout->insertWidget(index_a, panel_2, 3);
			        main_layout->insertWidget(index_b, panel_1, 3);
		        }
		        else
		        {
			        main_layout->insertWidget(index_b, panel_1, 3);
			        main_layout->insertWidget(index_a, panel_2, 3);
		        }
	        });
}

void MainWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	m_switch_button->setMaximumHeight(height() * kSwitchButtonRatio);
}

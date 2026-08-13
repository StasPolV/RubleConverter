#include "CurrencyDropdown.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QToolButton>

namespace
{
	enum currency
	{
		RUB,
		USD,
		EUR,
		OTHER,
		ARROW,
		_COUNT
	};
}  // namespace

CurrencyDropdown::CurrencyDropdown(QWidget* parent) : QWidget(parent)
{
	QToolButton* buttons[_COUNT];
	for (size_t i = 0; i < _COUNT; ++i)
	{
		buttons[i] = new QToolButton(this);
		buttons[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	}
	buttons[ARROW]->setArrowType(Qt::ArrowType::DownArrow);

	buttons[RUB]->setText("RUB");
	buttons[USD]->setText("USD");
	buttons[EUR]->setText("EUR");
	buttons[OTHER]->setText("OTHER");

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	for (size_t i = 0; i < _COUNT; ++i)
	{
		layout->addWidget(buttons[i], 4);
		if (static_cast<currency>(i) == ARROW)
		{
			layout->setStretch(i, 1);
		}
	}

	// TODO: implement pop-up window after pressing arrow button
}

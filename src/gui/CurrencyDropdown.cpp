#include "CurrencyDropdown.h"

#include "CurrencyModel.h"

#include <QButtonGroup>
#include <QEvent>
#include <QHBoxLayout>
#include <QListView>
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

CurrencyDropdown::CurrencyDropdown(CurrencyModel* model, QWidget* parent)
    : QWidget(parent), m_currency_model(model)
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

	m_button_group = new QButtonGroup(this);
	m_button_group->setExclusive(true);
	connect(m_button_group, &QButtonGroup::buttonClicked, this,
	        [this](QAbstractButton* button) { emit CurrencyChanged(button->text()); });
	for (currency i = RUB; i <= OTHER;)
	{
		buttons[i]->setCheckable(true);
		m_button_group->addButton(buttons[i]);
		i = static_cast<currency>(i + 1);
	}

	buttons[RUB]->setChecked(true);

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

	m_view = new QListView(this);
	m_view->setModel(m_currency_model);
	m_view->setWrapping(true);
	m_view->setVisible(false);
	m_view->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

	m_other_button = buttons[OTHER];
	connect(buttons[ARROW], &QToolButton::clicked, this, [this]() { TogglePopup(); });
	connect(m_view, &QListView::clicked, this,
	        [this](const QModelIndex& index)
	        {
		        QString data = index.data(CurrencyModel::CodeRole).toString();
		        m_other_button->setText(data);
		        emit CurrencyChanged(data);
	        });
}

void CurrencyDropdown::TogglePopup()
{
	if (m_view->isVisible())
	{
		m_view->hide();
		if (window())
		{
			window()->removeEventFilter(this);
		}

		return;
	}

	if (window())
	{
		window()->installEventFilter(this);
	}

	ResizePopup();
}

void CurrencyDropdown::ResizePopup()
{
	const QPoint global_pos = mapToGlobal(QPoint(0, height()));
	m_view->move(global_pos);
	m_view->resize(window()->width(), 300);
	m_view->show();
}

bool CurrencyDropdown::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == window() && m_view->isVisible())
	{
		switch (event->type())
		{
		case QEvent::Move:
		case QEvent::Resize: ResizePopup(); break;
		case QEvent::WindowStateChange:
			if (window()->isMinimized())
			{
				m_view->hide();
			}
			else
			{
				ResizePopup();
			}
			break;
		default: break;
		}
	}

	return QWidget::eventFilter(watched, event);
}

QString CurrencyDropdown::CurrentCode() const
{
	QAbstractButton* checked = m_button_group->checkedButton();
	return checked ? checked->text() : QString();
}

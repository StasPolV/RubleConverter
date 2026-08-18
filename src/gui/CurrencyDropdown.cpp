#include "CurrencyDropdown.h"

#include "CurrencyListItemDelegate.h"
#include "CurrencyModel.h"

#include <QButtonGroup>
#include <QEvent>
#include <QFontMetrics>
#include <QHBoxLayout>
#include <QListView>
#include <QMenu>
#include <QStyleOptionViewItem>
#include <QToolButton>

#include <algorithm>

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
	buttons[ARROW]->setCheckable(true);

	buttons[RUB]->setObjectName("CurrencyOptionFirst");
	buttons[USD]->setObjectName("CurrencyOption");
	buttons[EUR]->setObjectName("CurrencyOption");
	buttons[OTHER]->setObjectName("CurrencyOption");
	buttons[ARROW]->setObjectName("CurrencyDropdownToggle");

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
		m_button_group->addButton(buttons[i], static_cast<int>(i));
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
	m_view->setObjectName("CurrencyListPopup");
	m_view->setModel(m_currency_model);
	m_view->setWrapping(true);
	m_view->setResizeMode(QListView::Adjust);
	m_view->setSpacing(2);
	m_view->setTextElideMode(Qt::ElideNone);
	m_view->setVisible(false);
	m_view->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	m_view->setAttribute(Qt::WA_TranslucentBackground);
	m_view->setMinimumHeight(400);

	m_item_delegate = new CurrencyListItemDelegate(this);
	m_view->setItemDelegate(m_item_delegate);

	m_other_button = buttons[OTHER];
	m_toggle_button = buttons[ARROW];
	connect(m_toggle_button, &QToolButton::clicked, this, [this]() { TogglePopup(); });
	connect(m_view, &QListView::clicked, this,
	        [this](const QModelIndex& index)
	        {
		        QString data = index.data(CurrencyModel::CodeRole).toString();
		        m_other_button->setText(data);
		        m_other_button->setChecked(true);
		        emit CurrencyChanged(data);
		        SetPopupOpen(false);
	        });
}

void CurrencyDropdown::TogglePopup()
{
	SetPopupOpen(!m_view->isVisible());
}

void CurrencyDropdown::SetPopupOpen(bool open)
{
	m_toggle_button->setChecked(open);
	m_toggle_button->setArrowType(open ? Qt::ArrowType::UpArrow : Qt::ArrowType::DownArrow);

	if (!open)
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

	UpdatePopupGridSize();
	ResizePopup();
}

void CurrencyDropdown::UpdatePopupGridSize()
{
	if (!m_currency_model || m_currency_model->rowCount() == 0)
	{
		return;
	}

	QStyleOptionViewItem option;
	option.font = m_view->font();
	option.fontMetrics = QFontMetrics(option.font);

	QSize grid_size(0, 0);
	for (int row = 0; row < m_currency_model->rowCount(); ++row)
	{
		const QSize item_size = m_item_delegate->sizeHint(option, m_currency_model->index(row, 0));
		grid_size.setWidth(std::max(grid_size.width(), item_size.width()));
		grid_size.setHeight(std::max(grid_size.height(), item_size.height()));
	}

	m_view->setGridSize(grid_size);
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
				SetPopupOpen(false);
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

void CurrencyDropdown::SetCode(const QString& code)
{
	if (code == "RUB")
	{
		m_button_group->button(static_cast<int>(RUB))->setChecked(true);
	}
	else if (code == "EUR")
	{
		m_button_group->button(static_cast<int>(EUR))->setChecked(true);
	}
	else if (code == "USD")
	{
		m_button_group->button(static_cast<int>(USD))->setChecked(true);
	}
	else
	{
		auto* button = m_button_group->button(static_cast<int>(OTHER));
		button->setText(code);
		button->setChecked(true);
	}

	emit CurrencyChanged(code);
}

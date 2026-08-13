#include "AmountInputWidget.h"

#include "ScalableLineEdit.h"

#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>

AmountInputWidget::AmountInputWidget(QWidget* parent) : QFrame(parent)
{
	m_line_edit = new ScalableLineEdit(this);
	m_line_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QRegularExpression reg_exp("^[0-9.]+$");
	QRegularExpressionValidator* validator = new QRegularExpressionValidator(reg_exp, this);
	m_line_edit->setValidator(validator);

	m_label = new QLabel(this);
	m_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_label->setText("1 RUB = 1 RUB");

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->setSpacing(3);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->addWidget(m_line_edit);
	main_layout->addWidget(m_label);
}

void AmountInputWidget::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);

	const int target_size = m_line_edit->font().pixelSize();

	if (m_label->font().pixelSize() != target_size)
	{
		QFont label_font = m_label->font();
		label_font.setPixelSize(target_size);
		m_label->setFont(label_font);
	}
}

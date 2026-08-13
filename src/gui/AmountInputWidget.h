#pragma once

#include <QFrame>
#include <QResizeEvent>

class QLineEdit;
class QLabel;

class AmountInputWidget : public QFrame
{
	Q_OBJECT
public:
	explicit AmountInputWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QLabel* m_label;
	QLineEdit* m_line_edit;
};

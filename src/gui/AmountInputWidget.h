#pragma once

#include <QFrame>
#include <QResizeEvent>
#include <QString>

class QLineEdit;
class QLabel;

class AmountInputWidget : public QFrame
{
	Q_OBJECT

signals:
	void TextEdited(const QString& text);

public slots:
	void SetAmount(const QString& text);

public:
	explicit AmountInputWidget(QWidget* parent = nullptr);

	QString Amount() const;
	void SetLabel(const QString& src_currency, double src_val, const QString& dest_currency,
	              double dest_val);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QLabel* m_label;
	QLineEdit* m_line_edit;
};

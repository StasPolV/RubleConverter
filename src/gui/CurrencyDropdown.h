#pragma once

#include <QString>
#include <QWidget>

class QListView;
class CurrencyModel;
class QToolButton;
class QButtonGroup;

class CurrencyDropdown : public QWidget
{
	Q_OBJECT

signals:
	void CurrencyChanged(const QString& code);

public:
	explicit CurrencyDropdown(CurrencyModel* model, QWidget* parent = nullptr);
	QString CurrentCode() const;

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void TogglePopup();
	void ResizePopup();

	CurrencyModel* m_currency_model;
	QListView* m_view;
	QToolButton* m_other_button;
	QButtonGroup* m_button_group;
};

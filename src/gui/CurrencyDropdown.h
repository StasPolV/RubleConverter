#pragma once

#include <QWidget>

class QListView;
class CurrencyModel;

class CurrencyDropdown : public QWidget
{
	Q_OBJECT
public:
	explicit CurrencyDropdown(CurrencyModel* model, QWidget* parent = nullptr);

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void TogglePopup();
	void ResizePopup();

	CurrencyModel* m_currency_model;
	QListView* m_view;
};

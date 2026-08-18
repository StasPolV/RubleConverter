#pragma once

#include <QString>
#include <QWidget>

class QListView;
class CurrencyModel;
class QToolButton;
class QButtonGroup;
class CurrencyListItemDelegate;

class CurrencyDropdown : public QWidget
{
	Q_OBJECT

signals:
	void CurrencyChanged(const QString& code);

public:
	explicit CurrencyDropdown(CurrencyModel* model, QWidget* parent = nullptr);
	QString CurrentCode() const;
	void SetCode(const QString& code);

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	void TogglePopup();
	void SetPopupOpen(bool open);
	void ResizePopup();
	void UpdatePopupGridSize();

	CurrencyModel* m_currency_model;
	QListView* m_view;
	CurrencyListItemDelegate* m_item_delegate;
	QToolButton* m_other_button;
	QToolButton* m_toggle_button;
	QButtonGroup* m_button_group;
};

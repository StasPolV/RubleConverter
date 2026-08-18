#pragma once

#include "AmountInputWidget.h"
#include "CurrencyDropdown.h"
#include "IExchangeView.h"

#include <QString>
#include <QWidget>

class CurrencyModel;

class CurrencyExchangePanel : public QWidget, public IExchangeView
{
	Q_OBJECT

signals:
	void AmountEdited();
	void CurrencyChanged();

public slots:
	void SetAmount(const QString& text) override;

	QObject* AsQObject() override;

public:
	explicit CurrencyExchangePanel(CurrencyModel* model, QWidget* parent = nullptr);

	QString CurrentCode() const override;
	QString Amount() const override;

private:
	CurrencyDropdown* m_dropdown;
	AmountInputWidget* m_amount_input;
};

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
	void SetCode(const QString& text) override;

	QObject* AsQObject() override;

public:
	explicit CurrencyExchangePanel(CurrencyModel* model, QWidget* parent = nullptr);

	QString CurrentCode() const override;
	QString Amount() const override;
	void SetLabel(const QString& src_currency, double src_val, const QString& dest_currency,
	              double dest_val) override;

private:
	CurrencyDropdown* m_dropdown;
	AmountInputWidget* m_amount_input;
};

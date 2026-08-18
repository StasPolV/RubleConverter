#pragma once

#include "ScalableIconButton.h"

#include <QResizeEvent>
#include <QWidget>

class CurrencyModel;
class CurrencyExchangePanel;

class MainWidget : public QWidget
{
	Q_OBJECT

signals:
	void SwitchRequested(CurrencyExchangePanel* panel_1, CurrencyExchangePanel* panel_2);

public:
	explicit MainWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	ScalableIconButton* m_switch_button;
	CurrencyModel* m_currency_model;
};

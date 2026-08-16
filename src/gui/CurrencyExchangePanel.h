#pragma once

#include "AmountInputWidget.h"
#include "CurrencyDropdown.h"

#include <QWidget>

class CurrencyModel;

class CurrencyExchangePanel : public QWidget
{
public:
	explicit CurrencyExchangePanel(CurrencyModel* model, QWidget* parent = nullptr);
};

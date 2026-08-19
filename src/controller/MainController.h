#pragma once

#include <QObject>

class IExchangeView;

class MainController : public QObject
{
	Q_OBJECT

public slots:
	static void SwitchPanels(IExchangeView* panel_1, IExchangeView* panel_2);

public:
	MainController(QObject* parent = nullptr);
};

#include "MainController.h"

#include "IExchangeView.h"

MainController::MainController(QObject* parent) : QObject(parent) {}

void MainController::SwitchPanels(IExchangeView* panel_1, IExchangeView* panel_2)
{
	QString panel_1_code = panel_1->CurrentCode();
	panel_1->SetCode(panel_2->CurrentCode());
	panel_2->SetCode(panel_1_code);
}

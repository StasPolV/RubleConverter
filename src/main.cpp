#include "CurrencyExchangePanel.h"
#include "CurrencyFetcherController.h"
#include "CurrencyModel.h"
#include "MainWidget.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWidget main_widget;

	main_widget.show();

	return app.exec();
}

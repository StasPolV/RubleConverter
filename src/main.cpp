#include "CurrencyExchangePanel.h"
#include "CurrencyFetcherController.h"
#include "CurrencyModel.h"
#include "MainWidget.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

namespace
{
	void applyAppStyleSheet(QApplication& app)
	{
		QFile style_file(":/styles/app.qss");
		if (!style_file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return;
		}

		app.setStyleSheet(QTextStream(&style_file).readAll());
	}
}  // namespace

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	applyAppStyleSheet(app);

	MainWidget main_widget;

	main_widget.show();

	return app.exec();
}

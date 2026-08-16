#pragma once

#include <QNetworkAccessManager>
#include <QObject>

struct CurrencyRecord
{
	QString date;
	QString base;
	QString quote;
	double rate = 0.0;
};

class QNetworkAccessManager;
class QNetworkReply;

class CurrencyFetcher : public QObject
{
	Q_OBJECT

signals:
	void Finished(QVector<CurrencyRecord> = {});

public:
	explicit CurrencyFetcher(QObject* parent = nullptr);

	void Fetch();

private slots:
	void OnReplyFinished(QNetworkReply* reply);

private:
	QNetworkAccessManager m_manager;
};

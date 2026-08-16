#include "CurrencyFetcher.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

CurrencyFetcher::CurrencyFetcher(QObject* parent) : QObject(parent)
{
	connect(&m_manager, &QNetworkAccessManager::finished, this, &CurrencyFetcher::OnReplyFinished);
}

void CurrencyFetcher::Fetch()
{
	QUrl url("https://api.frankfurter.dev/v2/rates");

	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::UserAgentHeader, "QtConverter/1.0");

	m_manager.get(request);
}

void CurrencyFetcher::OnReplyFinished(QNetworkReply* reply)
{
	reply->deleteLater();

	if (reply->error() != QNetworkReply::NoError)
	{
		qWarning() << "Network Error:" << reply->errorString();
		emit Finished();
		return;
	}

	const QByteArray raw_data = reply->readAll();

	QJsonParseError parse_error;
	const QJsonDocument doc = QJsonDocument::fromJson(raw_data, &parse_error);

	if (parse_error.error != QJsonParseError::NoError)
	{
		qWarning() << "JSON parsing error:" << parse_error.errorString();
		emit Finished();
		return;
	}

	QVector<CurrencyRecord> records;
	if (doc.isArray())
	{
		const QJsonArray array = doc.array();
		records.reserve(array.size());

		for (const QJsonValue& val : array)
		{
			if (!val.isObject())
			{
				continue;
			}

			const QJsonObject obj = val.toObject();

			CurrencyRecord rec;
			rec.date = obj.value("date").toString();
			rec.base = obj.value("base").toString();
			rec.quote = obj.value("quote").toString();
			rec.rate = obj.value("rate").toDouble();

			records.append(rec);
		}
	}
	else
	{
		qWarning() << "Unexpected response format (JSON array expected)";
	}

	emit Finished();
}

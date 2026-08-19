#include "CurrencyModel.h"

CurrencyModel::CurrencyModel(QObject* parent) : QAbstractListModel(parent) {}

int CurrencyModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
	{
		return 0;
	}
	return static_cast<int>(m_currencies.size());
}

QVariant CurrencyModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || index.row() < 0 || index.row() >= m_currencies.size())
	{
		return {};
	}

	const Currency& c = m_currencies.at(index.row());

	switch (role)
	{
	case Qt::DisplayRole: return QString("%1 %2").arg(c.code).arg(c.name);
	case NameRole: return c.name;
	case CodeRole: return c.code;
	default: return {};
	}
}

Qt::ItemFlags CurrencyModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
	{
		return Qt::NoItemFlags;
	}
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void CurrencyModel::AddCurrency(const Currency& currency)
{
	const int row = static_cast<int>(m_currencies.size());
	beginInsertRows(QModelIndex(), row, row);
	m_currencies.append(currency);
	endInsertRows();
}

void CurrencyModel::RemoveCurrency(int row)
{
	if (row < 0 || row >= m_currencies.size())
	{
		return;
	}

	beginRemoveRows(QModelIndex(), row, row);
	m_currencies.removeAt(row);
	endRemoveRows();
}

void CurrencyModel::SetCurrencies(QVector<Currency> currencies)
{
	beginResetModel();
	m_currencies = std::move(currencies);
	endResetModel();
}

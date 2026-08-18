#pragma once

#include <QStyledItemDelegate>

class CurrencyListItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit CurrencyListItemDelegate(QObject* parent = nullptr);

	void paint(QPainter* painter, const QStyleOptionViewItem& option,
	           const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
	static constexpr int kHorizontalPadding = 12;
	static constexpr int kVerticalPadding = 10;
	static constexpr int kNameCodeGap = 16;
};

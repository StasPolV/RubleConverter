#include "CurrencyListItemDelegate.h"

#include "CurrencyModel.h"

#include <QApplication>
#include <QFontMetrics>
#include <QPainter>
#include <QStyle>

#include <algorithm>

namespace
{
	const QColor kNameColor("#1A1F29");
	const QColor kCodeColor("#8B93A1");
}  // namespace

CurrencyListItemDelegate::CurrencyListItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void CurrencyListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const
{
	QStyleOptionViewItem opt(option);
	initStyleOption(&opt, index);

	opt.text.clear();
	QStyle* style = opt.widget ? opt.widget->style() : QApplication::style();
	style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);

	const QString name = index.data(CurrencyModel::NameRole).toString();
	const QString code = index.data(CurrencyModel::CodeRole).toString();

	const QRect content_rect = opt.rect.adjusted(kHorizontalPadding, 0, -kHorizontalPadding, 0);

	QFont code_font = opt.font;
	code_font.setBold(true);
	const QFontMetrics code_metrics(code_font);
	const int code_width = code_metrics.horizontalAdvance(code);

	const QRect code_rect(content_rect.right() - code_width, content_rect.top(), code_width,
	                      content_rect.height());
	const QRect name_rect(content_rect.left(), content_rect.top(),
	                      std::max(0, content_rect.width() - code_width - kNameCodeGap),
	                      content_rect.height());

	painter->setFont(opt.font);
	painter->setPen(kNameColor);
	painter->drawText(name_rect, Qt::AlignVCenter | Qt::AlignLeft,
	                  QFontMetrics(opt.font).elidedText(name, Qt::ElideRight, name_rect.width()));

	painter->setFont(code_font);
	painter->setPen(kCodeColor);
	painter->drawText(code_rect, Qt::AlignVCenter | Qt::AlignRight, code);

	painter->restore();
}

QSize CurrencyListItemDelegate::sizeHint(const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
	const QString name = index.data(CurrencyModel::NameRole).toString();
	const QString code = index.data(CurrencyModel::CodeRole).toString();

	QFont code_font = option.font;
	code_font.setBold(true);

	const int text_width = QFontMetrics(option.font).horizontalAdvance(name) + kNameCodeGap +
	        QFontMetrics(code_font).horizontalAdvance(code);
	const int height = option.fontMetrics.height() + kVerticalPadding * 2;

	return QSize(text_width + kHorizontalPadding * 2, height);
}

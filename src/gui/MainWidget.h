#pragma once

#include "ScalableIconButton.h"

#include <QResizeEvent>
#include <QWidget>

class MainWidget : public QWidget
{
	Q_OBJECT
public:
	explicit MainWidget(QWidget* parent = nullptr);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	ScalableIconButton* m_switch_button;
};

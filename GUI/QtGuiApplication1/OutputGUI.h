#pragma once

#include <QWidget>
#include "ui_OutputGUI.h"
#include "GUI.h"

class OutputGUI : public QWidget
{
	Q_OBJECT

public:
	OutputGUI(QWidget *parent = Q_NULLPTR);
	~OutputGUI();
	void setDecision(QString something);

	void setLeftPhoto(QImage something);

	void setRightPhoto(QImage something);

private:
	Ui::OutputGUI out;

};
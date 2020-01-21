#include "OutputGUI.h"

OutputGUI::OutputGUI(QWidget *parent)
	: QWidget(parent)
{
	out.setupUi(this);
}

OutputGUI::~OutputGUI()
{
}

void OutputGUI::setDecision(QString text)
{
	out.decisionText->setText(text);
}

void OutputGUI::setLeftPhoto(QImage image)
{
	out.tirePhoto->setPixmap(QPixmap::fromImage(image));
}

void OutputGUI::setRightPhoto(QImage image)
{
	out.detectPhoto->setPixmap(QPixmap::fromImage(image));
}
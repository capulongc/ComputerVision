#include "GUI.h"
#include "OutputGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GUI main;
	main.show();

	OutputGUI out;

	return a.exec();
}

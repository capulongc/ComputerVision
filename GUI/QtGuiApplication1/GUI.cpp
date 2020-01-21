#include "GUI.h"
#include "OutputGUI.h"
#include <QFileDialog>

GUI::GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(
		ui.exitButton,
		SIGNAL(clicked()),
		this,
		SLOT(exit())
	);

	connect(
		ui.folderButton,
		SIGNAL(clicked()),
		this,
		SLOT(selectFile())
	);

	connect(
		ui.startButton,
		SIGNAL(clicked()),
		this,
		SLOT(start())
	);
}

GUI::~GUI()
{

}

void GUI::selectFile()
{
	dir = QFileDialog::getExistingDirectory(
		this,
		tr("Open Directory"),
		"C:\\",
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
	);
	ui.locationLabel->setText("Photo Folder Location : " + dir);
	ui.startButton->setEnabled(true);
}

void GUI::start()
{
	if (ui.comboBox->currentIndex() == 0)
	{
		this->hide();
		faceDetection(dir, this);
	}

	if (ui.comboBox->currentIndex() == 1)
	{
		this->hide();
		tireDetection(dir, this);
	}

	if (ui.comboBox->currentIndex() == 2)
	{
		this->hide();
		shapeDetection(dir, this);
	}

	if (ui.comboBox->currentIndex() == 3)
	{
		this->hide();
		colorDetection(dir, this);
	}

	if (ui.comboBox->currentIndex() == 4)
	{
		this->hide();
		licenseReader(dir, this);
	}

	this->exit();
}


void GUI::exit()
{
	QApplication::exit();
}
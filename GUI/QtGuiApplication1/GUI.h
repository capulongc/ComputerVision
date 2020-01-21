#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include <qmessagebox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qstring.h>
#include <qprogressbar.h>

#include "opencv2\core\core.hpp"
#include "opencv2\opencv.hpp"

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;
using namespace dlib;


class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI(QWidget *parent = Q_NULLPTR);
	~GUI();
	QString dir;

private:
	Ui::QtGuiApplication1Class ui;


private slots:
	void start();
	void selectFile();
	void exit();
};

//TIRE CODE
bool checkdistance(Vec3i a, Vec3i b);

bool checklugboundary(std::vector<Vec3f>a, std::vector<Vec3f>rim);

bool checkcircular(std::vector < Vec3f>something, Mat somename, std::vector<Vec3f>rim);

std::vector<Vec3f> detectrim(Mat somename);

std::vector<Vec3f> detectlugs(Mat somename);

void checkprint(std::vector<Vec3f>something);

void drawCircles(Mat somename, std::vector<Vec3f>something);

Mat preprocess(Mat something);

bool checkImageSize(Mat something);

void tireDetection(QString qstr, GUI *const gui);


//SHAPE CODE
void shapeDetection(QString something, GUI *const gui);


//FACE CODE
void faceDetection(QString something, GUI *const gui);

void loadXML(dlib::array<array2d<unsigned char>>& a,
	std::vector<std::vector<dlib::rectangle>>& b,
	const string& str);


//COLOR CODE
void findMainColor(std::vector<int> something,
	std::vector<Mat> detImages);

void colorDetection(QString something, GUI *const gui);


//LICENSE CODE
char checkcharacter(
	std::vector<std::vector<Point>> something, 
	std::vector<std::vector<Point>>something2);

void licenseReader(QString something, GUI *const gui);

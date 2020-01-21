#include "GUI.h"
#include "OutputGUI.h"
#include "characters.h"

using namespace std;
using namespace cv;

//Compares the contours with the templates to find matching character
//INPUT:  Vector of contours of a character in the plate
//		  Vector of templates of all possible characters
//OUTPUT: The found character or '0' if no character was found
char checkcharacter(std::vector<std::vector<Point>> something, std::vector<std::vector<Point>>something2) {
	char holder = ' ';
	for (int i = 0; i < 36; i++) {
		double match = matchShapes(something[i], something2[0], CV_CONTOURS_MATCH_I1, 0);
		if (match < .5) {
			holder = characters[i];
			break;
		}
	}
	return holder;
}

void licenseReader(QString folderLocation, GUI *const gui)
{
	//Places all character templates from "characters.h" into a single vector"
	std::vector<std::vector<Point>>templates;
	templates.push_back(N1);
	templates.push_back(N2);
	templates.push_back(N3);
	templates.push_back(N4);
	templates.push_back(N5);
	templates.push_back(N6);
	templates.push_back(N7);
	templates.push_back(N8);
	templates.push_back(N9);
	templates.push_back(A);
	templates.push_back(B);
	templates.push_back(C);
	templates.push_back(D);
	templates.push_back(E);
	templates.push_back(F);
	templates.push_back(G);
	templates.push_back(H);
	templates.push_back(I);
	templates.push_back(J);
	templates.push_back(K);
	templates.push_back(L);
	templates.push_back(M);
	templates.push_back(N);
	templates.push_back(O);
	templates.push_back(P);
	templates.push_back(Q);
	templates.push_back(R);
	templates.push_back(S);
	templates.push_back(T);
	templates.push_back(U);
	templates.push_back(V);
	templates.push_back(W);
	templates.push_back(X);
	templates.push_back(Y);
	templates.push_back(Z);
	templates.push_back(N0);


	//Displays the output GUI containing two photos and the decision text
	OutputGUI outputGUI;
	outputGUI.show();

	//Creates three vectors to hold filenames, photos of tires, and binary images
	std::vector<String> fn;
	std::vector<Mat> originArr;
	std::vector<Mat> testArr;
	string path = folderLocation.toLocal8Bit();

	///Scans files with the .jpg extension
	string jpgpath = path + "/*.jpg";
	std::vector<String> jpgfn;
	//Detects each .jpg file in the folder and adds its directory location to the temporary filename vector
	glob(jpgpath, jpgfn, true);
	//Inserts all temporary file names into main filename vector
	fn.insert(
		fn.end(),
		jpgfn.begin(),
		jpgfn.end());

	///Scans files with the .JPG extension
	string JPGpath = path + "/*.JPG";
	std::vector<String> JPGfn;
	//Detects each .JPG file in the folder and adds its directory location to the temporary filename vector
	glob(JPGpath, JPGfn, true);
	//Inserts all temporary file names into main filename vector
	fn.insert(
		fn.end(),
		JPGfn.begin(),
		JPGfn.end());

	///Scans files with the .bmp extension
	string bmppath = path + "/*.bmp";
	std::vector<String> bmpfn;
	//Detects each .bmp file in the folder and adds its directory location to the temporary filename vector
	glob(bmppath, bmpfn, true);
	fn.insert(
		fn.end(),
		bmpfn.begin(),
		bmpfn.end());

	///Scans files with the .png extension
	string pngpath = path + "/*.png";
	std::vector<String> pngfn;
	//Detects each .png file in the folder and adds its directory location to the temporary filename vector
	glob(pngpath, pngfn, true);
	fn.insert(
		fn.end(),
		pngfn.begin(),
		pngfn.end());

	///Scans files with the .PNG extension
	string PNGpath = path + "/*.PNG";
	std::vector<String> PNGfn;
	//Detects each .PNG file in the folder and adds its directory location to the temporary filename vector
	glob(PNGpath, PNGfn, true);
	fn.insert(
		fn.end(),
		PNGfn.begin(),
		PNGfn.end());

	///Scans files with the .gif extension
	string gifpath = path + "/*.gif";
	std::vector<String> giffn;
	//Detects each .gif file in the folder and adds its directory location to the temporary filename vector
	glob(gifpath, giffn, true);
	fn.insert(
		fn.end(),
		giffn.begin(),
		giffn.end());

	///Scans files with the .tiff extension
	string tiffpath = path + "/*.tiff";
	std::vector<String> tifffn;
	//Detects each .tiff file in the folder and adds its directory location to the temporary filename vector
	glob(tiffpath, tifffn, true);
	fn.insert(
		fn.end(),
		tifffn.begin(),
		tifffn.end());

	//Loads each image from the filename vector
	//Loads a colored image and binary image and adds each to respective vector
	for (size_t i = 0; i < fn.size(); i++)
	{
		Mat originT = imread(fn[i], CV_LOAD_IMAGE_COLOR);
		Mat testT = imread(fn[i], CV_LOAD_IMAGE_GRAYSCALE);

		if (originT.empty()) continue;
		originArr.push_back(originT);
		testArr.push_back(testT);
	}

	//Iterates through image vectors and performs necessary scans
	for (size_t j = 0; j < originArr.size(); j++)
	{
		Mat origin = originArr[j];
		Mat test = testArr[j];
		
		//Resizes and blurs image for accuracy
		Size preprocess(800, 800);
		resize(origin, origin, preprocess);
		resize(test, test, preprocess);

		medianBlur(test, test, (13, 13));

		//Vectors to hold contours of characters
		std::vector<std::vector<Point>>holdscontours1;
		std::vector<Vec4i>holdsorder1;
		std::vector<std::vector<Point>>holdscontours2;
		std::vector<Vec4i>holdsorder2;
		std::vector<std::vector<Point>>holdscontours3;
		std::vector<Vec4i>holdsorder3;
		std::vector<std::vector<Point>>holdscontours4;
		std::vector<Vec4i>holdsorder4;
		std::vector<std::vector<Point>>holdscontours5;
		std::vector<Vec4i>holdsorder5;
		std::vector<std::vector<Point>>holdscontours6;
		std::vector<Vec4i>holdsorder6;

		Scalar blue = (0, 0, 255);
		Scalar black = (0, 0, 0);
		threshold(test, test, 130, 255, 1);

		//Draws rectangles around the significant points of the image
		cv::rectangle(origin, Point(50, 250), Point(135, 600), black, 2, 8, 0);
		cv::rectangle(origin, Point(140, 250), Point(225, 600), black, 2, 8, 0);
		cv::rectangle(origin, Point(230, 250), Point(315, 600), black, 2, 8, 0);

		cv::rectangle(origin, Point(490, 250), Point(575, 600), black, 2, 8, 0);
		cv::rectangle(origin, Point(580, 250), Point(665, 600), black, 2, 8, 0);
		cv::rectangle(origin, Point(670, 250), Point(755, 600), black, 2, 8, 0);

		Rect rect1(50, 220, 85, 400);
		Rect rect2(140, 220, 85, 400);
		Rect rect3(230, 220, 85, 400);
		Rect rect4(490, 220, 85, 400);
		Rect rect5(580, 220, 85, 400);
		Rect rect6(670, 220, 85, 400);

		//Finds all contours in the six segments of the plate
		findContours(test(rect1), holdscontours1, holdsorder1, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (int i = 0; i < holdscontours1.size(); i++) {
			drawContours(origin, holdscontours1, i, blue, 2, 8, holdsorder1, 0, Point(50, 220));
		}
		findContours(test(rect2), holdscontours2, holdsorder2, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (int i = 0; i < holdscontours2.size(); i++) {
			drawContours(origin, holdscontours2, i, blue, 2, 8, holdsorder2, 0, Point(140, 220));
		}
		findContours(test(rect3), holdscontours3, holdsorder3, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (int i = 0; i < holdscontours3.size(); i++) {
			drawContours(origin, holdscontours3, i, blue, 2, 8, holdsorder3, 0, Point(230, 220));
		}
		findContours(test(rect4), holdscontours4, holdsorder4, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (int i = 0; i < holdscontours4.size(); i++) {
			drawContours(origin, holdscontours4, i, blue, 2, 8, holdsorder4, 0, Point(490, 220));
		}
		findContours(test(rect5), holdscontours5, holdsorder5, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (int i = 0; i < holdscontours5.size(); i++) {
			drawContours(origin, holdscontours5, i, blue, 2, 8, holdsorder5, 0, Point(580, 220));
		}
		findContours(test(rect6), holdscontours6, holdsorder6, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
		for (int i = 0; i < holdscontours6.size(); i++) {
			drawContours(origin, holdscontours6, i, blue, 2, 8, holdsorder6, 0, Point(670, 220));
		}

		//Gives a character for each detected segment of the plate
		char one = checkcharacter(templates, holdscontours1);
		char two = checkcharacter(templates, holdscontours2);
		char three = checkcharacter(templates, holdscontours3);
		char four = checkcharacter(templates, holdscontours4);
		char five = checkcharacter(templates, holdscontours5);
		char six = checkcharacter(templates, holdscontours6);

		//Converts the six characters to a string and sets the string as the decision text
		string str = std::string() 
			+ one + ' '
			+ two + ' '
			+ three + ' '
			+ four + ' '
			+ five + ' '
			+ six;
		QString qstr2 = QString::fromStdString(str);
		outputGUI.setDecision(qstr2);

		//Converts cv colored image to QImage
		Mat destTire;
		cvtColor(origin, destTire, CV_BGR2RGB);
		QImage imTire(
			(uchar*)destTire.data,
			destTire.cols,
			destTire.rows,
			QImage::Format_RGB888
		);
		//Sets the QImage as the right photo in the output GUI
		outputGUI.setLeftPhoto(imTire);

		//Converts cv binary image to greyscale QImage
		QImage imDet(
			(uchar*)test.data,
			test.cols, test.rows,
			QImage::Format_Grayscale8
		);
		//Sets the QImage as the right photo in the output GUI
		outputGUI.setRightPhoto(imDet);

		//Converts the CV::String filename to a Qt::QString
		String cvs = fn[j];
		string stds = cvs.operator std::string();
		QString qstr = QString::fromStdString(stds);

		//Displays a message box signaling file has been successfully scanned
		QMessageBox::information
		(
			gui,
			GUI::tr("Image Scanned"),
			qstr + " successfully scanned. Click OK to proceed to next image"
		);
	}

	//Displays a message box signaling folder scan has been completed
	QMessageBox::information(
		gui,
		GUI::tr("Completed"),
		"Folder scan completed"
	);
}
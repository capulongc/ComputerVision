//#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include <stdint.h>
#include "GUI.h"
#include "OutputGUI.h"
#include <string>

using namespace cv;
using namespace std;

//Checks if point is with the bounds of a circle
//INPUT:  Vector of Vec3f objects containing the location of a point
//		  Vector of Vec3f objects containing the location of the boundary of a circle
//OUTPUT: Boolean
//		  TRUE if the point falls inside the circle
//		  FALSE if the point falls outisde the circle
bool checkdistance(Vec3i a, Vec3i b) {
	int radius = b[2] * b[2];
	int x = a[0];
	int y = a[1];
	int cirx = b[0];
	int ciry = b[1];
	if (((x - cirx)*(x - cirx)) + ((y - ciry)*(y - ciry)) <= (radius*radius)) {
		return true;
	}
	else {
		return false;
	}
}

//Checks if detected lugs fall within boundary of detected rim 
//INPUT:  Vector of Vec3f objects containing the location of the main rim within the given image
//		  Vector of Vec3f objects containing the locations of lugs within the given image
//OUTPUT: Boolean
//		  TRUE if all lugs are within the rim boundary
//		  FALSE if at least one lug falls outside the rim boundary
bool checklugboundary(std::vector<Vec3f>a, std::vector<Vec3f>rim) {
	Vec3i bounds = rim[0];
	std::vector<Vec3f>holder;

	for (int i = 0; i < a.size(); i++) {
		Vec3i lug = a[i];
		if (checkdistance(lug, bounds)) {
			holder.push_back(a[i]);
		}
	}

	if (holder.size() >= 4 && holder.size() <= 6) {
		return true;
	}
	else {
		return false;
	}

}

//Checks if the detected lugs are in a circular pattern
//INPUT:  Mat object containing an image with dimensions 800x800px
//		  Vector of Vec3f objects containing the location of the main rim within the given image
//		  Vector of Vec3f objects containing the locations of lugs within the given image
//OUTPUT: Boolean
//		  TRUE if lugs and rims are circular
//		  FALSE if lugs and rims are not circular
bool checkcircular(std::vector < Vec3f>something, Mat somename, std::vector<Vec3f>rim) {
	float radius = rim[0][2] * .45;
	int xcounter = 0;
	int ycounter = 0;
	std::vector<Vec3f>holder;

	for (int i = 0; i < something.size(); i++) {
		Vec3i a = something[i];
		xcounter += a[0];
		ycounter += a[1];
	}

	int xmean = xcounter / something.size();
	int ymean = ycounter / something.size();

	Point center = Point(xmean, ymean);

	circle(somename, center, radius, Scalar(0, 100, 100), 3, LINE_AA);

	Vec3i circlecheck = { xmean,ymean,(int)radius };

	for (int i = 0; i < something.size(); i++) {
		Vec3i a = something[i];
		if (checkdistance(a, circlecheck)) {
			holder.push_back(something[i]);
		}

	}

	if (holder.size() > 4) {
		return true;
	}
	else {
		return false;
	}

}

//Checks for a rim in the given image
//INPUT: Mat object containing an image with dimensions 800x800px
//OUTPUT: Vector of Vec3f objects containing the location of the main rim within the given image
std::vector<Vec3f> detectrim(Mat somename) {					
	for (int i = 100; i < 130; i++) {
		std::vector<Vec3f>something;
		HoughCircles(somename, something, HOUGH_GRADIENT, 1.2, 300, 255, i, 50, 350);
		if (something.size() == 1) {
			return something;
		}
	}

	std::vector<Vec3f>fake;
	HoughCircles(somename, fake, HOUGH_GRADIENT, 1.2, 300, 255, 255, 50, 350);

	return fake;
}

//Checks for lugs within the given image
//INPUT: Mat object containing an image with dimensions 800x800px
//OUTPUT: Vector of Vec3f objects containing the locations of lugs within the given image
std::vector<Vec3f> detectlugs(Mat somename) {
	for (int i = 30; i < 47; i++) {
		std::vector<Vec3f>something;
		HoughCircles(somename, something, HOUGH_GRADIENT, 1.5, 45, 255, i, 10, 30);
		if (something.size() >= 4 && something.size() <= 6) {
			return something;
		}
	}

	std::vector<Vec3f>fake;

	HoughCircles(somename, fake, HOUGH_GRADIENT, 1.5, 40, 255, 255, 10, 30);
	return fake;
}

void checkprint(std::vector<Vec3f>something) {					//For debugging purposes 
	for (int i = 0; i < something.size(); i++) {
		Vec3i lug = something[i];
		cout << lug[0] << "\t" << lug[1] << endl;
	}
	cout << endl;
}

//Uses the coordinates in the Vec3f vector to draw circles around necessary objects
//in the given image
//INPUT: Mat object containing an image with dimensions 800x800px
//		 Empty vector of Vec3f objects
//OUTPUT: VOID
void drawCircles(Mat somename, std::vector<Vec3f>something) {
	for (int i = 0; i < something.size(); i++) {
		Vec3i circles = something[i];
		Point center = Point(circles[0], circles[1]);
		circle(somename, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		int radius = circles[2];
		circle(somename, center, radius, Scalar(0, 0, 255), 10, LINE_AA);
	}

}

//Downsizes image to exactly 800x800px
//INPUT: Mat object containing an image larger than 800x800px
//OUTPUT: Mat object containing an image with dimensions of exactly 800x800px
Mat preprocess(Mat something) {
	Size preproccess(800, 800);
	resize(something, something, preproccess);


	return something;
}

//Checks if an image is large enough
//INPUT: Mat object containing an image
//OUTPUT: Boolean
//		  TRUE if image dimensions are greater than 800x800px
//		  FALSE if image dimensions are not greater than 800x800px
bool checkImageSize(Mat something) {
	int rowscounter = something.rows;
	int colscounter = something.cols;

	if (rowscounter < 800 && colscounter < 800) {
		return false;
	}

	else {
		return true;
	}
}



//MAIN BLOCK OF CODE
//INPUT:QString containing the folder directory containing images
//		GUI object of the main parent GUI
//OUTPUT: Second GUI containing two images and a decision text
void tireDetection(QString folderLocation, GUI *const gui)
{
	//Displays the output GUI containing two photos and the decision text
	OutputGUI outputGUI;
	outputGUI.show();

	//Creates three vectors to hold filenames, photos of tires, and binary images
	std::vector<String> fn;
	std::vector<Mat> tires;
	std::vector<Mat> detects;
	string 	path = folderLocation.toLocal8Bit();

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
		Mat image = imread(fn[i], CV_LOAD_IMAGE_COLOR);
		Mat imageD = imread(fn[i], CV_LOAD_IMAGE_GRAYSCALE);

		if (image.empty()) continue;
		tires.push_back(image);
		detects.push_back(imageD);
	}

	//Iterates through image vectors and performs necessary scans
	for (size_t j = 0; j < detects.size(); j++)
	{
		Mat tire = tires[j];
		Mat detect = detects[j];

		//Checks if the image is at least 800x800px
		//If true performs scans
		//If false returns an error message
		if (checkImageSize(tire)) {

			//Resizes the colored and binary photos to 800x800px
			tire = preprocess(tire);
			detect = preprocess(detect);

			medianBlur(detect, detect, (9, 9));

			Canny(detect, detect, 100, 300, 3);

			std::vector<Vec3f>outrim;
			std::vector<Vec3f>lugs;

			outrim = detectrim(detect);
			drawCircles(tire, outrim);

			lugs = detectlugs(detect);
			drawCircles(tire, lugs);

			if (outrim.size() > 0) {

				if (checklugboundary(lugs, outrim) && checkcircular(lugs, tire, outrim)) {
					//Sets the output GUI decision text to indicate image is a tire
					outputGUI.setDecision("This is a tire");
				}
				else {
					//Sets the output GUI decision text to indicate image is not a tire
					outputGUI.setDecision("This is not a tire");
				}

			}
			else {
				//Sets the output GUI decision text to indicate image is not a tire
				outputGUI.setDecision("This is not a tire");
			}

			//Converts cv colored image to QImage
			Mat destTire;
			cvtColor(tire, destTire, CV_BGR2RGB);
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
				(uchar*)detect.data,
				detect.cols, detect.rows,
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

		else
		{
			//Converts the CV::String filename to a Qt::QString
			String cvs = fn[j];
			string stds = cvs.operator std::string();
			QString qstr = QString::fromStdString(stds);

			//Displays a message box signaling file could not be scanned due to insufficient photo size
			QMessageBox::warning
			(
				gui,
				GUI::tr("Image Not Scanned"),
				qstr + " could not be scanned. Image must have a resolution value of at least 800 pixels."
			);
		}

	}

	//Displays a message box signaling folder scan has been completed
	QMessageBox::information(
		gui,
		GUI::tr("Completed"),
		"Folder scan completed"
	);
}
#include "opencv2\opencv.hpp"
#include <stdint.h>
#include "GUI.h"
#include "OutputGUI.h"
#include <string>

using namespace cv;
using namespace std;

void shapeDetection(QString folderLocation, GUI *const gui)
{
	//Displays the output GUI containing two photos and the decision text
	OutputGUI outputGUI;
	outputGUI.show();

	//Stores a vector of strings of filenames
	std::vector<String> fn;
	//This creates a vector of image object of the original inputed images.
	std::vector<Mat> shapes;
	//This creates a vector of image objects of the binary images
	std::vector<Mat> detects;
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

	for (size_t i = 0; i < fn.size(); i++)
	{
		Mat image = imread(fn[i], CV_LOAD_IMAGE_COLOR);
		//This creates an image object of the original inputed image.

		Mat imageD = imread(fn[i], CV_LOAD_IMAGE_GRAYSCALE);
		//Creates a file object that is grayscaled, but otherwise identical to the last object

		if (image.empty()) continue;
		//skips empty images

		shapes.push_back(image);
		//Adds the object to the vector

		detects.push_back(imageD);
		//adds the object to the binary vector

	}

	for (size_t j = 0; j < detects.size(); j++)
	{
		//The "size" object just takes in two numbers to represent the size of a matrix
		Size size(800, 800);

		//Resizes images
		Mat shape = preprocess(shapes[j]);
		Mat detect = preprocess(detects[j]);

		//Creates an object for the rescaled images
		Mat shapeScaled;
		Mat detectScaled;

		//Debugging line, vector to track contours
		std::vector <std::vector<Point>> contours;

		//Vector that stores a variable for the thresholding method
		std::vector<Vec4i> hierarchy;

		//Put the resized image in the new image objects
		cv::resize(shape, shapeScaled, size);
		cv::resize(detect, detectScaled, size);

		//Blurs the grayscaled image to reduce artifacts on the image
		medianBlur(detectScaled, detectScaled, (9, 9));

		//Set threshold and maxValue
		double thresh = 100;
		double maxValue = 255;

		//Binary Threshold
		Mat weeabooFactor;

		//Creates the binary image
		threshold(detectScaled, weeabooFactor, thresh, maxValue, THRESH_BINARY);

		//imshow("binary", weeabooFactor); debugging line
		Canny(weeabooFactor, weeabooFactor, 50, 200, 3);

		//This vector stores the coordinates for the lines detected by the hough line transformation
		std::vector<Vec4i> lines;

		//Detects edges of shapes
		HoughLinesP(weeabooFactor, lines, 2, CV_PI / 180, 250, 100, 10);

		for (size_t i = 0; i < lines.size(); i++)
		{
			//Draws lines along the detected images
			Vec4i l = lines[i];
			line(
				shapeScaled,
				Point(l[0], l[1]),
				Point(l[2], l[3]),
				Scalar(0, 0, 255),
				3,
				CV_AA
			);
		}

		//Uses the number of edges to figure out the shape
		//Sets the output GUI decision text to indicate which shape the image resembles
		if (lines.size() < 3 && lines.size() > 0)
		{
			//If there are 1 or 2 edges then the object is not a shape.
			/*If there are 0 edges detected then the program will attempt to check
			if the image is actually a circle*/

			//Sets the output GUI decision text to indicate image is not a shape
			outputGUI.setDecision("This is not a shape");
		}
		else if (lines.size() == 3) {
			outputGUI.setDecision("This is a triangle");
		}
		else if (lines.size() == 4) {
			outputGUI.setDecision("This is a square");
		}
		else if (lines.size() == 5) {
			outputGUI.setDecision("This is a pentagon");
		}
		else if (lines.size() == 6) {
			outputGUI.setDecision("This is a hexagon");
		}
		else if (lines.size() == 7) {
			outputGUI.setDecision("This is a heptahon");
		}
		else if (lines.size() == 8) {
			outputGUI.setDecision("This is an octagon");
		}
		else if (lines.size() == 9) {
			outputGUI.setDecision("This is a nonagon");
		}
		else if (lines.size() == 10) {
			outputGUI.setDecision("This is a decagon");
		}
		else if (lines.size() == 11) {
			outputGUI.setDecision("This is a undecagon");
		}
		else if (lines.size() == 12) {
			outputGUI.setDecision("This is a dodecagon");
		}
		else if (lines.size() > 12 && lines.size()) {
			QString qstr;
			qstr += "This is a ";
			qstr += lines.size();
			qstr += "-gon";
			outputGUI.setDecision(qstr);
		}
		else {
			std::vector<Vec3f> conversationalJapanese;
			//Checks for a circle
			HoughCircles(
				detectScaled,
				conversationalJapanese,
				CV_HOUGH_GRADIENT,
				1,
				detectScaled.rows / 8, 200, 50, 0, 0
			);
			if (conversationalJapanese.size() == 1) {
				//If circle is found
				//Sets the outputGUI text to signal image is a circle
				outputGUI.setDecision("This is a circle");
			}
			else {
				//Sets the outputGUI text to signal image is not a shape
				outputGUI.setDecision("This is not shape");
			}
		}

		//Converts the cv colored image to a QImage
		Mat destShape;
		cvtColor(shape, destShape, CV_BGR2RGB);
		QImage imShape(
			(uchar*)destShape.data,
			destShape.cols,
			destShape.rows,
			QImage::Format_RGB888
		);
		//Sets the QImage as the left photo in the output GUI
		outputGUI.setLeftPhoto(imShape);


		//Converts the cv binary image to a  greyscale QImage
		QImage imDet(
			(uchar*)weeabooFactor.data,
			weeabooFactor.cols,
			weeabooFactor.rows,
			QImage::Format_Grayscale8
		);
		//Sets the QImage as the right photo in the output GUI
		outputGUI.setRightPhoto(imDet);


		//Converts the CV::String filename to a Qt::QString
		String cvs = fn[j];
		string stds = cvs.operator std::string();
		QString qstr = QString::fromStdString(stds);

		//Displays a message box showing the image's filename and location
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
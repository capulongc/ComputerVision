#include "GUI.h"
#include "OutputGUI.h"

using namespace cv;
using namespace std;

Mat mainColorDet;
QString mainColorName;

//Compares the number of detected pixels in each pixel count and finds the main color of the image
//INPUT:  Vector of integers containing the number of found pixels for each color
//		  Vector of Mat images containing the binary display of found pixels vs not found pixels
//OUTPUT: VOID
void findMainColor(std::vector<int> colorCounts,
	std::vector<Mat> detImages)
{
	int maxNum = 0;
	int maxNumIndex = 0;

	//Iterates through pixel color count array and finds greatest integer value
	for (size_t i = 0; i < colorCounts.size(); i++)
	{
		if (colorCounts[i] > maxNum)
		{
			maxNum = colorCounts[i];
			maxNumIndex = i;
		}
	}
	mainColorDet = detImages[maxNumIndex];

	//Sets color name variable to match primary image in photo
	cout << maxNumIndex;
	if (maxNumIndex == 0)
		mainColorName = "black";
	else if (maxNumIndex == 1)
		mainColorName = "red";
	else if (maxNumIndex == 2)
		mainColorName = "green";
	else if (maxNumIndex == 3)
		mainColorName = "blue";
	else if (maxNumIndex == 4)
		mainColorName = "yellow";
	else if (maxNumIndex == 5)
		mainColorName = "purple";
	else if (maxNumIndex == 6)
		mainColorName = "blue";
	else if (maxNumIndex == 7)
		mainColorName = "pink";
}

void colorDetection(QString folderLocation, GUI *const gui)
{
	//Displays the output GUI containing two photos and the decision text
	OutputGUI outputGUI;
	outputGUI.show();

	//Creates two vectors to hold filenames and photos of colored images
	std::vector<String> fn;
	std::vector<Mat> color;
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
	//Loads a colored image and adds to vector
	for (size_t i = 0; i < fn.size(); i++)
	{
		Mat image = imread(fn[i], CV_LOAD_IMAGE_COLOR);

		if (image.empty()) continue;
		color.push_back(image);
	}

	//Iterates through image vectors and performs necessary scans
	for (size_t j = 0; j < color.size(); j++)
	{
		Mat coloredImage = color[j];
		std::vector<Mat> detects;
		std::vector<int> colorPixelCounts;

		//Creates a second binary image counting the number of black pixels
		Mat checkBlack;
		inRange(coloredImage, Scalar(0, 0, 0), Scalar(20, 20, 20), checkBlack);
		int numBlack = countNonZero(checkBlack);
		detects.push_back(checkBlack);
		colorPixelCounts.push_back(numBlack);

		//Creates a second binary image counting the number of red pixels
		Mat checkRed;
		inRange(coloredImage, Scalar(10, 10, 100), Scalar(150, 150, 256), checkRed);
		int numRed = countNonZero(checkRed);
		detects.push_back(checkRed);
		colorPixelCounts.push_back(numRed);

		//Creates a second binary image counting the number of green pixels
		Mat checkGreen;
		inRange(coloredImage, Scalar(10, 100, 10), Scalar(150, 256, 150), checkGreen);
		int numGreen = countNonZero(checkGreen);
		detects.push_back(checkGreen);
		colorPixelCounts.push_back(numGreen);

		//Creates a second binary image counting the number of blue pixels
		Mat checkBlue;
		inRange(coloredImage, Scalar(100, 100, 10), Scalar(256, 256, 150), checkBlue);
		int numBlue = countNonZero(checkBlue);
		detects.push_back(checkBlue);
		colorPixelCounts.push_back(numBlue);

		//Creates a second binary image counting the number of yellow pixels
		Mat checkYellow;
		inRange(coloredImage, Scalar(10, 100, 100), Scalar(150, 256, 256), checkYellow);
		int numYellow = countNonZero(checkYellow);
		detects.push_back(checkYellow);
		colorPixelCounts.push_back(numYellow);

		//Creates a second binary image counting the number of purple pixels
		Mat checkPurple;
		inRange(coloredImage, Scalar(100, 10, 100), Scalar(255, 150, 255), checkPurple);
		int numPurple = countNonZero(checkPurple);
		detects.push_back(checkPurple);
		colorPixelCounts.push_back(numPurple);

		//Creates a second binary image counting the number of cyan pixels
		Mat checkCyan;
		inRange(coloredImage, Scalar(100, 10, 10), Scalar(255, 255, 150), checkCyan);
		int numCyan = countNonZero(checkCyan);
		detects.push_back(checkCyan);
		colorPixelCounts.push_back(numCyan);

		//Creates a second binary image counting the number of pink pixels
		Mat checkPink;
		inRange(coloredImage, Scalar(50, 10, 100), Scalar(200, 150, 256), checkPink);
		int numPink = countNonZero(checkPink);
		detects.push_back(checkPink);
		colorPixelCounts.push_back(numPink);

		//Finds primary color in image
		findMainColor(colorPixelCounts, detects);

		//Resizes the colored and binary photos to 800x800px
		coloredImage = preprocess(coloredImage);
		mainColorDet = preprocess(mainColorDet);

		//Sets decision text in GUI to indicate primary color
		QString qstr1;
		qstr1 += "This image is primarily ";
		qstr1 += mainColorName;
		outputGUI.setDecision(qstr1);

		//Converts cv colored image to QImage
		Mat destImg;
		cv::cvtColor(coloredImage, destImg, CV_BGR2RGB);
		QImage imImg(
			(uchar*)destImg.data,
			destImg.cols,
			destImg.rows,
			QImage::Format_RGB888
		);
		//Sets the QImage as the right photo in the output GUI
		outputGUI.setLeftPhoto(imImg);

		//Converts cv binary image to greyscale QImage
		QImage imDet(
			(uchar*)mainColorDet.data,
			mainColorDet.cols,
			mainColorDet.rows,
			QImage::Format_Grayscale8
		);
		//Sets the QImage as the right photo in the output GUI
		outputGUI.setRightPhoto(imDet);

		///Displays a message box signaling file has been successfully scanned
		//Converts the CV::String filename to a Qt::QString
		String cvs = fn[j];
		string stds = cvs.operator std::string();
		QString qstr = QString::fromStdString(stds);
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
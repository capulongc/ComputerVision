#include "GUI.h"
#include "OutputGUI.h"

void loadXML(
	dlib::array<array2d<unsigned char> >& a,
	std::vector<std::vector<dlib::rectangle> >& b,
	const string& str
)
{
	load_image_dataset(a, b, str);
}

void faceDetection(QString folderLocation, GUI *const gui)
{
	//Displays the output GUI containing two photos and the decision text
	OutputGUI outputGUI;
	outputGUI.show();

	QMessageBox::information(gui, GUI::tr("Test"), "Checkpoint 1");

	try
	{
		const string dir = folderLocation.toLocal8Bit();

		//This array holds the image training set and the image testing set
		dlib::array<array2d<unsigned char>> imageTrain;
		dlib::array<array2d<unsigned char>> imageTest;
		//This vector holds the box locations for the data we are training and the data the NN finds similar to the trained data
		std::vector<std::vector<dlib::rectangle>> faceBoxTrain;
		std::vector<std::vector<dlib::rectangle>> faceBoxLocal;

		//Here we find the image set that has all the image locations
		//This particuler one also has the boxes to train
		load_image_dataset(imageTrain, faceBoxTrain, dir + "/mydataset.xml");

		QMessageBox::information(gui, GUI::tr("Test"), "Checkpoint 3");

		//This particular one is the set we are testing and attemping to find faces
		loadXML(imageTest, faceBoxLocal, dir + "/testset.xml");


		//Here we are doubling our training set by making another group of images from our original training set that is mirrored
		//Since faces are symetrical for the most part, this 
		add_image_left_right_flips(imageTrain, faceBoxTrain);

		cout << "Number of training images: " << imageTrain.size() << endl;
		cout << "Number images being tested: " << imageTest.size() << endl;


		//Here we have to create the type hog Scanner, This makes a box scan that moves through the images pixel by pixel to examine them and get
		//Gradients for each segments
		typedef scan_fhog_pyramid<pyramid_down<4> > hogScanner;

		hogScanner scanner;

		//EDIT this ------- Value to find the best property for the size of each cell scan 
		scanner.set_detection_window_size(80, 80);

		//This regularize can be used in certain image types that might have more drastic differences
		//scanner.set_nuclear_norm_regularization_strength(1.0);


		//This is our actually object trainer
		//It teaches our NN to detected something from the provided images in my data set
		structural_object_detection_trainer<hogScanner> trainer(scanner);

		//This changes the number of cores used to run this program, change this if you are having issues
		trainer.set_num_threads(4);

		//EDIT this ------- Value to find the best property for the SVM C parameter
		trainer.set_c(2);
		trainer.be_verbose();

		//This is the rsik gap for the SVM. A 0.01 risk is accurate enough
		trainer.set_epsilon(0.01);

		//Match threshold
		trainer.set_match_eps(0.5);

		//Outputs the training process. Letting us check the weights, thresholds, success rates, and learning rates
		object_detector<hogScanner> detector = trainer.train(imageTrain, faceBoxTrain);

		//These output our final results
		cout << "training results: " << test_object_detection_function(detector, imageTrain, faceBoxTrain) << endl;

		cout << "testing results:  " << test_object_detection_function(detector, imageTest, faceBoxLocal) << endl;


		//Displays the learned histogram of oriented gradients
		image_window hogwin(draw_fhog(detector), "Learned fHOG detector");

		image_window win;

		//Loops through every windows and illustrates the found boxes
		for (unsigned int i = 0; i < imageTest.size(); ++i)
		{
			//Displays the boxes
			std::vector<dlib::rectangle> dets = detector(imageTest[i]);
			win.clear_overlay();

			//Sets the window to the image
			win.set_image(imageTest[i]);

			//Illustrates the boxes
			win.add_overlay(dets, rgb_pixel(0, 255, 0));
			cout << "Hit enter to process the next image..." << endl;
			cin.get();

		}
	}
	catch (exception& e)
	{

		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;

	}
}

# ComputerVision
Computer vision software written with C++ using OpenCV, dlib, and QT

**Developed by:**
* Samuel Cuervo
* Calvin Capulong
* Stephen Thomas

**Created March/April 2018**

**Uploaded January 2020**

QT and OpenCV Computer vision software designed to detect shapes, colors, and license plate numbers.
A seperate part of the project uses dlib to train a neural network to detect faces in still images

# OpenCV
OpenCV library provides computer vision technologies to detect gradients and edges on images. Below is a quote about OpenCV from our original design document:

*OpenCV offers some rudimentary functions on detecting lines and circles which we tried to extrapolate into shape detection, license plate recognition, and tire detection. For shape detection we learned to detect the number of sides of the shape, however the shape had to be a solid color or else there would be errors. We decided this would be the best approach, regardless of errors, for the only other conceivable way to detect shapes would be by counting the vertices drawn by contours, however this did not produce a consistent result. For license plate recognition we used contours to track the shape of each character and compared it to a pre-generated stock of the characters to see what it matches. Unsure of the proper method for creating and comparing templates, we ran each alphanumeric character through our image preprocessing, and saved its resulting data in the form of a vector. This greatly reduced compilation time compared to processing each alphanumeric character at runtime. For tire recognition we used circle detection, to detect the rim and lug nuts. The lesson to take from all of this is that while OpenCV is an easy to manipulate library, but it is very basic and not great at its job. Even the OpenCV documentation admits this. However, we still learned the basics of image processing by looking at how the methods that OpenCV uses works.*

# DLib
Seperately, dlib generates a convolutional neural network that uses supervised learning to train from provided photos with faces marked. Below is a quote about dlib from our original design document:

*Dlib introduces machine learning into the process of image detection. Through the neural network framework provide by dlib, we can create a histogram of oriented gradient. This histogram is the gradients of change when the image is gray scaled. The image is scanned in a 8 by 8 scanner that finds the gradient for that group. We then use a 3 by 3 kernel that runs through each pixel in a x direction and in a y direction. Both images affected by kernels are combined to create a gradient of change that we can use to find image similarities. The neural net runs through the provided images to learn the HOG and apply to images to find similarities. It then checks it's error percentage and that way determines if the image is similar. With dlib, we found the process was mainly dependent on the accuracy of the learning process of the neural net. We had a few items we could change like the weights and threshold and learning rate to provide a faster finally HOG. We also are able to adjust the error threshold and the SVM C parameter. We found the best C parameter for our faces was that of 2, a higher trade off from training errors and testing errors. This parameter mixed with our epsilon size was the perfect amounts for accurate face detection, even at awkward angles. Last thing to mention, we came up with the idea of mirroring our images (since faces are symmetrical) to double our training data and create a more accurate HOG filter. All of these factors combined creates our very accurate face detector.*

# QT
QT library provides the tools to create a nice looking UI. Below is a quote about QT from our original design document:

*We used the QT library in order to help us build our GUI. The visual portion of the GUI can be made using the Qt Designer, which allows one to drag and drop buttons, displays, or widgets to take in user input. Those aspects added in then have to be connected to a “slot” that holds a method. The slot is then activated whenever a certain signal goes off. The main benefit from using QT is that it is made for creating and manipulating visual aspect of your program and so it has many useful additions. The Qt Designer, for example, is a great aid as being able to drag and drop allows one to see changes instantly and build the window with ease, which helps one seperate the GUI from the methods and organize the program. It also makes resizing buttons, images, or the entire window much easier than if one were building it from scratch. Ultimately, programming using this library taught us the connection between the user’s screen and the code. We learned more about how to combine the two and how they work in harmony to make a cohesive program.*

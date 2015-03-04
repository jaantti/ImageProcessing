// ImageProcessing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/photo/photo.hpp"
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ofstream outFile;

	namedWindow("Video", 1);

	int exposure = 8;
	createTrackbar("Exposure", "Video", &exposure, 15);

	int canny = 0;
	createTrackbar("Canny", "Video", &canny, 1);

	int binThresh = 0;
	createTrackbar("Binary threshhold", "Video", &binThresh, 1);

	int thresh = 127;
	createTrackbar("Thresh", "Video", &thresh, 255);

	int min = 10;
	createTrackbar("Min", "Video", &min, 255);

	int max = 100;
	createTrackbar("Max", "Video", &max, 255);

	//VideoCapture cap("C:\\Users\\t420s\\Dropbox\\Image processing\\v2.mkv");
	VideoCapture cap(0);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 800);
	
	Mat first;
	cap.read(first);
	Mat frame, prevFrame;
	cap.read(prevFrame);
	//Size size(1280, 720);
	cout << "Open: " << cap.isOpened();
	while (cap.read(frame)){
		double exp = exposure / 100.0;
		cap.set(CV_CAP_PROP_EXPOSURE, -exposure);
		//cap.read(frame);
		char key = (char)waitKey(5);
		if (key == 'n') frame.copyTo(first);
		frame = frame - first;
		//bitwise_or(prevFrame, frame, frame);
		frame.copyTo(prevFrame);
		cvtColor(frame, frame, CV_BGR2GRAY);		
		flip(frame, frame, -1);
		GaussianBlur(frame, frame, Size(11, 11), 0);
		//resize(frame, frame, size);
		if (binThresh) threshold(frame, frame, thresh, 255, CV_THRESH_BINARY);
		//goodFeaturesToTrack(frame, frame, min, 0.1, 0.1);
		if (canny) Canny(frame, frame, min, max);
		//equalizeHist(frame, frame);
		imshow("Video", frame);
		//waitKey(0);
		if (waitKey(5) == 27) break;
		
	}
	outFile.open("data.txt");
	outFile << "thresh: " << getTrackbarPos("Thresh", "Video") << ", min: " << getTrackbarPos("Min", "Video") << ", max: " << getTrackbarPos("Max", "Video") << endl;
	outFile.close();
	//cout << "thresh: " << thresh << ", min: " << min << ", max: " << max << endl;
	//waitKey(0);
	return 0;
}


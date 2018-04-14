//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//
//using namespace std;
//using namespace cv;
//
//
//int main()
//{
//	// My var.
//	const double STRIP_WIDTH = 0.6;
//	const int FRAME_SAMPLING_RATE = 8;
//
//	const int START_FRAME = 115;
//	const int END_FRAME = 329;
//
//	// To measure the time elapsed.
//	clock_t startTime, endTime;
//	startTime = clock();
//
//	// Source video
//	string filename = "input/mountain.mov";
//	VideoCapture video(filename);
//
//	// Check if exist.
//	if (!video.isOpened())
//	{
//		cout << "Error when reading the video file..";
//		return -1;
//	}
//
//	// Stitcher parameters.
//	bool try_use_gpu = true;
//	Stitcher::Mode mode = Stitcher::PANORAMA;
//
//	// For hold the relevant frame/s.
//	vector<Mat> leftArr, rightArr;
//	Mat tempFrame;
//	Mat leftPano;
//	Mat rightPano;
//	Mat leftRrightPano;
//
//	// Get info from source video.
//	int frameCount = video.get(CV_CAP_PROP_FRAME_COUNT);
//
//	// Height and width are Opposite - Because the video is tilted 90 degrees.
//	int height = video.get(CV_CAP_PROP_FRAME_WIDTH);
//	int width = video.get(CV_CAP_PROP_FRAME_HEIGHT);
//
//	// Create strips size.
//	Rect rectLeft(Point(width / 4 - (STRIP_WIDTH * width / 2), 0), Point(width / 4 + (STRIP_WIDTH * width / 2), height));
//	Rect rectRight(Point(width / 4 * 3 - (STRIP_WIDTH * width / 2), 0), Point(width / 4 * 3 + (STRIP_WIDTH * width / 2), height));
//
//	// Fill selected strips into arrays.
//	for (int i = 0; i < frameCount; i++)
//	{
//		video >> tempFrame;
//
//		if (i >= START_FRAME && i <= END_FRAME && i % FRAME_SAMPLING_RATE == 0)
//		{
//			rotate(tempFrame, tempFrame, 0);
//
//			leftArr.push_back(tempFrame.clone()(rectLeft));
//
//			rightArr.push_back(tempFrame.clone()(rectRight));
//		}
//	}
//
//	cout << "Number of frame = " << leftArr.size() << endl;
//	cout << "Strip size = " << STRIP_WIDTH << endl;
//
//	// Stitching all frames into one panorama.
//	Ptr<Stitcher> stitcher = Stitcher::create(mode, try_use_gpu);
//	Stitcher::Status status;
//
//	cout << "Stitching left panorama..." << endl;
//	status = stitcher->stitch(leftArr, leftPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch frames in leftArr, error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	cout << "Stitching right panorama..." << endl;
//	status = stitcher->stitch(rightArr, rightPano);
//	if (status != Stitcher::OK)
//	{
//		cout << "Can't stitch frames in rightArr, error code = " << int(status) << endl;
//		system("pause");
//		return -1;
//	}
//
//	// Makes the panorama images same size if needed.
//	if (leftPano.size < rightPano.size)
//		resize(rightPano, rightPano, leftPano.size());
//	else if (rightPano.size < leftPano.size)
//		resize(leftPano, leftPano, rightPano.size());
//
//	// vertical concatenation.
//	vconcat(leftPano, rightPano, leftRrightPano);
//
//	// add red cyan by code.
//
//
//
//	// Save results to computer.
//	imwrite("output/leftPano.jpg", leftPano);
//	imwrite("output/rightPano.jpg", rightPano);
//	imwrite("output/leftRrightPano.jpg", leftRrightPano);
//
//	// Print time elapsed.
//	endTime = clock();
//	cout << "Total time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " Sec" << endl;
//
//	system("pause");
//	return 0;
//
//} // End main.
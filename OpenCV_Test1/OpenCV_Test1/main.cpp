#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat srcImg = imread("C:\\Users\\bafs\\Downloads\\picture1.png");
	if (srcImg.empty()) 
	{
		cout << "could not load image,please check your code..." << endl;
		return -1;
	}
	Mat dst;
	cvtColor(srcImg, dst, CV_BGR2GRAY);
	imshow("Test", srcImg);
	threshold(dst, dst, 100, 255, CV_THRESH_BINARY);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy; 
	findContours(dst, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	vector<Rect> boundRect(contours.size());  //������Ӿ��μ���
	vector<RotatedRect> box(contours.size()); //������С��Ӿ��μ���
	Point2f rect[4];
	Mat show;
	show = srcImg.clone();
	for (int i = 0; i < contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));  //����ÿ��������С��Ӿ���
		boundRect[i] = boundingRect(Mat(contours[i]));
		circle(show, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //������С��Ӿ��ε����ĵ�
		box[i].points(rect);  //����С��Ӿ����ĸ��˵㸴�Ƹ�rect����
		rectangle(show, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		for (int j = 0; j < 4; j++)
		{
			line(show, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //������С��Ӿ���ÿ����
		}
	}
	imshow("dst", show);
	waitKey(0);
	return(0);
}
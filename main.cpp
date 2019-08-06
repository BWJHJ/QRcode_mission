/****************************
The recognition method of QRcode is not robost enough for all circumstances.
****************************/

#include <iostream>
#include <opencv2/opencv.hpp>  
#include <opencv2/xfeatures2d.hpp>
#include <time.h>
using namespace cv;
using namespace std; 

RNG rng(12345);

Mat get(Mat img_src);
int Find_Part_Position(Mat image);

int main()
{
	Mat img_a = imread("C:\\Users\\bafs\\Desktop\\1��\\a.jpg");
	Mat src_a = get(img_a);
	//imwrite("H:\\COMB\\IARC\\QR code\\try5\\a.jpg",src_a);

	Mat img_b = imread("C:\\Users\\bafs\\Desktop\\1��\\b.jpg");
	Mat src_b = get(img_b);
	////imwrite("H:\\COMB\\IARC\\QR code\\try5\\b.jpg",src_b);

	Mat img_c = imread("C:\\Users\\bafs\\Desktop\\1��\\c.jpg");
	Mat src_c = get(img_c);
	////imwrite("H:\\COMB\\IARC\\QR code\\try5\\c.jpg",src_c);

	Mat img_d = imread("C:\\Users\\bafs\\Desktop\\1��\\d.jpg");
	Mat src_d = get(img_d);
	//imshow("img_a", img_a);
	//imshow("img_b", img_b);
	//imshow("img_c", img_c);
	//imshow("img_d", img_d);
	imshow("a", src_a);
	imshow("b", src_b);
	imshow("c", src_c);
	imshow("d", src_d);
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	a = Find_Part_Position(src_a);
	b = Find_Part_Position(src_b);
	c = Find_Part_Position(src_c);
	d = Find_Part_Position(src_d);
	cout << "src_a position is: " << a << endl;
	cout << "src_b position is: " << b << endl;
	cout << "src_c position is: " << c << endl;
	cout << "src_d position is: " << d << endl;
	waitKey(0);
	return 1;
}


Mat get(Mat img_src)
{
	resize(img_src, img_src, Size(4056, 3040));
	pyrDown(img_src, img_src);
	pyrDown(img_src, img_src);
	Mat img_temp = img_src.clone();
	Mat img_bin, img_canny;
	//medianBlur(img_src,img_src,5);//��ֵ�˲�///////////�������!!!!!!!!
	cvtColor(img_src, img_bin, CV_BGR2GRAY);
	threshold(img_bin, img_bin, 120, 255, CV_THRESH_BINARY); //��ֵ��/�������!!!!!!!!
	//imshow("��ֵ��",img_bin);
	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10)); ///////////�������!!!!!!!!
	morphologyEx(img_bin, img_canny, MORPH_CLOSE, element);//������
	Canny(img_canny, img_canny, 200, 300);///////////�������!!!!!!!!

	vector<vector<Point> > contours;
	vector<Vec4i> hierarcy;

	findContours(img_canny, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());  //������Ӿ��μ���
	vector<RotatedRect> box(contours.size()); //������С��Ӿ��μ���
	Point2f rect[4];
	int sxy = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));  //����ÿ��������С��Ӿ���
		boundRect[i] = boundingRect(Mat(contours[i]));
		//���ó�����ѡ���������������
		if (box[i].size.width > 300 || box[i].size.height > 300 || box[i].size.width < 100 || box[i].size.height < 100 || abs(box[i].size.width - box[i].size.height)>20)
			continue;///////////�������!!!!!!!!
		//circle(img_temp, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //������С��Ӿ��ε����ĵ�
		box[i].points(rect);  //����С��Ӿ����ĸ��˵㸴�Ƹ�rect����

		//rectangle(img_temp, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		//for (int j = 0; j < 4; j++)
		//{
		//	line(img_temp, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //������С��Ӿ���ÿ����
		//}
		sxy++;
	}
	//imshow("��С��Ӿ�����ȡ", img_temp);
	//cout<<"num="<<sxy<<endl;

	Point2f srcPoints[4], dstPoints[4];

	//���ĸ���������� �ֳ����� ���� ���� ����(˳ʱ��)
	for (int i = 0; i < 2; i++) {
		for (int j = i + 1; j < 3; j++) {
			if (rect[i].x > rect[j].x)
				swap(rect[i], rect[j]);
		}
	}
	if (rect[0].y < rect[1].y) {
		srcPoints[0] = rect[0];
		srcPoints[1] = rect[1];
	}
	else {
		srcPoints[1] = rect[0];
		srcPoints[0] = rect[1];
	}
	if (rect[2].y > rect[3].y) {
		srcPoints[2] = rect[2];
		srcPoints[3] = rect[3];
	}
	else {
		srcPoints[3] = rect[2];
		srcPoints[2] = rect[3];
	}

	dstPoints[0] = Point2f(0, 0);
	dstPoints[1] = Point2f(0, 400);
	dstPoints[2] = Point2f(400, 400);
	dstPoints[3] = Point2f(400, 0);

	Mat dst = Mat(400, 400, CV_8UC3);
	Mat transMat = getPerspectiveTransform(srcPoints, dstPoints);    //�õ��任����
	warpPerspective(img_bin, dst, transMat, dst.size());    //��������任
	threshold(dst, dst, 120, 255, CV_THRESH_BINARY); //��ֵ��/�������!!!!!!!!
	return dst;
}

int Find_Part_Position(Mat image)
{
	Mat src = image.clone();
	Mat edge=src.clone();
	Mat gray = src.clone();
	//cvtColor(gray, gray, CV_BGR2GRAY);
	//threshold(gray, gray, 40, 255, CV_THRESH_BINARY);
	Canny(gray, edge, 5, 30,3);
	imwrite("Bin.png", gray);
	imshow("edge", edge);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
    findContours(edge, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());  //������Ӿ��μ���

	//draw all the rectangle
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(contours[i]);
		rectangle(src, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
	}
	imshow("All edge", src);
    int ic = 0, parentIdx = -1;

	for (int i = 0; i < contours.size(); i++)
	{
		//�����óߴ�ɸѡ��Ĭ�Ͽ�400*400
		if (boundRect[i].height < 200 || boundRect[i].width < 200)
			continue;
		if (boundRect[i].height > 350 || boundRect[i].width > 350)
			continue;
        //�Ƿ�����Ƕ����
		//����
		if (hierarcy[i][3] != -1)
		{
			parentIdx = i;
			ic++;
			while (hierarcy[parentIdx][3] != -1)
			{
				ic++;
				parentIdx = hierarcy[parentIdx][3];
			}
			if (ic != 2)
				ic = 0;
		}
		//����
		else
		{
			continue;
		}
		if (parentIdx > 0)
		{
			rectangle(src, Point(boundRect[parentIdx].x, boundRect[parentIdx].y), Point(boundRect[parentIdx].x + boundRect[parentIdx].width, boundRect[parentIdx].y + boundRect[parentIdx].height), Scalar(0, 0, 255), 2, 8);
			imshow("dst", src);
		}
		else
			return 0;
		Point tl, br;
		tl = boundRect[parentIdx].tl();
		br = boundRect[parentIdx].br();
		if ((tl.x + br.x) / 2 > 200)
		{
			//����
			if ((tl.y + br.y) / 2 < 200)
				return 1;
			//����
			else
				return 2;
		}
		else
		{
			//����
			if ((tl.y + br.y) / 2 < 200)
				return 3;
			//����
			else
				return 4;
		}
	}
	return 0;
}
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
	Mat img_a = imread("C:\\Users\\bafs\\Desktop\\1米\\a.jpg");
	Mat src_a = get(img_a);
	//imwrite("H:\\COMB\\IARC\\QR code\\try5\\a.jpg",src_a);

	Mat img_b = imread("C:\\Users\\bafs\\Desktop\\1米\\b.jpg");
	Mat src_b = get(img_b);
	////imwrite("H:\\COMB\\IARC\\QR code\\try5\\b.jpg",src_b);

	Mat img_c = imread("C:\\Users\\bafs\\Desktop\\1米\\c.jpg");
	Mat src_c = get(img_c);
	////imwrite("H:\\COMB\\IARC\\QR code\\try5\\c.jpg",src_c);

	Mat img_d = imread("C:\\Users\\bafs\\Desktop\\1米\\d.jpg");
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
	//medianBlur(img_src,img_src,5);//中值滤波///////////参数需调!!!!!!!!
	cvtColor(img_src, img_bin, CV_BGR2GRAY);
	threshold(img_bin, img_bin, 120, 255, CV_THRESH_BINARY); //二值化/参数需调!!!!!!!!
	//imshow("二值化",img_bin);
	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10)); ///////////参数需调!!!!!!!!
	morphologyEx(img_bin, img_canny, MORPH_CLOSE, element);//闭运算
	Canny(img_canny, img_canny, 200, 300);///////////参数需调!!!!!!!!

	vector<vector<Point> > contours;
	vector<Vec4i> hierarcy;

	findContours(img_canny, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<Rect> boundRect(contours.size());  //定义外接矩形集合
	vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
	Point2f rect[4];
	int sxy = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		box[i] = minAreaRect(Mat(contours[i]));  //计算每个轮廓最小外接矩形
		boundRect[i] = boundingRect(Mat(contours[i]));
		//利用长宽来选择符合条件的轮廓
		if (box[i].size.width > 300 || box[i].size.height > 300 || box[i].size.width < 100 || box[i].size.height < 100 || abs(box[i].size.width - box[i].size.height)>20)
			continue;///////////参数需调!!!!!!!!
		//circle(img_temp, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //绘制最小外接矩形的中心点
		box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组

		//rectangle(img_temp, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
		//for (int j = 0; j < 4; j++)
		//{
		//	line(img_temp, rect[j], rect[(j + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
		//}
		sxy++;
	}
	//imshow("最小外接矩形提取", img_temp);
	//cout<<"num="<<sxy<<endl;

	Point2f srcPoints[4], dstPoints[4];

	//对四个点进行排序 分出左上 右上 右下 左下(顺时针)
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
	Mat transMat = getPerspectiveTransform(srcPoints, dstPoints);    //得到变换矩阵
	warpPerspective(img_bin, dst, transMat, dst.size());    //进行坐标变换
	threshold(dst, dst, 120, 255, CV_THRESH_BINARY); //二值化/参数需调!!!!!!!!
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
	vector<Rect> boundRect(contours.size());  //定义外接矩形集合

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
		//先利用尺寸筛选，默认块400*400
		if (boundRect[i].height < 200 || boundRect[i].width < 200)
			continue;
		if (boundRect[i].height > 350 || boundRect[i].width > 350)
			continue;
        //是否含有内嵌轮廓
		//含有
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
		//不含
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
			//右上
			if ((tl.y + br.y) / 2 < 200)
				return 1;
			//右下
			else
				return 2;
		}
		else
		{
			//左上
			if ((tl.y + br.y) / 2 < 200)
				return 3;
			//左下
			else
				return 4;
		}
	}
	return 0;
}
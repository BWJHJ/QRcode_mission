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

int Find_Part_Position(Mat image);

int main()
{
	//clock_t start, finish;
	//float time_temp;
	//start = clock();
	int a = 0;
	Mat image_src = imread("C:\\Users\\bafs\\Desktop\\1米\\i3.jpg");
	a = Find_Part_Position(image_src);
	cout << "The position is: " << a << endl;
//	Mat src = imread("C:\\Users\\bafs\\Desktop\\1米\\1.jpg"),src_img,preprocess_img,floodfill_img;
//	pyrDown(src, src);
//	pyrDown(src, src);
//    src_img = src.clone();
//
//	cvtColor(src_img, preprocess_img, COLOR_BGR2GRAY);
//	//GaussianBlur(preprocess_img, preprocess_img, Size(5, 5), 0, 0);
//	imshow("src", src_img);
//	medianBlur(preprocess_img, preprocess_img, 5);
//	threshold(preprocess_img, preprocess_img, 100, 255, THRESH_BINARY);
//	//preprocessing picture output
//	finish = clock();
//	time_temp =(float)(finish - start);
//	cout << "The running time for Preprocessing is" << time_temp / CLOCKS_PER_SEC << "  sec" << endl;
//	imshow("preprocessing", preprocess_img);
//
//
//	//floodfill the edge
//	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
//	floodfill_img = preprocess_img.clone();
//	morphologyEx(floodfill_img, floodfill_img, CV_MOP_CLOSE, element, Point(-1, -1), 2);
//	const int nr = floodfill_img.rows;
//	const int nc = floodfill_img.cols;
//	Mat edge[4];
//	edge[0] = floodfill_img.row(0);    //up
//	edge[1] = floodfill_img.row(nr - 1); //bottom
//	edge[2] = floodfill_img.col(0);    //left
//	edge[3] = floodfill_img.col(nc - 1); //right
//
//	std::vector<Point> edgePts;
//	const int minLength = std::min(nr, nc) / 4;
//	for (int i = 0; i < 4; ++i)
//	{
//		std::vector<Point> line;
//		Mat_<uchar>::const_iterator iter = edge[i].begin<uchar>();       //当前像素
//		Mat_<uchar>::const_iterator nextIter = edge[i].begin<uchar>() + 1; //下一个像素
//		while (nextIter != edge[i].end<uchar>())
//		{
//			if (*iter == 255)
//			{
//				if (*nextIter == 255)
//				{
//					Point pt = iter.pos();
//					if (i == 1)
//						pt.y = nr - 1;
//					if (i == 3)
//						pt.x = nc - 1;
//
//					//line.push_back(pt);
//					edgePts.push_back(pt);
//				}
//			}
//			++iter;
//			++nextIter;
//		}
//	}
//
//	for (int n = 0; n < edgePts.size(); ++n)
//		//cout<<edgePts[n];
//		floodFill(floodfill_img, edgePts[n], 0);//漫水填充法
//	finish = clock();
//	cout << "The running time for floodfill is" <<( finish - start - time_temp ) / CLOCKS_PER_SEC << "  sec" << endl;
//    time_temp = (float)(finish - start);
//	imshow("floodfill", floodfill_img);
//
//	//开操作(用来去除周边的噪声，让全局只剩下二维码部分)
//	Mat Open_img = floodfill_img.clone();
//	morphologyEx(Open_img, Open_img, MORPH_OPEN, element);
//	morphologyEx(Open_img, Open_img, CV_MOP_CLOSE, element,Point(-1,-1),10);
//	imshow("Open", Open_img);
//
//	//边缘检测
//    //Mat Contour_img;
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarcy;
//	findContours(Open_img, contours, hierarcy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	//Canny(Open_img, Contour_img, 10, 30, 3);
//
//	vector<Rect> boundRect(contours.size());  //定义外接矩形集合
//	vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
//	Point2f rect[4];
//	Mat show;
//	show = src.clone();
//	for (int i = 0; i < contours.size(); i++)
//	{
//		box[i] = minAreaRect(Mat(contours[i]));  //计算每个轮廓最小外接矩形
//		boundRect[i] = boundingRect(Mat(contours[i]));
//		circle(show, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //绘制最小外接矩形的中心点
//		box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组
//		int Maxarea = 0;
//		//rectangle(show, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
//		for (int j = 0; j < 4; j++)
//		{
//			if (contourArea(box[j].points) > contourArea(box[Maxarea].points))
//				Maxarea = j;
//		}
//		line(show, rect[Maxarea], rect[(Maxarea + 1) % 4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
//	}
//	imshow("boundRect", show);
//
//	//Point2f srcPoints[4], dstPoints[4];
//
//	//srcPoints[0] = Point(boundRect[0].x,boundRect[0].y);
//	//srcPoints[1] = Point(boundRect[0].x, boundRect[0].y+ boundRect[0].height);
//	//srcPoints[2] = Point(boundRect[0].x+boundRect[0].width, boundRect[0].y + boundRect[0].height);
//	//srcPoints[3] = Point(boundRect[0].x+ boundRect[0].width, boundRect[0].y);
//
//	//dstPoints[0] = Point2f(0, 0);
//	//dstPoints[1] = Point2f(0, 400);
//	//dstPoints[2] = Point2f(400, 400);
//	//dstPoints[3] = Point2f(400, 0);
//
//	//Mat dst = Mat(400, 400, CV_8UC3);
//	//Mat temp = src.clone();
//	//Mat transMat = getPerspectiveTransform(srcPoints, dstPoints);    //得到变换矩阵
//	//warpPerspective(floodfill_img, dst, transMat, dst.size());    //进行坐标变换
//
//	//imshow("dst", dst);
//	//imwrite("4.png", dst);
//	//Mat Hough_img = Contour_img.clone();
//	//vector<Vec2f>lines;
//	//HoughLines(Hough_img, lines, 1, CV_PI / 180, 10, 20, 10);
//	//Point pt1, pt2, pt3, pt4, pt5, pt6;
//	//for (rsize_t i = 0; i < lines.size(); i++)
//	//{
//	//	if (i != lines.size() - 2)
//	//	{
//	//		float zhongxinjuli = lines[i][0], theta = lines[i][1];
//	//		double cos_theta = cos(theta), sin_theta = sin(theta);
//	//		double x0 = zhongxinjuli * cos_theta, y0 = zhongxinjuli * sin_theta;
//	//		pt1.x = cvRound(x0 - 1000 * sin_theta);
//	//		pt1.y = cvRound(y0 + 1000 * cos_theta);
//	//		pt2.x = cvRound(x0 + 1000 * sin_theta);
//	//		pt2.y = cvRound(y0 - 1000 * cos_theta);
//	//		line(Hough_img, pt1, pt2, Scalar(255, 255, 255), 2, LINE_AA);
//	//	}
//	//}
//	//imshow("Hough", Hough_img);
//	//vector<vector<Point>> contours;    //储存轮廓
//	//vector<Vec4i> hierarchy;
//	//findContours(Contour_img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);    //获取轮廓
//	//Mat draw_contour = Mat::zeros(Contour_img.size(), CV_8UC3);
//	////for (int i = 0; i < contours.size(); i++)
//	////{
//	////	Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//	////	drawContours(draw_contour, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
//	////}
//	//int maxArea = 0;
//	//int index = 0;
// //   for (index = 0; index < contours.size(); index++) {
//	//if (contourArea(contours[index]) > contourArea(contours[maxArea]))
//	//	maxArea = index;
//	////approxPolyDP(contours[index], polyContours[index], 70, true);
// //   }
//	//drawContours(draw_contour, contours, 7, (255,255,255), 2, 8, vector<Vec4i>(), 0, Point());
//	//finish = clock();
// //   cout << "The running time for findContour is" <<( finish - start - time_temp ) / CLOCKS_PER_SEC << "  sec" << endl;
// //   //time_temp = (float)(finish - start) / CLOCKS_PER_SEC;
//	//imshow("All contours", draw_contour);
//
//	//vector<vector<Point>> polyContours(contours.size());
//	//int maxArea = 0;
//	//for (int index = 0; index < contours.size(); index++) {
//	//	if (contourArea(contours[index]) > contourArea(contours[maxArea]))
//	//		maxArea = index;
//	//	approxPolyDP(contours[index], polyContours[index], 70, true);
//	//}
//	////Draw the biggest contours
//	//Mat Contour_img = src.clone();
//	//drawContours(Contour_img, polyContours, maxArea, Scalar(0, 0, 255/*rand() & 255, rand() & 255, rand() & 255*/), 2);
//	//finish = clock();
//	//cout << "The running time for findContour is" << finish - start - time_temp << "  sec" << endl;
//	////time_temp = (float)(finish - start) / CLOCKS_PER_SEC;
// //   imshow("Contour", Contour_img);
//
//	//vector<int>  hull;
//	//convexHull(polyContours[maxArea], hull, false);    //检测该轮廓的凸包
//	//for (size_t i = 0; i < hull.size(); ++i) {
//	//	circle(Corner_img, polyContours[maxArea][i], 10, Scalar(rand() & 255, rand() & 255, rand() & 255), 3);
//	//}
//	////addWeighted(dst4, 0.5, shrinkedPic, 0.5, 0, shrinkedPic);
//	//imshow("four corner", Corner_img);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//	//Point2f srcPoints[4], dstPoints[4];
//
//	//srcPoints[0] = polyContours[maxArea][0];
// //   srcPoints[1] = polyContours[maxArea][1];
// //   srcPoints[2] = polyContours[maxArea][2];
// //   srcPoints[3] = polyContours[maxArea][3];
//
//	//dstPoints[0] = Point2f(0, 0);
//	//dstPoints[1] = Point2f(0, 400);
//	//dstPoints[2] = Point2f(400, 400);
//	//dstPoints[3] = Point2f(400, 0);
//
//	//Mat dst=Mat(400,400, CV_8UC3);
//	//Mat temp = src.clone();
//	//Mat transMat = getPerspectiveTransform(srcPoints, dstPoints);    //得到变换矩阵
//	//warpPerspective(temp, dst, transMat, dst.size());    //进行坐标变换
//
//	//imshow("dst", dst);
//	//imwrite("2.png", dst);
	waitKey(0);
	return 1;
}


int Find_Part_Position(Mat image)
{
	Mat src = image.clone();
	Mat edge=src.clone();
	Mat gray = src.clone();
	cvtColor(gray, gray, CV_BGR2GRAY);
	threshold(gray, gray, 40, 255, CV_THRESH_BINARY);
	Canny(gray, edge, 5, 30,3);
	imwrite("Bin.png", gray);
	imshow("edge", edge);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
    findContours(edge, contours, hierarcy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
	//drawContours(src);
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
		//else if (hierarcy[i][2] != -1)
		//{
		//	ic++;
		//}
		//else if (hierarcy[i][2] == -1)
		//{
		//	parentIdx = -1;
		//	ic = 0;
		//}
		//if (ic >= 2)
		//{
		//	contours2.push_back(contours[parentIdx]);
		//	//drawContours(canvas, contours, parentIdx, Scalar(0, 0, 255), 1, 8);
		//	ic = 0;
		//	parentIdx = -1;
		//}
	}
	//for (int i = 0; i < contours.size(); i++)
	//{
		
		////尺寸错误，跳过
		//if (boundRect[i].height < 200 || boundRect[i].width < 200)
		//	continue;
		//if (boundRect[i].height > 500 || boundRect[i].width > 500)
		//	continue;
		////长宽比不对，跳过
		//if (boundRect[i].height / boundRect[i].width < 0.8 && boundRect[i].height / boundRect[i].width > 1.2)
		//	continue;
		//Point tl, br;

		//uint white_flag=0,change_flag=0;
		//for (int i = tl.y; i < br.y; i++)
		//{
		//	if (gray.at<uchar>((int)((tl.x + br.x) / 2), i) == 255)
		//		white_flag = 1;
		//	if ((gray.at<uchar>((int)((tl.x + br.x) / 2), i) == 255) && (gray.at<uchar>((int)((tl.x + br.x) / 2), i + 1) ==0))
		//		change_flag++;
		//}
		//change_flag = change_flag - white_flag;
		//if (change_flag == 2)
		//{
		//	rectangle(src, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 0, 255), 2, 8);
		//	imshow("dst", src);
			
		//}

	//}

	//cout << (size_t)(edge.at<uchar>(20, 20)) << "|" << endl;
	//cout << (size_t)(edge.at<uchar>(90, 20)) << "&" << endl;
	return 0;
}
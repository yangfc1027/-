#include<iostream>  
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

bool draw;

Mat src;//ԭʼͼ��    
Mat dest;
Mat roi;//ROIͼ��  
Point cursor;//��ʼ����     
Rect rect;//���ROI�ľ��ο�

void onMouse(int event, int x, int y, int flags, void* param)
{
	Mat img = src.clone();
	switch (event)
	{
		//����������  
	case CV_EVENT_LBUTTONDOWN:
		//������ͼ��ʱ�����֮ǰROIͼ�����ʾ����    
		cvDestroyWindow("ROI");
		//�����ʼ����    
		cursor = Point(x, y);
		//��ʼ����ʼ���ο�    
		rect = Rect(x, y, 0, 0);
		draw = true;
		break;

		//�ɿ�������        
	case CV_EVENT_LBUTTONUP:
		if (rect.height > 0 && rect.width > 0)
		{
			//��img�еľ��������Ƹ�roi������ʾ��SignROI����   
			roi = img(Rect(rect.x, rect.y, rect.width, rect.height));
			rectangle(img, rect, Scalar(0, 0, 255), 2);
			namedWindow("SignROI");
			imshow("SignROI", img);

			//���������ο��ͼ����ԭͼ��ԭ    
			src.copyTo(img);
			imshow("SrcImage", img);

			//��ʾROIͼ��  
			namedWindow("ROI");
			imshow("ROI", roi);
			imwrite("MY_ROI.png", roi);
			cout << "�Ѿ��������Ȥ����:MY_ROI.png" << endl;

			//dest = imread("MY_ROI.png");
			//namedWindow("DestImage");
			//imshow("DestImage", dest);
			waitKey(0);
		}
		draw = false;
		break;

		//�ƶ����  
	case CV_EVENT_MOUSEMOVE:
		if (draw)
		{
			//��MIN�õ����ϵ���Ϊ���ο����ʼ���꣬������������������ʱֻ����һ���������    
			rect.x = MIN(x, cursor.x);
			rect.y = MIN(y, cursor.y);
			rect.width = abs(cursor.x - x);
			rect.height = abs(cursor.y - y);
			//��ֹ�������򳬳�ͼ��ķ�Χ    
			rect &= Rect(0, 0, src.cols, src.rows);
		}
		break;
	}
}


int main()
{
	//src = imread("transmitter.jpg");
	src = imread("transmitter.jpg");
	if (src.data == 0)
	{
		cout << "ͼƬ������" << endl;
		return -1;
	}

	namedWindow("SrcImage");
	imshow("SrcImage", src);
	/*

	void setMouseCallback(const string& winname, MouseCallback onMouse, void* userdata=0 );
	Parameters:
	��һ��������windows�Ӵ����ƣ�����Ϊwinname���Ӵ���������أ�
	�ڶ��������������Ӧ���������������ĵ�����ƶ����ɿ����ж����Ĳ������ͣ���������Ӧ�ĺ�������
	�����������������Ӧ��������ID���������Ӧ��������ƥ����У���ʱֻ�õ�Ĭ��Ϊ0�������
	*/

	setMouseCallback("SrcImage", onMouse, NULL);
	waitKey();
	return 0;
}

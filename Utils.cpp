#include "stdafx.h"

double ComputeDistance(Vec3b from, Vec3b to)
{
	return sqrt(pow(from.val[0] - to.val[0], 2) + pow(from.val[1] - to.val[1], 2) + pow(from.val[2] - to.val[2], 2));
}

double ComputeImageMean(Mat image, bool convert)
{
	float sum = 0;
	Mat imgGray = convert ? ConvertImageToGray(image) : image;
	for (size_t i = 0; i < imgGray.rows; i++)
	{
		for (size_t j = 0; j < imgGray.cols; j++)
		{
			sum += convert ? imgGray.at<uchar>(i, j) : imgGray.at<float>(i, j);
		}
	}
	return sum / (imgGray.rows*imgGray.cols);
}

double ComputeImageStandardDeviation(Mat image)
{
	float mean = ComputeImageMean(image, true);
	Mat imgGray = ConvertImageToGray(image);
	Mat differences = Mat(Size(image.cols, image.rows), CV_32FC1);
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			differences.at<float>(i, j) = pow((float)imgGray.at<uchar>(i, j) - mean, 2);
		}
	}
	float meanDif = ComputeImageMean(differences, false);
	return sqrt(meanDif);
}

Mat ConvertImageToGray(Mat image)
{
	Mat imgGray = Mat(Size(image.cols, image.rows), CV_8UC1);
	cvtColor(image, imgGray, COLOR_BGR2GRAY);
	return imgGray;
}
#include "stdafx.h"

MeanShift::MeanShift()
{

}

MeanShift::~MeanShift()
{
}

void MeanShift::Image(string imagePath)
{
	image = imread(imagePath);
}

void MeanShift::Image(Mat image)
{
	this->image = image;
}

Mat MeanShift::Image()
{
	return image;
}

Mat MeanShift::Result()
{
	return result;
}

Mat MeanShift::ApplyMeanShift(double spatialRadius, double colorRadius, int maxLevel)
{
	pyrMeanShiftFiltering(image, result, spatialRadius, colorRadius, maxLevel);
	return result;
}

Mat MeanShift::ApplyMeanShift(Mat image, double spatialRadius, double colorRadius, int maxLevel)
{
	Image(image);
	return ApplyMeanShift(spatialRadius, colorRadius, maxLevel);
}

Mat MeanShift::ApplyMeanShift(string imagePath, double spatialRadius, double colorRadius, int maxLevel)
{
	Image(imagePath);
	return ApplyMeanShift(spatialRadius, colorRadius, maxLevel);
}

float** MeanShift::GetConfidence()
{
	confidence = new float*[image.rows];
	for (size_t i = 0; i < image.rows; i++)
	{
		confidence[i] = new float[image.cols];
		for (size_t j = 0; j < image.cols; j++)
		{
			Vec3b imageVal = image.at<Vec3b>(i, j);
			Vec3b resultVal = result.at<Vec3b>(i, j);
			confidence[i][j] = ComputeDistance(imageVal, resultVal);
		}
	}
	return confidence;
}

Mat MeanShift::GetVisualConfidence(int treshold, bool binarizedImage)
{
	Mat conf = Mat(Size(image.cols, image.rows), CV_8U);
	GetConfidence();
	float max = FindMax();
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			if (max > 0)
			{
				conf.at<uchar>(i, j) = binarizedImage ? (((uchar)(confidence[i][j] / max) * 255 < treshold) ? 0 : 255) : (uchar)((confidence[i][j] / max) * 255);
			}
		}
	}
	return conf;
}

float MeanShift::FindMax()
{
	float max = INT_MIN;
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			if (confidence[i][j] > max)
				max = confidence[i][j];
		}
	}
	return max;
}
#pragma once

class MeanShift
{
	private:
		Mat image, result;
		float** confidence;
	public:
		MeanShift();
		MeanShift(string imagePath);
		MeanShift(Mat image);
		~MeanShift();
		void Image(string imagePath);
		void Image(Mat image);
		Mat Image();
		Mat Result();
		Mat ApplyMeanShift(double spatialRadius, double colorRadius, int maxLevel);
		Mat ApplyMeanShift(Mat image, double spatialRadius, double colorRadius, int maxLevel);
		Mat ApplyMeanShift(string imagePath, double spatialRadius, double colorRadius, int maxLevel);
		float** GetConfidence();
		Mat GetVisualConfidence(int treshold, bool opt);
		float FindMax();
};
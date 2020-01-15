#pragma once

double ComputeDistance(Vec3b from, Vec3b to);
double ComputeImageMean(Mat image);
double ComputeImageStandardDeviation(Mat image);
Mat ConvertImageToGray(Mat image);
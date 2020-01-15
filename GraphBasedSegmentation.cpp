#include "stdafx.h"

ImageGraph::ImageGraph()
{

}

ImageGraph::~ImageGraph()
{
	vertices.clear();
	edges.clear();
}

ImageGraph::ImageGraph(string imagePath)
{
	CreateGraph(imagePath);
}

ImageGraph::ImageGraph(Mat image)
{
	CreateGraph(image);
}

void ImageGraph::Image(string imagePath)
{
	image = imread(imagePath);
}

void ImageGraph::Image(Mat image)
{
	this->image = image;
}

Mat ImageGraph::Image()
{
	return image;
}

void ImageGraph::CreateGraph(string imagePath)
{
	Image(imagePath);
	CreateGraph(image);
}

void ImageGraph::CreateGraph(Mat image)
{
	Image(image);
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			Vertex vertex = Vertex(j, i, image.at<Vec3b>(i, j));
			vertices.push_back(vertex);
			CreateEdges(vertex.x, vertex.y);
		}
	}
}

void ImageGraph::CreateEdges(int x, int y)
{
	if (x - 1 > 0)
		CreateEdge(vertices.size() - 1, y * image.cols + x - 1);
	if (y - 1 > 0)
		CreateEdge(vertices.size() - 1, (y - 1)*image.cols + x);
}

void ImageGraph::CreateEdge(int from, int to)
{
	edges.push_back(Edge(ComputeDistance(vertices[from].value, vertices[to].value), from, to));
}

void ImageGraph::SortEdges()
{
	Edge* sortedEdges = new Edge[edges.size()];
	for (size_t i = 0; i < edges.size(); i++)
	{
		sortedEdges[i] = edges[i];
	}
	sort(sortedEdges, sortedEdges + edges.size());
	for (size_t i = 0; i < edges.size(); i++)
	{
		edges[i] = sortedEdges[i];
	}
}

DisjointSet ImageGraph::CreateDisjointSet(float treshold)
{
	SortEdges();

	float* tresholds = new float[vertices.size()];
	for (size_t i = 0; i < vertices.size(); i++)
		tresholds[i] = treshold;
	
	set = DisjointSet(vertices.size());

	for (size_t i = 0; i < edges.size(); i++)
	{
		int element1 = set.FindElement(edges[i].vertex1);
		int element2 = set.FindElement(edges[i].vertex2);
		if (element1 != element2)
		{
			if (edges[i].weight <= tresholds[edges[i].vertex1] &&
				edges[i].weight <= tresholds[edges[i].vertex2])
			{
				set.JoinElements(element1, element2);
				element1 = set.FindElement(element1);
				tresholds[element1] = edges[i].weight + treshold / set.ElementSize(element1);
			}
		}
	}
	delete tresholds;
	return set;
}

void ImageGraph::PostProcessComponents(int minSize)
{
	for (int i = 0; i < edges.size(); i++)
	{
		int element1 = set.FindElement(edges[i].vertex1);
		int element2 = set.FindElement(edges[i].vertex2);
		if ((element1 != element2) && ((set.ElementSize(element1) < minSize) || (set.ElementSize(element2) < minSize)))
			set.JoinElements(element1, element2);
	}
}

Mat ImageGraph::SegmentGraph(float treshold, int minSize, bool randomColors)
{
	Mat segmentedImage = Mat(Size(image.cols, image.rows), CV_8UC3);
	CreateDisjointSet(treshold);
	//post-process small components
	
	PostProcessComponents(minSize);
	ColorSegments(segmentedImage, randomColors);
	return segmentedImage;
}

vector<Vec3b> ImageGraph::RandomSegmentColors()
{
	Mat randomColors = Mat(Size(image.cols, image.rows), CV_8UC3);
	randu(randomColors, Scalar(0, 0, 0), Scalar(255, 255, 255));
	vector<Vec3b> finalColors;
	for (size_t i = 0; i < randomColors.rows; i++)
	{
		for (size_t j = 0; j < randomColors.cols; j++)
		{
			finalColors.push_back(randomColors.at<Vec3b>(i, j));
		}
	}
	return finalColors;
}

void ImageGraph::ColorSegments(Mat &src, bool randomColors)
{
	vector<Vec3b> colors = RandomSegmentColors();
	for (size_t i = 0; i < image.rows; i++)
	{
		for (size_t j = 0; j < image.cols; j++)
		{
			int index = set.FindElement(i*image.cols + j);
			src.at<Vec3b>(i, j) = (randomColors) ? colors[index] : vertices[index].value;
		}
	}
}
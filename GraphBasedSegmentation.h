#pragma once

struct Vertex
{
	int x, y;
	Vec3b value;

	Vertex()
	{
		x = y = 0;
		value = Vec3b(0, 0, 0);
	}

	Vertex(int x, int y, Vec3b value)
	{
		this->x = x;
		this->y = y;
		this->value = value;
	}
};

struct Edge
{
	float weight;
	int vertex1, vertex2;

	Edge()
	{

	}

	Edge(float weight, int vertex1, int vertex2)
	{
		this->weight = weight;
		this->vertex1 = vertex1;
		this->vertex2 = vertex2;
	}	
};

inline bool operator < (const Edge &edge1, const Edge &edge2)
{
	return edge1.weight < edge2.weight;
}

class ImageGraph
{
	private:
		vector<Vertex> vertices;
		vector<Edge> edges;
		DisjointSet set;
		Mat image;
	public:
		ImageGraph();
		~ImageGraph();
		ImageGraph(string imagePath);
		ImageGraph(Mat image);
		void Image(string imagePath);
		void Image(Mat image);
		Mat Image();
		void CreateGraph(string imagePath);
		void CreateGraph(Mat image);
		void CreateEdges(int x, int y);
		void CreateEdge(int from, int to);
		void SortEdges();
		DisjointSet CreateDisjointSet(float treshold);
		void PostProcessComponents(int minSize);
		Mat SegmentGraph(float treshold, int minSize, bool randomColors);
		vector<Vec3b> RandomSegmentColors();
		void ColorSegments(Mat &src, bool randomColors);
};
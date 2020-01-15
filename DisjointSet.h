#pragma once

struct SetElement
{
	int rank, size;
	int pair;
	bool checked = false;

	SetElement(int rank, int size, int pair)
	{
		this->rank = rank;
		this->size = size;
		this->pair = pair;
	}
};

class DisjointSet
{
	private:
		vector<SetElement> elements;
	public:
		DisjointSet();
		DisjointSet(int totalElements);
		~DisjointSet();
		int FindElement(int toFind);
		void JoinElements(int element1, int element2);
		int ElementSize(int index);
		vector<SetElement> Elements();
};
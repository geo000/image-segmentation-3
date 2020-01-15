#include "stdafx.h"

DisjointSet::DisjointSet()
{

}

DisjointSet::DisjointSet(int totalElements)
{
	for (size_t i = 0; i < totalElements; i++)
	{
		elements.push_back(SetElement(0, 1, i));
	}
}

DisjointSet::~DisjointSet()
{
	elements.clear();
}

int DisjointSet::FindElement(int toFind)
{
	int index = toFind;
	while (index != elements[index].pair)
		index = elements[index].pair;
	elements[toFind].pair = index;
	return index;
}

void DisjointSet::JoinElements(int element1, int element2)
{
	if (elements[element1].rank > elements[element2].rank)
	{
		elements[element2].pair = element1;
		elements[element1].size += elements[element2].size;
	}
	else 
	{
		elements[element1].pair = element2;
		elements[element2].size += elements[element1].size;
		if (elements[element1].rank == elements[element2].rank)
			elements[element2].rank++;
	}
}

int DisjointSet::ElementSize(int index)
{
	return elements[index].size;
}

vector<SetElement> DisjointSet::Elements()
{
	return elements;
}
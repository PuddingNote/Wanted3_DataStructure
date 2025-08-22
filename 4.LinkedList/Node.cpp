#include "Node.h"

Node::Node() : Node(0) //data(0), next(nullptr)
{

}

Node::Node(int data) : data(data), next(nullptr)
{

}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
	return os << "Data: " << node.data;
}
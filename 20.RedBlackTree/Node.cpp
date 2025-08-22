#include "Node.h"

Node::Node(int data, Color color)
    : data(data), color(color)
{

}

const char* Node::GetColorString() const
{
    return color == Color::Red ? "RED" : "BLACK";
}
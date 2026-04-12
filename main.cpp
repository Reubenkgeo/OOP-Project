/*
NTO1046
OOP(object-oriented programming) project
Author: Reuben Kuruvila George
Student ID: 40467327
boolean expression and truth table gen
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class boolop
{
public:
    virtual string nameget() const = 0;
    virtual bool eval(bool a, bool b) const { return false; }
}
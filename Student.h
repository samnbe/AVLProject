#pragma once
#include <iostream>
#include <string>

using namespace std;

class Student {
public:
	string name;
	int id;
	int height;
	Student* left;
	Student* right;
	Student();
};

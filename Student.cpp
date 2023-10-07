#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

Student::Student() {
	this->name = "";
	this->id = 0;
	this->height = 0;
	this->left = nullptr;
	this->right = nullptr;
}

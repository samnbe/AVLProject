#pragma once
#include <iostream>
#include <string>
#include "Student.h"

using namespace std;

class AVL {
	Student* root;
	Student* InsertHelper(string name, int id, Student* node);
	void RemoveIDHelper(int id, Student* node, Student* parentNode);
	void SearchIDHelper(int id, Student* node);
	void SearchNameHelper(string name);
	void PrintInorderHelper(Student* node);
	void PrintPreorderHelper(Student* node); 
	void PrintPostorderHelper(Student* node);
	void PrintLevelCountHelper();
	void RemoveInorderNHelper(int n, Student* node);
	Student* RotateRight(Student* localRoot);
	Student* RotateLeft(Student* localRoot);
public:
	void GetRoot();
	AVL(Student* root);
	AVL();
	~AVL();
	void Insert(string name, int id); 
	void RemoveID(int id); 
	void SearchID(int id);
	void SearchName(string name);
	void PrintInorder();
	void PrintPreorder();
	void PrintPostorder();
	void PrintLevelCount();
	void RemoveInorderN(int n);
};


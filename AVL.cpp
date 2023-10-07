#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
#include <ctype.h>
#include "AVL.h"

using namespace std;
int countN = 0; 
bool firstNode = true;

AVL::AVL(Student* root_) {
	this->root = root_;
}

//returns root's name
void AVL::GetRoot() {
	cout << root->name << endl;
}

//constructor
AVL::AVL() {
	this->root = nullptr;
}

//delete avl tree after code is finsihed, destructor 
AVL::~AVL() {
	stack<Student*> deleteTree;
	deleteTree.push(root);

	while (!deleteTree.empty()) {
		Student* node = deleteTree.top();

		deleteTree.pop();
		if (node->right != nullptr) {
			deleteTree.push(node->right);
		}
		if (node->left != nullptr) {
			deleteTree.push(node->left);
		}
		delete node;
	}
}

//rotation left 
Student* AVL::RotateLeft(Student* localRoot) {
	Student* grandChild = localRoot->right->left;
	Student* newParent = localRoot->right;
	newParent->left = localRoot;
	localRoot->right = grandChild;
	if (localRoot == root) { 
		root = newParent; 
	}
	localRoot->height = 1 + max(localRoot->left ? localRoot->left->height : 0, localRoot->right ? localRoot->right->height : 0);
	if (grandChild != nullptr) {
		grandChild->height = 1 + max(grandChild->left ? grandChild->left->height : 0, grandChild->right ? grandChild->right->height : 0); 
	}
	newParent->height = 1 + max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0); 
	return newParent;
}

//rotation right 
Student* AVL::RotateRight(Student* localRoot) {
	Student* grandChild = localRoot->left->right;
	Student* newParent = localRoot->left;
	newParent->right = localRoot;
	localRoot->left = grandChild;
	if (localRoot == root) {
		root = newParent; 
	} 
	localRoot->height = 1 + max(localRoot->left ? localRoot->left->height : 0, localRoot->right ? localRoot->right->height : 0); 
	if (grandChild != nullptr) { 
		grandChild->height = 1 + max(grandChild->left ? grandChild->left->height : 0, grandChild->right ? grandChild->right->height : 0); 
	}
	newParent->height = 1 + max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);
	return newParent;
}

//inserts a node into the tree and balances the tree after insertion 
Student* AVL::InsertHelper(string name_, int id_, Student* node_) {
	//if node is not in the tree already
	if (node_ == nullptr) {
		cout << "successful" << endl;
		node_ = new Student;
		node_->name = name_;
		node_->id = id_;
		node_->left = nullptr;
		node_->right = nullptr;
		if (root == nullptr) {
			root = node_;
		}
	}
	//if the node is in the tree already
	else if (node_->id == id_) {
		cout << "unsuccessful" << endl;
		return nullptr; 
	} 
	//if the node's id is less then the id that wants to be inserted 
	else if (id_ < node_->id) { 
		node_->left = InsertHelper(name_, id_, node_->left); 
	} 
	//if the node's id is greater than the id that wants to be inserted 
	else { 
		node_->right = InsertHelper(name_, id_, node_->right); 
	} 

	//calculate heights of nodes, assign that number of node's height value 
	node_->height = 1 + max(node_->left ? node_->left->height : 0, node_->right ? node_->right->height : 0);

	//balancing tree 
	//making sure node has children on both sides and needs balancing on left side (left heavy)
	if (node_->left != nullptr && node_->right != nullptr && node_->left->height - node_->right->height > 1) {
		//if node's left child has both children, node->left->left heavy, rotate right
		if (node_->left->left != nullptr && node_->left->right != nullptr && node_->left->left->height > node_->left->right->height) {
			node_ = RotateRight(node_);
		}
		//else if node's child has both child, node->left->right heavy, rotate left then right 
		else if (node_->left->left != nullptr && node_->left->right != nullptr && node_->left->left->height < node_->left->right->height) {
			node_->left = RotateLeft(node_->left);
			node_ = RotateRight(node_);
		}
		//if node's left child has left child, rotate right
		else if (node_->left->left != nullptr && node_->left->right == nullptr) {
			node_ = RotateRight(node_);
		}
		//if node has left child and that child has a right child, rotate left then right
		else if (node_->left != nullptr && node_->left->right != nullptr){
			node_->left = RotateLeft(node_->left);
			node_ = RotateRight(node_);
		}
		//any other case rotate node right
		else {
			node_ = RotateRight(node_);
		}
	}
	//if node only has left child, still may need balancing on left side  
	else if (node_->left != nullptr && node_->right == nullptr && node_->left->height > 1) {
		//if node's left child has both children, node->left->left heavy, rotate right
		if (node_->left->left != nullptr && node_->left->right != nullptr && node_->left->left->height > node_->left->right->height) {
			node_ = RotateRight(node_);
		}
		//else if node's child has both child, node->left->right heavy, rotate left then right 
		else if (node_->left->left != nullptr && node_->left->right != nullptr && node_->left->left->height < node_->left->right->height) {
			node_->left = RotateLeft(node_->left);
			node_ = RotateRight(node_);
		}
		//if node's left child has left child, rotate right
		else if (node_->left->left != nullptr && node_->left->right == nullptr) {
			node_ = RotateRight(node_);
		}
		//if node has left child and that child has a right child, rotate left then right
		else if (node_->left != nullptr && node_->left->right != nullptr) {
			node_->left = RotateLeft(node_->left);
			node_ = RotateRight(node_);
		}
		//any other case rotate node right
		else {
			node_ = RotateRight(node_);
		}
	}
	//making sure node has both children, needs balancing on right side (right heavy)
	else if (node_->right != nullptr && node_->left != nullptr && node_->left->height - node_->right->height < -1) {
		//if node's right child has both children, node->right->right heavy, rotate left
		if (node_->right->right != nullptr && node_->right->left != nullptr && node_->right->right->height > node_->right->left->height) {
			node_ = RotateLeft(node_);
		}
		//else if node's child has both child, node->right->left heavy, rotate right then left
		else if (node_->right->right != nullptr && node_->right->left != nullptr && node_->right->right->height < node_->right->left->height) {
			node_->right = RotateRight(node_->right);
			node_ = RotateLeft(node_);
		}
		//if node's right child has right child, rotate left
		else if (node_->right->right != nullptr && node_->right->left == nullptr) {
			node_ = RotateLeft(node_);
		}
		//if node has right child and that child has a left child, rotate right then left
		else if (node_->right != nullptr && node_->right->left != nullptr) {
			node_->right = RotateRight(node_->right);
			node_ = RotateLeft(node_);
		}
		//any other case rotate node left
		else {
			node_ = RotateLeft(node_);
		}
	}
	//if node only has right child, still may need balancing on right side 
	else if (node_->left == nullptr && node_->right != nullptr && node_->right->height > 1) {
		//if node's right child has both children, node->right->right heavy, rotate left
		if (node_->right->right != nullptr && node_->right->left != nullptr && node_->right->right->height > node_->right->left->height) {
			node_ = RotateLeft(node_);
		}
		//else if node's child has both child, node->right->left heavy, rotate right then left
		else if (node_->right->right != nullptr && node_->right->left != nullptr && node_->right->right->height < node_->right->left->height) {
			node_->right = RotateRight(node_->right);
			node_ = RotateLeft(node_);
		}
		//if node's right child has right child, rotate left
		else if (node_->right->right != nullptr && node_->right->left == nullptr) {
			node_ = RotateLeft(node_);
		}
		//if node has right child and that child has a left child, rotate right then left
		else if (node_->right != nullptr && node_->right->left != nullptr) {
			node_->right = RotateRight(node_->right);
			node_ = RotateLeft(node_);
		}
		else {
			//any other case rotate node left
			node_ = RotateLeft(node_);
		}
	}
	return node_;
}

//removes a node given the id number, keep strack of parent of removed node to rearrange the nodes after deletion
void AVL::RemoveIDHelper(int id_, Student* node, Student* parentNode) {
	Student* temp = node;
	Student* parent = parentNode;

	if (temp == nullptr) {
		//item is not in tree
		cout << "unsuccessful" << endl;
		return;
	}
	//search for item that needs to be removed 
	if (temp->id < id_) {
		RemoveIDHelper(id_, temp->right, temp);
	}
	else if (temp->id > id_) {
		RemoveIDHelper(id_, temp->left, temp);
	}
	else {
		//if the id is found on a node 
		if (temp->left == nullptr && temp->right == nullptr) {
			//set parent to reference nullptr (has no children)
			if (root != temp) { 
				if (temp == parent->left) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			//if removing the root, sent the root to nullptr
			else if (root == temp) {
				root = nullptr;
			}
			delete temp;
		}
		else if (temp->right == nullptr) {
			//set parent ref only the left children (temp only have left child)
			if (temp == parent->left) {
				parent->left = temp->left;
			}
			else {
				parent->right = temp->left;
			}
			delete temp;
		}
		else if (temp->left == nullptr) {
			//set parent ref only the right children (temp only have right child)
			if (temp == parent->left) {
				parent->left = temp->right;
			}
			else {
				parent->right = temp->right;
			}
			delete temp;
		}
		else { //has both children 
			Student* child = temp;
			Student* secChild = temp;
			if (temp->right == nullptr) {
				//temp is the inorder predecessor 
				//set parent to reference left child 
				parent->left = child;
				child->right = temp->right;
				delete temp;
			}
			else {
				while (child->left != nullptr) {
					secChild = child;
					child = child->left;
				}
				node->name = child->name;
				node->id = child->id;
				//temp2 is the rightmost child of the left subtree of the local root 
				if (child->right != nullptr) {
					secChild->right = child->left;
				}
				else {
					secChild->left = nullptr;
				}
				delete child;
			}
		}
		cout << "successful" << endl;
		return;
	}
}

//searches through tree to find specific id number, print out the name of the student with that id number 
void AVL::SearchIDHelper(int id_, Student* node) {
	if (node == nullptr) {
		//not in the tree
		cout << "unsuccessful" << endl;
		return;
	}
	else if (node->id == id_) {
		//found in tree
		cout << node->name << endl;
		return;
	}
	//searching in tree still
	else if (node->id < id_) {
		SearchIDHelper(id_, node->right);
	}
	else {
		SearchIDHelper(id_, node->left);
	}
}

//searches for the node(s) with a certain name, prints out the id number of the student(s)
void AVL::SearchNameHelper(string name_) {
	if (root == nullptr) {
		//if tree is empty
		cout << "unsuccessful" << endl;
		return;
	}

	stack<Student*> studStack;
	studStack.push(root);
	bool inTree = false;
	Student* node = studStack.top();

	while (!studStack.empty()) {
		node = studStack.top();

		if (node->name == name_) {
			//found in tree
			cout << node->id << endl;
			inTree = true;
		}
		studStack.pop(); 
		if (node->right != nullptr) {
			studStack.push(node->right);
		}
		if (node->left != nullptr) {
			studStack.push(node->left);
		}
	}

	if (!inTree) {
		//not in the tree
		cout << "unsuccessful" << endl;
	}
}

//prints the students in inorder
void AVL::PrintInorderHelper(Student* node) {
	if (node != nullptr) {
		PrintInorderHelper(node->left);
		if (firstNode) {
			firstNode = false;
			cout << node->name;
		}
		else {
			cout << ", " << node->name;
		}
		PrintInorderHelper(node->right);
	}
	//if the tree is empty 
	if (root == nullptr) {
		cout << "unsuccessful";
		return;
	}
}

//print the students in preorder
void AVL::PrintPreorderHelper(Student* node) {
	if (node != nullptr) {
		if (firstNode) {
			firstNode = false;
			cout << node->name;
		}
		else {
			cout << ", " << node->name;
		}
		PrintPreorderHelper(node->left);
		PrintPreorderHelper(node->right);
	}
	//if the tree is empty
	if (root == nullptr) {
		cout << "unsuccessful";
		return;
	}
}

//prints the tree in postorder
void AVL::PrintPostorderHelper(Student* node) {
	if (node != nullptr) {
		PrintPostorderHelper(node->left); 
		PrintPostorderHelper(node->right);
		if (firstNode) {
			firstNode = false;
			cout << node->name;
		}
		else {
			cout << ", " << node->name;
		}
	}
	//if the tree is empty
	if (root == nullptr) {
		cout << "unsuccessful";
		return;
	}
}

//prints the level amount of the tree
void AVL::PrintLevelCountHelper() {
	//if tree is empty 
	if (root == nullptr) {
		cout << 0 << endl;
		return;
	}
	else {
		queue<Student*> StudQueue;
		StudQueue.push(root);
		int count = 0;
		int level = 0;
		int prevChildCount = 1;
		int childCount = 0;

		while (!StudQueue.empty()) {
			Student* node = StudQueue.front();

			if (node->left != nullptr) {
				StudQueue.push(node->left);
				count++;
				childCount++;
			}
			else if (node->left == nullptr) {
				count++;
			}

			if (node->right != nullptr) {
				StudQueue.push(node->right);
				count++;
				childCount++;
			}
			else if (node->right == nullptr) {
				count++;
			}

			if (prevChildCount * 2 == count) {
				level++;
				prevChildCount = childCount;
				count = 0;
				childCount = 0;
			}
			StudQueue.pop();
		}
		cout << level << endl;
	}
}

//removes the nth term in the inorder sequence 
void AVL::RemoveInorderNHelper(int n, Student* node) {
	if (node == nullptr) {
		return;
	}
	RemoveInorderNHelper(n, node->left);
	if (countN == n) {
		RemoveID(node->id);
		countN = 0;
		return;
	}
	else {
		countN++;
	}
	RemoveInorderNHelper(n, node->right);
	
}

//Use public functions to call private/helper functions
//also use helper to recurse through the tree, use node as parameter 
void AVL::Insert(string name_, int id_) {
	InsertHelper(name_, id_, root);
}

void AVL::RemoveID(int id_) {
	RemoveIDHelper(id_, root, nullptr);
}

void AVL::SearchID(int id_) {
	SearchIDHelper(id_, root);
}

void AVL::SearchName(string name_) {
	SearchNameHelper(name_);
}

void AVL::PrintInorder() {
	firstNode = true;
	PrintInorderHelper(root);
	cout << endl; 
}

void AVL::PrintPreorder() {
	firstNode = true;
	PrintPreorderHelper(root); 
	cout << endl; 
}

void AVL::PrintPostorder() {
	firstNode = true;
	PrintPostorderHelper(root);
	cout << endl; 
}

void AVL::PrintLevelCount() {
	PrintLevelCountHelper();
}

void AVL::RemoveInorderN(int n) {
	RemoveInorderNHelper(n, root);
}

#include <iostream>
#include <string>
#include <vector>
#include "AVL.h"

using namespace std;

int main() {
    bool bk = false; 
    bool messedup = false;
    string act;
    getline(cin, act);

    //check to make sure the first input is a number
    for (int w = 0; w < act.length(); w++) {
        char ch = act[w];
        if (isdigit(ch) == 0) {
            cout << "unsuccessful" << endl;
            messedup = true; 
            break;
        }
    }

    //if not correct format, second try
    if (messedup) {
        getline(cin, act);
    }

    //turn first/second input into int for the for loop
    //declare the vector for the line of inputs and the avl class
    int actionsNum = stoi(act);
    vector<string> inputs;
    AVL tree;

    string line;
    //run each command, number given by the first line of input 
    for (int i = 0; i < actionsNum; i++) {
        getline(cin, line);
        string temp = "";
        string name = "";
        bool inName = false;
        bool firstName = true;
        int ufid;
        //bk = break, make sure the inputs are correctly formated 
        bk = false;

        //loop through each line to seperate the words to get the proper commands 
        for (auto x : line) {
            if (x == ' ' && temp != "") {
                //remove the "" from name using substr, keeping track of the name/if there is a name in the input 
                if (temp[0] == '\"' && temp[temp.length() - 1] != '\"') {
                    inName = true;
                }
                else if (temp[0] == '\"' && temp[temp.length() - 1] == '\"') {
                    name = name + temp;
                    name = name.substr(1, name.length() - 2);
                    temp = "";
                    inputs.push_back(name); 
                }
                else if (temp[temp.length() - 1] == '\"' && inName) { 
                    inName = false;
                    name = name + " " + temp;
                    name = name.substr(0, name.length() - 1);
                    temp = "";
                    inputs.push_back(name);
                }
                //making the name a whole variable, combining all the words together into one string 
                if (inName) {
                    if (firstName) {
                        name = name + temp;
                        name = name.substr(1);
                        firstName = false;
                    }
                    else {
                        name = name + " " + temp;
                    }
                    temp = "";
                }
                else {
                    //add each command/argument into a vector to call information 
                    if (temp != "" && temp != " ") {
                        inputs.push_back(temp);
                    }
                    temp = "";
                }
            }
            else {
                temp = temp + x;
            }
        }
        if (temp != "" && temp != " ") {
            //if the name is the last word in the input, make sure it is included into the vector and name string 
            if (temp[0] == '\"' && temp[temp.length() - 1] == '\"') {
                name = name + temp;
                name = name.substr(1, name.length() - 2);
                inputs.push_back(name);
            }
            else if (temp[temp.length() - 1] == '\"' && inName) {
                inName = false; 
                name = name + " " + temp; 
                name = name.substr(0, name.length() - 1); 
                inputs.push_back(name); 
            }
            else {
                inputs.push_back(temp); 
            }
        }

        //make sure the name is all letters and/or spaces
        for (int r = 0; r < name.length(); r++) {
            if (isalpha(name[r]) == 0) {
                if (isspace(name[r]) == 0) {
                    bk = true;
                    break; 
                }
            }
        }

        //make sure id number is 8 digits long and only numbers (for the search, insert, and remove functions)
        if (inputs.size() >= 2) {
            if ((inputs[0] == "search" || inputs[0] == "remove") && inputs[1].length() == 8 && name == "") {
                string id_ = inputs[1];
                for (int y = 0; y < inputs[1].length(); y++) {
                    char ch = id_[y];
                    if (isdigit(ch) == 0) {
                        bk = true;
                        break;
                    }
                }
            }
            else if (inputs[0] == "insert" && inputs[2].length() == 8) {
                string id_ = inputs[2];
                for (int y = 0; y < inputs[2].length(); y++) {
                    char ch = id_[y];
                    if (isdigit(ch) == 0) {
                        bk = true;
                        break;
                    }
                }
            }
            else if (inputs[0] == "insert" && inputs[2].length() != 8) {
                bk = true;
            }
            else if ((inputs[0] == "search" || inputs[0] == "remove") && inputs[1].length() != 8 && name == "") {
                bk = true;
            }
        }
        
        //checks the size to make sure proper amount of arguments are given 
        //only 1 input 
        if (inputs.size() == 1 && !bk) {
            if (inputs[0] == "printInorder") {
                tree.PrintInorder(); 
            }
            else if (inputs[0] == "printPreorder") {
                tree.PrintPreorder();
            }
            else if (inputs[0] == "printPostorder") {
                tree.PrintPostorder();
            }
            else if (inputs[0] == "printLevelCount") {
                tree.PrintLevelCount();
            }
            else if (inputs[0] == "getRoot") {
                tree.GetRoot();
            }
            else {
                //error : function does not exist 
                cout << "unsuccessful" << endl;
            }
        }
        //2 inputs
        else if (inputs.size() == 2 && !bk) {
            if (inputs[0] == "remove") {
                //make sure putting a letter, won't make the code crash 
                try {
                    int ufid = stoi(inputs[1]);
                    tree.RemoveID(ufid);
                }
                catch (...) {
                    cout << "unsuccessful" << endl;
                }
            }
            else if (inputs[0] == "search") {
                //find difference between search id and search name 
                if (inputs[1] == name) {
                    tree.SearchName(inputs[1]);
                }
                else{
                    try {
                        int ufid = stoi(inputs[1]);
                        tree.SearchID(ufid);
                    }
                    catch (...){
                        cout << "unsuccessful" << endl;
                    }
                }
            }
            else if (inputs[0] == "removeInorder") {
                int n = stoi(inputs[1]);
                tree.RemoveInorderN(n);
            }
            else {
                //error : function does not exist 
                cout << "unsuccessful" << endl;
            }
        }
        //3 inputs 
        else if (inputs.size() == 3 && !bk) {
            if (inputs[0] == "insert" && inputs[1] == name) {
                ufid = stoi(inputs[2]);
                tree.Insert(inputs[1], ufid);
            }
            else {
                //error : function does not exist or too many arugments 
                cout << "unsuccessful" << endl;
            }
        }
        else {
            //error: input is incorrect, format/arguments are wrong
            cout << "unsuccessful" << endl;
        }
        //clears the vector for the next line of input 
        inputs.clear();
    }
}

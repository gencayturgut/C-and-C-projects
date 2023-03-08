#include <iostream>
#include <vector>
#include "exercise2_utils.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

void readFile(vector<string>& scores, string fileName)
{
    ifstream file;
    file.open(fileName);
    string line;
    while (getline(file, line))
    {
        scores.push_back(line);
    }
    file.close();
}
Node* SetNode(Node* newEntry) {
    Node* newNode = new Node();
    newNode->is_home = newEntry->is_home;
    newNode->score = newEntry->score;
    newNode->shirt_no = newEntry->shirt_no;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* Insert(Node* root, Node* newEntry) {
    if (root == NULL) {
        root = SetNode(newEntry);
    }
    else if (newEntry->score <= root->score) {
        root->left = Insert(root->left, newEntry);
    }
    else {
        root->right = Insert(root->right, newEntry);
    }
    return root;
}

int search_min(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    else if (root->left == NULL) {
        return root->score;
    }
    else {
        return search_min(root->left);
    }
}

int search_max(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    else if (root->right == NULL) {
        return root->score;
    }
    else {
        return search_max(root->right);
    }
}


void print_between(Node* root, int min, int max) {
    if (root == NULL) {
        return;
    }
    print_between(root->left, min, max);

    if (root->score >= min && root->score <= max) {
        cout << root->score << " ";
    }

    print_between(root->right, min, max);
}

int main(int argc, char** argv) {

//    string path = argv[1];
    //cout << "path = " << path << endl;
 //   int s_min = atoi(argv[2]);
    //cout << "s_min = " << s_min << endl;

//    int s_max = atoi(argv[3]);
    //cout << "s_max = " << s_max << endl;

    Node* root = new Node[3];
    Node* rootTree = NULL;

    vector<string> scores;
    readFile(scores, "scores.csv");
    stringstream ss;
    scores.push_back(ss.str());
    for (int i = 1; i < scores.size() - 1; i++)
    {
        if (scores[i][0] == 'A') {
            root[i].is_home = false;
        }
        else {
            root[i].is_home = true;
        }

        for (int j = 2; j < scores[i].size(); j++)
        {
            if (scores[i][j] == ',')
            {
                string shirt_no_str = scores[i].substr(2, j);
                root[i].shirt_no = atoi(shirt_no_str.c_str());
                string score_str = scores[i].substr(j + 1, scores[i].size());
                root[i].score = atoi(score_str.c_str());
                break;
            }
        }
        rootTree = Insert(rootTree, root + i);
    }


    print_binary_tree(*rootTree);
    print_between(rootTree, search_min(rootTree), search_max(rootTree));
}
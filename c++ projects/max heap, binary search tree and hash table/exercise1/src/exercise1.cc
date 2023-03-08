
#include <iostream>
#include <vector>
#include "exercise1_utils.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

void swap(Node* a, Node* b)
{
    Node temp = *b;
    *b = *a;
    *a = temp;
}
void sort_heap(Node* hT, int i)
{
    int size = sizeof(hT);
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && hT[l].score > hT[largest].score)
        largest = l;
    if (r < size && hT[r].score > hT[largest].score)
        largest = r;

    if (largest != i)
    {
        swap(&hT[i], &hT[largest]);
        sort_heap(hT, largest);
    }
}
void push(Node* hT, Node entry)
{
    int size = sizeof(hT);
    for (int i = 0; i < size; i++)
    {
        if (hT[i].score < 0)
        {
            hT[i] = entry;
            break;
        }
    }
    size++;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        sort_heap(hT, i);
    }
}

void printArray(vector<Node>& hT)
{
    for (int i = 0; i < hT.size(); ++i)
        cout << hT[i].score << " ";
    cout << "\n";
}
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


Node pop(Node* hT)
{
    int size = sizeof(hT);
    Node popped = hT[0];
    hT[0].score = -1;

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        sort_heap(hT, i);
    }
    return popped;
}


int main()
{
    Node* heapTree = new Node[10];

    int heap_capacity = 10;
    Node* heap = new Node[heap_capacity];
    vector<string> scores;
    readFile(scores, "scores.csv");
    stringstream ss;
    scores.push_back(ss.str());
    for (int i = 1; i < scores.size()-1; i++)
    {
        if (scores[i][0] == 'A') {
            heap[i].is_home = false;
        }
        else {
            heap[i].is_home = true;
        }

        for (int j = 2; j < scores[i].size(); j++)
        {
            if (scores[i][j] == ',')
            {
                string shirt_no_str = scores[i].substr(2, j);
                heap[i].shirt_no = atoi(shirt_no_str.c_str());
                string score_str = scores[i].substr(j + 1, size(scores[i]));
                heap[i].score = atoi(score_str.c_str());
                break;
            }
        }
        push(heapTree, heap[i]);
    }


    int heap_size = 3;
    print_complete_binary_tree(heapTree, heap_size);

    vector<Node> bests;
    bests.push_back(pop(heapTree));
    bests.push_back(pop(heapTree));
    bests.push_back(pop(heapTree));
    for (int i = 0;i < bests.size();i++) {
        if (bests[i].is_home)
        {
            cout << "H";
        }
        else
        {
            cout << "A";
        }
        cout << " ";
        cout << bests[i].shirt_no;
        cout << " ";
        cout << bests[i].score << endl;
    }
}
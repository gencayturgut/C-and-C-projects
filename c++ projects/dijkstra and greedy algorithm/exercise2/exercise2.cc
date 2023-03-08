#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;
struct Node {
    int player;
};

vector<int> greedy_algorithm(int t, vector<vector<double>> matrix) {
    Node n;
    n.player = 0;
    vector<Node> visited(matrix.size(), n);
    vector<int> path;


    int min_index_count = 0;
    int min_index;
    visited[t].player = t;
    bool can_score = false;
    int current_node = t;
    for (int i = 0; i < matrix[t].size(); i++) {
        if (matrix[t][i] == 0) {
            continue;
        }

        if (matrix[t][i] > 0 && min_index_count == 0) {
            min_index = i;
            min_index_count = 1;
        }
        if (matrix[t][i] < matrix[t][min_index] && matrix[t][i] > 0) {
            min_index = i;
        }
    }
    visited[t].player = 999;
    if (matrix[current_node][current_node] != 0) {
        can_score = true;
    }
    path.push_back(current_node);
    while (!can_score) {
        path.push_back(min_index);
        current_node = min_index;
        min_index = 0;
        min_index_count = 0;
        visited[current_node].player = current_node;

        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[current_node][i] == 0 || visited[i].player == 999) {
                continue;
            }
            if (matrix[current_node][i] > 0 && min_index_count == 0) {
                min_index = i;
                min_index_count = 1;
            }
            if (matrix[current_node][min_index] > matrix[current_node][i]) {
                min_index = i;
            }
        }
        visited[current_node].player = 999;
        if (matrix[min_index][min_index] != 0) {
            can_score = true;
            path.push_back(min_index);
        }

    }


    return path;
}


void readFile(vector<string> &scores, string fileName) {
    ifstream file;
    file.open(fileName);
    string line;
    while (getline(file, line)) {
        scores.push_back(line);
    }
    file.close();
}

int main() {
    vector<string> times;
    readFile(times, "times.csv");
    stringstream ss;
    vector<vector<double>> times_matrix(11, vector<double>(11, 0));
    times.push_back(ss.str());

    for (int i = 0; i < times.size() - 1; i++) {
        int comma = 0;
        int index = 0;
        for (int j = 0; j < times[i].size(); j++) {
            if (times[i][j] == ',') {
                string time = times[i].substr(comma, j - comma);
                double time_d = stod(time);
                times_matrix[i][index] = time_d;
                index++;
                comma = j + 1;
            }
            if (j == times[i].size() - 1) {
                string time = times[i].substr(comma, j - comma + 1);
                double time_d = stod(time);
                times_matrix[i][index] = time_d;
            }
        }
    }

    for (int i = 0; i < times_matrix.size(); i++) {
        for (int j = 0; j < times_matrix[i].size(); j++) {
            if (j == times_matrix[i].size() - 1) {
                cout << times_matrix[i][j];
            } else {
                cout << times_matrix[i][j] << ",";
            }
        }
        cout << endl;
    }
    int s = 1;
    vector<int> greedy_path = greedy_algorithm(s, times_matrix);
    for (int i = 0; i < greedy_path.size(); i++) {
        if (i == greedy_path.size() - 1) {
            cout << greedy_path[i];
            break;
        }
        cout << greedy_path[i] << " ";


    }


    return 0;
}

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
    int where_from;
    double distance;
};

struct Scorer {
    int player;
    double scoring_probability;
};

vector<int> dijkstra_algorithm(int t, vector<vector<double>> matrix) {
    Node n;
    n.player = 999;
    n.where_from = 999;
    vector<Node> visited(matrix.size(), n);
    vector<int> unvisited(matrix.size(), 0);
    vector<double> distances(matrix.size(), INFINITY);
    Scorer k;
    k.player = 0;
    k.scoring_probability = 0;
    vector<Scorer> scorers(matrix.size(), k);
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][i] != 0) {
            scorers[i].player = i;
            scorers[i].scoring_probability = matrix[i][i];
            matrix[i][i] = 0;
        }
    }


    //fill unvisited
    int total = 0;
    for (int i = 0; i < matrix.size(); i++) {
        unvisited[i] = i;
        total += i;
    }
    total -= t;
    int min_index_count = 0;
    int min_index;
    visited[t].where_from = t;
    visited[t].player = t;
    distances[t] = 0;
    for (int i = 0; i < matrix[t].size(); i++) {
        if (matrix[t][i] == 0) {
            continue;
        }
        distances[i] = matrix[t][i];
        visited[i].where_from = t;
        if (matrix[t][i] > 0 && min_index_count == 0) {
            min_index = i;
            min_index_count = 1;
        }
        if (matrix[t][i] < matrix[t][min_index] && matrix[t][i] > 0) {
            min_index = i;
        }
    }
    while (total > 0) {
        total = total - min_index;
        unvisited[min_index] = 999;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[min_index][i] == 0) {
                continue;
            }

            if (distances[min_index] + matrix[min_index][i] < distances[i]) {
                distances[i] = distances[min_index] + matrix[min_index][i];
                visited[i].where_from = min_index;
            }
        }
        visited[min_index].player = min_index;
        for (int i = 0; i < unvisited.size(); i++) {
            if (unvisited[i] != 0) {
                min_index = i;
            }
        }
        for (int i = 0; i < distances.size(); i++) {
            if (visited[i].player != 999) {
                continue;
            }
            if (distances[i] < distances[min_index]) {
                min_index = i;
            }
        }

    }
    for (int i = 0; i < visited.size(); i++) {
        visited[i].distance = distances[i];
        if (t == scorers[i].player) {
            visited[i].distance = 1;
        }
    }
    int best_scorer = 0;
    int best_scorer_count = 0;
    for (int i = 0; i < scorers.size(); i++) {
        if (best_scorer_count == 0 && scorers[i].scoring_probability != 0) {
            best_scorer_count = 1;
            best_scorer = i;
        }
        if (scorers[best_scorer].scoring_probability * visited[best_scorer].distance <
            scorers[i].scoring_probability * visited[i].distance &&
            scorers[i].scoring_probability != 0)
            best_scorer = i;
    }
    vector<int> path;
    path.push_back(best_scorer);
    bool done = false;
    while (!done) {
        path.push_back(best_scorer);
        if (best_scorer == visited[best_scorer].where_from) {
            break;
        }
        best_scorer = visited[best_scorer].where_from;

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
    vector<string> probabilities;
    readFile(probabilities, "probabilities.csv");
    stringstream ss;
    vector<vector<double>> probabilities_matrix(11, vector<double>(11, 0));
    probabilities.push_back(ss.str());
    for (int i = 0; i < probabilities.size() - 1; i++) {
        int comma = 0;
        int index = 0;
        for (int j = 0; j < probabilities[i].size(); j++) {
            if (probabilities[i][j] == ',') {
                string prob = probabilities[i].substr(comma, j - comma);
                double probd = stod(prob);
                probabilities_matrix[i][index] = probd;
                index++;
                comma = j + 1;
            }
            if (j == probabilities[i].size() - 1) {
                string prob = probabilities[i].substr(comma, j - comma + 1);
                double probd = stod(prob);
                probabilities_matrix[i][index] = probd;
            }
        }
    }
    vector<vector<double>> probabilities_matrix_log(11, vector<double>(11, 0));
    for (int i = 0; i < probabilities_matrix.size(); i++) {
        for (int j = 0; j < probabilities_matrix.size(); j++) {
            if (probabilities_matrix[i][j] != 0 && i != j) {
                probabilities_matrix_log[i][j] = -log10(probabilities_matrix[i][j]);

            } else {
                probabilities_matrix_log[i][j] = probabilities_matrix[i][j];
            }


        }
    }
    for (int i = 0; i < probabilities_matrix.size(); i++) {
        for (int j = 0; j < probabilities_matrix[i].size(); j++) {
            if (j == probabilities_matrix[i].size() - 1) {
                cout << probabilities_matrix[i][j];
            } else {
                cout << probabilities_matrix[i][j] << ",";
            }
        }
        cout << endl;
    }
    int s = 1;
    vector<int> dijkstra_distances = dijkstra_algorithm(s, probabilities_matrix_log);
    for (int i = dijkstra_distances.size() - 1; i > 0; i--) {
        if (i == 1) {
            cout << dijkstra_distances[i];
            break;
        }
        cout << dijkstra_distances[i] << " ";
    }
    return 0;
}

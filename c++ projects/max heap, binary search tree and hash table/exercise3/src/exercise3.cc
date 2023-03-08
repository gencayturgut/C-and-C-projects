#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;
struct Node {
    int score = 0;
    string team;
    int shirt_no;
    int goals = 0;
    int assists = 0;
};

void readFile(vector<string> &scores, string fileName) {
    ifstream file;
    file.open(fileName);
    string line;
    while (getline(file, line)) {
        scores.push_back(line);
    }
    file.close();
}
int event_score_calculator(string event) {
    if (event == "S"){
        return 20;
    }
    else if (event == "A"){
        return 10;
    }
    else if (event == "T"){
        return 1;
    }
    else if (event == "P"){
        return 1;
    }
    else if (event == "SH"){
        return 2;
    }
    else if (event == "SG"){
        return 3;
    }
    else if (event == "IP"){
        return -1;
    }
    else if (event == "YC"){
        return -10;
    }
    else if (event == "RC"){
        return -20;
    }
    else if (event == "L"){
        return -2;
    }
    else if (event == "CG"){
        return -5;
    }
    else{
        return 0;
    }
}
int main(int argc, char** argv) {
    Node *hash_table = new Node[28];
    vector<string> events;
    readFile(events, "events.csv");
    stringstream ss;
    events.push_back(ss.str());

    int i = 1;
    int min_check = 0;
    int min = 16;
    while (min >= min_check) {

        int comma_counter = 0;
        int event_comma_1 = 0;
        int event_comma_2 = 0;
        int event_comma_3 = 0;
        for (int j = 0; j < events[i].size(); j++) {
            if (comma_counter == 3) {
                break;
            }
            if (events[i][j] == ',' && comma_counter == 0) {
                event_comma_1 = j;
                comma_counter++;
            } else if (events[i][j] == ',' && comma_counter == 1) {
                event_comma_2 = j;
                comma_counter++;
            } else if (events[i][j] == ',' && comma_counter == 2) {
                event_comma_3 = j;
                comma_counter++;
            }
        }
        string str_current_min = events[i].substr(0, event_comma_1);
        min_check = atoi(str_current_min.c_str());
        if (min < min_check) {
            break;
        }

        int shirt_no;
        string team = events[i].substr(event_comma_1 + 1, 1);
        int team_hash_no;
        if (team == "A") {
            team_hash_no = 99;
        } else {
            team_hash_no = 0;
        }
        string shirt_no_str = events[i].substr(event_comma_2 + 1, event_comma_3 - event_comma_2 - 1);
        shirt_no = atoi(shirt_no_str.c_str());

        string event_string = events[i].substr(event_comma_3 + 1, events[i].size() - event_comma_3 - 1);
        int event_value = event_score_calculator(event_string);
        int hash_number = (team_hash_no + shirt_no) % 28;
        int if_no_collision= 0;
        int b = 1;
        while (hash_table[hash_number].shirt_no != shirt_no && hash_table[hash_number].team != team) {
            if_no_collision++;
            if (hash_table[hash_number].shirt_no == 0) {
                hash_table[hash_number].score += event_value;
                hash_table[hash_number].shirt_no = shirt_no;
                hash_table[hash_number].team = team;
                if (event_string == "S") {
                    hash_table[hash_number].goals++;
                } else if (event_string == "A") {
                    hash_table[hash_number].assists++;

                }
                break;
            }
            if (hash_table[hash_number].shirt_no == shirt_no && hash_table[hash_number].team == team) {
                hash_table[hash_number].score += event_value;
                if (event_string == "S") {
                    hash_table[hash_number].goals++;
                } else if (event_string == "A") {
                    hash_table[hash_number].assists++;
                }
                break;
            }
            if (hash_table[hash_number].shirt_no == shirt_no && hash_table[hash_number].team != team) {
                hash_number = ((team_hash_no + shirt_no) % 28 + b * b) % 28;
            }
            if (hash_table[hash_number].shirt_no != shirt_no && hash_table[hash_number].team != team) {
                hash_number = ((team_hash_no + shirt_no) % 28 + b * b) % 28;

            }
            b++;


        }
        if(if_no_collision == 0) {
            hash_table[hash_number].score += event_value;
            if (event_string == "S") {
                hash_table[hash_number].goals++;
            } else if (event_string == "A") {
                hash_table[hash_number].assists++;

            }
        }

        i++;
        }


    cout << "Index Team No Goals Assists Score" << endl;
    for (int k = 0; k < 28; k++) {
        cout <<k <<"   " << hash_table[k].team <<"   " <<hash_table[k].shirt_no<< "   " <<hash_table[k].goals<< "   " <<hash_table[k].assists<< "   " <<hash_table[k].score <<endl;
    }
    }









// This time no utility functions are provided.

// Do not forget to parse the command line argument.

// Consider defining
// Key as a struct or a class that contains two fields: team and shirt number, and
// Value as a struct or a class that contains three fields: goals, assists and score.
// The hash table is an array of 28 such (Key, Value) pairs.





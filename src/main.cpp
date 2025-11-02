#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <math.h>
#include <random>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

// Random number generator for shuffling
std::mt19937 rng_shuffle(0); // Seeded with 0 for reproducibility

int col = 0;

// Read data
void input_schools_capacities(string filename, int *&Cap) {

    fstream file(filename, ios::in);
    string line, data;
    int sc, s;

    if (file.is_open()) {
        getline(file, line);
        stringstream str(line);
        while (getline(str, data, ','))
            ; // reads the header

        while (getline(file, line)) {

            stringstream str(line);
            getline(str, data, ',');
            sc = stoi(data);
            getline(str, data, ',');

            getline(str, data, ',');
            Cap[sc] = stoi(data);
            // printf("%d %d\n", sc, Cap[sc]);
        }
    }
    else {
        cout << "Could not open the file\n";
    }
}

void readrealschooldata(string filename, int *&Cap, double *&poorcap) {

    fstream file(filename, ios::in);
    string line, data;
    int sc, s;

    if (file.is_open()) {
        getline(file, line);
        stringstream str(line);
        while (getline(str, data, ','))
            ; // reads the header

        while (getline(file, line)) {

            stringstream str(line);
            getline(str, data, ',');
            sc = stoi(data);
            getline(str, data, ',');

            getline(str, data, ',');
            Cap[sc] = stoi(data);
            // printf("%d %d\n", sc, Cap[sc]);
            getline(str, data, ',');
            poorcap[sc] = stof(data);
        }
    }
    else {
        cout << "Could not open the file\n";
    }
}

void input_schools_preferences(string filename, int *&number_preferences, int **&preference, int **&schools_rejected) {

    fstream file(filename, ios::in);
    string line, data, stop;
    int st, s;

    if (file.is_open()) {
        getline(file, line);
        stringstream str(line);
        while (getline(str, data, ','))
            ; // reads the header

        while (getline(file, line)) {

            stringstream str(line);
            getline(str, data, ',');
            st = stoi(data);

            getline(str, data, ',');
            number_preferences[st] = stoi(data);

            getline(str, data, ',');
            bool leave_loop = false;
            if (data.find(']') != std::string::npos) {
                leave_loop = true;
            }
            data.erase(remove(data.begin(), data.end(), '['), data.end());
            data.erase(remove(data.begin(), data.end(), '"'), data.end());
            data.erase(remove(data.begin(), data.end(), ']'), data.end());

            s = 0;
            preference[st][s] = stoi(data);
            // printf("%d ", schools_preferences[st][s]);
            s = s + 1;

            if (not(leave_loop)) {
                while (getline(str, stop, ',')) {

                    if (stop.find(']') != std::string::npos) {
                        leave_loop = true;
                    }
                    data.erase(remove(data.begin(), data.end(), '"'), data.end());
                    data.erase(remove(data.begin(), data.end(), ']'), data.end());
                    preference[st][s] = stoi(stop);
                    // printf("%d ", schools_preferences[st][s]);
                    s = s + 1;
                    if (leave_loop) {
                        break;
                    }
                }
            }
            // printf("\n");

            getline(str, data, ',');
            leave_loop = false;
            if (data.find(']') != std::string::npos) {
                leave_loop = true;
            }
            data.erase(remove(data.begin(), data.end(), '['), data.end());
            data.erase(remove(data.begin(), data.end(), '"'), data.end());
            data.erase(remove(data.begin(), data.end(), ']'), data.end());

            s = 0;
            schools_rejected[st][s] = stoi(data);
            // printf("%d ", schools_rejected[st][s]);
            s = s + 1;

            if (not(leave_loop)) {
                while (getline(str, stop, ',')) {

                    if (stop.find(']') != std::string::npos) {
                        leave_loop = true;
                    }
                    data.erase(remove(data.begin(), data.end(), '"'), data.end());
                    data.erase(remove(data.begin(), data.end(), ']'), data.end());
                    schools_rejected[st][s] = stoi(stop);
                    // printf("%d ", schools_rejected[st][s]);
                    s = s + 1;
                    if (leave_loop) {
                        break;
                    }
                }
            }

            getline(str, data, ',');
        }
    }
    else {
        cout << "Could not open the file\n";
    }
}

void readrealstudentdata(string filename, int *&number_preferences, int *&number_family, int **&preference, bool *&poorind, int **&family) {

    fstream file(filename, ios::in);
    string line, data, stop;
    int st, s;

    if (file.is_open()) {
        getline(file, line);
        stringstream str(line);
        while (getline(str, data, ','))
            ; // reads the header

        while (getline(file, line)) {

            stringstream str(line);
            getline(str, data, ',');
            st = stoi(data);

            // getline(str, data, ',');
            number_preferences[st] = 0;

            getline(str, data, ',');
            bool leave_loop = false;
            if (data.find(']') != std::string::npos) {
                leave_loop = true;
            }
            data.erase(remove(data.begin(), data.end(), '['), data.end());
            data.erase(remove(data.begin(), data.end(), '"'), data.end());
            data.erase(remove(data.begin(), data.end(), ']'), data.end());

            s = 0;
            preference[st][s] = stoi(data);
            number_preferences[st]++;
            // printf("%d ", schools_preferences[st][s]);
            s = s + 1;

            if (not(leave_loop)) {
                while (getline(str, stop, ',')) {

                    if (stop.find(']') != std::string::npos) {
                        leave_loop = true;
                    }
                    data.erase(remove(data.begin(), data.end(), '"'), data.end());
                    data.erase(remove(data.begin(), data.end(), ']'), data.end());
                    preference[st][s] = stoi(stop);
                    // printf("%d ", schools_preferences[st][s]);
                    s = s + 1;
                    number_preferences[st]++;
                    if (leave_loop) {
                        break;
                    }
                }
            }
            // printf("\n");
            getline(str, data, ',');
            poorind[st] = stoi(data);

            getline(str, data, ',');
            leave_loop = false;
            if (data.find(']') != std::string::npos) {
                leave_loop = true;
            }
            data.erase(remove(data.begin(), data.end(), '['), data.end());
            data.erase(remove(data.begin(), data.end(), '"'), data.end());
            data.erase(remove(data.begin(), data.end(), ']'), data.end());

            s = 0;
            number_family[st] = 0;
            // cout << data << endl;
            if (data != "") {
                // cout << data << endl;
                family[st][s] = stoi(data);
                number_family[st]++;
                // printf("%d ", schools_preferences[st][s]);
                s = s + 1;
            }

            if (not(leave_loop)) {
                while (getline(str, stop, ',')) {

                    if (stop.find(']') != std::string::npos) {
                        leave_loop = true;
                    }
                    data.erase(remove(data.begin(), data.end(), '"'), data.end());
                    data.erase(remove(data.begin(), data.end(), ']'), data.end());
                    family[st][s] = stoi(stop);
                    // printf("%d ", schools_preferences[st][s]);
                    s = s + 1;
                    number_family[st]++;
                    if (leave_loop) {
                        break;
                    }
                }
            }
            getline(str, data, ',');
        }
    }
    else {
        cout << "Could not open the file\n";
    }
}

void removeStudent(vector<int> &v, int K) {
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end()) {
        v.erase(it);
    }
    else {
        cout << "WHAT?  Student " << K << " not in list??!" << endl;
    }
}

int getIndex(int v[], int K, int Nv) {
    for (int i = 0; i < Nv; i++) {
        if (v[i] == K) {
            return i;
        }
    }
    return -1;
    // calculating the index
}

void SchoolAssignment(double ALL, bool poor, bool family, int N_s, int N_e, int *number_preferences, int **preference, int *Cap, int **&RES, double *INDpoor, bool *poorst, int *number_family, int **familyschools) {
    // bool ALL = true;
    int *count_ind_Schools = new int[N_s]; // Index to count which student is next in each random ticket
    // initialize the count indext at the capacity of the schools
    for (int i = 0; i < N_s; i++) {
        count_ind_Schools[i] = Cap[i];
    }

    vector<vector<int>> rand_ticket(N_s); // random lists for schools (vector of vectors--> N_s upper vectors with each a variable length
    vector<vector<int>> temp_ticket(N_s); // temporary ticket (vector of vectors--> N_s upper vectors with each a lenght of Cap[i]

    int *maxpref = new int[N_e];
    int maxall = int(ALL * N_e);

    for (int i = 0; i < maxall; i++) {
        maxpref[i] = N_s;
    }
    for (int i = maxall; i < N_e; i++) {
        maxpref[i] = number_preferences[i];
    }

    // ++++++++++++++++++++++++++++++++++++++++++++++ Algorithm  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // ************* Create random list for each school (based on preference)

    // loop: assign schools to students based on preference
    for (int j = 0; j < N_e; j++) {
        // cout << "++++ Student " << j << " number preferences : " << maxpref[j] << endl;
        for (int t = 0; t < maxpref[j]; t++) {
            // cout << "School " << preference[j][t] << endl;
            if (preference[j][t] == N_s) {
                preference[j][t] = 0;
            }
            rand_ticket[preference[j][t]].push_back(j);
        }
        /*
        if (ALL) {
                int N_s2 = N_s - maxpref[j];
                for (int t = 0; t < N_s2; t++) {
                        //cout << "School " << preference[j][t] << endl;
                        if (schools_rejected[j][t] == N_s) schools_rejected[j][t] = 0;
                        rand_ticket[schools_rejected[j][t]].push_back(j);
                }
        }
        */
    }

    // cout << "check \n";
    srand(0);
    // random shuffle --> std::shuffle(myvector.begin(), myvector.end(), rng);
    for (int i = 0; i < N_s; i++) {
        std::shuffle(rand_ticket[i].begin(), rand_ticket[i].end(), rng_shuffle);
        // here put students that have family in school i at the front of rand_ticket[i] ALSO put poor students at the front if its a poor cpacity allocation

        if (poor) {
            if (i % 2 == 0) { // capacities for poor ppl
                for (int j = 0; j < rand_ticket[i].size(); j++) {
                    if (poorst[rand_ticket[i][j]] == 1) { // if student in random ticket is poor
                        int st = rand_ticket[i][j];
                        rand_ticket[i].erase(rand_ticket[i].begin() + j); // place them at the start of the ticket
                        rand_ticket[i].insert(rand_ticket[i].begin(), st);
                    }
                }
            }
            if (family) {
                for (int j = 0; j < rand_ticket[i].size(); j++) {
                    for (int l = 0; l < number_family[rand_ticket[i][j]]; l++) {
                        if (2 * familyschools[rand_ticket[i][j]][l] == i || 2 * familyschools[rand_ticket[i][j]][l] + 1 == i) {
                            int st = rand_ticket[i][j];
                            rand_ticket[i].erase(rand_ticket[i].begin() + j); // place them at the start of the ticket
                            rand_ticket[i].insert(rand_ticket[i].begin(), st);
                            break;
                        }
                    }
                }
            }
        }
        if (family) {
            for (int j = 0; j < rand_ticket[i].size(); j++) {
                for (int l = 0; l < number_family[rand_ticket[i][j]]; l++) {
                    if (familyschools[rand_ticket[i][j]][l] == i) {
                        int st = rand_ticket[i][j];
                        rand_ticket[i].erase(rand_ticket[i].begin() + j); // place them at the start of the ticket
                        rand_ticket[i].insert(rand_ticket[i].begin(), st);
                        break;
                    }
                }
            }
        }
    }

    /*
    //cout << " random list : \n";
    for (int i = 0; i < N_s; i++) {
            cout << "---- School " << i << "( Cap=" << Cap[i]<< "): \n";
            for (int j = 0; j < rand_ticket[i].size(); j++) {
                    cout << " Student " << rand_ticket[i][j] << endl;
            }
    }
    cout << endl;
    //*/
    //*************** Create temporary tickets
    for (int i = 0; i < N_s; i++) {
        for (int j = 0; j < min(Cap[i], int(rand_ticket[i].size())); j++) {
            temp_ticket[i].push_back(rand_ticket[i][j]);
        }
    }

    // Check for students with more than one assignment
    vector<vector<int>> double_schools(N_e);
    for (int s = 0; s < N_e; s++) {
        // cout << " Student " << s << endl;
        for (int i = 0; i < N_s; i++) {
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                if (temp_ticket[i][j] == s) {
                    // cout << " School " << i << endl;
                    double_schools[s].push_back(i);
                    break;
                }
            }
        }
    }

    //------------------- LOOP -------------------------------
    // assignment with lower reference get destroyed
    int itr = 0;
    while (true) {
        /*
        cout << "students assigned to schools:\n";
        for (int s = 0; s < N_e; s++) {
                cout << "******* Student " << s << endl;
                for (int i = 0; i < double_schools[s].size(); i++) {
                        cout << "School " << double_schools[s][i] << endl;
                }
        }
        cout << endl;
        //*/
        // cout << "+++++++++++++++++++++++++++++++++++++++++++ iteration " << itr << endl;
        int count_removals = 0;
        for (int i = 0; i < N_s; i++) {
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " check 0 \n";
                // cout << " School " << i << " student index " << j << " cap " << Cap[i] << endl;
                // cout << "Student " << temp_ticket[i][j] << endl;
                int s = temp_ticket[i][j];
                // cout << " check \n";
                // cout << double_schools[s].size() << endl;;
                if (double_schools[s].size() > 1) { // if student s is assigned to more than one school
                    count_removals++;
                    // cout <<"-->  assigned more than once\n";
                    int rank = getIndex(preference[s], i, maxpref[s]); // rank of the school for student
                    if (rank == -1) {
                        cout << " +++++++++++++++++++++++++++ WHAT 1 +++++++++++++++++++++++++++++++";
                        exit(0);
                    }
                    // cout << "rank of school " << i << " for student " << s << ": " << rank << endl;
                    bool highest = true;
                    if (rank > 0) {
                        for (int t = 0; t < double_schools[s].size(); t++) {
                            int rank_temp = getIndex(preference[s], double_schools[s][t], maxpref[s]);
                            if (rank_temp == -1) {
                                cout << "Preference Student " << s << endl;
                                for (int y = 0; y < maxpref[s]; y++) {
                                    cout << preference[s][y] << " ";
                                }
                                cout << endl;
                                cout << "Double school " << double_schools[s][t] << endl;

                                cout << "Double schools of student \n";
                                for (int j = 0; j < double_schools[s].size(); j++) {
                                    cout << double_schools[s][j] << " ";
                                }
                                cout << endl;
                                cout << "Temp ticket of double sch \n";
                                for (int j = 0; j < temp_ticket[double_schools[s][t]].size(); j++) {
                                    cout << temp_ticket[double_schools[s][t]][j] << " ";
                                }
                                cout << endl;
                                cout << "Random ticket of double sc \n";
                                for (int j = 0; j < rand_ticket[double_schools[s][t]].size(); j++) {
                                    cout << rand_ticket[double_schools[s][t]][j] << " ";
                                }
                                cout << endl;
                                cout << " +++++++++++++++++++++++++++ WHAT 2 +++++++++++++++++++++++++++++++";
                                exit(0);
                            }
                            if (rank_temp < rank) { // if school i is not the highest ranked among assigned schools
                                highest = false;
                                break;
                            }
                        }
                    }
                    if (!highest) { // if not the hisgest ranked school for student s then
                        // remove student s from school i
                        // cout << "student " << s << " must be removed from school " << i;
                        removeStudent(temp_ticket[i], s);
                        removeStudent(double_schools[s], i);
                        // Update temporary ticket
                        // cout << " index " << count_ind_Schools[i];
                        if (count_ind_Schools[i] < rand_ticket[i].size()) {
                            // cout << " --> new student: " << rand_ticket[i][count_ind_Schools[i]] << endl;
                            temp_ticket[i].push_back(rand_ticket[i][count_ind_Schools[i]]);
                            double_schools[rand_ticket[i][count_ind_Schools[i]]].push_back(i);
                            count_ind_Schools[i]++;
                        }
                        // else cout << " NO new student\n";
                    }
                }
            }
        }
        // cout << "count removals: " << count_removals << endl;
        if (count_removals == 0) {
            break;
        }
        itr++;
    }

    // check solution
    // cout << "students assigned to multiple schools:\n";
    string bad = "Students that have more than one assignment: \n";
    bool feas = true;
    string student_0 = "";
    int count_0 = 0;

    vector<int> bStu;
    for (int s = 0; s < N_e; s++) {
        // cout << "******* Student " << s << "\t";
        int count_b = 0;
        for (int i = 0; i < double_schools[s].size(); i++) {
            // cout << "School " << double_schools[s][i] << "\t";
            count_b++;
        }
        // cout << endl;
        if (count_b > 1) {
            bad += " Student " + to_string(s) + "\n";
            feas = false;
        }
        else if (count_b == 0) {
            student_0 += " Student " + to_string(s) + "\n";
            count_0++;
            bStu.push_back(s);
        }
    }

    if (!feas) {
        bad += "\n Overcapacity \n";
    }
    else {
        bad += "Overcapacity \n";
    }

    string capa = "";
    int cap_u = 0;
    for (int i = 0; i < N_s; i++) {
        // cout << "---- School " << i << ": \n";
        int count_s = 0;
        for (int j = 0; j < temp_ticket[i].size(); j++) {
            // cout << " Student " << temp_ticket[i][j] << endl;
            count_s++;
        }
        if (count_s > Cap[i]) {
            feas = false;
            bad += "---- School " + to_string(i) + ": \n";
        }
        else if (count_s < Cap[i]) {
            // cout << "School " + to_string(i) + ": " + to_string(Cap[i] - count_s) + " under capacity\n";
            cap_u += (Cap[i] - count_s);
            capa += "School " + to_string(i) + ": " + to_string(Cap[i] - count_s) + " under capacity\n";
            /*
            for (int t = 0; t < bStu.size(); t++) {
                    for (int q = 0; q < maxpref[bStu[t]]; q++) {
                            if (preference[bStu[t]][q] == i) {
                                    cout << "Student " << bStu[t] << "has this school as his " << q + 1 << "th choice \n";
                            }
                    }
            }
            */
        }
    }

    if (!feas) {
        cout << bad;
    }
    else {
        cout << "ALL GOOD! Feasible solution\n";
    }
    cout << "------------- Under capacity: \n";
    // cout << capa;
    cout << "++++ Total: " << cap_u << endl;
    RES[0][col] = cap_u;
    cout << "------------- Students not assigned: \n";
    // cout << student_0;
    cout << "++++ Total: " << count_0 << endl;
    RES[1][col] = count_0;
    cout << endl;
    ///*
    // print solution
    cout << "\n++++++++++++++++ SOLUTION ++++++++++++++++++++++ : \n";
    vector<int> first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, rest;
    if (!poor) {
        for (int i = 0; i < N_s; i++) {
            // cout << "---- School " << i << ": \n";
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " Student " << temp_ticket[i][j] << endl;
                if (preference[temp_ticket[i][j]][0] == i) {
                    first.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][1] == i) {
                    second.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][2] == i) {
                    third.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][3] == i) {
                    fourth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][4] == i) {
                    fifth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][5] == i) {
                    sixth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][6] == i) {
                    seventh.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][7] == i) {
                    eighth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][8] == i) {
                    ninth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][9] == i) {
                    tenth.push_back(temp_ticket[i][j]);
                }
                // else if (preference[temp_ticket[i][j]][10] == i && maxpref[i] > 10)eleventh.push_back(temp_ticket[i][j]);
                else {
                    rest.push_back(temp_ticket[i][j]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < N_s; i++) {
            // cout << "---- School " << i << ": \n";
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " Student " << temp_ticket[i][j] << endl;
                if (preference[temp_ticket[i][j]][0] == i || preference[temp_ticket[i][j]][1] == i) {
                    first.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][2] == i || preference[temp_ticket[i][j]][3] == i) {
                    second.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][4] == i || preference[temp_ticket[i][j]][5] == i) {
                    third.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][6] == i || preference[temp_ticket[i][j]][7] == i) {
                    fourth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][8] == i || preference[temp_ticket[i][j]][9] == i) {
                    fifth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][10] == i || preference[temp_ticket[i][j]][11] == i) {
                    sixth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][12] == i || preference[temp_ticket[i][j]][13] == i) {
                    seventh.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][14] == i || preference[temp_ticket[i][j]][15] == i) {
                    eighth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][16] == i || preference[temp_ticket[i][j]][17] == i) {
                    ninth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][18] == i || preference[temp_ticket[i][j]][19] == i) {
                    tenth.push_back(temp_ticket[i][j]);
                }
                // else if (preference[temp_ticket[i][j]][10] == i && maxpref[i] > 10)eleventh.push_back(temp_ticket[i][j]);
                else {
                    rest.push_back(temp_ticket[i][j]);
                }
            }
        }
    }
    cout << "Number of students with 1st preference school: " << first.size() << endl;
    RES[2][col] = first.size();
    cout << "Number of students with 2nd preference school: " << second.size() << endl;
    RES[3][col] = second.size();
    cout << "Number of students with 3rd preference school: " << third.size() << endl;
    RES[4][col] = third.size();
    cout << "Number of students with 4th preference school: " << fourth.size() << endl;
    RES[5][col] = fourth.size();
    cout << "Number of students with 5th preference school: " << fifth.size() << endl;
    RES[6][col] = fifth.size();
    cout << "Number of students with 6th preference school: " << sixth.size() << endl;
    RES[7][col] = sixth.size();
    cout << "Number of students with 7th preference school: " << seventh.size() << endl;
    RES[8][col] = seventh.size();
    cout << "Number of students with 8th preference school: " << eighth.size() << endl;
    RES[9][col] = eighth.size();
    cout << "Number of students with 9th preference school: " << ninth.size() << endl;
    RES[10][col] = ninth.size();
    cout << "Number of students with 10th preference school: " << tenth.size() << endl;
    RES[11][col] = tenth.size();
    cout << " --> rest: " << rest.size() << endl;
    RES[12][col] = rest.size();
    col++;

    // Swap kids that have each others first choice
    cout << "--------- now with improvment swap ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";
    for (int s = 0; s < N_e; s++) {
        // cout << "---- School " << i << ": \n";
        for (int ss = 0; ss < N_e; ss++) {
            if (s != ss) {
                if (double_schools[s].size() > 0 && double_schools[ss].size() > 0) {
                    int i = double_schools[s][0];
                    int ii = double_schools[ss][0];
                    if (preference[s][0] == ii && preference[ss][0] == i) {
                        // cout << " FOUND\n";
                        removeStudent(temp_ticket[i], s);
                        temp_ticket[i].push_back(ss);
                        double_schools[s][0] = ii;

                        removeStudent(temp_ticket[ii], ss);
                        temp_ticket[ii].push_back(s);
                        double_schools[ss][0] = i;
                    }
                }
            }
        }
    }
    // check solution
    // cout << "students assigned to multiple schools:\n";
    bad = "Students that have more than one assignment: \n";
    feas = true;
    student_0 = "";
    count_0 = 0;

    bStu.clear();
    for (int s = 0; s < N_e; s++) {
        // cout << "******* Student " << s << "\t";
        int count_b = 0;
        for (int i = 0; i < double_schools[s].size(); i++) {
            // cout << "School " << double_schools[s][i] << "\t";
            count_b++;
        }
        // cout << endl;
        if (count_b > 1) {
            bad += " Student " + to_string(s) + "\n";
            feas = false;
        }
        else if (count_b == 0) {
            student_0 += " Student " + to_string(s) + "\n";
            count_0++;
            bStu.push_back(s);
        }
    }

    if (!feas) {
        bad += "\n Overcapacity \n";
    }
    else {
        bad += "Overcapacity \n";
    }

    capa = "";
    cap_u = 0;
    for (int i = 0; i < N_s; i++) {
        // cout << "---- School " << i << ": \n";
        int count_s = 0;
        for (int j = 0; j < temp_ticket[i].size(); j++) {
            // cout << " Student " << temp_ticket[i][j] << endl;
            count_s++;
        }
        if (count_s > Cap[i]) {
            feas = false;
            bad += "---- School " + to_string(i) + ": \n";
        }
        else if (count_s < Cap[i]) {
            // cout << "School " + to_string(i) + ": " + to_string(Cap[i] - count_s) + " under capacity\n";
            cap_u += (Cap[i] - count_s);
            capa += "School " + to_string(i) + ": " + to_string(Cap[i] - count_s) + " under capacity\n";
            /*
            for (int t = 0; t < bStu.size(); t++) {
                    for (int q = 0; q < maxpref[bStu[t]]; q++) {
                            if (preference[bStu[t]][q] == i) {
                                    cout << "Student " << bStu[t] << "has this school as his " << q + 1 << "th choice \n";
                            }
                    }
            }
            */
        }
    }

    if (!feas) {
        cout << bad;
    }
    else {
        cout << "ALL GOOD! Feasible solution\n";
    }
    cout << "------------- Schools under capacity: \n";
    // cout << capa;
    cout << "++++ Total: " << cap_u << endl;
    RES[0][col] = cap_u;
    cout << "------------- Students not assigned: \n";
    // cout << student_0;
    cout << "++++ Total: " << count_0 << endl;
    RES[1][col] = count_0;
    cout << endl;
    ///*
    // print solution
    cout << "\n++++++++++++++++ SOLUTION ++++++++++++++++++++++ : \n";
    first.clear();
    second.clear();
    third.clear();
    fourth.clear();
    fifth.clear();
    sixth.clear();
    seventh.clear();
    eighth.clear();
    ninth.clear();
    tenth.clear();
    rest.clear();
    if (!poor) {
        for (int i = 0; i < N_s; i++) {
            // cout << "---- School " << i << ": \n";
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " Student " << temp_ticket[i][j] << endl;
                if (preference[temp_ticket[i][j]][0] == i) {
                    first.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][1] == i) {
                    second.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][2] == i) {
                    third.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][3] == i) {
                    fourth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][4] == i) {
                    fifth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][5] == i) {
                    sixth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][6] == i) {
                    seventh.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][7] == i) {
                    eighth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][8] == i) {
                    ninth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][9] == i) {
                    tenth.push_back(temp_ticket[i][j]);
                }
                // else if (preference[temp_ticket[i][j]][10] == i && maxpref[i] > 10)eleventh.push_back(temp_ticket[i][j]);
                else {
                    rest.push_back(temp_ticket[i][j]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < N_s; i++) {
            // cout << "---- School " << i << ": \n";
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " Student " << temp_ticket[i][j] << endl;
                if (preference[temp_ticket[i][j]][0] == i || preference[temp_ticket[i][j]][1] == i) {
                    first.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][2] == i || preference[temp_ticket[i][j]][3] == i) {
                    second.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][4] == i || preference[temp_ticket[i][j]][5] == i) {
                    third.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][6] == i || preference[temp_ticket[i][j]][7] == i) {
                    fourth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][8] == i || preference[temp_ticket[i][j]][9] == i) {
                    fifth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][10] == i || preference[temp_ticket[i][j]][11] == i) {
                    sixth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][12] == i || preference[temp_ticket[i][j]][13] == i) {
                    seventh.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][14] == i || preference[temp_ticket[i][j]][15] == i) {
                    eighth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][16] == i || preference[temp_ticket[i][j]][17] == i) {
                    ninth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][18] == i || preference[temp_ticket[i][j]][19] == i) {
                    tenth.push_back(temp_ticket[i][j]);
                }
                // else if (preference[temp_ticket[i][j]][10] == i && maxpref[i] > 10)eleventh.push_back(temp_ticket[i][j]);
                else {
                    rest.push_back(temp_ticket[i][j]);
                }
            }
        }
    }
    cout << "Number of students with 1st preference school: " << first.size() << endl;
    RES[2][col] = first.size();
    cout << "Number of students with 2nd preference school: " << second.size() << endl;
    RES[3][col] = second.size();
    cout << "Number of students with 3rd preference school: " << third.size() << endl;
    RES[4][col] = third.size();
    cout << "Number of students with 4th preference school: " << fourth.size() << endl;
    RES[5][col] = fourth.size();
    cout << "Number of students with 5th preference school: " << fifth.size() << endl;
    RES[6][col] = fifth.size();
    cout << "Number of students with 6th preference school: " << sixth.size() << endl;
    RES[7][col] = sixth.size();
    cout << "Number of students with 7th preference school: " << seventh.size() << endl;
    RES[8][col] = seventh.size();
    cout << "Number of students with 8th preference school: " << eighth.size() << endl;
    RES[9][col] = eighth.size();
    cout << "Number of students with 9th preference school: " << ninth.size() << endl;
    RES[10][col] = ninth.size();
    cout << "Number of students with 10th preference school: " << tenth.size() << endl;
    RES[11][col] = tenth.size();
    cout << " --> rest: " << rest.size() << endl;
    RES[12][col] = rest.size();
    col++;

    delete[] count_ind_Schools;
    delete[] maxpref;
}

void SerialDictatorship(double ALL, bool poor, bool family, int N_s, int N_e, int *number_preferences, int **preference, int *Cap, int **&RES, double *INDpoor, bool *stpoor, int *number_family, int **familyschools) {
    //----------------- Initialize
    int *maxpref = new int[N_e];
    int maxall = int(ALL * N_e);

    for (int i = 0; i < maxall; i++) {
        maxpref[i] = N_s;
    }
    for (int i = maxall; i < N_e; i++) {
        maxpref[i] = number_preferences[i];
    }

    int *currcap = new int[N_s];     // current cpacity of the schools
    vector<vector<int>> temp_ticket; // for solution
    for (int i = 0; i < N_s; i++) {
        currcap[i] = 0;
        vector<int> tempt;
        temp_ticket.push_back(tempt);
    }

    int count_0 = 0;
    if (!poor) {
        vector<int> rand_stu;
        // ----------------- Create random list of students
        for (int i = 0; i < N_e; i++) {
            rand_stu.push_back(i);
        }
        srand(0);

        if (family) {
            // PHASE 1
            for (int i = 0; i < N_e; i++) {
                for (int l = 0; l < number_family[rand_stu[i]]; l++) {
                    if (familyschools[rand_stu[i]][l] == preference[rand_stu[i]][0]) { // if its the first preference
                        temp_ticket[preference[rand_stu[i]][0]].push_back(rand_stu[i]);
                        // cout << "check 2 \n";
                        currcap[preference[rand_stu[i]][0]]++;
                        removeStudent(rand_stu, rand_stu[i]);
                        // cout << " chosen \n";
                        break;
                    }
                }
            }
        }

        std::shuffle(rand_stu.begin(), rand_stu.end(), rng_shuffle);
        count_0 = 0;
        // +++++++++++++++++++++ Start loop to assign students
        while (rand_stu.size() > 0) {
            int s = rand_stu[0];
            int i;
            // cout << "Students remaining: " << rand_stu.size() << " current student " << s << " number of preferences: "<< maxpref[s] << endl;
            for (i = 0; i < maxpref[s]; i++) {
                int currschool = preference[s][i];
                // cout << " School " << preference[s][i] << " ";
                if (currcap[currschool] < Cap[currschool]) {
                    // cout << "check \n";
                    // cout << "\n size " << temp_ticket<< endl;
                    temp_ticket[currschool].push_back(s);
                    // cout << "check 2 \n";
                    currcap[currschool]++;
                    removeStudent(rand_stu, s);
                    // cout << " chosen \n";
                    break;
                }
            }
            if (i == maxpref[s]) {
                removeStudent(rand_stu, s);
                count_0++;
                // cout << " NOT chosen \n";
            }
        }
    }
    else {
        vector<int> rand_stu;
        vector<int> rand_stu_poor;
        // ----------------- Create random list of students
        for (int i = 0; i < N_e; i++) {
            if (stpoor[i] == 1) {
                rand_stu_poor.push_back(i);
            }
            else {
                rand_stu.push_back(i);
            }
        }
        srand(0);
        if (family) {
            // PHASE 1
            for (int i = 0; i < N_e; i++) {
                if (!stpoor[i] == 1) {
                    for (int l = 0; l < number_family[i]; l++) {
                        if (2 * familyschools[i][l] + 1 == preference[i][0]) { // if its the first preference
                            int s = 2 * familyschools[i][l] + 1;
                            temp_ticket[s].push_back(i);
                            // cout << "check 2 \n";
                            currcap[s]++;
                            cout << " PHASE 1 \n";
                            removeStudent(rand_stu, i);
                            // cout << " chosen \n";
                            break;
                        }
                    }
                }
                else {
                    for (int l = 0; l < number_family[i]; l++) {
                        if (2 * familyschools[i][l] + 1 == preference[i][0]) { // if its the first preference
                            int s = 2 * familyschools[i][l];
                            temp_ticket[s].push_back(i);
                            // cout << "check 2 \n";
                            currcap[s]++;
                            cout << " PHASE 1 \n";
                            removeStudent(rand_stu_poor, i);
                            // cout << " chosen \n";
                            break;
                        }
                    }
                }
            }
        }
        // std::shuffle(rand_stu.begin(), rand_stu.end(), rng_shuffle);
        std::shuffle(rand_stu_poor.begin(), rand_stu_poor.end(), rng_shuffle);
        // +++++++++++++++++++++ Start loop to assign students first poor ppl
        while (rand_stu_poor.size() > 0) {
            int s = rand_stu_poor[0];
            int i;
            // cout << "Students remaining: " << rand_stu_poor.size() << " current student " << s << " number of preferences: "<< maxpref[s] << endl;
            for (i = 0; i < maxpref[s]; i++) {
                int currschool = preference[s][i];
                // cout << " School " << preference[s][i] << " ";
                if (currschool % 2 == 0 && currcap[currschool] < Cap[currschool]) { // only poor capcities
                    // cout << "check \n";
                    // cout << "\n size " << temp_ticket<< endl;
                    temp_ticket[currschool].push_back(s);
                    // cout << "check 2 \n";
                    currcap[currschool]++;
                    // cout << " PHASE 2 chosen \n";
                    removeStudent(rand_stu_poor, s);
                    // cout << " chosen \n";
                    break;
                }
            }
            if (i == maxpref[s]) {
                // cout << " PHASE 2 NOT chosen \n";
                removeStudent(rand_stu_poor, s);
                rand_stu.push_back(s);
                // count_0++;
                // cout << " NOT chosen \n";
            }
        }

        // NOW remaining students
        count_0 = 0;
        std::shuffle(rand_stu.begin(), rand_stu.end(), rng_shuffle);
        while (rand_stu.size() > 0) {
            int s = rand_stu[0];
            int i;
            // cout << "Students remaining: " << rand_stu.size() << " current student " << s << " number of preferences: "<< maxpref[s] << endl;
            for (i = 0; i < maxpref[s]; i++) {
                int currschool = preference[s][i];
                // cout << " School " << preference[s][i] << " ";
                if (currcap[currschool] < Cap[currschool]) {
                    // cout << "check \n";
                    // cout << "\n size " << temp_ticket<< endl;
                    temp_ticket[currschool].push_back(s);
                    // cout << "check 2 \n";
                    currcap[currschool]++;
                    removeStudent(rand_stu, s);
                    // cout << " chosen \n";
                    break;
                }
            }
            if (i == maxpref[s]) {
                removeStudent(rand_stu, s);
                count_0++;
                // cout << " NOT chosen \n";
            }
        }
    }

    int cap_u = 0;
    for (int i = 0; i < N_s; i++) {
        // cout << "---- School " << i << ": \n";
        int count_s = 0;
        for (int j = 0; j < temp_ticket[i].size(); j++) {
            // cout << " Student " << temp_ticket[i][j] << endl;
            count_s++;
        }
        if (count_s < Cap[i]) {
            // cout << "School " + to_string(i) + ": " + to_string(Cap[i] - count_s) + " under capacity\n";
            cap_u += (Cap[i] - count_s);
        }
    }

    cout << "\n--------------  Under capacity: " << cap_u << endl;
    RES[0][col] = cap_u;
    cout << "--------------  Number of students NOT assigned: " << count_0 << endl;
    RES[1][col] = count_0;
    cout << "\n++++++++++++++++ SOLUTION ++++++++++++++++++++++ : \n";
    vector<int> first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth, rest;
    if (!poor) {
        for (int i = 0; i < N_s; i++) {
            // cout << "---- School " << i << ": \n";
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " Student " << temp_ticket[i][j] << endl;
                if (preference[temp_ticket[i][j]][0] == i) {
                    first.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][1] == i) {
                    second.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][2] == i) {
                    third.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][3] == i) {
                    fourth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][4] == i) {
                    fifth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][5] == i) {
                    sixth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][6] == i) {
                    seventh.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][7] == i) {
                    eighth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][8] == i) {
                    ninth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][9] == i) {
                    tenth.push_back(temp_ticket[i][j]);
                }
                // else if (preference[temp_ticket[i][j]][10] == i && maxpref[i] > 10)eleventh.push_back(temp_ticket[i][j]);
                else {
                    rest.push_back(temp_ticket[i][j]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < N_s; i++) {
            // cout << "---- School " << i << ": \n";
            for (int j = 0; j < temp_ticket[i].size(); j++) {
                // cout << " Student " << temp_ticket[i][j] << endl;
                if (preference[temp_ticket[i][j]][0] == i || preference[temp_ticket[i][j]][1] == i) {
                    first.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][2] == i || preference[temp_ticket[i][j]][3] == i) {
                    second.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][4] == i || preference[temp_ticket[i][j]][5] == i) {
                    third.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][6] == i || preference[temp_ticket[i][j]][7] == i) {
                    fourth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][8] == i || preference[temp_ticket[i][j]][9] == i) {
                    fifth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][10] == i || preference[temp_ticket[i][j]][11] == i) {
                    sixth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][12] == i || preference[temp_ticket[i][j]][13] == i) {
                    seventh.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][14] == i || preference[temp_ticket[i][j]][15] == i) {
                    eighth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][16] == i || preference[temp_ticket[i][j]][17] == i) {
                    ninth.push_back(temp_ticket[i][j]);
                }
                else if (preference[temp_ticket[i][j]][18] == i || preference[temp_ticket[i][j]][19] == i) {
                    tenth.push_back(temp_ticket[i][j]);
                }
                // else if (preference[temp_ticket[i][j]][10] == i && maxpref[i] > 10)eleventh.push_back(temp_ticket[i][j]);
                else {
                    rest.push_back(temp_ticket[i][j]);
                }
            }
        }
    }
    cout << "Number of students with 1st preference school: " << first.size() << endl;
    RES[2][col] = first.size();
    cout << "Number of students with 2nd preference school: " << second.size() << endl;
    RES[3][col] = second.size();
    cout << "Number of students with 3rd preference school: " << third.size() << endl;
    RES[4][col] = third.size();
    cout << "Number of students with 4th preference school: " << fourth.size() << endl;
    RES[5][col] = fourth.size();
    cout << "Number of students with 5th preference school: " << fifth.size() << endl;
    RES[6][col] = fifth.size();
    cout << "Number of students with 6th preference school: " << sixth.size() << endl;
    RES[7][col] = sixth.size();
    cout << "Number of students with 7th preference school: " << seventh.size() << endl;
    RES[8][col] = seventh.size();
    cout << "Number of students with 8th preference school: " << eighth.size() << endl;
    RES[9][col] = eighth.size();
    cout << "Number of students with 9th preference school: " << ninth.size() << endl;
    RES[10][col] = ninth.size();
    cout << "Number of students with 10th preference school: " << tenth.size() << endl;
    RES[11][col] = tenth.size();
    cout << " --> rest: " << rest.size() << endl;
    RES[12][col] = rest.size();
    col++;

    delete[] maxpref;
    delete[] currcap;
}

int main() {
    //-------------------- Read data
    /*
    const int N_s = 3; // number of schools
    const int N_e = 6; // number of students

    vector<vector<int>> preference(N_e); //preferences (vector of vectors --> N_e upper vectors with each a variable length
    preference[0].push_back(0);
    preference[0].push_back(1);

    preference[1].push_back(0);
    preference[1].push_back(1);

    preference[2].push_back(1);
    preference[2].push_back(2);
    preference[2].push_back(0);

    preference[3].push_back(1);

    preference[4].push_back(1);
    preference[4].push_back(2);

    preference[5].push_back(2);
    preference[5].push_back(0);

    int Cap[N_s] = { 2,2,1 }; // Cpacities of the school
    */

    bool realdata = true; // Using real data ?
    bool poor = true;
    bool family = true;

    if (!realdata) {
        poor = false;
        family = false;
        int N_e = 7000;
        int N_s = 75;
        double *INDpoor = new double[N_s];
        if (poor) {
            N_s = N_s * 2;
        }
        bool *stpoor = new bool[N_e];

        int **preference = new int *[N_e];
        int **familyschools = new int *[N_e];
        int **schools_rejected = new int *[N_e];
        for (int i = 0; i < N_e; i++) {
            preference[i] = new int[N_s];
            schools_rejected[i] = new int[N_s];
            familyschools[i] = new int[N_s];
        }
        int *number_preferences = new int[N_e];
        int *number_family = new int[N_e];
        int *Cap = new int[N_s];

        int column = 33; // number of experimets: 11 experiments for % of students with optimal strategy * 3 algorithms
        int row = 13;    // number of metrics

        int **RES = new int *[row];
        for (int i = 0; i < row; i++) {
            RES[i] = new int[column];
        }

        vector<string> namecap = {"6000", "6500", "7000", "7500", "8000"};
        for (int icap = 0; icap < 5; icap++) {
            ofstream resultI("Instance_capacity_" + namecap[icap] + ".txt");
            cout << "*********************************** CAPACITY: " << namecap[icap] << " ***********************************************\n";
            for (int inst = 0; inst < 5; inst++) {
                resultI << "++++++++++++++++++++++++++++++++++++++++++++++++++++++ Instance " << inst + 1 << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";
                col = 0;
                cout << "++ Start reading data \n";
                input_schools_preferences("schools_assignments_" + to_string(inst + 1) + ".csv", number_preferences, preference, schools_rejected);
                input_schools_capacities("schools_capacities_" + to_string(inst + 1) + "_" + namecap[icap] + ".csv", Cap);
                cout << "-- End reading data\n";
                for (int i = 0; i < N_e; i++) {
                    for (int j = number_preferences[i]; j < N_s; j++) {
                        preference[i][j] = schools_rejected[i][j - number_preferences[i]];
                    }
                }
                string head = "\t";

                // After reading data
                if (poor) {
                    for (int i = 0; i < N_e; i++) {
                        vector<int> temp1;
                        vector<int> temp2;
                        for (int j = 0; j < number_preferences[i]; j++) {
                            temp1.push_back(preference[i][j]);
                        }
                        for (int j = 0; j < N_s / 2 - number_preferences[i]; j++) {
                            temp2.push_back(schools_rejected[i][j]);
                        }
                        int k = 0;
                        for (int j = 0; j < number_preferences[i] * 2; j += 2) {
                            preference[i][j] = 2 * temp1[k];
                            preference[i][j + 1] = 2 * temp1[k] + 1;
                            k++;
                        }
                        k = 0;
                        for (int j = 0; j < (N_s / 2 - number_preferences[i]) * 2; j += 2) {
                            schools_rejected[i][j] = 2 * temp2[k];
                            schools_rejected[i][j + 1] = 2 * temp2[k] + 1;
                            k++;
                        }
                        number_preferences[i] *= 2;
                    }
                    vector<int> temp1;
                    for (int i = 0; i < N_s / 2; i++) {
                        temp1.push_back(Cap[i]);
                    }
                    int k = 0;
                    for (int i = 0; i < N_s; i += 2) {
                        Cap[i] = int(INDpoor[k] * temp1[k]); // capacity for poor
                        Cap[i + 1] = temp1[k] - int(INDpoor[k] * temp1[k]);
                        k++;
                    }
                }

                //--------------------- School assignments
                for (int f = 0; f < 11; f++) {
                    double pr = f / 10.0;
                    head += "A1_" + to_string(int(pr * 100)) + "%\tA2_" + to_string(int(pr * 100)) + "%\tA3_" + to_string(int(pr * 100)) + "%\t";
                    cout << " ++++++++++++++++++ " << int(pr * 100) << "% of students with ALL schools as a preference ++++++++++++++++++++++++++++\n";
                    cout << "************ NORMAL ASSIGNMENT ************************\n\n";
                    SchoolAssignment(pr, poor, family, N_s, N_e, number_preferences, preference, Cap, RES, INDpoor, stpoor, number_family, familyschools);
                    cout << "\n********** SERIAL DICTATORSHIP **********************\n\n";
                    SerialDictatorship(pr, poor, family, N_s, N_e, number_preferences, preference, Cap, RES, INDpoor, stpoor, number_family, familyschools);
                }

                // Rows same as in excl
                // columns: percentage f (3 columns: normal assignment, with improvement, serial dictatorship)

                resultI << head << endl;

                vector<string> rr = {
                    "UC\t",
                    "NA\t",
                    "P_1\t",
                    "P_2\t",
                    "P_3\t",
                    "P_4\t",
                    "P_5\t",
                    "P_6\t",
                    "P_7\t",
                    "P_8\t",
                    "P_9\t",
                    "P_10\t",
                    "P_>10\t",
                };
                for (int r = 0; r < row; r++) {
                    string q = rr[r];
                    for (int c = 0; c < column; c++) {
                        q += to_string(RES[r][c]) + "\t";
                        // resultI << rr[r] << RES[r][c] << "\t";
                    }
                    q += "\n";
                    resultI << q;
                }
                resultI << endl;
            }
            resultI << "\n *************** LEGEND ******************\n\n-----------ROWS---------\nUC:\tNumber of vacant places in schools\nNA:\tNumber of students that are not assigned to a school\nP_i:\tNumber of students that are assigned to their i^th preferred school\n----------COLUMNS----------\nA1_i%:\tSPDA without optimization, with i% of students choosing the optimal strategy\nA2_i%:\tSPDA with optimization, with i% of students choosing the optimal strategy\nA3_i%:\tSerial dictatorship algorithm with i% of students choosing the optimal strategy";
            // resultI << "\n\n *************** INFORMATION *************\nTotal school capacity:\t" << namecap[icap] << "\nTotal number of students:\t" << N_e << "\nTotal number of schools : \t" << N_s << endl;
            if (!poor) {
                resultI << "\n\n *************** INFORMATION *************\nTotal school capacity:\t" << namecap[icap] << "\nTotal number of students:\t" << N_e << "\nTotal number of schools : \t" << N_s << endl;
            }
            else {
                resultI << "\n\n *************** INFORMATION *************\nTotal school capacity:\t" << namecap[icap] << "\nTotal number of students:\t" << N_e << "\nTotal number of schools : \t" << N_s / 2 << endl;
            }
            resultI << "Each instance corresponds with different random numbers for the data\nSame random numbers are used for the algorithms for each percentage of students using the optimal strategy (common random numbers)";
            resultI.close();
        }
        for (int i = 0; i < N_e; i++) {
            delete[] preference[i];
            delete[] schools_rejected[i];
            delete[] familyschools[i];
        }
        delete[] preference;
        delete[] schools_rejected;
        delete[] number_preferences;
        delete[] familyschools;
        delete[] number_family;
        delete[] Cap;
        delete[] INDpoor;
        delete[] stpoor;

        for (int i = 0; i < row; i++) {
            delete[] RES[i];
        }
        delete[] RES;
    }
    else {
        int N_e = 8500;
        int N_s = 86;
        double *INDpoor = new double[N_s];
        if (poor) {
            N_s = N_s * 2;
        }
        bool *stpoor = new bool[N_e];

        int **preference = new int *[N_e];
        int **familyschools = new int *[N_e];
        int **schools_rejected = new int *[N_e];
        for (int i = 0; i < N_e; i++) {
            preference[i] = new int[N_s];
            schools_rejected[i] = new int[N_s];
            familyschools[i] = new int[N_s];
        }
        int *number_preferences = new int[N_e];
        int *number_family = new int[N_e];
        int *Cap = new int[N_s];

        int column = 3; // number of experimets: 11 experiment * 3 algorithms
        int row = 13;   // number of metrics
        int **RES = new int *[row];
        for (int i = 0; i < row; i++) {
            RES[i] = new int[column];
        }

        readrealschooldata("realschooldata.csv", Cap, INDpoor);
        readrealstudentdata("realstudentdata.csv", number_preferences, number_family, preference, stpoor, familyschools);

        for (int i = 0; i < N_e; i++) {
            int it = 0;
            for (int l = 0; l < N_s; l++) {
                bool schrj = true;
                for (int j = 0; j < number_preferences[i]; j++) {
                    if (preference[i][j] == l) {
                        schrj = false;
                        break;
                    }
                }
                if (schrj) {
                    schools_rejected[i][it] = l;
                    it++;
                }
            }
        }

        // After reading data
        if (poor) {
            for (int i = 0; i < N_e; i++) {
                vector<int> temp1;
                vector<int> temp2;
                for (int j = 0; j < number_preferences[i]; j++) {
                    temp1.push_back(preference[i][j]);
                }
                for (int j = 0; j < N_s / 2 - number_preferences[i]; j++) {
                    temp2.push_back(schools_rejected[i][j]);
                }
                int k = 0;
                for (int j = 0; j < number_preferences[i] * 2; j += 2) {
                    preference[i][j] = 2 * temp1[k];
                    preference[i][j + 1] = 2 * temp1[k] + 1;
                    k++;
                }
                k = 0;
                for (int j = 0; j < (N_s / 2 - number_preferences[i]) * 2; j += 2) {
                    schools_rejected[i][j] = 2 * temp2[k];
                    schools_rejected[i][j + 1] = 2 * temp2[k] + 1;
                    k++;
                }
                number_preferences[i] *= 2;
            }
            vector<int> temp1;
            for (int i = 0; i < N_s / 2; i++) {
                temp1.push_back(Cap[i]);
            }
            int k = 0;
            for (int i = 0; i < N_s; i += 2) {
                Cap[i] = int(INDpoor[k] * temp1[k]); // capacity for poor
                Cap[i + 1] = temp1[k] - int(INDpoor[k] * temp1[k]);
                k++;
            }
        }

        /*
        cout << "Cap and Poor\n";
        for (int i = 0; i < N_s; i++) {
                cout << Cap[i] << " " << INDpoor[i] <<  endl;
        }
        cout << "Number pref, number family, poor\n";
        for (int i = 0; i < N_e; i++) {
                cout << number_preferences[i] << " " << number_family[i] << " " << stpoor[i] << endl;
        }
        cout << "Preferences\n";
        for (int i = 0; i < N_e; i++) {
                for (int j = 0; j < number_preferences[i]; j++) {
                        cout << preference[i][j] <<  " ";
                }
                cout << endl;
        }
        cout << "Family\n";
        for (int i = 0; i < N_e; i++) {
                if (number_family[i] == 0) cout << " no fam :(\n";
                else {
                        for (int j = 0; j < number_family[i]; j++) {
                                cout << familyschools[i][j] << " ";
                        }
                        cout << endl;
                }
        }
        //*/

        string resname = "";
        if (!poor && !family) {
            resname = "Instance_real_noIND_noFamily.txt";
        }
        else if (poor && !family) {
            resname = "Instance_real_IND_noFamily.txt";
        }
        else if (!poor && family) {
            resname = "Instance_real_noIND_Family.txt";
        }
        else {
            resname = "Instance_real_IND_Family.txt";
        }

        ofstream resultI(resname);
        resultI << "++++++++++++++++++++++++++++++++++++++++++++++++++++++ RESULTS of: " << resname << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n";
        col = 0;

        for (int i = 0; i < N_e; i++) {
            for (int j = number_preferences[i]; j < N_s; j++) {
                preference[i][j] = schools_rejected[i][j - number_preferences[i]];
            }
        }
        string head = "\t";

        //--------------------- School assignments
        for (int f = 0; f < column / 3; f++) {
            double pr = f / 10.0;
            head += "A1_" + to_string(int(pr * 100)) + "%\tA2_" + to_string(int(pr * 100)) + "%\tA3_" + to_string(int(pr * 100)) + "%\t";
            cout << " ++++++++++++++++++ " << int(pr * 100) << "% of students with ALL schools as a preference ++++++++++++++++++++++++++++\n";
            cout << "************ NORMAL ASSIGNMENT ************************\n\n";
            SchoolAssignment(pr, poor, family, N_s, N_e, number_preferences, preference, Cap, RES, INDpoor, stpoor, number_family, familyschools);
            cout << "\n********** SERIAL DICTATORSHIP **********************\n\n";
            SerialDictatorship(pr, poor, family, N_s, N_e, number_preferences, preference, Cap, RES, INDpoor, stpoor, number_family, familyschools);
        }

        // Rows same as in excl
        // columns: percentage f (3 columns: normal assignment, with improvement, serial dictatorship)

        resultI << head << endl;

        vector<string> rr = {
            "UC\t",
            "NA\t",
            "P_1\t",
            "P_2\t",
            "P_3\t",
            "P_4\t",
            "P_5\t",
            "P_6\t",
            "P_7\t",
            "P_8\t",
            "P_9\t",
            "P_10\t",
            "P_>10\t",
        };
        for (int r = 0; r < row; r++) {
            string q = rr[r];
            for (int c = 0; c < column; c++) {
                q += to_string(RES[r][c]) + "\t";
                // resultI << rr[r] << RES[r][c] << "\t";
            }
            q += "\n";
            resultI << q;
        }
        resultI << endl;

        int TOTcap = 0;
        for (int i = 0; i < N_s; i++) {
            TOTcap += Cap[i];
        }
        resultI << "\n *************** LEGEND ******************\n\n-----------ROWS---------\nUC:\tNumber of vacant places in schools\nNA:\tNumber of students that are not assigned to a school\nP_i:\tNumber of students that are assigned to their i^th preferred school\n----------COLUMNS----------\nA1_i%:\tSPDA without optimization, with i% of students choosing the optimal strategy\nA2_i%:\tSPDA with optimization, with i% of students choosing the optimal strategy\nA3_i%:\tSerial dictatorship algorithm with i% of students choosing the optimal strategy";
        if (!poor) {
            resultI << "\n\n *************** INFORMATION *************\nTotal school capacity:\t" << TOTcap << "\nTotal number of students:\t" << N_e << "\nTotal number of schools : \t" << N_s << endl;
        }
        else {
            resultI << "\n\n *************** INFORMATION *************\nTotal school capacity:\t" << TOTcap << "\nTotal number of students:\t" << N_e << "\nTotal number of schools : \t" << N_s / 2 << endl;
        }
        resultI << "Same random numbers are used for the algorithms for each percentage of students using the optimal strategy (common random numbers)";
        resultI.close();

        for (int i = 0; i < N_e; i++) {
            delete[] preference[i];
            delete[] schools_rejected[i];
            delete[] familyschools[i];
        }
        for (int i = 0; i < row; i++) {
            delete[] RES[i];
        }
        delete[] familyschools;
        delete[] RES;
        delete[] preference;
        delete[] schools_rejected;
        delete[] number_preferences;
        delete[] number_family;
        delete[] Cap;
        delete[] INDpoor;
        delete[] stpoor;
    }
}
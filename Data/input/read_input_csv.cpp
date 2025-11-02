#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define maxstudents 7000
#define maxschools 150


typedef int matrixSS[maxstudents + 1][maxschools + 1];
typedef int listSC[maxschools + 1];
typedef int listST[maxstudents + 1];

matrixSS schools_preferences, schools_rejected;
listST number_preferences;
listSC schools_capacity;

void input_schools_capacities(char *filename) {

	fstream file (filename, ios::in);
	string line, data;
	int sc, s;

	if(file.is_open())
	{
		getline(file, line);
		stringstream str(line);
		while(getline(str, data, ',')); //reads the header
		
		while(getline(file, line))
		{

			stringstream str(line);
			getline(str, data, ',');
			sc = stoi(data);
			getline(str, data, ',');

			getline(str, data, ',');
			schools_capacity[sc] = stoi(data);
			printf("%d %d\n", sc, schools_capacity[sc]);
			

		}

	} else cout<<"Could not open the file\n";
}

void input_schools_preferences(char *filename) {

	fstream file (filename, ios::in);
	string line, data, stop;
	int st, s;

	if(file.is_open())
	{
		getline(file, line);
		stringstream str(line);
		while(getline(str, data, ',')); //reads the header
		
		while(getline(file, line))
		{

			stringstream str(line);
			getline(str, data, ',');
			st = stoi(data);
			
			getline(str, data, ',');
			number_preferences[st] = stoi(data);
			

			getline(str, data, ',');
			bool leave_loop = false;
			if (data.find(']') != std::string::npos)
					leave_loop = true; 
			data.erase(remove(data.begin(), data.end(), '['), data.end());
			data.erase(remove(data.begin(), data.end(), '"'), data.end());
			data.erase(remove(data.begin(), data.end(), ']'), data.end());

			s = 0;
			schools_preferences[st][s] = stoi(data);
			//printf("%d ", schools_preferences[st][s]);
			s = s + 1;
			
			if (not (leave_loop)) {
				while(getline(str, stop, ',')) {
					
					if (stop.find(']') != std::string::npos)
						leave_loop = true; 
					data.erase(remove(data.begin(), data.end(), '"'), data.end());
					data.erase(remove(data.begin(), data.end(), ']'), data.end());
					schools_preferences[st][s] = stoi(stop);
					//printf("%d ", schools_preferences[st][s]);
					s = s + 1;
					if (leave_loop)
						break;
				}
			}
			//printf("\n");
			
			getline(str, data, ',');
			leave_loop = false;
			if (data.find(']') != std::string::npos)
					leave_loop = true; 
			data.erase(remove(data.begin(), data.end(), '['), data.end());
			data.erase(remove(data.begin(), data.end(), '"'), data.end());
			data.erase(remove(data.begin(), data.end(), ']'), data.end());

			s = 0;
			schools_rejected[st][s] = stoi(data);
			//printf("%d ", schools_rejected[st][s]);
			s = s + 1;
			
			if (not (leave_loop)) {
				while(getline(str, stop, ',')) {
					
					if (stop.find(']') != std::string::npos)
						leave_loop = true; 
					data.erase(remove(data.begin(), data.end(), '"'), data.end());
					data.erase(remove(data.begin(), data.end(), ']'), data.end());
					schools_rejected[st][s] = stoi(stop);
					//printf("%d ", schools_rejected[st][s]);
					s = s + 1;
					if (leave_loop)
						break;
				}
			}
						
			getline(str, data, ',');

		}

	} else cout<<"Could not open the file\n";
}

int preprocessData(int argc, char **argv) {

	input_schools_preferences("schools_preferences_1.csv");
	input_schools_capacities("schools_capacities_1.csv");
	
}
// read in file
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

string read_inputs(string filename){
	ifstream f(filename);

        if (!f.is_open()){
                cerr << "failed to open file \n";
                return " ";
        }

        string s;
        string contents;
	while (getline(f, s)){
                contents+= s;
        }
	
	f.close();
        return contents;
}

long check_range(string min, string max){
	long counter = 0;
	
	if (min.length()%2 !=0){
		// must have even number of digits
		if (max.length() == min.length()){
			// know this can never have one
			return 0;
		} else {
			min = to_string(static_cast<int>(pow(10, max.length()-1)));
		}
	}
	if (max.length()%2 !=0){
		//same here, must have even digits
		max = to_string(static_cast<int>(pow(10, max.length())-1));
	}
		
	int lowest = stol(min.substr(0, min.length() / 2));
	int highest = stol(max.substr(0, max.length() / 2));
	
	for (int v=lowest; v<highest+1; v++) {
		long test = stol(to_string(v) + to_string(v));
		// cout << v<<"\t"<<test<<"\n";
		if ((stol(min) <= test) && (stol(max) >= test)) {
			counter +=test;
		}
	}

	return counter;
}

int main(){
	//string s = read_inputs("testin.txt");
	string s = read_inputs("input.txt");
	// make sure we get the loop at the end
	s += ",";
		
	long total_counts = 0;
	long counts;
	while (s.find(",") != string::npos) {
		string new_range = s.substr(0, s.find(","));
		counts = check_range(new_range.substr(0, new_range.find("-")), new_range.substr(new_range.find("-")+1, -1));
		total_counts += counts;
		
		s = s.substr(s.find(",")+1, -1);
	}

	cout << "part 1: "<<total_counts << "\n";
}

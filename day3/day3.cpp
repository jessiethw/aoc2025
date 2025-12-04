#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string get_max_chars(string s){
	
	char first = s[0];
	int max_ind = 0;
	
	// get max char in string
	// if it's the last char, it cant be the max
	for (int i=1; i<(s.length()-1); i++){
		if (first < s[i]){
			first = s[i];
			max_ind = i;
		}
	}

	string best;
	best+=first;
	// now find the max of the rest
	char last = '0';  //any other number is greater
	for (int j=max_ind+1; j<s.length(); j++){
		if (last < s[j]){
			last = s[j];
		}
	}
	best+=last;
	return best;
}

string max_joltage(string s){
	string best;
	char current='0';
	int ind = -1;
	int nchars_left = 11;

	while (nchars_left >=0){
		for (int i=ind+1; i<(s.length()-nchars_left); i++){
		
			if (current < s[i]) {
				current = s[i];
				ind=i; //next time to check	
			}
		}
		
		best += current;
		current='0';
		nchars_left-=1;
	}

	return best;
}

long parse_lines(string filename, bool use_12){
	ifstream f(filename);

	if (!f.is_open()){
		cerr << "failed to open \n";
		return 1;
	}
	
	string s;
	long sum=0;
	while (getline(f,s)){
		if (!use_12){
			sum += stoi(get_max_chars(s));
		} else {
			sum += stol(max_joltage(s));
		}
	}

	f.close();
	return sum;

}

int main(){
	
	//string file = "testin.txt";
	string file="input.txt";
	
	int sum = parse_lines(file, 0);
	cout << "Part 1: "<<sum<<"\n";
	
	long sum2 = parse_lines(file, 1);
	cout << "Part 2: " << sum2<<"\n";
}

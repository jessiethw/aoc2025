#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

int print_arr(long arr[][2], int rows){
	int cols=2;
	for (int i=0; i<rows; i++){
		for (int j=0; j< cols; j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}

int print_vec(vector<string>& arr){
        for (int i=0; i<arr.size(); i++){
        	cout<<arr[i]<<"\n";
        }
        return 0;
}


int parse_lines(string filename, vector<string>& fresh, vector<string>& veg){
        ifstream f(filename);

        if (!f.is_open()){
                cerr << "failed to open \n";
                return 1;
        }
	
	string s;
        while (getline(f,s)){
               if (s.find("-") != string::npos){
		       fresh.push_back(s);
	       } else if (!s.empty()) {
		       veg.push_back(s);
	       }
        }
	f.close();

	if (f.is_open()){
		cerr<<"failed to close \n";
		return 1;
	} else { return 0;}

}

bool scan_em(long veg, long freezer[][2], int rows){
	bool good = 0;
	int i=0;
	while ((!good)&&(i<rows)){
		if ((veg >=freezer[i][0])&&(veg<=freezer[i][1])){
			good=1;
		} else {
			i++;
		}
	}
	return good;
}

long in_range(long start, long stop){
	if (start!=0){
		return (stop-start)+1;
	} else {
		return 0;
	}
}

long count_all(long freezer[][2], int rows){
	// start by iteratively removing overlap among rows
	int nchanged=100;
	while (nchanged>0){
		nchanged = 0;
		for (int i=0; i<rows; i++){
			long tmp_row[2] = {freezer[i][0], freezer[i][1]};
			for (int j=0; j<rows; j++){
				//skip itself
				if ((j!=i) && freezer[i][0]!=0){
					//loop over other rows and check they don't overlap
					if ((tmp_row[0] >= freezer[j][0]) && (tmp_row[0] <= freezer[j][1])){
						//overlap found at beginning
						tmp_row[0] = freezer[j][1]+1;
						nchanged+=1;
					}
					if ((tmp_row[1] >= freezer[j][0]) && (tmp_row[1] <= freezer[j][1])){
						//overlap found at end
						tmp_row[1] = freezer[j][0] -1;
						nchanged+=1;
					}
				}
			}
			if (tmp_row[1] < tmp_row[0]){
				freezer[i][0] = 0;
				freezer[i][1] = 0;
			} else {
				freezer[i][0] = tmp_row[0];
				freezer[i][1] = tmp_row[1];
			}
		}
	}
	//now that there are no overlapping guys, count it
	long n_good = 0;
	for (int k=0; k<rows; k++){
		n_good+=in_range(freezer[k][0], freezer[k][1]);	
	}

	return n_good;
}

int main(){

        //string file = "testin.txt";
        string file="input.txt";
	
	vector<string> fresh;
	vector<string> veg;
        parse_lines(file, fresh, veg);
	
	// make the freezer
	// a new array which is freezer[entries][2]=min, max
        int shelves = fresh.size();
	long freezer[shelves][2];
        for (int i=0; i<fresh.size(); i++){
              int split = fresh[i].find("-");
              freezer[i][0] = stol(fresh[i].substr(0,split));
              freezer[i][1] = stol(fresh[i].substr(split+1,-1));
        }

	//do the check
	int sum =0;
	
	for (int v=0; v<veg.size(); v++){
		if (scan_em(stol(veg[v]), freezer, shelves)){
			sum+=1;
		}
	}	
	  	
        cout << "Part 1: "<<sum<<"\n";

        long n_good = count_all(freezer, shelves);
        cout << "Part 2: " << n_good<<"\n";
}


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

string parse_lines(string filename, vector<string>& vals){
        ifstream f(filename);

        if (!f.is_open()){
                cerr << "failed to open \n";
                return "";
        }

        string s;
	string operators;
        while (getline(f,s)){
		if (s.find("+") != string::npos){
                       operators=s;
                } else {
                       vals.push_back(s);
                }
        }
        f.close();

        if (f.is_open()){
                cerr<<"failed to close \n";
                return "";
        } else { 
		return operators;
	}

}

char get_next_op(string& v){
	char op;
	int i=0;
	while ((op != '+')&& (op !='*')){
		op=v[i];
		i++;
	}
	if (i<v.length()){
		v = v.substr(i);
	}
	if ((v.find("+")==string::npos) && (v.find("*")==string::npos)){
		v="";
	}
	return op;
}

long get_next_num(string& v){
	string num;
	int i;
	for (i=0; i<v.length(); i++){
		if (v[i]>='0'){
			num+=v[i];
		} else if ((v[i] <'0')&&(num.length()>0)){
			break;
		}
	}

	if (i<v.length()){
                v = v.substr(i);
        }
	
	if (num.length()>0){
		return stol(num);
	} else {
		// why are we hitting this case?
		return 0;
	}
}

long multiply(vector<long>& vals){
	long tmp=1;
	for (int j=0; j<vals.size(); j++){
		tmp*=vals[j];
	}
	return tmp;
}

long addition(vector<long>& vals){
	long tmp=0;
	for (int k=0; k<vals.size(); k++){
		tmp+=vals[k];
	}
	return tmp;
}

int main(){
	string file = "input.txt";
	//string file="testin.txt";
	
	vector<string> vals;
	string operators = parse_lines(file, vals);
	if (operators.length()==0){
		//failed to pass correctly, exit
		return 1;
	}
	
	vector<long> tmp_v;
	long result=0;
	while (operators.length()>0){
		char this_op = get_next_op(operators);
		
		for (int p=0; p<vals.size(); p++){
			tmp_v.push_back(get_next_num(vals[p]));
		}
		if (this_op=='+'){
			result+=addition(tmp_v);
		} else if (this_op=='*'){
			result+=multiply(tmp_v);
		}
		tmp_v={};
	}

	cout<<"Part 1: "<<result<<"\n";

}

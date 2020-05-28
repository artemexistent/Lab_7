#include <iostream>
#include <fstream>

#include "geometry.cpp"
	
using namespace std;





string getNameIn();
string getNameOut(string nameIn);
void solve(ifstream& in, ofstream& out);


int main(){
	
	profile();
	
	
	string nameIn = getNameIn();
	char nameIn_c[100];
	for(int i = 0; i < nameIn.size(); i ++)
		nameIn_c[i] = nameIn[i];
	ifstream in(nameIn_c);
	cout << "<OK> : file \"" << nameIn << "\" was opened for Input" << endl << endl;
	

	string nameOut = getNameOut(nameIn);	
	char nameOut_c[100];
	for(int i = 0; i < nameOut.size(); i ++)
		nameOut_c[i] = nameOut[i];
	ofstream out(nameOut_c);
	cout << "<OK> : file \"" << nameOut << "\" was opened for Output" << endl << endl;
	
	
	
	solve(in, out);
	
	
	cout << "<OK> : Answer was wroten in file : \"" << nameOut << "\"" << endl << endl;
	
	close();
	
	return 0;
}


string getNameIn(){
	cout << "Enter name of Inout_file or empty string if you want to use standart \"in.txt\" file" << endl;
	while(true){
		string s;
		getline(cin, s);
		if (s.empty())
			return "in.txt";
		if (s == "out.txt"){
			cout << "<WARNING> : this file same with standart Outout file" << endl;
		}
		else{
			ifstream in;
			char ss[100];
			for (int i = 0; i < s.size(); i ++)
				ss[i] = s[i];
				
			in.open(ss);
			if (in.is_open()){
				in.close();
				return s;
			}
			cout << "<WARNING> : try again, fail wasn't find" << endl;
		}
	}
}

string getNameOut(string nameIn){
	cout << "Enter name of Output_file or empty string if you want to use standart \"out.txt\" file" << endl;
	while(true){
		string s;
		getline(cin, s);
		if (s.empty())
			return "out.txt";
		if (s == nameIn){
			cout << "<WARNING> : this file same with file for Input" << endl;
		}
		else
		if (s == "in.txt"){
			cout << "<WARNING> : this file same with standart Input file" << endl;		
		}
		else{
			ifstream out;
			char ss[100];
			for (int i = 0; i < s.size(); i ++)
				ss[i] = s[i];
				
			out.open(ss);
			if (out.is_open()){
				out.close();
				return s;
			}	
			cout << "<WARNING> : try again, fail wasn't find" << endl;
		}
		
		
	}
}

void solve(ifstream& in, ofstream& out){
	
	Triangle T;
	in >> T;

	Line L;
	while (!in.eof()){
		in >> L;
		if (fabs(L.getA()) < Math::EPS && fabs(L.getB()) < Math::EPS && fabs(L.getC()) < Math::EPS)
			break;
		
		out << "distance from " << T << "   to   " << L << " = " << Math::distanceTriangleToLine(T, L) << endl << endl;
		
	}	
	
	
}

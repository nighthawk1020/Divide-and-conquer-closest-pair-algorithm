#include <iostream>
#include <fstream>
using namespace std;
int main(){
	ofstream inFile("input1.txt");
	int n = 10000;
	for(int i = 0; i < n; i++){
		inFile<<i<<"	"<<i+1<<"	"<<i<<endl;
	}
};

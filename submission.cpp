#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
struct Point{
	int index;
	float x;
	float y;
};
Point smallestP1;
Point smallestP2;
Point smallestP3;
Point smallestP4;
vector<Point> *vec = new vector<Point>;
vector<Point> *vec2 = new vector<Point>;
int arraySize = 0;
int compX(const void* lhs, const void* rhs){
	Point* p1 = (Point*) lhs;
	Point* p2 = (Point*) rhs;
	return (p1->x - p2->x);
};
int compY(const void* lhs, const void* rhs){
	Point* p1 = (Point*) lhs;
	Point* p2 = (Point*) rhs;
	return (p1->y - p2->y);
};
void read(ifstream& stream){
	Point point;
	stream>>point.index;
	while(stream.is_open()){
		stream>>point.x;
		stream>>point.y;
		vec->push_back(point);
		vec2->push_back(point);
		stream>>point.index;
		if(stream.eof()){
			stream.close();
		}
	}arraySize = (int)vec->size();
};
float distance(Point p1, Point p2){
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
};
float smallestDistance(Point a[], int size){
	float min = FLT_MAX;
	for(int i = 0; i < size; i++){
		for(int j = i + 1; j < size; j++){
			if(distance(a[i], a[j]) < min){
				min = distance(a[i], a[j]);
			}
		}
	}return min;
};
float min(int x, int y){
	if(x < y){
		return x;
	}else{
		return y;
	}
};
float closest(Point a[], int size, float dist){
	float min = dist;
	qsort(a, size, sizeof(Point), compY);
	for(int i = 0; i < size; i++){
		for(int j = i + 1; j < size && (a[j].y - a[i].y) < min; j++){
			if(distance(a[i], a[j]) < min){
				min = distance(a[i], a[j]);
			}
		}
	}return min;
};
float closestPoints(Point a[], int size){
	if(size <= 3){
		return smallestDistance(a, size);
	}int middle = size/2;
	Point midPoint = a[middle];
	float leftSmallestDistance = closestPoints(a, middle);
	float rightSmallestDistance = closestPoints(a + middle, size - middle);
	float smallestDist = min(leftSmallestDistance, rightSmallestDistance);
	Point stripArr[size];
	int j = 0;
	for(int i = 0; i < size; i++){
		if(abs(a[i].x - midPoint.x) < smallestDist){
			stripArr[j] = a[i];
			j++;
		}
	}return min(smallestDist, closest(stripArr, j, smallestDist));
};
void closestPointsAux(Point a[], float size, ofstream& outFile){
	float retVal = closestPoints(a, size);
	outFile<<retVal<<endl;
	smallestP1 = smallestP3;
	outFile<<smallestP1.index<<"	"<<smallestP1.x<<"	"<<smallestP1.y<<endl;
	smallestP2 = smallestP4;
	outFile<<smallestP2.index<<"	"<<smallestP2.x<<"	"<<smallestP2.y<<endl;
	ofstream out("BruteForce.txt");
	out<<retVal<<endl;
	out<<smallestP3.index<<"	"<<smallestP3.x<<"	"<<smallestP3.y<<endl;
	out<<smallestP4.index<<"	"<<smallestP4.x<<"	"<<smallestP4.y<<endl;
};
void findClosest(Point a[], ofstream& outFile){
	qsort(a, arraySize, sizeof(Point), compX);
	closestPointsAux(a, arraySize, outFile);
};
void bruteForceAlgorithm(vector<Point> *vector1){
	float minDist = FLT_MAX;
	for(int i = 0; i < (int) vector1->size(); i++){
		for(int j = i + 1; j < (int) vector1->size(); j++){
			if(abs(distance(vector1->at(i), vector1->at(j))) < minDist){
				minDist = distance(vector1->at(i), vector1->at(j));
				smallestP3 = vector1->at(i);
				smallestP4 = vector1->at(j);
			}
		}
	}
};
int main(int argc, char* argv[]){
	if(argc != 3){
		cout<<"Please input an inputFile and an outputFile"<<endl;
		return 1;
	}else{
		ifstream in(argv[1]);
		ofstream out(argv[2]);
		if(!in.is_open()){
			cout<<"Please input a valid file"<< endl;
			return 1;
		}read(in);
		Point a[arraySize];
		for(int i = 0; i < (int)vec->size(); i++){
			a[i] = vec->at(i);
		}
		chrono::nanoseconds elapsed;
		chrono::steady_clock::time_point start, finish;
		start = chrono::steady_clock::now();
		bruteForceAlgorithm(vec2);
		finish = chrono::steady_clock::now();
		elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);
		cout<<"The timing of my brute force algorithm is "<<elapsed.count()<<" nanoseconds"<<endl;
		start = chrono::steady_clock::now();
		findClosest(a, out);
		finish = chrono::steady_clock::now();
		elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start);
		cout<<"The timing of my divide and conquer algorithm is "<<elapsed.count()<<" nanoseconds"<<endl;
	}return 0;
};

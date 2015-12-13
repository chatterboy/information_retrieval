#define SINGLE

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
using namespace std;

typedef pair<string, pair<int, double>> Cube;
typedef map<string, pair<int, vector<pair<int, int>>>> IIndex;

const int BUFFER_SIZE = 128;

char buf[BUFFER_SIZE];

// 단어, 문서 #, tf*idf, 

int readLineFile(FILE * fin) {
	memset(buf, 0, sizeof buf);
	if (fgets(buf, sizeof buf, fin) != NULL) return 1;
	return 0;
}

void getFiles(vector<string> & fileName) {
#ifdef SINGLE
	fileName.push_back(string("tfIdfSingle.txt"));
#else
	puts("df");
#endif
}

void makeTokens(vector<Cube> & cube, vector<string> & fileName) {
	int n = fileName.size();
	for (int i = 0; i < n; i++) {
		FILE * fin = fopen(fileName[i].c_str(), "r");
		while (readLineFile(fin)) {
			char w[BUFFER_SIZE] = {0};
			double tf;
			double idf;
			sscanf(buf, "%s %lf %lf", w, &tf, &idf);
			cube.push_back(make_pair(string(w), make_pair(i, tf * idf)));
		}
		fclose(fin);
	}
	sort(cube.begin(), cube.end(), [](const Cube & a, const Cube & b){
		return a.first < b.first;
	});
}


void makeInvertedIndex(IIndex & pack, vector<Cube> & cube) {
	int n = cube.size();
	for (int i = 0; i < n; i++) {
		pack[cube[i].first].first++;
		pack[cube[i].first].second.push_back(make_pair(cube[i].second.first, cube[i].second.second));
	}
}

void printTokens(vector<Cube> & cube) {
	for (auto e : cube) printf("%s %f %f\n", e.first.c_str(), e.second.first, e.second.second);
}

typedef map<string, pair<int, vector<pair<int, int>>>> IIndex;

void printIIndex(IIndex & pack) {
	for (auto a : pack) {
		int n = a.second.second.size();
		printf("%s %d\n", a.first.c_str(), a.second.first);
		for (auto b : a.second.second) printf("%d %d\n", b.first, b.second);
	}
}

// 
void init() {

}



// [0,n)

void input() {
}

void preprocess() {

}

int main() {
	vector<string> fileName;
	getFiles(fileName);

	vector<Cube> cube;
	makeTokens(cube, fileName);

	IIndex pack;
	makeInvertedIndex(pack, cube);

	printIIndex(pack);
}

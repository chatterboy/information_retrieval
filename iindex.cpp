#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
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
	// 
}

void makeTokens(vector<Cube> & cube, vector<string> & fileName) {
	int n = fileName.size();
	for (int i = 0; i < n; i++) {
		FILE * fin = fopen(fileName[i].c_str(), "r");
		while (readLineFile(fin)) {
			char w[BUFFER_SIZE] = {0};
			double tf;
			double idf;
			sscanf(fin, "%s %lf %lf", w, &tf, &idf);
			cube.push_back(make_pair(string(w), make_pair(i, tf * idf));
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

// 
void init() {

}



// [0,n)

void input() {
	for (int i = 0; i < n; i++)
}

void preprocess() {

}

int main() {
	preprocess();
	for (;;) {
		
	}
}

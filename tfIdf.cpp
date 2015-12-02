#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define maxs 128

typedef map<string,int> table;
typedef vector<pair<double,string>> vec;

// tf
// 하나의 문서에 있는 각 단어에 대한 tf를 계산한다.
// 단어 w의 빈도 수 / 단어의 총 수
// (단어,빈도수) 쌍이 있어야 한다.
double tf(table & tb, string & w, int n) {
	return 1.0 * tb[w] / n;
}

double idf() {

}

/*
void _run() {
	char s[maxs];
	fin = fopen("after_applying_stemming.txt", "r");
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s\n", s) == EOF) break;
		puts(s);
		tb[string(s)]++;
	}
	fclose(fin);
}
*/

// fr에 있는 단어들을 읽어서 (단어,빈도수) 쌍을 만든다.
// (단어,빈도수) 쌍을 이용해서 현재 문서에 있는 각 단어별
// tf를 계산 후 (tf(w),w) 쌍을 만들고 tf 기준으로 정렬을 한다.
// (tf(w),w)를 fw에 저장한다.
void _getTf(char * fr, char * fw) {
	int n = 0;
	char s[maxs];
	table tb;
	vec v;
	FILE * fin = fopen(fr, "r");
	FILE * fout;
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		tb[string(s)]++;
		n++;
	}
	fclose(fin);
	fout = fopen(fw, "w");
	for (auto b : tb) {
		string s2(b.first);
		v.push_back(make_pair(tf(tb, s2, n), b.first));
	}
	sort(v.begin(), v.end());
	for (auto b : v)
		fprintf(fout, "%s %lf\n", b.second.c_str(), b.first);
	fclose(fout);
}

// 문서를 입력으로 받아서 각 단어들의 빈도수를 (단어,빈도수) 쌍으로
// 저장한다.
void getTf(string & doc) {
	int n = 0;
	char s[maxs];
	map<string,int> m;
	FILE * fin = fopen(doc.c_str(), "r");
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		m[string(s)]++;
		n++;
	}
	fclose(fin);

}

void _getIdf(char * docs[], ...) {

}

// 문서군을 입력으로 받아서 각 단어들이 나타나는 문서의 인덱스를
// 단어1 -> 문서1, 문서4
// 단어2 -> 문서 6, 문서 9, 문서 10
// 와 같은 형태로 저장한다.
void getIdx(vector<string> & docs) {
	int i;
	int n = docs.size();
	char s[maxs];
	map<string,set<int>> m;
	for (i = 0; i < n; i++) {
		FILE * fin = fopen(docs[i].c_str(), "r");
		for (;;) {
			memset(s, 0, sizeof s);
			if (fscanf(fin, "%s\n", s) == EOF) break;
			m[string(s)].insert(i);
		}
		fclose(fin);
	}
	FILE * fout = fopen("index.txt", "w");
	for (auto a : m) {
		fprintf(fout, "%s", a.first.c_str());
		for (auto b : a.second)
			fprintf(fout, " %d", b);
		fprintf(fout, "\n");
	}
	fclose(fout);
}

// index.txt로부터 입력을 받아서 각 단어별로 idf를 계산 후 저장한다.
void getIdf() {
	FILE * fin = fopen("index.txt", "r");
	
	fclose(fin);
}

int main() {
//	_run();
	/*
	vector<pair<int,string>> tb2;
	for (auto e : tb)
		tb2.push_back(make_pair(e.second, e.first));
	sort(tb2.rbegin(), tb2.rend());
	for (auto e : tb2)
		printf("%s %d\n", e.second.c_str(), e.first);
	puts("successfully completed!");
	*/
	return 0;
}
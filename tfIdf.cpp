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
void _run_(char * fr, char * fw) {
	int n = 0;
	char s[maxs];
	table tb;
	vec v;
	FILE * fin = fopen(fr, "r");
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		tb[string(s)]++;
		n++;
	}
	fclose(fin);
	fout = fopen(fw, "w");
	for (auto b : tb)
		v.push_back(make_pair(tf(tb, b.first.c_str(), n), b.first.c_str()));
	sort(v.begin(), v.end());
	for (auto b : v)
		fprintf(fout, "%s %lf\n", b.second.c_str(), b.first);
	fclose(fout);
}

int main() {
	_run();
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
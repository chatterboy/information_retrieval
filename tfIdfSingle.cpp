#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define maxs 256

void getTfIdfSingle() {
	int n = 0;
	char s[maxs];
	FILE * fin = fopen("stemmed.txt", "r");
	map<string,int> m;
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		m[string(s)]++;
		n++;
	}
	fclose(fin);
	vector<pair<string,double>> tf;
	for (auto a : m)
		tf.push_back(make_pair(a.first, 1.0 * a.second / n));
	sort(tf.begin(), tf.end(), [](const pair<string,double> & l, const pair<string,double> & r) {
		if (l.second > r.second) return true;
		else if (l.second < r.second) return false;
		return l.first < r.first;
	});
//	for (auto a : tf)
//		printf("%-20s %-10f %-10f\n", a.first.c_str(), a.second, log(1.0 * 1 / 1));
	FILE * fout = fopen("tfIdfSingle.txt", "w");
	fprintf(fout, "%*sword%*stf%*sidf\n", 8, "", 12, "", 8, "");
	for (auto a : tf)
		fprintf(fout, "%-20s %-10f %-10f\n", a.first.c_str(), a.second, log(1.0 * 1 / 1));
	fclose(fout);
}

int main() {
	getTfIdfSingle();
	puts("successfully completed!");
	return 0;
}
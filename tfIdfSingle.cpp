#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define maxs 256

// input: a single file with stemmed words.
// output: tf and idf for each words.
// but, note the idf is always 0 because we just calculate it
// with a single document.
void getTfIdfSingle() {
	int n = 0; // the total number of the words in a single file.
	char s[maxs]; // just buffer for storing a string.
	FILE * fin = fopen("stemmed.txt", "r");
	// we need (string, int) pairings that are mapped (a word, frequency of a word).
	// this structure makes calculation for tf easy.
	map<string,int> m;
	// now, we get stemmed words in a single file.
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		m[string(s)]++; // count the total number of a word.
		n++; // count the total number of the words.
	}
	fclose(fin);
	// we need (string, double) pairings that are mapped (a word, tf for a word).
	// this structure makes sorting for specific method easy.
	vector<pair<string,double>> tf;
	for (auto a : m)
		tf.push_back(make_pair(a.first, 1.0 * a.second / n));
	// sort
	sort(tf.begin(), tf.end(), [](const pair<string,double> & l, const pair<string,double> & r) {
		if (l.second > r.second) return true;
		else if (l.second < r.second) return false;
		return l.first < r.first;
	});
//	for (auto a : tf)
//		printf("%-20s %-10f %-10f\n", a.first.c_str(), a.second, log(1.0 * 1 / 1));
	// output the results to file.
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

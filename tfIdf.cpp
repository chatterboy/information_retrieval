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
void getTfIdfSingle(string & fr, string & fw) {
	int n = 0; // the total number of the words in a single file.
	char s[maxs]; // just buffer for storing a string.
	FILE * fin = fopen(fr.c_str(), "r");
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
	FILE * fout = fopen(fw.c_str(), "w");
//	fprintf(fout, "%*sword%*stf%*sidf\n", 8, "", 12, "", 8, "");
	for (auto a : tf)
//		fprintf(fout, "%-20s %-10f %-10f\n", a.first.c_str(), a.second, log(1.0 * 1 / 1));
		fprintf(fout, "%s %f %f\n", a.first.c_str(), a.second, (double)log(1.0 * 1 / 1));
	fclose(fout);
}

// input: a single file with stemmed words.
// output: tf and idf for each words.
// but, note the idf is always 0 because we just calculate it
// with a single document.
void _getTfIdfSingle() {
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
//	fprintf(fout, "%*sword%*stf%*sidf\n", 8, "", 12, "", 8, "");
	for (auto a : tf)
//		fprintf(fout, "%-20s %-10f %-10f\n", a.first.c_str(), a.second, log(1.0 * 1 / 1));
		fprintf(fout, "%s %f %f\n", a.first.c_str(), a.second, (double)log(1.0 * 1 / 1));
	fclose(fout);
}

static const vector<string> fileName = {
	"almond.txt", "apple.txt", "banana.txt", "bmw.txt", "car.txt",
	"computer.txt", "dog.txt", "dragon fruit.txt", "durian.txt", "ferrari.txt",
	"food.txt", "football.txt", "ford.txt", "google.txt", "grape.txt",
	"guava.txt", "horse.txt", "internet.txt", "kiwifruit.txt", "korean melon.txt",
	"mango.txt", "mangosteen.txt", "maple.txt", "michael jackson.txt", "movie.txt",
	"music.txt", "musician.txt", "naver.txt", "papaya.txt", "pear.txt",
	"pine.txt", "pineapple.txt", "rabbit.txt", "romantic music.txt", "samsung.txt",
	"sausage.txt", "strawberry.txt", "tangerine.txt", "tomato.txt", "tree.txt",
	"walnut.txt", "watermelon.txt", "yahoo.txt"
};

void getTfIdf() {
	char s[maxs];
	int n = fileName.size();
	vector<map<string,int>> v(n);
	vector<map<string, pair<double, double>>> res(n);
	for (int i = 0; i < n; ++i) {
		int k = 0;
		string fr = "";
		fr += "stemmed\\" + fileName[i];
		FILE * fin = fopen(fr.c_str(), "r");
		for (;;) {
			memset(s, 0, sizeof s);
			if (fscanf(fin, "%s\n", s) == EOF) break;
			v[i][string(s)]++;
			k++;
		}
		fclose(fin);

		// tf
		for (auto e : v[i]) res[i][e.first].first = 1.0 * v[i][e.first] / k;
	}
	
	for (int i = 0; i < n; ++i) { // idf
		for (auto m : v[i]) {
			int ndocs = 0;
			for (int j = 0; j < n; ++j) if (v[j][m.first]) { ndocs++; break; }
			res[i][m.first].second = log(1.0 * n / ndocs);
		}
	}

	for (int i = 0; i < n; ++i) {
		string fw = "";
		fw += "tfidf\\" + fileName[i];
		FILE * fout = fopen(fw.c_str(), "w");
		for (auto e : res[i]) fprintf(fout, "%s %f %f\n", e.first.c_str(), e.second.first, e.second.second);
		fclose(fout);
	}
}

void _getTfIdf() {
	int n = fileName.size();
	for (int i = 0; i < n; ++i) {
		string fr = "";
		string fw = "";
		fr += "stemmed\\" + fileName[i];
		fw += "tfidf\\" + fileName[i];
		getTfIdfSingle(fr, fw);
	}
}

int main() {
	getTfIdf();
	puts("successfully completed!");
	return 0;
}

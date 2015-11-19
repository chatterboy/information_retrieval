#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define BUFFER_SIZE 128
#define WHITE_SPACE 0x20

FILE* fin;
FILE* fout;
char buf[BUFFER_SIZE];
map<string,int> wtb;
set<string> swl;

void init_read_file(const char* fname) {
	fin = fopen(fname, "r");
}

void free_read_file() {
	fclose(fin);
}

int read_line_file() {
	memset(buf, 0, sizeof buf);
	if (fgets(buf, sizeof buf, fin) != NULL)
		return 0;
	return 1;
}

void get_stopwords_list_file() {
	while (!read_line_file()) {
		string w(buf);
		while (w.back() == '\n')
			w.pop_back();
		swl.insert(w);
	}
}

void change_to_lower(string& w) {
	int n;
	n = w.size();
	for (int i = 0; i < n; i++)
		if (isalpha(w[i]) && isupper(w[i]))
			w[i] = tolower(w[i]);
}

void get_words_line() {
	int n;
	bool flag;
	string w;
	n = strlen(buf);
	for (int i = 0; i < n; i++) {
		if (isalpha(buf[i]))
			w.push_back(buf[i]);
		else {
			flag = false;
			if (buf[i] != WHITE_SPACE)
				if ((i-1 >= 0 && isalpha(buf[i-1])) && (i+1 < n && isalpha(buf[i+1]))) {
					flag = true;
					w.push_back(buf[i]);
				}
			if (!flag) {
				if (!w.empty()) {
					change_to_lower(w);
					wtb[w]++;
				}
				w.clear();
			}
		}
	}
}

bool cmp(const pair<int,string>& a, const pair<int,string>& b) {
	if (a.first > b.first) return true;
	if (a.first < b.first) return false;
	return a.second < b.second;
}

void get_sorted_words(vector<pair<int,string>>& v) {
	for (auto it = wtb.begin(); it != wtb.end(); it++)
		v.push_back(make_pair(it->second, it->first));
	sort(v.begin(), v.end(), cmp);
}

void print_sorted_words() {
	vector<pair<int,string>> v;
	get_sorted_words(v);
	for (auto e : v)
		printf("%s %d\n", e.second.c_str(), e.first);
}

void print_sorted_words_file(const char* fname) {
	vector<pair<int,string>> v;
	get_sorted_words(v);
	fout = fopen(fname, "w");
	for (auto e : v)
		fprintf(fout, "%s %d\n", e.second.c_str(), e.first);
	fclose(fout);
}

void remove_stopwords_wtb() {
	for (auto sw : swl) {
		auto p = wtb.find(sw);
		if (p != wtb.end())
			wtb.erase(p);
	}
}

int main() {
	init_read_file("Adventures_of_Huckleberry_Finn.txt");
	while (!read_line_file())
		get_words_line();
	free_read_file();
	init_read_file("default_stopwords_list.txt");
	get_stopwords_list_file();
	free_read_file();
	int before_sz = wtb.size();
	print_sorted_words_file("before_removing_stopwords.txt");
	remove_stopwords_wtb();
	int after_sz = wtb.size();
	print_sorted_words_file("after_removing_stopwords.txt");
	fout = fopen("compare_no_words.txt", "w");
	fprintf(fout, "number of words before removing stopwords: %d\n", before_sz);
	fprintf(fout, "number of words after removing stopwords: %d", after_sz);
	fclose(fout);
}
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define BUFFER_SIZE 128
#define WHITE_SPACE 0x20

FILE *fin;
char buf[BUFFER_SIZE];
map<string,int> wtb;

void init_read_file() {
	fin = fopen("Adventures_of_Huckleberry_Finn.txt", "r");
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

void change_to_lower(string& w) {
	int n;
	n = w.size();
	for (int i = 0; i < n; i++)
		if (isalpha(w[i]) && isupper(w[i]))
			w[i] = tolower(w[i]);
}

void make_words_line() {
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

void print_sorted_words() {
	vector<pair<int,string>> v;
	for (auto it = wtb.begin(); it != wtb.end(); it++)
		v.push_back(make_pair(it->second, it->first));
	sort(v.begin(), v.end(), cmp);
	for (auto e : v)
		printf("%s %d\n", e.second.c_str(), e.first);
}

int main() {
	init_read_file();
	while (!read_line_file())
		make_words_line();
	free_read_file();
	print_sorted_words();
}
// Porter Stemming Algorithm
// ref @ http://snowball.tartarus.org/algorithms/porter/stemmer.html
#define TEST
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;
#define BUFFER_SIZE 128
FILE *fin;
FILE *fout;
const char* rules[] = {
	"step 1a", "step 1b", "step 1c", "step 2",
	"step 3", "step 4", "step 5a", "step 5b"
};
char buf[BUFFER_SIZE];
int readLineFile() {
	memset(buf, 0, sizeof buf);
	if (fgets(buf, sizeof buf, fin) != NULL)
		return 0;
	return 1;
}
bool isconstant(char ch) {
	static char constant[] = {'a', 'e', 'i', 'o', 'u'};
	int i;
	for (i = 0; i < 5; i++)
		if (ch == constant[i])
			return false;
	return true;
}
int m(string sf) {
	int i;
	deque<char> form;
	for (i = 0; i < sf.size(); i++) {
		if (!isconstant(sf[i]) || (sf[i] == 'y' && i+1 < sf.size() && isconstant(sf[i+1])))
			form.push_back('v');
		else
			form.push_back('c');
	}
	form.erase(unique(form.begin(), form.end()), form.end());
	if (form.front() == 'c') form.pop_front();
	if (form.back() == 'v') form.pop_back();
	return (int)form.size() / 2;
}
bool v(string sf) {
	int i;
	for (i = 0; i < sf.size(); i++)
		if (!isconstant(sf[i]))
			return true;
	return false;
}
int step1a(string &s) {
	static int len[] = {4, 3, 2, 1};
	static string sf[] = {"sses", "ies", "ss", "s"};
	static string sf2[] = {"ss", "i", "ss", ""};
	int i;
	for (i = 0; i < 4; i++)
		if (s.size() >= len[i] && s.substr(s.size()-len[i], s.size()) == sf[i]) {
			s = s.substr(0, s.size()-len[i]) + sf2[i];
			return i + 1;
		}
	return 0;
}
int step1b(string &s) {
	if (s.size() >= 3 && s.substr(s.size()-3, s.size()) == "eed" && m(s.substr(0, s.size()-3)) > 0) {
		s = s.substr(0, s.size()-3) + "ee";
		return 1;
	} else if (s.size() >= 2 && s.substr(s.size()-2, s.size()) == "ed" && v(s.substr(0, s.size()-2))) {
		s = s.substr(0, s.size()-2);
		return 2;
	} else if (s.size() >= 3 && s.substr(s.size()-3, s.size()) == "ing" && v(s.substr(0, s.size()-3))) {
		s = s.substr(0, s.size()-3);
		return 3;
	}
	return 0;
}
int step1c(string &s) {
 	if (s.size() >= 1 && s.substr(s.size()-1, s.size()) == "y" && v(s.substr(0, s.size()-1))) {
 		s = s.substr(0, s.size()-1) + "i";
 		return 1;
 	}
 	return 0;
}
int step2(string &s) {
	static int len[] = {7, 6, 4, 4, 4,
				 		4, 4, 5, 3, 5,
				 		7, 5, 4, 5, 7,
				 		7, 7, 5, 5, 6};
	static string sf[] = {	"ational", "tional", "enci", "anci", "izer",
							"abli", "alli", "entli", "eli", "ousli",
							"ization", "ation", "ator", "alism", "iveness",
							"fulness", "ousness", "aliti", "iviti", "biliti"};
	static string sf2[] = {	"ate", "tion", "ence", "ance", "ize",
							"able", "al", "ent", "e", "ous",
							"ize", "ate", "ate", "al", "ive",
							"ful", "ous", "al", "ive", "ble"};
	int i;
	for (i = 0; i < 20; i++)
		if (s.size() >= len[i] && s.substr(s.size()-len[i], s.size()) == sf[i] && m(s.substr(0, s.size()-len[i])) > 0) {
			s = s.substr(0, s.size()-len[i]) + sf2[i];
			return i + 1;
		}
	return 0;
}
int step3(string &s) {
	static int len[] = {5, 5, 5, 5, 4, 3, 4};
	static string sf[] = {"icate", "ative", "alize", "iciti", "ical", "ful", "ness"};
	static string sf2[] = {"ic", "", "al", "ic", "ic", "", ""};
	int i;
	for (i = 0; i < 7; i++)
		if (s.size() >= len[i] && s.substr(s.size()-len[i], s.size()) == sf[i] && m(s.substr(0, s.size()-len[i])) > 0) {
			s = s.substr(0, s.size()-len[i]) + sf2[i];
			return i + 1;
		}
	return 0;
}
int step4(string &s) {
	static int len[] = {2, 4, 4, 2, 2,
				 		4, 4, 3, 5, 4,
				 		3, 3, 2, 3, 3,
				 		3, 3, 3, 3};
	static string sf[] = {	"al", "ance", "ence", "er", "ic",
							"able", "ible", "ant", "ement", "ment",
							"ent", "ion", "ou", "ism", "ate",
							"iti", "ous", "ive", "ize"};
	int i;
	for (i = 0; i < 19; i++)
		if (s.size() >= len[i] && s.substr(s.size()-len[i], s.size()) == sf[i] && m(s.substr(0, s.size()-len[i])) > 1) {
			if (sf[i] != "ion") {
				s = s.substr(0, s.size()-len[i]);
				return i + 1;
			}
			else {
				if (s.substr(0, s.size()-len[i]).back() == 's' || s.substr(0, s.size()-len[i]).back() == 't') {
					s = s.substr(0, s.size()-len[i]);
					return i + 1;
				}
			}
		}
	return 0;
}
int step5a(string &s) {
	int i;
	if (s.size() >= 1)
		for (i = 0; i < 2; i++) {
			if (m(s.substr(0, s.size()-1)) > 1) {
				s = s.substr(0, s.size()-1);
				return i + 1;
			} else if (m(s.substr(0, s.size()-1)) == 1 && s.substr(0, s.size()-1).back() != 'o') {
				s = s.substr(0, s.size()-1);
				return i + 1;
			}
		}
	return 0;
}
int step5b(string &s) {
	int i;
	if (s.size() >= 2)
		if (m(s.substr(0, s.size()-2)) > 1 && s.back() == 'l' && s.back() == s[s.size()-2]) {
			s = s.substr(0, s.size()-1);
			return 1;
		}
	return 0;			
}
int main() {
#ifdef TEST
	fin = fopen("input.in", "r");
	fout = fopen("output.out", "w");
	while (!readLineFile())
		printf("%s", buf);
	fclose(fin);
	fclose(fout);
#else

#endif
	/*
	string s1 = "caresses";
	string s2 = "ponies";
	string s3 = "caress";
	string s4 = "cats";
	step1a(s1);
	step1a(s2);
	step1a(s3);
	step1a(s4);
	puts(s1.c_str());
	puts(s2.c_str());
	puts(s3.c_str());
	puts(s4.c_str());

	printf("%s\n", getRuleStep1a(0));
	*/
}
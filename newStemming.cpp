#include <cstdio>
#include <cstring>

// ok
// s => [0,k)
// [0,j), [j,k)
struct stemmer {
	char * s;
	int j, k;
	stemmer() {}
	stemmer(char * s) : s(s) { k = strlen(s); }
};

int conso(stemmer * z, int i) {
	switch (z->s[i]) {
		case 'a': case 'e': case 'i': case 'o': case 'u': return 0;
		case 'y' : return (i == 0) ? 1 : !conso(z, i - 1);
		default: return 1;
	}
}

int v(stemmer * z) {

}

int m(stemmer * z) {

}

// ok
// string z->s ends with the string s.
// ends(z, "ing")
int ends(stemmer * z, char * s) {
	int length = strlen(s);
	if (length > z->k) return 0;
	if (strcmp(z->s + z->k - length, s)) return 0;
	z->j = z->k - length;
	return 1;
}

void step1ab(stemmer * z) {
	if (z->s[z->k - 1] == 's') {
		if (ends(z, "sses") || ends(z, "ies")) z->k -= 2;
		else if (z->s[z->k - 2] != 's') z->k--;
	}
	if (ends(z, "eed")) {
		if (m(z) > 0)
			z->k--;
	} else if (ends(z, "ed") || ends(z, "ing")) {
		if (v(z)) {

		}
	}
}

void step2(stemmer * z) {
	static const int n = 7;
	static char * a[n] = {

	};
	static char * b[n] = {

	};
	int i;
	for (i = 0; i < n; i++)
		if (ends(z, a[i])) {
			// 
			break;
		}
}

void step3(stemmer * z) {
	static const int n = 7;
	static char * a[n] = {

	};
	static char * b[n] = {

	};
	int i;
	for (i = 0; i < n; i++)
		if (ends(z, a[i])) {
			//
			break;
		}
}

int main() {
	return 0;
}
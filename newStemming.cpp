#include <cstdio>
#include <cstring>

FILE * fin;
FILE * fout;

// ok
// s => [0,k)
// [0,j), [j,k)
struct stemmer {
	char * s;
	int j, k;
	stemmer() {}
	stemmer(char * s) : s(s) {
		k = strlen(s);
		j = k;
	}
};

int cons(stemmer * z, int i) {
	switch (z->s[i]) {
		case 'a': case 'e': case 'i': case 'o': case 'u': return 0;
		case 'y' : return (i == 0) ? 1 : !cons(z, i - 1);
		default: return 1;
	}
}

int v(stemmer * z) {
	int i;
	int j = z->j;
	for (i = 0; i < j; i++)
		if (!cons(z, i))
			return 1;
	return 0;
}

// cvc()
// if i-2, i-1, i has the form consonant, vowel, consonant
// this function returns true.
int cvc(stemmer * z, int i) {
	char ch;
	if (i >= 2 && cons(z, i) && !cons(z, i-1) && cons(z, i-2)) {
		ch = z->s[i];
		if (ch != 'w' && ch != 'x' && ch != 'y')
			return 1;
	}
	return 0;
}

// d() is 1 <=> i-1, i contains a double consonant.
// d() is 0 <=> otherwise.
int d(stemmer * z, int i) {
	char * s = z->s;
	if (i >= 1)
		if (s[i-1] == s[i])
			return 1;
	return 0;
}

// we count the number of a consecutive consonants in string
int m(stemmer * z) {
	int n = 0;
	int i = 0;
	int j = z->j;
	for (; i < j && cons(z, i); i++);
	if (i >= j) return n;
	for (;;) {
		for (; i < j && !cons(z, i); i++);
		if (i >= j) return n;
		for (; i < j && cons(z, i); i++);
		n++;
		if (i >= j) return n;
	}
}

// setto() 
void setto(stemmer * z, char * s) {
	int i;
	int length = strlen(s);
	int j = z->j;
	for (i = 0; i < length; i++)
		z->s[j + i] = s[i];
	z->k = j + length;
}

// ok
// string z->s ends with the string s.
// ends(z, "ing")
int ends(stemmer * z, char * s) {
	int length = strlen(s);
	int k = z->k;
	char * b = z->s;
	if (length > k) return 0;
	if (strncmp(b + k - length, s, length)) return 0;
	z->j = k - length;
	return 1;
}

int r(stemmer * z, char * s) {
	if (m(z) > 0)
		setto(z, s);
	return 0;
}

void step1ab(stemmer * z) {
	char ch;
	if (z->s[z->k - 1] == 's') {
		if (ends(z, "sses") || ends(z, "ies")) z->k -= 2;
		else if (z->s[z->k - 2] != 's') z->k--;
	}
	if (ends(z, "eed")) {
		if (m(z) > 0)
			z->k--;
	} else if ((ends(z, "ed") || ends(z, "ing")) && v(z)) {
		z->k = z->j;
		if (ends(z, "at"))
			setto(z, "ate");
		else if (ends(z, "bl"))
			setto(z, "ble");
		else if (ends(z, "iz"))
			setto(z, "ize");
		else if (d(z, z->k)) {
			z->k--;
			ch = z->s[z->k];
			if (ch == 'l' || ch == 's' || ch == 'z')
				z->k++;
		} else if (m(z) == 1 && cvc(z, z->k))
			setto(z, "e");
	}
}

void step1c(stemmer * z) {
	if (ends(z, "y") && v(z))
		z->s[z->k - 1] = 'i';
}

void step2(stemmer * z) {
	static const int n = 20;
	static char * a[n] = {
		"ational", "tional", "enci", "anci", "izer",
		"abli", "alli", "entli", "eli", "ousli",
		"ization", "ation", "ator", "alism", "iveness",
		"fulness", "ousness", "aliti", "iviti", "biliti"
	};
	static char * b[n] = {
		"ate", "tion", "ence", "ance", "ize",
		"able", "al", "ent", "e", "ous",
		"ize", "ate", "ate", "al", "ive",
		"ful", "ous", "al", "ive", "ble"
	};
	int i;
	for (i = 0; i < n; i++)
		if (ends(z, a[i])) {
			r(z, b[i]);
			break;
		}
}

void step3(stemmer * z) {
	static const int n = 7;
	static char * a[n] = {
		"icate", "ative", "alize", "iciti", 
		"ical", "ful", "ness"
	};
	static char * b[n] = {
		"ic", "", "al", "ic",
		"ic", "", ""
	};
	int i;
	for (i = 0; i < n; i++)
		if (ends(z, a[i])) {
			r(z, b[i]);
			break;
		}
}

void step4(stemmer * z) {
	static const int n = 19;
	static char * a[n] = {
		"al", "ance", "ence", "er", "ic",
		"able", "ible", "ant", "ement", "ment",
		"ent", "ion", "ou", "ism", "ate",
		"iti", "ous", "ive", "ize"
	};
	int i;
	for (i = 0; i < n; i++)
		if (ends(z, a[i]) && m(z) > 1) {
			z->k = z->j;
			break;
		}
}

void step5(stemmer * z) {
	char * s = z->s;
	int k = z->k;
	z->j = k;
	if (s[k - 1] == 'e')
		if (m(z) > 1 || (m(z) == 1 && !cvc(z, k - 2)))
			z->k--;
	if (s[k - 1] == 'l' && d(z, k - 1) && m(z) > 1)
		z->k--;
}

int stemming(stemmer * z) {
	if (z->k > 1) {
		step1ab(z);
		step1c(z);
		step2(z);
		step3(z);
		step4(z);
		step5(z);
	}
	return z->k;
}

void run() {
	char s[256];
	stemmer z;
	fin = fopen("after_removing_stopwords.txt", "r");
	fout = fopen("stemmed.txt", "w");
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s %*d\n", s) == EOF) break;
		z = stemmer(s);
		s[stemming(&z)] = '\0';
		fprintf(fout, "%s\n", s);
	}
	fclose(fin);
	fclose(fout);
}

void _run() {
	char s[256];
	stemmer z;
	fin = fopen("after_removing_stopwords.txt", "r");
	fout = fopen("after_applying_stemming.txt", "w");
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s %*d\n", s) == EOF) break;
		fprintf(fout, "%s -> ", s);
		z = stemmer(s);
		s[stemming(&z)] = '\0';
		fprintf(fout, "%s\n", s);
	}
	fclose(fin);
	fclose(fout);
}

// this function tests the m() of a string is correct.
// input the data from input.txt
// output the data to output.txt
void test() {
	char s[101];
	stemmer z;
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		z = stemmer(s);
		fprintf(fout, "%-10s %2d\n", z.s, m(&z));
	}
	fclose(fin);
}

// this function tests the setto()
void test2() {
	char s[100] = "crack";
	stemmer z(s);
	printf("%s %d\n", z.s, z.k);
	z.j--;
	setto(&z, "df");
	printf("%s %d\n", z.s, z.k);
}

void _test() {
	char s[256], s2[256];
	FILE * fin2 = fopen("input.txt", "r");
	fin = fopen("after_applying_stemming.txt", "r");
	for (;;) {
		memset(s, 0, sizeof s);
		memset(s2, 0, sizeof s2);
		if (fscanf(fin2, "%s", s) == EOF || fscanf(fin, "%s", s2) == EOF) break;
		if (strcmp(s, s2))
			printf("%s %s\n", s, s2);
	}
	fclose(fin);
	fclose(fin2);
}

int main() {
	run();
	puts("successfully completed!");
	return 0;
}
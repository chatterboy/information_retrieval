#include <cstdio>
#include <cstring>

// s[begin...end]
struct Stemming {
	char * s;
	int begin;
	int end;
	Stemming() {}
	Stemming(char * s) : s(s) {
		begin = 0;
		end = strlen(s) - 1;
	}
};

// gets rid of plurals and -ed or -ing.
// step1ab() pseudo code
/*

step1ab(string s)
	if 

*/


int oldIsConsonant(char ch) {
	switch (ch) {
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return 0;
		case 'y':
			// need a process

			break;
	}
	return 1;
}

int isConsonant(int i, Stemming & stm) {
	switch (stm.s[i]) {
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return 0;
		case 'y':
			// need a process
			// 0이라고 해야하나 stm.begin 이라 해야하나
			if (i-1 >= 0 && isConsonant(i-1, stm))
				return 0;
			break;
	}
	return 1;
}

int endWith(char * s, Stemming & stm) {
	int n = strlen(s);
	// this line needs some exceptions.
	return strcmp(stm.s + stm.end - n + 1, s);
}

/* step1a()

sses -> ss
ies -> i
ss -> ss
s ->

*/
// stm 좋은 이름 없을까
void step1a(Stemming & stm) {
	if (stm.s[stm.end] == 's') {
		if (endWith("sses", stm) || endWith("ies", stm))
			stm.end -= 2;
		else if (endWith("s", stm))
			stm.end--;
	}
}

//*****************
// -eed, -ed, -ing
// step1b()
//*****************
void step1b(Stemming & stm) {
	/* 줄이는 방법 없나 
	if (endWith("eed", stm)) {
		stm.end--;
		if (!(m(stm) > 0))
			stm.end++;
	} else if (endWith("ed", stm) || endWith("ing", stm)) {
		if (v(stm))
	}
	*/
	if (endWith("eed", stm)) {
		stm.end -= 3;
		if (m(stm) > 0)
			stm.end += 2;
		else
			stm.end += 3;
	} else if (endWith("ed", stm)) {
		stm.end -= 2;
		if (!(v(stm)))
			stm.end += 2;
	} else if (endWith("ing", stm)) {
		stm.end -= 3;
		if (!v(stm)))
			stm.end += 3;
	}
}

//*****************
// step 1c
// 
// (*v*) Y -> I
//
// e.g.
//
// happy -> happi
// sky -> sky
// 
//*****************
void step1c(Stemming & stm) {
	if (endWith("y", stm)) {
		stm.end--;
		if (v(stm)) {
			setToEnd("i", stm);
		} else
			stm.end++;
	}
}

//*****************
// step 1c
// 
// (*v*) Y -> I
//
// e.g.
//
// happy -> happi
// sky -> sky
// 
//*****************

int main() {
	Stemming stm("processes");
	printf("%d\n", endWith("sses", stm));
	printf("%d\n", endWith("s", stm));
}
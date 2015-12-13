// (단어,빈도수) 쌍으로 만든다.
// tf를 계산한다.
void getTf(string & doc, vector<pair<string,double>> & tf) {
	int n = 0;
	char s[maxs];
	map<string,int> m;
	FILE * fin = fopen(doc.c_str(), "r");
	for (;;) {
		memset(s, 0, sizeof s);
		if (fscanf(fin, "%s", s) == EOF) break;
		m[string(s)]++;
		n++;
	}
	fclose(fin);
	for (auto a : m)
		tf.push_back(make_pair(a.first, 1.0 * a.second / n));
	sort(tf.begin(), tf.end(), [](auto & l, auto & r){
		if (l.second < r.second) return true;
		else if (l.second > r.second) return false;
		return l.first < r.first;
	});
}
//-----------------------------------------------------------------------------
#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <print>
#include <random>
#include <ranges>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <cctype>
using namespace std;

default_random_engine dre;
normal_distribution ndWord{ 0.0, 0.23 };			// 단어의 길이
normal_distribution ndSentence{ 0.0, 0.33 };		// 문장의 길이
uniform_int_distribution<int> uidC{ 'a', 'z' };

//---------
int main()
//---------
{
	ifstream in{ "기말시험.txt" };

	if (not in) {
		cout << "기말시험.txt - 파일을 열 수 없습니다" << endl;
		return -1;
	}


	//-------------------------------------------------------------------------- 
	// [문제 1]
	vector<vector<string>> sentences;
	string line;
	while (getline(in, line)) {
		istringstream iss(line);
		int n;
		iss >> n;
		vector<string> sentence;
		copy_n(istream_iterator<string>{iss}, n, back_inserter(sentence));
		sentences.push_back(sentence);
	}
	cout << "문장 수: " << sentences.size() << endl;
	// 출력값: 문장 수: 500



	//-------------------------------------------------------------------------- 
	// [문제 2]
	double totalWords = accumulate(sentences.begin(), sentences.end(), 0.0,
		[](double sum, const auto& s) { return sum + s.size(); });
	double avgWords = totalWords / sentences.size();
	cout << "평균 단어 수: " << avgWords << endl;
	// 출력값: 평균 단어 수: 3.768



	//-------------------------------------------------------------------------- 
	// [문제 3]
	double totalLength = 0;
	int wordCount = 0;
	for (const auto& sentence : sentences) {
		for (const auto& word : sentence) {
			totalLength += word.length();
			++wordCount;
		}
	}
	double avgLength = totalLength / wordCount;
	cout << "평균 단어 길이: " << avgLength << endl;
	// 출력값: 평균 단어 길이: 9.968



	//------------------------------------------------------------------
	vector<string> words;
	for (const auto& s : sentences)
		copy(s.begin(), s.end(), back_inserter(words));

	/*
	for (const string& s : words | views::take(20))
		cout << s << " ";
	cout << endl;
	*/



	//----------------------------------------------------------------------
	// [문제 4]
	transform(words.begin(), words.end(), words.begin(), [](string s) {
		if (!s.empty()) s[0] = toupper(s[0]);
		return s;
		});
	for (const string& s : words | views::take(20))
		cout << s << " ";
	cout << endl;
	// 출력 결과:
	// Heozy Zzzeszzycmu Uwynruaj Wfyrrktttm Ehsuaihwb Dczvvsd Arldjftbuaekm Llmqusxtu
	// Dlmuyoiwpvfat Vgvnyskxlypo Zgivhgay Fjxfwgyqumz Xshrtktojfo Nbkbjnpujyzde Asikey
	// Uliwnq Girnrst Zlscxfnxo Nozlcwlpcm Zz



	//--------------------------------------------------------------------------------
	// [문제 5]
	// std::copy( v.begin( ), v.end( ), REVERSE( v.begin( ) ) );
	std::copy(words.rbegin(), words.rend(), words.begin());

	/*
	for (const string& s : words | views::take(20))
		cout << s << " ";
	cout << endl;
	*/
	// 출력 결과:
	// yzoeH umcyzzsezzZ jaurnywU mtttkrryfW bwhiaushE dsvvzcD mkeaubtfjdlrA utxsuqmlL
	// tafvpwioyumlD opylxksynvgV yaghvigZ zmuqygwfxjF ofjotktrhsX edzyjupnjbkbN yekisA
	// qnwilU tsrnriG oxnfxcslZ mcplwclzoN zZ

	return 0;
}

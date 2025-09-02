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
normal_distribution ndWord{ 0.0, 0.23 };			// �ܾ��� ����
normal_distribution ndSentence{ 0.0, 0.33 };		// ������ ����
uniform_int_distribution<int> uidC{ 'a', 'z' };

//---------
int main()
//---------
{
	ifstream in{ "�⸻����.txt" };

	if (not in) {
		cout << "�⸻����.txt - ������ �� �� �����ϴ�" << endl;
		return -1;
	}


	//-------------------------------------------------------------------------- 
	// [���� 1]
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
	cout << "���� ��: " << sentences.size() << endl;
	// ��°�: ���� ��: 500



	//-------------------------------------------------------------------------- 
	// [���� 2]
	double totalWords = accumulate(sentences.begin(), sentences.end(), 0.0,
		[](double sum, const auto& s) { return sum + s.size(); });
	double avgWords = totalWords / sentences.size();
	cout << "��� �ܾ� ��: " << avgWords << endl;
	// ��°�: ��� �ܾ� ��: 3.768



	//-------------------------------------------------------------------------- 
	// [���� 3]
	double totalLength = 0;
	int wordCount = 0;
	for (const auto& sentence : sentences) {
		for (const auto& word : sentence) {
			totalLength += word.length();
			++wordCount;
		}
	}
	double avgLength = totalLength / wordCount;
	cout << "��� �ܾ� ����: " << avgLength << endl;
	// ��°�: ��� �ܾ� ����: 9.968



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
	// [���� 4]
	transform(words.begin(), words.end(), words.begin(), [](string s) {
		if (!s.empty()) s[0] = toupper(s[0]);
		return s;
		});
	for (const string& s : words | views::take(20))
		cout << s << " ";
	cout << endl;
	// ��� ���:
	// Heozy Zzzeszzycmu Uwynruaj Wfyrrktttm Ehsuaihwb Dczvvsd Arldjftbuaekm Llmqusxtu
	// Dlmuyoiwpvfat Vgvnyskxlypo Zgivhgay Fjxfwgyqumz Xshrtktojfo Nbkbjnpujyzde Asikey
	// Uliwnq Girnrst Zlscxfnxo Nozlcwlpcm Zz



	//--------------------------------------------------------------------------------
	// [���� 5]
	// std::copy( v.begin( ), v.end( ), REVERSE( v.begin( ) ) );
	std::copy(words.rbegin(), words.rend(), words.begin());

	/*
	for (const string& s : words | views::take(20))
		cout << s << " ";
	cout << endl;
	*/
	// ��� ���:
	// yzoeH umcyzzsezzZ jaurnywU mtttkrryfW bwhiaushE dsvvzcD mkeaubtfjdlrA utxsuqmlL
	// tafvpwioyumlD opylxksynvgV yaghvigZ zmuqygwfxjF ofjotktrhsX edzyjupnjbkbN yekisA
	// qnwilU tsrnriG oxnfxcslZ mcplwclzoN zZ

	return 0;
}

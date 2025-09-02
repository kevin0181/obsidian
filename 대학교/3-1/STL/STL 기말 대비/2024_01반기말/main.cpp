//-----------------------------------------------------------------------------
// 2024 STL �⸻����
// 
// Visual Studio ���� 17.9.0 �̻� 
// Release / x64
// ������Ʈ �Ӽ� - C++ ��� ǥ�� - �ֽ� C++ �ʾ��� ���(/std:c++latest)
//-----------------------------------------------------------------------------
// ���� �ۼ� ���
// - �� ������ �ذ��ϴ� �� �ʿ��� �ڵ常 ���´�.
// - ȭ�鿡 ����� �䱸�ϴ� ������ ��µ� ������ ������ ���´�.
// - ��� ������ ���� �ʿ�� ����.
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
using namespace std;

default_random_engine dre;
normal_distribution ndWord{ 0.0, 0.23 };			// �ܾ��� ����
normal_distribution ndSentence{ 0.0, 0.33 };		// ������ ����
uniform_int_distribution<int> uidC{ 'a', 'z' };

//-------------------------------------------------------------------------------------------
// �� ������ �𸣴� ������ "�⸻����.txt" ���Ͽ� �����Ͽ���.
// 
// [�� ���迡�� ������ ����] 
// �ϳ��� ������ 1�� �̻��� �ܾ�(std::string)�� �����Ǹ� �� �ܾ�� �������� ������ �ִ�.
//
// �� ����� �� ���� ������ �������� ���еȴ�.
// 
// ���Ͽ���, ������ �̷�� �ܾ��� ������ ���� �� �Ŀ� �� �ܾ �������� �и��Ͽ� ����Ͽ���.
//-------------------------------------------------------------------------------------------
// ������ ���� ��������. 
//
// [������ ����]
// stl algorithm   
// Comments serve as a sort of in-code documentation 
// heozyz zzeszzycmu uwynruaj 
//
// [���Ͽ� ������ ����]
// 2 stl algorithm   
// 8 Comments serve as a sort of in-code documentation 
// 3 heozyz zzeszzycmu uwynruaj 
//-------------------------------------------------------------------------------------------



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
	// [���� 1] ���Ͽ� ����� ��� ������ �о� STL Container�� �����϶�.	
	// ��� �� ���� ������ �о��� �� ȭ�鿡 ����ϰ� �������� �����.       (40)
	//--------------------------------------------------------------------------
	// ������ �о� �����̳ʿ� �����ϱ� ���� �ڵ带 ������ �����.
	// ����� �����̳� / �а� �����ϴ� �ڵ� / ���� �� ��� �ڵ�  / ��µ� ��
	//
	// (����) ������ ��� �б� ������ �� ���� ������ �ִ� �� �� �� ����.
	// (����) ������ ǥ���ϴ� class�� �ۼ����� �ʰ� �� ������ �ذ��� �� �ִ�.
	// (�κ� ����) ������ class�� �ۼ��� ��� 20������ ä��
	//--------------------------------------------------------------------------

	// ���⿡ 1�� ������ ���� �ڵ��Ѵ�
	vector<vector<string>> sentences;
	string line;
	while (getline(in, line)) {
		istringstream iss(line);
		int wordCount;
		iss >> wordCount;
		vector<string> sentence;
		copy_n(istream_iterator<string>(iss), wordCount, back_inserter(sentence));
		sentences.push_back(sentence);
	}
	cout << "Number of sentences read: " << sentences.size() << endl;




	//--------------------------------------------------------------------------
	// [���� 2] �� ������ ��� �� ���� �ܾ�� �����Ǵ� �� ����϶�.	
	// ��� �ܾ� ���� ȭ�鿡 ����ϰ� �������� �����.                      (20)
	//--------------------------------------------------------------------------
	// �� ������ �ܾ� ���� ���� �� [���� 1]���� ���� ���� ���� ������ �ȴ�.
	// ����� ���ϴ� �ڵ� / ���� ����ϴ� �ڵ� / ��µ� ��
	//
	// (�κ� ����) �˰����� ������� �ʰ� �հ踦 ��� �� ��� 10������ ä��
	//--------------------------------------------------------------------------

	// ���⿡ 2�� ������ ���� �ڵ��Ѵ�

	double totalWords = 0;
	for (const auto& sentence : sentences) {
		totalWords += sentence.size();
	}
	double averageWords = totalWords / sentences.size();
	cout << "Average number of words per sentence: " << averageWords << endl;






	//---------------------------------------------------------------------------
	// [���� 3] ��ü ���忡 ����� ��� �ܾ��� ��� ���̸� ����϶�.	
	// ��� ���̸� ȭ�鿡 ����ϰ� �������� �����.                          (20)
	//---------------------------------------------------------------------------
	// �ܾ��� ���̴� �� �״�� std:string::size() �Ǵ� std::string::length() ��.
	// �� ���忡 �ִ� �ܾ��� ���̸� ��� ���� �� ��� �ܾ��� ������ ������. 
	// ��� �ܾ��� ������ [���� 2]���� �̹� ����Ͽ���.
	// ��� ���̸� ���ϴ� �ڵ� / ���� ����ϴ� �ڵ� / ��µ� ��
	// 
	// (�κ� ����) �˰����� ������� �ʰ� �հ踦 ��� �� ��� 10�� ä��
	//---------------------------------------------------------------------------

	// ���⿡ 3�� ������ ���� �ڵ��Ѵ�

	double totalLength = 0;
	int wordCount = 0;
	for (const auto& sentence : sentences) {
		for (const auto& word : sentence) {
			totalLength += word.length();
			wordCount++;
		}
	}
	double averageLength = totalLength / wordCount;
	cout << "Average word length: " << averageLength << endl;





	//------------------------------------------------------------------
	// ���� �����̳ʿ� �ִ� ��� �ܾ vector<string> words�� �����϶�.
	// ����� �˾Ƽ� �ϰ� ������ ���� �ʾƵ� �ȴ�.
	//------------------------------------------------------------------
	// ���� �������� �ذ����� ���� �л��� ������ string�� 100�� �����Ͽ�
	// vector<string> �����̳ʿ� ������ �� ���� ������ �ذ��ϸ� �ȴ�.
	//------------------------------------------------------------------

	vector<string> words;

	// ���⿡�� words�� ���忡 �ִ� string�� �����Ѵ�.

	// ���� words���� ���Ͽ� �ִ� ��� �ܾ ���� ������� ����Ǿ� �ִ�.


	//--------------------------------------------------------------
	// ������ words�� ����� �ܾ 20���� ����� �ڵ�� �� ����̴�
	// �ڽ��� ����� ���� ����
	//--------------------------------------------------------------

	// �տ��� 20�� ȭ�� ��� �ڵ�
	/*
	for (const string& s : words | views::take( 20 ))
		cout << s << " ";
	cout << endl;
	*/

	// �տ��� 20�� ȭ�� ��� ���
	//	heozy zzzeszzycmu uwynruaj wfyrrktttm ehsuaihwb dczvvsd arldjftbuaekm llmqusxtu
	//	dlmuyoiwpvfat vgvnyskxlypo zgivhgay fjxfwgyqumz xshrtktojfo nbkbjnpujyzde asikey
	//	uliwnq girnrst zlscxfnxo nozlcwlpcm zz



	//----------------------------------------------------------------------
	// [���� 4] words�� ������ ��� �ܾ��� ù ���ڸ� �빮�ڷ� ��ȯ�϶�.	(20)
	//----------------------------------------------------------------------
	// ��ȯ �ڵ�
	//
	// (����) �˰����� ������� ���� ��� ���� ����
	//----------------------------------------------------------------------

	// ���⿡ 4�� ������ ���� �ڵ��Ѵ�
	transform(words.begin(), words.end(), words.begin(), [](string& s) {
		if (!s.empty()) s[0] = toupper(s[0]);
		return s;
		});




	// �տ��� 20�� ȭ�� ��� �ڵ�
	/*
	for (const string& s : words | views::take( 20 ))
		cout << s << " ";
	cout << endl;
	*/

	// �տ��� 20�� ȭ�� ��� ���
	//	Heozy Zzzeszzycmu Uwynruaj Wfyrrktttm Ehsuaihwb Dczvvsd Arldjftbuaekm Llmqusxtu
	//	Dlmuyoiwpvfat Vgvnyskxlypo Zgivhgay Fjxfwgyqumz Xshrtktojfo Nbkbjnpujyzde Asikey
	//	Uliwnq Girnrst Zlscxfnxo Nozlcwlpcm Zz



	//--------------------------------------------------------------------------------
	// [���� 5] ������ ���� std::copy�� ȣ���Ͽ� v�� ��� �ܾ �������� �ٲٷ� �Ѵ�.
	// �ʿ��� �ڵ��� �߰��϶�.                                                    (40)
	//--------------------------------------------------------------------------------

	// ���� �ּ����� �����ϰ� �ǵ���� ����� �� �־�� �Ѵ�
	// std::copy( v.begin( ), v.end( ), REVERSE( v.begin( ) ) );


	// �տ��� 20�� ȭ�� ��� �ڵ�
	/*
	for (const string& s : words | views::take( 20 ))
		cout << s << " ";
	cout << endl;
	*/

	// �տ��� 20�� ȭ�� ��� ���
	//	yzoeH umcyzzsezzZ jaurnywU mtttkrryfW bwhiaushE dsvvzcD mkeaubtfjdlrA utxsuqmlL
	//	tafvpwioyumlD opylxksynvgV yaghvigZ zmuqygwfxjF ofjotktrhsX edzyjupnjbkbN yekisA
	//	qnwilU tsrnriG oxnfxcslZ mcplwclzoN zZ

	vector<string> reversed(words.size());
	copy(words.rbegin(), words.rend(), reversed.begin());


}
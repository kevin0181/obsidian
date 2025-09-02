//-----------------------------------------------------------------------------
// 2024 STL 기말시험
// 
// Visual Studio 버전 17.9.0 이상 
// Release / x64
// 프로젝트 속성 - C++ 언어 표준 - 최신 C++ 초안의 기능(/std:c++latest)
//-----------------------------------------------------------------------------
// 답지 작성 방법
// - 각 문제를 해결하는 데 필요한 코드만 적는다.
// - 화면에 출력을 요구하는 문제는 출력된 내용을 답지에 적는다.
// - 헤더 파일을 적을 필요는 없다.
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
normal_distribution ndWord{ 0.0, 0.23 };			// 단어의 길이
normal_distribution ndSentence{ 0.0, 0.33 };		// 문장의 길이
uniform_int_distribution<int> uidC{ 'a', 'z' };

//-------------------------------------------------------------------------------------------
// 몇 개인지 모르는 문장을 "기말시험.txt" 파일에 저장하였다.
// 
// [이 시험에서 문장의 정의] 
// 하나의 문장은 1개 이상의 단어(std::string)로 구성되며 각 단어는 공백으로 나뉘어 있다.
//
// 한 문장과 그 다음 문장은 공백으로 구분된다.
// 
// 파일에는, 문장을 이루는 단어의 개수를 먼저 쓴 후에 각 단어를 공백으로 분리하여 기록하였다.
//-------------------------------------------------------------------------------------------
// 다음의 예를 참고하자. 
//
// [원래의 문장]
// stl algorithm   
// Comments serve as a sort of in-code documentation 
// heozyz zzeszzycmu uwynruaj 
//
// [파일에 저장한 내용]
// 2 stl algorithm   
// 8 Comments serve as a sort of in-code documentation 
// 3 heozyz zzeszzycmu uwynruaj 
//-------------------------------------------------------------------------------------------



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
	// [문제 1] 파일에 저장된 모든 문장을 읽어 STL Container에 저장하라.	
	// 모두 몇 개의 문장을 읽었는 지 화면에 출력하고 답지에도 적어라.       (40)
	//--------------------------------------------------------------------------
	// 문장을 읽어 컨테이너에 저장하기 위한 코드를 답지에 적어라.
	// 사용한 컨테이너 / 읽고 저장하는 코드 / 문장 수 출력 코드  / 출력된 값
	//
	// (주의) 파일을 모두 읽기 전에는 몇 개의 문장이 있는 지 알 수 없다.
	// (도움) 문장을 표현하는 class를 작성하지 않고 이 문제를 해결할 수 있다.
	// (부분 점수) 문장을 class로 작성한 경우 20점까지 채점
	//--------------------------------------------------------------------------

	// 여기에 1번 문제의 답을 코딩한다
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
	// [문제 2] 각 문장은 평균 몇 개의 단어로 구성되는 지 출력하라.	
	// 평균 단어 수를 화면에 출력하고 답지에도 적어라.                      (20)
	//--------------------------------------------------------------------------
	// 각 문장의 단어 수를 더한 후 [문제 1]에서 구한 문장 수로 나누면 된다.
	// 평균을 구하는 코드 / 값을 출력하는 코드 / 출력된 값
	//
	// (부분 점수) 알고리즘을 사용하지 않고 합계를 계산 한 경우 10점까지 채점
	//--------------------------------------------------------------------------

	// 여기에 2번 문제의 답을 코딩한다

	double totalWords = 0;
	for (const auto& sentence : sentences) {
		totalWords += sentence.size();
	}
	double averageWords = totalWords / sentences.size();
	cout << "Average number of words per sentence: " << averageWords << endl;






	//---------------------------------------------------------------------------
	// [문제 3] 전체 문장에 저장된 모든 단어의 평균 길이를 출력하라.	
	// 평균 길이를 화면에 출력하고 답지에도 적어라.                          (20)
	//---------------------------------------------------------------------------
	// 단어의 길이는 말 그대로 std:string::size() 또는 std::string::length() 임.
	// 각 문장에 있는 단어의 길이를 모두 더한 후 모든 단어의 개수로 나눈다. 
	// 모든 단어의 개수는 [문제 2]에서 이미 계산하였다.
	// 평균 길이를 구하는 코드 / 값을 출력하는 코드 / 출력된 값
	// 
	// (부분 점수) 알고리즘을 사용하지 않고 합계를 계산 한 경우 10점 채점
	//---------------------------------------------------------------------------

	// 여기에 3번 문제의 답을 코딩한다

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
	// 이제 컨테이너에 있는 모든 단어를 vector<string> words에 복사하라.
	// 복사는 알아서 하고 답지에 쓰지 않아도 된다.
	//------------------------------------------------------------------
	// 앞의 문제들을 해결하지 못한 학생은 임의의 string을 100개 생성하여
	// vector<string> 컨테이너에 저장한 후 이후 문제를 해결하면 된다.
	//------------------------------------------------------------------

	vector<string> words;

	// 여기에서 words에 문장에 있는 string을 복사한다.

	// 이제 words에는 파일에 있는 모든 단어가 읽은 순서대로 저장되어 있다.


	//--------------------------------------------------------------
	// 다음은 words에 저장된 단어를 20개만 출력한 코드와 그 결과이다
	// 자신의 결과와 비교해 보자
	//--------------------------------------------------------------

	// 앞에서 20개 화면 출력 코드
	/*
	for (const string& s : words | views::take( 20 ))
		cout << s << " ";
	cout << endl;
	*/

	// 앞에서 20개 화면 출력 결과
	//	heozy zzzeszzycmu uwynruaj wfyrrktttm ehsuaihwb dczvvsd arldjftbuaekm llmqusxtu
	//	dlmuyoiwpvfat vgvnyskxlypo zgivhgay fjxfwgyqumz xshrtktojfo nbkbjnpujyzde asikey
	//	uliwnq girnrst zlscxfnxo nozlcwlpcm zz



	//----------------------------------------------------------------------
	// [문제 4] words에 저장한 모든 단어의 첫 글자를 대문자로 변환하라.	(20)
	//----------------------------------------------------------------------
	// 변환 코드
	//
	// (감점) 알고리즘을 사용하지 않은 경우 점수 없음
	//----------------------------------------------------------------------

	// 여기에 4번 문제의 답을 코딩한다
	transform(words.begin(), words.end(), words.begin(), [](string& s) {
		if (!s.empty()) s[0] = toupper(s[0]);
		return s;
		});




	// 앞에서 20개 화면 출력 코드
	/*
	for (const string& s : words | views::take( 20 ))
		cout << s << " ";
	cout << endl;
	*/

	// 앞에서 20개 화면 출력 결과
	//	Heozy Zzzeszzycmu Uwynruaj Wfyrrktttm Ehsuaihwb Dczvvsd Arldjftbuaekm Llmqusxtu
	//	Dlmuyoiwpvfat Vgvnyskxlypo Zgivhgay Fjxfwgyqumz Xshrtktojfo Nbkbjnpujyzde Asikey
	//	Uliwnq Girnrst Zlscxfnxo Nozlcwlpcm Zz



	//--------------------------------------------------------------------------------
	// [문제 5] 다음과 같이 std::copy를 호출하여 v의 모든 단어를 역순으로 바꾸려 한다.
	// 필요한 코딩을 추가하라.                                                    (40)
	//--------------------------------------------------------------------------------

	// 다음 주석문을 제거하고 의도대로 실행될 수 있어야 한다
	// std::copy( v.begin( ), v.end( ), REVERSE( v.begin( ) ) );


	// 앞에서 20개 화면 출력 코드
	/*
	for (const string& s : words | views::take( 20 ))
		cout << s << " ";
	cout << endl;
	*/

	// 앞에서 20개 화면 출력 결과
	//	yzoeH umcyzzsezzZ jaurnywU mtttkrryfW bwhiaushE dsvvzcD mkeaubtfjdlrA utxsuqmlL
	//	tafvpwioyumlD opylxksynvgV yaghvigZ zmuqygwfxjF ofjotktrhsX edzyjupnjbkbN yekisA
	//	qnwilU tsrnriG oxnfxcslZ mcplwclzoN zZ

	vector<string> reversed(words.size());
	copy(words.rbegin(), words.rend(), reversed.begin());


}
//------------ 주 의 ------------
// namespace std를 사용하였다.
// include 문장을 답지에 적을 필요없다.
// 실행되지 않는 코드를 적으면 감점한다
// 답이 맞더라도 효율 낮은 코드나 알고리즘을 사용하지 않은 코드는 감점한다.
// 프로그램 환경 - Release/x64, 프로젝트 속성 - 미리 보기 - 최신 C++ 초안의 기능(/std:c++latest)

// e-class에서 시험.zip을 다운 받은 후 시작한다.

// 각 문제를 해결하는데 필요한 코드( 멤버함수 포함 )를 답지에 적는다.
// 화면 출력을 적으라는 문제는 출력된 내용을 답지에 적는다.

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <ranges>
using namespace std;

//---------
int main()
//---------
{
    // "시험.txt" 파일에는 알파벳과 공백 문자가 기록되어 있다.

    ifstream in{ "시험.txt" };

    vector<char> v;

    // [문제 1] "시험.txt"에 저장된 문자를 공백은 제외하고 모두 읽어 벡터 v에 저장하라.   
    // v에 저장된 원소의 수를 화면에 출력하고 답지에도 적어라.            			(코드:15, 출력값:5)
    // (주의) v는 이미 생성되어있다.
    copy_if(istream_iterator<char>{in}, {}, back_inserter(v),
        [](char c) { return c != ' '; });

    cout << "v의 size: " << v.size() << endl;


    // [문제 2] v에 저장되어 있는 글자들에서 글자 's' 't' 'l' 이 연속된 경우는  
    // 모두 몇 번인가 출력하고 답지에도 적어라.                           			(코드:25, 출력값:5)
    // (예) mnqsorhzhybjgbkstlksuuqunebcpoannstljkvdndcyfipievtfwsak
    // 위 글자들에서 's' 't' 'l' 이 연속된 경우는 두 번이다.

    int count{};
    for (size_t i = 0; i + 2 < v.size(); ++i)
        if (v[i] == 's' && v[i + 1] == 't' && v[i + 2] == 'l')
            ++count;

    cout << "'stl' 등장 횟수: " << count << endl;





    // [문제 3] v에 저장된 글자를 대문자와 소문자로 분리하라.                (코드:25, 출력값:5)
    // 대문자는 v1에 저장하고 소문자는 v2에 저장하라.
    // v1과 v2의 size를 화면에 출력하고 답지에도 써라.

    vector<char> v1, v2;
    partition_copy(v.begin(), v.end(), back_inserter(v1), back_inserter(v2),
        [](char c) { return isupper(c); });

    cout << "대문자 개수: " << v1.size() << ", 소문자 개수: " << v2.size() << endl;


    // [문제 4] 오름차순으로 정렬된 벡터 v2에서 각 알파벳의 개수를 컨테이너 alpha에 저장하라. 		
    // a[0]에는 'a', a[1]에는 'b' ... , a[25]에는 'z'의 개수가 저장되도록 하라.
    // 각 알파벳의 개수를 화면에 출력하고 'c'의 개수는 답안지에도 적어라.  			(코드:25, c의 개수:5)
    // (주의) O(n) 알고리즘을 사용하면 점수없음. 정렬되어 있다는 점을 활용할 것. 

    ranges::sort(v2); // 문제 지시에 따라 정렬은 반드시 필요

    array<int, 26> alpha{};
    auto it = v2.begin();

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        it = upper_bound(it, v2.end(), ch);
        alpha[ch - 'a'] = distance(v2.begin(), it) - accumulate(alpha.begin(), alpha.begin() + (ch - 'a'), 0);
    }

    for (int i = 0; i < 26; ++i)
        cout << static_cast<char>('a' + i) << ": " << alpha[i] << '\n';

    cout << "'c'의 개수: " << alpha['c' - 'a'] << endl;


    // [참고] 컨테이너의 원소를 출력해 본다
    string s{ "C++20 STL" };
    for_each(s.begin(), s.end(), print<char>);
    cout << endl;                                           // 출력 결과  C - + - + - 2 - 0 -   - S - T - L -


    // [문제 5] 다음 문장을 실행하면 화면에 [1, 11)까지 숫자가 출력되도록 필요한 코딩을 하라.	(관련코드:40)

    // 주석을 해제하고 실행되도록 하자
    //for_each( NUM( 1 ), NUM( 11 ), print<int> );        // 출력 결과   1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 -
    //cout << endl << endl;

}
//기말문제01반
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
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <format>
using namespace std;

#define REVERSE(x) reverse_iterator<decltype(x)>(x)

//---------
int main()
//---------
{
    ifstream in{ "기말단어.txt" };
    if (not in)
        return 0;

    vector<string> v;

    // [문제 1] 파일 "기말단어.txt"에 있는 모든 단어를 읽어 컨테이너 v에 저장하라.
    // 모두 몇 개의 단어를 읽었는지 화면에 출력하고 출력결과를 답지에도 적어라.   (코드:15, 결과:5)                             
    // (참고) 파일은 텍스트 모드로 기록되었으며 텍스트 편집기로 읽을 수 있다.
    // (주의) v는 이미 생성되어있다.

    v = { istream_iterator<string>{in}, {} };
    cout << "단어 개수: " << v.size() << endl;

    // [문제 2] v에 저장된 단어의 평균 길이를 소수점 둘째자리까지 출력하고 답지에도 적어라. (코드:15, 출력값:5)
    // (참고) {:2.2f}
    double avg_len = accumulate(v.begin(), v.end(), 0.0,
        [](double sum, const string& s) { return sum + s.size(); }) / v.size();
    cout << format("평균 길이: {:2.2f}", avg_len) << endl;

    // [문제 3]  v에 저장된 단어 중에서 "stl"이라는 연속된 문자가 들어간 단어를 찾아라. 
    // "stl"이 들어간 단어 모두와 단어의 개수를 화면에 출력하고 답지에 출력된 개수도 적어라.   (코드:20, 개수:5)
    // (예) jnziastlizef - 이 단어에는 stl이 들어있다.
    vector<string> with_stl;
    copy_if(v.begin(), v.end(), back_inserter(with_stl),
        [](const string& s) { return s.find("stl") != string::npos; });

    for (const string& s : with_stl)
        cout << s << '\n';

    cout << "stl 포함 단어 개수: " << with_stl.size() << endl;

    // [문제 4] v를 사전으로 만든 후 사전의 단어 수를 출력하고 답지에도 적어라. (코드:10, 단어개수:5)
    // (주의) 사전은 오름차순으로 정렬되어 있으며 중복된 단어가 없다.
    ranges::sort(v);
    v.erase(unique(v.begin(), v.end()), v.end());

    cout << "사전의 단어 수: " << v.size() << endl;


    // 다음 코드는 "단어들.txt"를 읽어 words에 저장한다.
    // (참고) words는 오름차순 정렬되어 있으며 중복된 단어가 없다.

    ifstream in2{ "단어들.txt" };
    if (not in2)
        return 0;

    vector<string> words{ istream_iterator<string>{in2}, {} };
    cout << "단어들.txt - " << words.size() << endl;

    // (출력) 단어들.txt - 369882



    // [문제 5] v에 있는 단어 중에서 "단어들.txt"에 있는 단어를 찾아 v2에 저장하라.              
    // v2에 모두 몇 단어가 있는지 출력하고 답지에도 써라.                      (코드:15, 개수:5)
    // (참고) 공통 단어는 set_intersection으로 찾을 수 있다.
    vector<string> v2;
    ranges::sort(v);
    set_intersection(v.begin(), v.end(),
        words.begin(), words.end(),
        back_inserter(v2));

    cout << "공통 단어 개수: " << v2.size() << endl;


    // [문제 6] 다음과 같이 표준 알고리즘함수 copy를 호출하면 v의 모든 단어가 역순으로 바뀐다.
    // 필요한 코딩을 추가하라.                                                (관련코드:40)
    // (예) 다음은 v의 단어 4개를 역순으로 바꾼 것이다 
    // v의 처음 4 단어  - a aaat aacdkuopsavjiornyb aadksxwzjdfkovafbdyckguegepyx
    // 역순으로 바꾼 후 - a taaa bynroijvaspoukdcaa xypegeugkcydbfavokfdjzwxskdaa

    // 다음 주석문을 제거하고 실행할 것
    {
        const size_t n = v.size();

        // 역순 데이터 생성
        vector<string> temp = v;
        reverse(temp.begin(), temp.end());

        // v 크기를 2배로 늘려서 REVERSE(v.begin())가 안전하게 작동하도록 보장
        v.resize(n * 2);

        // 뒤쪽에 temp 삽입 (n ~ 2n 위치에 역순 데이터)
        copy(temp.begin(), temp.end(), v.begin() + n);

        // 이제 이 문장이 안전하게 앞쪽을 역순으로 덮어씀
        std::copy(v.begin() + n, v.end(), REVERSE(v.begin()));
    }

    for (int i = 0; i < 4; ++i)
        cout << v[i] << endl;

}


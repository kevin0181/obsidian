#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

#include "STRING.h"

// [1] vector<STRING>에 저장하라.
// [2] 모두 몇 단어인지 화면에 출력하라.
// [3] vector<STRING>의 단어를 모두 set<STRING>에 복사하라.
// [4] 찾는 단어가 있는지 알려주자.
// [5] 찾는 단어를 포함한 단어가 모두 몇개 있나 출력하라.
//		(예) "tion"이 포함된 단어는 - anmation, information 등등 이런느낌스

using namespace std;
int main() {

	fstream in{ "이상한 나라의 앨리스.txt" };

	/*vector<STRING> v{ istream_iterator<STRING>{in},{} }; // 이건 이쁘게 보이지만 사실 매우 많이 호출하기때문에 사용 x
	cout << "모두 " << v.size() << endl;*/


	vector<STRING>v;
	v.reserve(100000); // 크기를 알면 이걸 꼭 만들어서 넣어주자.
	STRING 단어;
	while (in >> 단어) {
		v.push_back(단어);
	}

	cout << "모두 " << v.size() << endl;

	//set<STRING> s;
	///*for (const STRING& 단어 : v)
	//	s.insert(단어);*/
	//s.insert(v.begin(), v.end());

	set<STRING> s{ v.begin(),v.end() }; //가능.
	cout << "모두 " << s.size() << "개의 서로 다른 단어를 사용하였다." << endl;

	for (const STRING& 단어 : s)
		cout << 단어 << " ";
	cout << endl;

	//while (true) {
	//	cout << "찾을 단어? ";
	//	STRING 단어;
	//	cin >> 단어;

	//	auto p = find(s.begin(), s.end(), 단어); // 지금 이건 매우 비효율적임 왜? 이미 다 정렬해둔 상태에서 처음부터 찾기때문에 비효율적임. //이렇게하면 0점이겟죠? ㅋ
	//	if (p != s.end()) {
	//		cout << 단어 << "를 set에서 찾았습니다." << endl;
	//	}
	//	else {
	//		cout << "없는 단어입니다." << endl;
	//	}
	//}

	// 정렬된 데이터이니깐 반으로 자르고 찾을 데이터의 크기를 비교해서 찾는거임. (set이 제일잘하는거 자기가 멤버함수로불리는거?)
	
	//cout << "set의 크기 " << sizeof(s) << endl;

	//while (true) { //이게맞음.
	//	cout << "찾을단어?";
	//	STRING 단어;
	//	cin >> 단어;
	//	
	//	if (s.contains(단어)) {
	//		cout << "있는 단어" << endl;
	//	}
	//	else {
	//		cout << "없다" << endl;
	//	}
	//}

	//flat_set?  visual studio에는 아직 구현이 안댐!!

	while (true) {
		cout << "찾을 단어? ";
		STRING 단어;
		cin >> 단어;
		// 단어가 포함된 s의 원소들은 모두 몇 개인가?
		// 입력한 단어를 포함한 s의 원소 개수를 모두 센다.

		size_t num = count_if(s.begin(), s.end(), [단어](const STRING& word) { //단어를 저런식으로 외부에 잇는걸 가져오는걸 람다 캡쳐 라고함. 모든 변수를 가져오고 싶을때 &이거쓰면되긴하는데 람다의 독립성이 훼손댐
			auto p = search(word.begin(), word.end(), 단어.begin(), 단어.end());
			if (p != word.end()) {
				return true;
			}
			return false;
			});

		cout << 단어 << "를 갖고 있는 개수 - " << num << endl;


	}

}

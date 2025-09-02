// ------------- 주의 ------------------
// namespace std를 사용하였다.
// include 문장을 답지에 적을 필요없다.
// 실행되지 않는 코드를 적으면 감점한다.
// 답이 맞더라도 효율 낮은 코드나 알고리즘을 사용하지 않은 코드는 감점한다.
// 프로그램 환경 - Release/x64, 프로젝트 속성 - 미리 보기 - 최신 C++ 초안의 기능(/std:c++latest})

// e-class에서 시험.zip을 다운 받은 후 시작한다.

// 각 문제를 해결하는데 필요한 코드(멤버함수 포함)를 답지에 적는다.
// 화면 출력을 적으라는 문제는 출력된 내용을 답지에 적는다.

//--------------------------------------------------------------------------
// class Test
//---------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include <filesystem>

using namespace std;

class Test {
	size_t id{};		// 랜덤 숫자
	string word{}; // 영문자, 공백이 없으며 최대 15글자

public:
	void write(ostream& os) const {
		os.write((char*)this, sizeof(Test));
	}

	void show() const {
		cout << "id: " << id << " word: " << word << endl;
	}
};


//--------------------
int main()
//--------------------
{
	// "TEST 객체" 파일(바이너리 모드)에 Test 객체를 write() 멤버함수로 기록하였다.
	// 파일에는 몇 개인지 모르는 Test 객체가 저장되어 있다.

	string fileName{ "Test 객체" };

	ifstream in{ fileName, ios::binary };
	if (!in) {
		cout << fileName << " 파일을 열 수 없습니다." << endl;
		exit(0);
	}

	size_t fileSize = filesystem::file_size(fileName);
	cout << "파일 \"" << fileName << "\"의 크기 = " << fileSize << " 바이트 " << endl;

	// [문제 1] 출력된 파일 크기를 보고 저장된 객체의 수를 알 수 있는지를
	// "예/아니오"로 답하고 그렇게 답한 이유를 설명하라. (10점)
	
	// (예/아니오) : 예
	// "Test 객체" 파일에는 저장된 객체의 수는 알 수 없지만,
	// 전체 파일의 크기는 출력했을 경우 32바이트 이다.
	// 이때 한개의 객체 즉 sizeof(Test)를 통해 한개의 크기를 알 수 있으므로
	// 전체 파일의 크기 / sizeof(Test)를 통해 저장된 객체의 수를 알 수 있다.
	



	// [문제 2] 파일을 읽어 객체를 컨테이너에 저장하라.

	// 읽은 객체의 개수를 출력하고, 마지막 객체의 show()를 호출하라.
	// 화면에 출력된 내용을 답지에도 적어라.

<<<<<<< HEAD
	vector<Test> test;




=======
	vector<Test> tests;
	Test temp;
	while (in.read((char*)&temp, sizeof(Test))) {
		tests.push_back(temp);
	}
>>>>>>> bb8511b400caa02540c5192a5ffda4efc67126d6

	cout << "Test 총 객체 수: " << tests.size() << endl;
	tests.back().show();


	// (확인) 처음과 다음 객체의 show()를 호출한 결과는 다음과 같다.
	// id: 5111803 word: vrkmetlqhubq
	// id 18649 word: ohjdt


	
	// [문제 3] 함수 deleteZ()는 [문제 2]에서 사용한 컨테이너를 인자로 받아
	// 컨테이너에 저장된 Test 객체의 word의 문자 중 소문자 'z'를 삭제하는 함수이다.
	// 이 함수를 선언하고 정의한 후 호출하라.

	// (참고) string은 begin()과 end()를 제공하며 글자는 contiguous memory에 저장된다.

	// (참고) 컨테이너 이름이 x라면 deleteZ(x)와 같이 호출한다.

	// (확인) 'z'를 삭제한 후 처음과 다음 객체의 show()를 호출한 결과는 다음과 같다.
	// id: 5111803 word: vrkmetlqhubq
	// id 18649 word: ohjdt

	
	// [문제 4] 컨테이너에 저장한 Test 객체를 word 오름차순으로 정렬하고
	// 제일 마지막 객체의 show()를 호출하라.
	// 화면에 출력된 결과를 답지에 적어라.

	// [문제 5] 컨테이너에 저장된 Test 객체 중 id 값이 같은 객체는 하나 만 남기고 다 삭제하라.
	// 삭제 후 컨테이너에 남은 Test객체의 수를 출력하고 결과를 답지에 적어라.






}
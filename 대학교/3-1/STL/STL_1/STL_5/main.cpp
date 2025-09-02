//-------------------------------------------------
// 2025. STL 3.20                           3w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 많은 개수 자료 처리하기 - 객체를 바이너리 모드 / 저수준 입출력
//-------------------------------------------------
// 메모장
//

#include <string>
#include <iostream>
#include <random>
#include <print>
#include <fstream>
#include <array>

std::default_random_engine dre;
std::uniform_int_distribution<int> uid{ 'a','z' };

class Dog {
public:
	Dog() {
		id = ++sid;
		for (int i = 0; i < 15; ++i) {
			name += uid(dre);
		}
	}

	void show() {
		std::println("[{:8}] - {}", id, name);
	}
private :
	std::string name;
	int id;
	static int sid; // access - local, life-time - global
	
	friend std::ostream& operator<< (std::ostream& os, const Dog& dog) {
		//return os << dog.id << "\t" << dog.name;
		os.write((char*)&dog, sizeof(Dog));
		return os;
	}

};

int Dog::sid{}; // - static 이렇게 초기화 

// [문제] Dog 객체 10만개를 binary모드로 연 파일 "Dog 10만 마리"에
// write 함수를 이용하여 메모리 그대로 저장하라. 
// 
// -- 실제 시험에선 이렇게 쓴다는듯?
// 출력 연산자 << 를 사용하여 저장하였다. (밑에처럼)
//    friend std::ostream& operator<< (std::ostream& os, const Dog& dog) {
//	    os.write((char*)&dog, sizeof(Dog));
//	    return os;
//    }
// 
//


// [진짜 문제] Dog 객체 10만개를 binary mode로 연 파일 "Dog 10만 마리"에 저장하였다.
// 파일의 write 함수를 사용하여 객체 메모리 전체를 그대로 저장하였다.
// 파일에 있는 객체 전체를 메모리로 읽어 와라.
// name과 id를 화면에 출력하라.

// [이렇게 낼듯?문제] 
//		이렇게 사용해서 저장하였다~~ 이러고 dog객체랑 id,name만 알려주고 이제 풀라고하는듯
//    friend std::ostream& operator<< (std::ostream& os, const Dog& dog) {
//	    os.write((char*)&dog, sizeof(Dog));
//	    return os;
//    }
// 다음 코드가 실행되게 하라~ 이러면서 ifstream 쪽만 써주는거임.
int main() {
	//std::ofstream out{ "Dog 10만 마리", std::ios::binary };
	//for (int i = 0; i < 100000; ++i) {
	//	Dog dog; // 이렇게 써도 뭐 최적화 뭐시기로 루프 밖으로 컴파일러가 빼낸다 뭐시기.; 
	//	out.write((char*)&dog, sizeof(dog));

	//}

	//std::ifstream in{ "Dog 10만 마리",std::ios::binary };

	//std::array<Dog, 100000> dogs;
	//in.read(reinterpret_cast<char*>(dogs.data()), dogs.size() * sizeof(Dog)); // 수정된 부분

	//for (Dog d : dogs) {
	//	d.show();
	//}

	// --저장 코드래
	/*for (int i = 0; i < 100000; ++i) {
		Dog dog;
		out << dog;
	}*/

	//교수님 코드---------------------------------------------

	std::ifstream in_p1{ "Dog 10만 마리", std::ios::binary };
	if (not in_p1)
		return 0;

	/*Dog dog;
	for (int i = 0; i < 10; ++i) {
		in_p1.read((char*)&dog, sizeof(Dog));

		std::cout << dog << std::endl;
	}*/

	std::array<Dog, 100000>dogs; // 이상태에서 실행하면 스택 메모리에 차서 안됨. 전역 변수로 옮기면 됨. (vector 사용해서 힙 메모리로 옮겨야함)

	in_p1.read((char*)dogs.data(), dogs.size() * sizeof(Dog));

	for ( const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}
	

	// [찐문제] 다음 코드가 실행되게하라.
	/*Dog dog;
	for (int i = 0; i < 10; ++i) {
		in >> dog;
		std::cout << dog << std::endl;
	}*/
	// 이코드가 돌아가게 해야됨.

}

//-------------------------------------------------
// 2025. STL 3.20                           3w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// ���� ���� �ڷ� ó���ϱ� - ��ü�� ���̳ʸ� ��� / ������ �����
//-------------------------------------------------
// �޸���
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

int Dog::sid{}; // - static �̷��� �ʱ�ȭ 

// [����] Dog ��ü 10������ binary���� �� ���� "Dog 10�� ����"��
// write �Լ��� �̿��Ͽ� �޸� �״�� �����϶�. 
// 
// -- ���� ���迡�� �̷��� ���ٴµ�?
// ��� ������ << �� ����Ͽ� �����Ͽ���. (�ؿ�ó��)
//    friend std::ostream& operator<< (std::ostream& os, const Dog& dog) {
//	    os.write((char*)&dog, sizeof(Dog));
//	    return os;
//    }
// 
//


// [��¥ ����] Dog ��ü 10������ binary mode�� �� ���� "Dog 10�� ����"�� �����Ͽ���.
// ������ write �Լ��� ����Ͽ� ��ü �޸� ��ü�� �״�� �����Ͽ���.
// ���Ͽ� �ִ� ��ü ��ü�� �޸𸮷� �о� �Ͷ�.
// name�� id�� ȭ�鿡 ����϶�.

// [�̷��� ����?����] 
//		�̷��� ����ؼ� �����Ͽ���~~ �̷��� dog��ü�� id,name�� �˷��ְ� ���� Ǯ����ϴµ�
//    friend std::ostream& operator<< (std::ostream& os, const Dog& dog) {
//	    os.write((char*)&dog, sizeof(Dog));
//	    return os;
//    }
// ���� �ڵ尡 ����ǰ� �϶�~ �̷��鼭 ifstream �ʸ� ���ִ°���.
int main() {
	//std::ofstream out{ "Dog 10�� ����", std::ios::binary };
	//for (int i = 0; i < 100000; ++i) {
	//	Dog dog; // �̷��� �ᵵ �� ����ȭ ���ñ�� ���� ������ �����Ϸ��� ������ ���ñ�.; 
	//	out.write((char*)&dog, sizeof(dog));

	//}

	//std::ifstream in{ "Dog 10�� ����",std::ios::binary };

	//std::array<Dog, 100000> dogs;
	//in.read(reinterpret_cast<char*>(dogs.data()), dogs.size() * sizeof(Dog)); // ������ �κ�

	//for (Dog d : dogs) {
	//	d.show();
	//}

	// --���� �ڵ巡
	/*for (int i = 0; i < 100000; ++i) {
		Dog dog;
		out << dog;
	}*/

	//������ �ڵ�---------------------------------------------

	std::ifstream in_p1{ "Dog 10�� ����", std::ios::binary };
	if (not in_p1)
		return 0;

	/*Dog dog;
	for (int i = 0; i < 10; ++i) {
		in_p1.read((char*)&dog, sizeof(Dog));

		std::cout << dog << std::endl;
	}*/

	std::array<Dog, 100000>dogs; // �̻��¿��� �����ϸ� ���� �޸𸮿� ���� �ȵ�. ���� ������ �ű�� ��. (vector ����ؼ� �� �޸𸮷� �Űܾ���)

	in_p1.read((char*)dogs.data(), dogs.size() * sizeof(Dog));

	for ( const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}
	

	// [����] ���� �ڵ尡 ����ǰ��϶�.
	/*Dog dog;
	for (int i = 0; i < 10; ++i) {
		in >> dog;
		std::cout << dog << std::endl;
	}*/
	// ���ڵ尡 ���ư��� �ؾߵ�.

}


#include <iostream>
#include <string>
#include <fstream>
#include <array>

class Dog {
private:
	std::string name;
	int id;
	friend std::ostream& operator<<(std::ostream& os, const Dog& dog) {
		return os << dog.id << "\t" << dog.name;
	}

	friend std::istream& operator>>(std::istream& is, Dog& dog) {
		return is.read((char*)&dog, sizeof(Dog));
	}
};

std::array<Dog, 100000> dogs;

int main(){
	std::ifstream in{ "Dog 10�� ����", std::ios::binary };
	if (not in)
		return 0;


	// [����] ���� �ڵ尡 ����ǰ��϶�.
	//�ѹ��� �޸𸮿� �о�´�.
	/*Dog dog;
	for (int i = 0; i < 10; ++i) {
		in >> dog;
		std::cout << dog << std::endl;
	}*/


	in.read((char*)dogs.data(), sizeof(Dog) * dogs.size());
	
	for (const Dog& dog : dogs) {
		std::cout << dog << std::endl;
	}

}


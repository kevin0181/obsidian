//-------------------------------------------------
// 2025. STL 5..08                           10w 2d
//-------------------------------------------------
// 
//-------------------------------------------------
// 
//-------------------------------------------------
// 
// list���� ã��� o(n)��. �׷��� find_if ��  list-> ������̴ϱ� ���� ������ ���� ã�°� vector�� ���ؼ� ����.
// forward_list<T> - it is intended that forward_list have zero space or time ovecrhead 
// relative to a hand-written c-style singly linked list.
// Features that would conflict width that goal have been omitted.
// span - ��� contigous �ڷᱸ���� ��ǥ�ϴ� �ڷᱸ��
// Iterator - iterators are a generalization of pointers that allow a c++ program
// to work width different data structures (for example,containers and ranges) in a uniform manner.


#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <span>
#include <vector>
#include <deque>
#include <string>

#include"STRING.h"

// f�� �Ųٷ� ����ϴ� �Լ�
void f(std::span<int> s) {
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
}

void f_s(std::span<std::string> s) {
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
}


int main() {

	std::fstream in{ "main.cpp" };
	if (not in)
		return 0;

	// [����] 'main.cpp"�� �ܾ list�� �����϶�.
	std::list<STRING> cont{ std::istream_iterator<STRING>{in},{} };

	// ������ ���� ���
	/*for (const STRING& s : cont)
		std::cout << s << std::endl;*/

	// [����] �ܾ �Է¹޾� cont�� �ִ��� ����Ѵ�.
	// �ִٸ� ó������ ������ �� ��° �ܾ����� ����϶�.
	// (����) ã�� �ܾ ��� ã�ƶ�.

	/*while (true) {

		std::cout << "ã�� �ܾ��?";

		STRING word;
		std::cin >> word;

		auto pos = std::find(cont.begin(), cont.end(), word);

		if (pos == cont.end())
			std::cout << word << "�� ���� �ܾ� �Դϴ�." << std::endl;
		else
			std::cout << word << "�� " << std::distance(cont.begin(), pos) + 1 << "��° �ܾ� �Դϴ�." << std::endl;
	}*/


	// [����] ����Ʈ�� �ִ� �ܾ� �߿��� ���̰� 5�ΰ� ��θ� ȭ�鿡 ����϶�.
	/*std::copy_if(cont.begin(), cont.end(), std::ostream_iterator<STRING> {std::cout, "\n"},
		[](const STRING& s) {
			return s.size() == 5;
		});*/

	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	// �Ųٷ� ����϶�.
	for (auto i = std::rbegin(a); i != std::rend(a);++i)
		std::cout << *i << std::endl;
	// a�� ���� contigous�� �޸𸮸� ���� ��鵵 rebegin()���� ���� �Լ��� ����ؼ� ����� ����.
	//f(a);

	std::vector<int> v{ std::begin(a), std::end(a) };
	//f(v);

	std::deque<int> d{ v.begin(),v.end() };
	//f(d); // deque�� contigous�� �޸𸮸� ������ ����. �׷��� span�� ������� ����.

	std::string s{ "hello world" };
	//f_s(s);


	// ------------------------------------------------------------------------------------------------

	//std::sort(std::begin(a) + 4, std::begin(a) + 6); // 4~6���� ���� �̰� range�����

	//for(int num : a)
	//	std::cout << num << " ";
	//std::cout << std::endl;

	//��¹ݺ��ڸ� �����
	//std::ostream_iterator <char> p; // �̷��� �ȵǴ� ����? �⺻�����ڰ� ����.
	std::ostream_iterator <char> p{ std::cout };

	//*p = 'A';
	////++p; // �̰� ����� �ڵ����� ���� �޸� �ڸ��� �˾Ƽ� �̵��� �ϱ� ��.
	//*p = 'B';
	////++p;
	//*p = 'C';
	////++p;
	//*p = '\n';

	STRING s1{ "hello" };

	//for (char c : s1) // -> �������� �ȵǴ� ���� �� begin, end ��� �ȴ�.
	//	std::cout << c << std::endl;

	//for (auto i = s1.begin(); i != s1.end(); ++i) // ������ �����Ѱ���.
	//	std::cout << *i << std::endl;

	for (char c : s1)
		std::cout << c;
	std::cout << std::endl;

}
//-------------------------------------------------
// 2025. STL 4.29                           9w 1d
//-------------------------------------------------
// ���⼭���ʹ� �⸻��糪���°�...
//-------------------------------------------------
// �߰���� Ǭ�� Ǯ���~~ 95������
//-------------------------------------------------
// 
//
// �⸻��� �ĺ� -> Test t(3); -> �޸� ���� �׸� �׷�����.

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

#include"string.h"

int main() {
	
	//std::vector<STRING> v{ "1","22","333","4444","55555" };
	// 
	//std::erase(v, "333"); // syntactic sugar // �߰��� �̷��� ����� ������ vector���� ��� �����͸� ������ ���� ������ ���� �ʴ�.
	//// list�� ����ϴ°� �մ��ϴ�. // list�� free-store���� ù��° ��ü�� ��ġ�� ����.
	//// ocp -> open close principle (���� ��� ��Ģ) -> ��ü���� ���� ��Ģ erase���� remove����̵Ǵ°�

	//for (const STRING& s : v) {
	//	std::cout << s << std::endl;
	//}

	std::list<STRING>	l{ "1", "22", "333", "4444", "55555" };
	l.remove("333");
	
	for (const STRING& s : l) {
		std::cout << s << std::endl;
	}

	// �����ð� vector/deque/list ��

};

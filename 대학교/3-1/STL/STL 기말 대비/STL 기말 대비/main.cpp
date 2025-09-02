//�⸻����01��
//------------ �� �� ------------
// namespace std�� ����Ͽ���.
// include ������ ������ ���� �ʿ����.
// ������� �ʴ� �ڵ带 ������ �����Ѵ�
// ���� �´��� ȿ�� ���� �ڵ峪 �˰����� ������� ���� �ڵ�� �����Ѵ�.
// ���α׷� ȯ�� - Release/x64, ������Ʈ �Ӽ� - �̸� ���� - �ֽ� C++ �ʾ��� ���(/std:c++latest)

// e-class���� ����.zip�� �ٿ� ���� �� �����Ѵ�.
// �� ������ �ذ��ϴµ� �ʿ��� �ڵ�( ����Լ� ���� )�� ������ ���´�.
// ȭ�� ����� ������� ������ ��µ� ������ ������ ���´�.

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
    ifstream in{ "�⸻�ܾ�.txt" };
    if (not in)
        return 0;

    vector<string> v;

    // [���� 1] ���� "�⸻�ܾ�.txt"�� �ִ� ��� �ܾ �о� �����̳� v�� �����϶�.
    // ��� �� ���� �ܾ �о����� ȭ�鿡 ����ϰ� ��°���� �������� �����.   (�ڵ�:15, ���:5)                             
    // (����) ������ �ؽ�Ʈ ���� ��ϵǾ����� �ؽ�Ʈ ������� ���� �� �ִ�.
    // (����) v�� �̹� �����Ǿ��ִ�.

    v = { istream_iterator<string>{in}, {} };
    cout << "�ܾ� ����: " << v.size() << endl;

    // [���� 2] v�� ����� �ܾ��� ��� ���̸� �Ҽ��� ��°�ڸ����� ����ϰ� �������� �����. (�ڵ�:15, ��°�:5)
    // (����) {:2.2f}
    double avg_len = accumulate(v.begin(), v.end(), 0.0,
        [](double sum, const string& s) { return sum + s.size(); }) / v.size();
    cout << format("��� ����: {:2.2f}", avg_len) << endl;

    // [���� 3]  v�� ����� �ܾ� �߿��� "stl"�̶�� ���ӵ� ���ڰ� �� �ܾ ã�ƶ�. 
    // "stl"�� �� �ܾ� ��ο� �ܾ��� ������ ȭ�鿡 ����ϰ� ������ ��µ� ������ �����.   (�ڵ�:20, ����:5)
    // (��) jnziastlizef - �� �ܾ�� stl�� ����ִ�.
    vector<string> with_stl;
    copy_if(v.begin(), v.end(), back_inserter(with_stl),
        [](const string& s) { return s.find("stl") != string::npos; });

    for (const string& s : with_stl)
        cout << s << '\n';

    cout << "stl ���� �ܾ� ����: " << with_stl.size() << endl;

    // [���� 4] v�� �������� ���� �� ������ �ܾ� ���� ����ϰ� �������� �����. (�ڵ�:10, �ܾ��:5)
    // (����) ������ ������������ ���ĵǾ� ������ �ߺ��� �ܾ ����.
    ranges::sort(v);
    v.erase(unique(v.begin(), v.end()), v.end());

    cout << "������ �ܾ� ��: " << v.size() << endl;


    // ���� �ڵ�� "�ܾ��.txt"�� �о� words�� �����Ѵ�.
    // (����) words�� �������� ���ĵǾ� ������ �ߺ��� �ܾ ����.

    ifstream in2{ "�ܾ��.txt" };
    if (not in2)
        return 0;

    vector<string> words{ istream_iterator<string>{in2}, {} };
    cout << "�ܾ��.txt - " << words.size() << endl;

    // (���) �ܾ��.txt - 369882



    // [���� 5] v�� �ִ� �ܾ� �߿��� "�ܾ��.txt"�� �ִ� �ܾ ã�� v2�� �����϶�.              
    // v2�� ��� �� �ܾ �ִ��� ����ϰ� �������� ���.                      (�ڵ�:15, ����:5)
    // (����) ���� �ܾ�� set_intersection���� ã�� �� �ִ�.
    vector<string> v2;
    ranges::sort(v);
    set_intersection(v.begin(), v.end(),
        words.begin(), words.end(),
        back_inserter(v2));

    cout << "���� �ܾ� ����: " << v2.size() << endl;


    // [���� 6] ������ ���� ǥ�� �˰����Լ� copy�� ȣ���ϸ� v�� ��� �ܾ �������� �ٲ��.
    // �ʿ��� �ڵ��� �߰��϶�.                                                (�����ڵ�:40)
    // (��) ������ v�� �ܾ� 4���� �������� �ٲ� ���̴� 
    // v�� ó�� 4 �ܾ�  - a aaat aacdkuopsavjiornyb aadksxwzjdfkovafbdyckguegepyx
    // �������� �ٲ� �� - a taaa bynroijvaspoukdcaa xypegeugkcydbfavokfdjzwxskdaa

    // ���� �ּ����� �����ϰ� ������ ��
    {
        const size_t n = v.size();

        // ���� ������ ����
        vector<string> temp = v;
        reverse(temp.begin(), temp.end());

        // v ũ�⸦ 2��� �÷��� REVERSE(v.begin())�� �����ϰ� �۵��ϵ��� ����
        v.resize(n * 2);

        // ���ʿ� temp ���� (n ~ 2n ��ġ�� ���� ������)
        copy(temp.begin(), temp.end(), v.begin() + n);

        // ���� �� ������ �����ϰ� ������ �������� ���
        std::copy(v.begin() + n, v.end(), REVERSE(v.begin()));
    }

    for (int i = 0; i < 4; ++i)
        cout << v[i] << endl;

}


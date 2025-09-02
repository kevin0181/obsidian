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
    // "����.txt" ���Ͽ��� ���ĺ��� ���� ���ڰ� ��ϵǾ� �ִ�.

    ifstream in{ "����.txt" };

    vector<char> v;

    // [���� 1] "����.txt"�� ����� ���ڸ� ������ �����ϰ� ��� �о� ���� v�� �����϶�.   
    // v�� ����� ������ ���� ȭ�鿡 ����ϰ� �������� �����.            			(�ڵ�:15, ��°�:5)
    // (����) v�� �̹� �����Ǿ��ִ�.
    copy_if(istream_iterator<char>{in}, {}, back_inserter(v),
        [](char c) { return c != ' '; });

    cout << "v�� size: " << v.size() << endl;


    // [���� 2] v�� ����Ǿ� �ִ� ���ڵ鿡�� ���� 's' 't' 'l' �� ���ӵ� ����  
    // ��� �� ���ΰ� ����ϰ� �������� �����.                           			(�ڵ�:25, ��°�:5)
    // (��) mnqsorhzhybjgbkstlksuuqunebcpoannstljkvdndcyfipievtfwsak
    // �� ���ڵ鿡�� 's' 't' 'l' �� ���ӵ� ���� �� ���̴�.

    int count{};
    for (size_t i = 0; i + 2 < v.size(); ++i)
        if (v[i] == 's' && v[i + 1] == 't' && v[i + 2] == 'l')
            ++count;

    cout << "'stl' ���� Ƚ��: " << count << endl;





    // [���� 3] v�� ����� ���ڸ� �빮�ڿ� �ҹ��ڷ� �и��϶�.                (�ڵ�:25, ��°�:5)
    // �빮�ڴ� v1�� �����ϰ� �ҹ��ڴ� v2�� �����϶�.
    // v1�� v2�� size�� ȭ�鿡 ����ϰ� �������� ���.

    vector<char> v1, v2;
    partition_copy(v.begin(), v.end(), back_inserter(v1), back_inserter(v2),
        [](char c) { return isupper(c); });

    cout << "�빮�� ����: " << v1.size() << ", �ҹ��� ����: " << v2.size() << endl;


    // [���� 4] ������������ ���ĵ� ���� v2���� �� ���ĺ��� ������ �����̳� alpha�� �����϶�. 		
    // a[0]���� 'a', a[1]���� 'b' ... , a[25]���� 'z'�� ������ ����ǵ��� �϶�.
    // �� ���ĺ��� ������ ȭ�鿡 ����ϰ� 'c'�� ������ ��������� �����.  			(�ڵ�:25, c�� ����:5)
    // (����) O(n) �˰����� ����ϸ� ��������. ���ĵǾ� �ִٴ� ���� Ȱ���� ��. 

    ranges::sort(v2); // ���� ���ÿ� ���� ������ �ݵ�� �ʿ�

    array<int, 26> alpha{};
    auto it = v2.begin();

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        it = upper_bound(it, v2.end(), ch);
        alpha[ch - 'a'] = distance(v2.begin(), it) - accumulate(alpha.begin(), alpha.begin() + (ch - 'a'), 0);
    }

    for (int i = 0; i < 26; ++i)
        cout << static_cast<char>('a' + i) << ": " << alpha[i] << '\n';

    cout << "'c'�� ����: " << alpha['c' - 'a'] << endl;


    // [����] �����̳��� ���Ҹ� ����� ����
    string s{ "C++20 STL" };
    for_each(s.begin(), s.end(), print<char>);
    cout << endl;                                           // ��� ���  C - + - + - 2 - 0 -   - S - T - L -


    // [���� 5] ���� ������ �����ϸ� ȭ�鿡 [1, 11)���� ���ڰ� ��µǵ��� �ʿ��� �ڵ��� �϶�.	(�����ڵ�:40)

    // �ּ��� �����ϰ� ����ǵ��� ����
    //for_each( NUM( 1 ), NUM( 11 ), print<int> );        // ��� ���   1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10 -
    //cout << endl << endl;

}
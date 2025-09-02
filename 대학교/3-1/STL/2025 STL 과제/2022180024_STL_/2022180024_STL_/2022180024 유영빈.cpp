#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <numeric>   // std::accumulate
#include <iomanip>  // setprecision
#include <unordered_map>
#include <algorithm> // std::sort
#include <ranges> // views
#include <print>

class Player {
private:
    std::string name; // �̸�, ����[3, 15], ['a', 'z']�θ� ����
    int score; // ����
    size_t id; // ���̵�, ��ġ�� ���̵� ���� �� ����
    size_t num; // free store�� Ȯ���� ����Ʈ ��
    std::unique_ptr<char[]> p; // free store�� Ȯ���� �޸�

public:

    Player(){}
    ~Player(){}

    // ���� ������
    Player(const Player& other)
        : name(other.name), score(other.score), id(other.id), num(other.num)
    {
        p = std::make_unique<char[]>(other.num);
        std::copy(other.p.get(), other.p.get() + num, p.get());
    }

    // ���� ���� ������
    Player& operator=(const Player& other)
    {
        if (this != &other)
        {
            name = other.name;
            score = other.score;
            id = other.id;
            num = other.num;
            p = std::make_unique<char[]>(other.num);
            std::copy(other.p.get(), other.p.get() + num, p.get());
        }
        return *this;
    }

    bool operator<(const Player& rhs) const {
        return score < rhs.score;
    }

    void read(std::istream& is) {
        is.read((char*)this, sizeof(Player));
        p.release();
        p = std::make_unique<char[]>(num);
        is.read(p.get(), num);
    }

    void print() const {
        std::cout << "�̸�:" << name
            << ", ���̵�:" << id
            << " , ����:" << score
            << ", �ڿ���:" << num << std::endl;
        std::cout << "����� ����: ";
        for (size_t i = 0; i < num; ++i)
            std::cout << p[i];
        std::cout << std::endl;
    }

    int getScore() const {
        return score;
    }

    size_t getId() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    char* getP() const {
        return p.get();
    }

    size_t getNum() const {
        return num;
    }

};

std::array<Player, 2'500'000> players;

std::array<Player, 2'500'000> playersId;
std::array<Player, 2'500'000> playersName;
std::array<Player, 2'500'000> playersScore;

void savePlayersWithSameId() {
    std::unordered_map<size_t, size_t> id_count;

    // 1. �� ID�� �� �� �����ϴ��� ����
    for (const Player& player : players) {
        ++id_count[player.getId()];
    }

    // 2. �ٽ� ��ü�� ���鼭 �ߺ��� ID�� ���Ͽ� ���
    std::ofstream out("�������̵�.txt");
    size_t duplicate_total_count = 0;

    for (const Player& player : players) {
        if (id_count[player.getId()] > 1) {
            ++duplicate_total_count;
            out << player.getName() << " " << player.getId() << "\n";
        }
    }

    std::cout << std::endl << "�ߺ��� ���̵� ���� Player ��: " << duplicate_total_count << "��" << std::endl;
}

void countPlayersWithManyA() {
    size_t count = 0;

    for (Player& player : players) {
        // 1. ���ڿ� ����
        std::sort(player.getP(), player.getP() + player.getNum());

        // 2. 'a' ���� ���� ����
        size_t a_count = 0;
        for (size_t i = 0; i < player.getNum(); ++i) {
            if (player.getP()[i] == 'a') {
                ++a_count;
            }
        }

        // 3. 10�� �̻��� ��츸 ī��Ʈ
        if (a_count >= 10) {
            ++count;
        }
    }

    std::cout << std::endl << "'a' ���ڰ� 10�� �̻��� Player ��: " << count << "��" << std::endl;
}

long long findAvgScorePlayer(long long sum, const Player& player) {
    return sum + player.getScore();
}

int main() {

    std::ifstream in{ "2025 STL ���� ���� - 2022180024", std::ios::binary };

    if (not in) {
        std::cerr << "������ �� �� �����ϴ�.\n";
        return 1;
    }

    for (Player& player : players) {
        player.read(in);
    }

    std::cout << std::endl << "[������ Player ����]" << std::endl;
    players.back().print();

    // 2.  ������ ���� ū Player�� ã�� ���
    const Player& max_player = *std::max_element(players.begin(), players.end());

    std::cout << std::endl << "[�ְ� ���� Player]" << std::endl;
    max_player.print();

    // 2. ��� ���� ���
    long long total_score = std::accumulate(players.begin(), players.end(), 0LL, findAvgScorePlayer);

    double avg_score = static_cast<double>(total_score) / players.size();

    std::cout << std::endl << "��ü �÷��̾� ��� ����: " << std::fixed << std::setprecision(5) << avg_score << std::endl;

    // 3. �������̵�.txt
    try {
        savePlayersWithSameId();
    }
    catch (const std::exception& e) {
        std::cout << "3. ���� ���̵�.txt ����" << std::endl;
    }

    // 4. 
    countPlayersWithManyA();

    // �������� üũ
    /*for (const Player& player : players | std::views::take(3)) {
        std::print("[{}] ���ĵ� p: {}\n", player.getName(), std::string_view{ player.getP(), player.getNum() });
    }*/

    // 5. loop

    std::copy(players.begin(), players.end(), playersId.begin()); // ���������, ���Կ����� �ʿ�
    std::copy(players.begin(), players.end(), playersName.begin());
    std::copy(players.begin(), players.end(), playersScore.begin());

    // �̸� ����
    std::sort(playersId.begin(), playersId.end(), [](const Player& a, const Player& b) {
        return a.getId() < b.getId();
        });

    std::sort(playersName.begin(), playersName.end(), [](const Player& a, const Player& b) {
        return a.getName() < b.getName();
        });

    std::sort(playersScore.begin(), playersScore.end(), [](const Player& a, const Player& b) {
        return a.getScore() < b.getScore();
        });


    while (true) {
        std::cout << std::endl;
        std::cout << "�˻��� ID�� �Է��ϼ��� : ";
        size_t input_id;
        std::cin >> input_id;


        auto target_Id = std::ranges::find_if(playersId, [input_id](const Player& p) {
            return p.getId() == input_id;
            });

        
        if (target_Id == playersId.end()) {
            std::cout << "�ش� ID�� ���� �÷��̾ �������� �ʽ��ϴ�.\n";
            continue;
        }

        // 1. ID ����
        std::cout << std::endl << std::endl << "------------------------- Player ID ���� ���� ���� �˻� --------------------------" << std::endl;

		size_t count = 1;
        while (target_Id != playersId.end() && target_Id->getId() == input_id) {

            // [��]
            std::print("\n                    {}. [�ش� ID �� Player]                    \n", count);
            if (target_Id != playersId.begin())
                (target_Id - 1)->print();

			// [�ش� ID]
            std::print("\n                    {}. [�ش�(����) ID�� ���� Player]                    \n", count);
            target_Id->print();

            // [��]
            std::print("\n                    {}. [�ش� ID �� Player]                    \n", count);

            ++target_Id;
            if (target_Id != playersId.end())
                target_Id->print();

            ++count;

            std::cout << std::endl << "----------------------------------------------------------------------------------" << std::endl;

        }

        // 2. Name ���� 53466
        std::cout << std::endl << std::endl << "------------------------- Player Name ���� ���� ���� �˻� --------------------------" << std::endl;

        auto target_Name = std::ranges::find_if(playersName, [input_id](const Player& p) {
            return p.getId() == input_id;
            });

        std::string input_name = target_Name->getName();

        // [��]
		std::cout << "\n                    [�ش� Name �� Player]                    \n" << std::endl;
        if (target_Name != playersName.begin())
            (target_Name - 1)->print();

        std::cout << "\n                    [�ش�(����) Name�� ���� Player��]                   \n" << std::endl;
        count = 1;
        while (target_Name != playersName.end() && target_Name->getName() == input_name) {
            // [�ش� Name]
            std::cout << count << "�� player - ";
            target_Name->print();
            std::cout << std::endl;
            ++target_Name; 
            ++count;
        }

        // [��]
        std::cout << "\n                    [�ش� Name �� Player]                   \n" << std::endl;
        ++target_Name;
        if (target_Name != playersName.end())
            target_Name->print();

        std::cout << std::endl << "----------------------------------------------------------------------------------" << std::endl;

        // 3. Score ���� 53466
        std::cout << std::endl << std::endl << "------------------------- Player Score ���� ���� ���� �˻� --------------------------" << std::endl;

        auto target_Score = std::ranges::find_if(playersScore, [input_id](const Player& p) {
            return p.getId() == input_id;
            });

        int input_Score = target_Score->getScore();

        // [��]
        std::cout << "\n                    [�ش� Score �� Player]                    \n" << std::endl;
        if (target_Score != playersScore.begin())
            (target_Score - 1)->print();

        std::cout << "\n                    [�ش�(����) Score�� ���� Player��]                   \n" << std::endl;
        count = 1;
        while (target_Score != playersScore.end() && target_Score->getScore() == input_Score) {
            // [�ش� Score]
            std::cout << count << "�� player - ";
            target_Score->print();
            std::cout << std::endl;
            ++target_Score;
            ++count;
        }

        // [��]
        std::cout << "\n                    [�ش� Score �� Player]                   \n" << std::endl;
        ++target_Score;
        if (target_Score != playersScore.end())
            target_Score->print();

        std::cout << std::endl << "----------------------------------------------------------------------------------" << std::endl;

    }
}
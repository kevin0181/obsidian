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
    std::string name; // 이름, 길이[3, 15], ['a', 'z']로만 구성
    int score; // 점수
    size_t id; // 아이디, 겹치는 아이디 있을 수 있음
    size_t num; // free store에 확보한 바이트 수
    std::unique_ptr<char[]> p; // free store에 확보한 메모리

public:

    Player(){}
    ~Player(){}

    // 복사 생성자
    Player(const Player& other)
        : name(other.name), score(other.score), id(other.id), num(other.num)
    {
        p = std::make_unique<char[]>(other.num);
        std::copy(other.p.get(), other.p.get() + num, p.get());
    }

    // 복사 대입 연산자
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
        std::cout << "이름:" << name
            << ", 아이디:" << id
            << " , 점수:" << score
            << ", 자원수:" << num << std::endl;
        std::cout << "저장된 글자: ";
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

    // 1. 각 ID가 몇 번 등장하는지 세기
    for (const Player& player : players) {
        ++id_count[player.getId()];
    }

    // 2. 다시 전체를 돌면서 중복된 ID만 파일에 출력
    std::ofstream out("같은아이디.txt");
    size_t duplicate_total_count = 0;

    for (const Player& player : players) {
        if (id_count[player.getId()] > 1) {
            ++duplicate_total_count;
            out << player.getName() << " " << player.getId() << "\n";
        }
    }

    std::cout << std::endl << "중복된 아이디를 가진 Player 수: " << duplicate_total_count << "명" << std::endl;
}

void countPlayersWithManyA() {
    size_t count = 0;

    for (Player& player : players) {
        // 1. 문자열 정렬
        std::sort(player.getP(), player.getP() + player.getNum());

        // 2. 'a' 글자 개수 세기
        size_t a_count = 0;
        for (size_t i = 0; i < player.getNum(); ++i) {
            if (player.getP()[i] == 'a') {
                ++a_count;
            }
        }

        // 3. 10개 이상인 경우만 카운트
        if (a_count >= 10) {
            ++count;
        }
    }

    std::cout << std::endl << "'a' 글자가 10개 이상인 Player 수: " << count << "명" << std::endl;
}

long long findAvgScorePlayer(long long sum, const Player& player) {
    return sum + player.getScore();
}

int main() {

    std::ifstream in{ "2025 STL 과제 파일 - 2022180024", std::ios::binary };

    if (not in) {
        std::cerr << "파일을 열 수 없습니다.\n";
        return 1;
    }

    for (Player& player : players) {
        player.read(in);
    }

    std::cout << std::endl << "[마지막 Player 정보]" << std::endl;
    players.back().print();

    // 2.  점수가 가장 큰 Player를 찾아 출력
    const Player& max_player = *std::max_element(players.begin(), players.end());

    std::cout << std::endl << "[최고 점수 Player]" << std::endl;
    max_player.print();

    // 2. 평균 점수 계산
    long long total_score = std::accumulate(players.begin(), players.end(), 0LL, findAvgScorePlayer);

    double avg_score = static_cast<double>(total_score) / players.size();

    std::cout << std::endl << "전체 플레이어 평균 점수: " << std::fixed << std::setprecision(5) << avg_score << std::endl;

    // 3. 같은아이디.txt
    try {
        savePlayersWithSameId();
    }
    catch (const std::exception& e) {
        std::cout << "3. 같은 아이디.txt 오류" << std::endl;
    }

    // 4. 
    countPlayersWithManyA();

    // 오름차순 체크
    /*for (const Player& player : players | std::views::take(3)) {
        std::print("[{}] 정렬된 p: {}\n", player.getName(), std::string_view{ player.getP(), player.getNum() });
    }*/

    // 5. loop

    std::copy(players.begin(), players.end(), playersId.begin()); // 복사생성자, 대입연산자 필요
    std::copy(players.begin(), players.end(), playersName.begin());
    std::copy(players.begin(), players.end(), playersScore.begin());

    // 미리 정렬
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
        std::cout << "검색할 ID를 입력하세요 : ";
        size_t input_id;
        std::cin >> input_id;


        auto target_Id = std::ranges::find_if(playersId, [input_id](const Player& p) {
            return p.getId() == input_id;
            });

        
        if (target_Id == playersId.end()) {
            std::cout << "해당 ID를 가진 플레이어가 존재하지 않습니다.\n";
            continue;
        }

        // 1. ID 기준
        std::cout << std::endl << std::endl << "------------------------- Player ID 기준 오름 차순 검색 --------------------------" << std::endl;

		size_t count = 1;
        while (target_Id != playersId.end() && target_Id->getId() == input_id) {

            // [앞]
            std::print("\n                    {}. [해당 ID 앞 Player]                    \n", count);
            if (target_Id != playersId.begin())
                (target_Id - 1)->print();

			// [해당 ID]
            std::print("\n                    {}. [해당(같은) ID를 가진 Player]                    \n", count);
            target_Id->print();

            // [뒤]
            std::print("\n                    {}. [해당 ID 뒤 Player]                    \n", count);

            ++target_Id;
            if (target_Id != playersId.end())
                target_Id->print();

            ++count;

            std::cout << std::endl << "----------------------------------------------------------------------------------" << std::endl;

        }

        // 2. Name 기준 53466
        std::cout << std::endl << std::endl << "------------------------- Player Name 기준 오름 차순 검색 --------------------------" << std::endl;

        auto target_Name = std::ranges::find_if(playersName, [input_id](const Player& p) {
            return p.getId() == input_id;
            });

        std::string input_name = target_Name->getName();

        // [앞]
		std::cout << "\n                    [해당 Name 앞 Player]                    \n" << std::endl;
        if (target_Name != playersName.begin())
            (target_Name - 1)->print();

        std::cout << "\n                    [해당(같은) Name를 가진 Player들]                   \n" << std::endl;
        count = 1;
        while (target_Name != playersName.end() && target_Name->getName() == input_name) {
            // [해당 Name]
            std::cout << count << "번 player - ";
            target_Name->print();
            std::cout << std::endl;
            ++target_Name; 
            ++count;
        }

        // [뒤]
        std::cout << "\n                    [해당 Name 뒤 Player]                   \n" << std::endl;
        ++target_Name;
        if (target_Name != playersName.end())
            target_Name->print();

        std::cout << std::endl << "----------------------------------------------------------------------------------" << std::endl;

        // 3. Score 기준 53466
        std::cout << std::endl << std::endl << "------------------------- Player Score 기준 오름 차순 검색 --------------------------" << std::endl;

        auto target_Score = std::ranges::find_if(playersScore, [input_id](const Player& p) {
            return p.getId() == input_id;
            });

        int input_Score = target_Score->getScore();

        // [앞]
        std::cout << "\n                    [해당 Score 앞 Player]                    \n" << std::endl;
        if (target_Score != playersScore.begin())
            (target_Score - 1)->print();

        std::cout << "\n                    [해당(같은) Score를 가진 Player들]                   \n" << std::endl;
        count = 1;
        while (target_Score != playersScore.end() && target_Score->getScore() == input_Score) {
            // [해당 Score]
            std::cout << count << "번 player - ";
            target_Score->print();
            std::cout << std::endl;
            ++target_Score;
            ++count;
        }

        // [뒤]
        std::cout << "\n                    [해당 Score 뒤 Player]                   \n" << std::endl;
        ++target_Score;
        if (target_Score != playersScore.end())
            target_Score->print();

        std::cout << std::endl << "----------------------------------------------------------------------------------" << std::endl;

    }
}
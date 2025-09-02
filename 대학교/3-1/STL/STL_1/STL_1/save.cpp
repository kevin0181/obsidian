#include "save.h"

void save(std::string_view fileName) {
    // 파일 fileName을 연다.
    std::ifstream in{ fileName.data() };
    if (not in) { // -> ! 말고 not 쓰기;;ㅋㅋㅋ
        std::cout << fileName << "을 열 수 없습니다." << std::endl;
        exit(0);
    }

    // 저장했음을 화면에 출력하자.
    std::cout << fileName << " - " << std::filesystem::file_size(fileName)
        << "byte를 저장 하였습니다." << std::endl;

    // 저장할 파일도 연다.
    std::ofstream out{ "2025 1학기 STL 화78목23 강의 저장.txt", std::ios::app };

    // 저장한 시간을 파일에 기록하자.
     // 현재 UTC 시간 가져오기
    auto now = std::chrono::system_clock::now();
    std::time_t utc = std::chrono::system_clock::to_time_t(now);

    // 스레드 안전한 지역 시간 변환
    std::tm localTime;
    localtime_s(&localTime, &utc); // Windows 환경 (POSIX는 localtime_r 사용)

    std::locale oldLocale = std::cout.getloc();

    // 출력 스트림의 로캘을 한국어로 설정
    std::locale loc("ko_KR.utf8"); // 시스템에서 지원되는지 확인 필요
    std::cout.imbue(loc);

    out << '\n\n';
    out << "========================================" << '\n';
    out << "저장 시간 : " << std::put_time(&localTime, "%c %A") << '\n';
    out << "========================================" << '\n';
    out << '\n';

    out.imbue(oldLocale); // out 지역을 원래대로 돌려놓는다.

    // 읽을 파일의 내용을 읽어서 저장할 파일에 덧붙인다.
    std::copy(std::istreambuf_iterator{ in }, {}, std::ostreambuf_iterator{ out });   // 파일을 메모리로
}



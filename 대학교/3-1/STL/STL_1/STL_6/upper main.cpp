//-------------------------------------------------
// 2025. STL 3.24                           4W 1D
//-------------------------------------------------
// 
//-------------------------------------------------
// 동적 할당과 스마트 포인터 - RAII
// 자원의 생명주기를 객체의 생명주기와 일치시키는 프로그래밍 기법
//-------------------------------------------------
// 다음시간 - CALLABLE 
//


#INCLUDE <IOSTREAM>
#INCLUDE <STRING>
#INCLUDE <FSTREAM>
#INCLUDE <ARRAY>
#INCLUDE <VECTOR>
#INCLUDE <ALGORITHM>
#INCLUDE <NUMERIC>

#INCLUDE <MEMORY>


//INT MAIN() {
//	// [문제] 양의 정수 NUM(INT의 MAX값까진 받자)을 입력받아라.
//	// NUM개 만큼 INT를 저장할 메모리를 확보하라.
//	// 메모리의 내용을 1부터 시작하는 정수로 채워라.
//	// 메모리에 저장한 INT의 합계를 출력하라.
//	// 이 과정을 영원히 반복하라.
//
//
//	WHILE (TRUE) {
//		/*STD::COUT << "값을 입력하세요 : ";
//		INT NUM;
//		STD::CIN >> NUM;
//
//		STD::VECTOR<INT> ARRAY;
//		ARRAY.RESERVE(NUM);
//
//		FOR (INT I = 0; I < NUM; ++I) {
//			ARRAY.PUSH_BACK(I + 1);
//		}
//
//		INT RESULT = 0;
//
//		FOR (INT I = 0; I < ARRAY.SIZE(); ++I) {
//			RESULT += ARRAY[I];
//		}
//
//		STD::COUT << "1부터 " << NUM << " 까지 합계입니다 - "<< RESULT << STD::ENDL;*/
//
//		// 교수님 코드 -----------------------------------------------------------------
//
//		STD::COUT << "값을 입력하세요 : ";
//		INT NUM;
//		STD::CIN >> NUM;
//		INT* P;
//		TRY {
//			P = NEW INT[NUM]; // FREE-STORE, HEAP(C++에선 HEAP이라고 부르지 않는다 강조하심;) // 내 의지와 상관없이 시스템이 할당하는거라 오류가 발생할 수 있음
//		}
//		CATCH (CONST STD::EXCEPTION& E) {
//			STD::COUT << E.WHAT() << STD::ENDL;
//			RETURN 0;
//		}
//
//		STD::IOTA(P, P + NUM, 1);			// IOTA = <NUMERIC>
//
//		//LONG LONG INT SUM{}; // INT 만 쓰면 10만쓰면 오버플로우 나오니깐 LONG타입
//		// LONG DOUBLE -> 젤큼 (자리수를 양보?하면서 크기를 키움)
//
//		LONG LONG SUM = STD::ACCUMULATE(P, P + NUM, 0LL); // 마지막 인자가 0이기 때문에 INT라고 인식하기 때문에 LL타입을 붙여줘야함 (LL 빼면 오류남)
//
//		STD::COUT << "1부터 " << NUM << " 까지 합계입니다 - " << SUM << STD::ENDL;
//
//		DELETE[] P; // 해제 하는거 까먹지말기.
//
//		// DELETE[] P; 이렇게 두번 해제하는거 댕글링포인터 (바로죽음)
//		
//	}
//
//}


//---------------------------------------------------------------------------------------------------

//CLASS DOG {
//PUBLIC:
//	DOG() {
//		STD::COUT << "멍~멍~" << STD::ENDL;
//	}
//	~DOG() {
//		STD::COUT << "꿱" << STD::ENDL;
//	}
//};
//
//CLASS 스마트 {
//	DOG* P;
//PUBLIC:
//	스마트(DOG* P) : P{ P } {} // RAII 클래스의 생명주기를 내부 객체의 생명주기와 일치하도록 하는것(핸들러가 사용하는동안 자원이 잇다가 핸들러 사라지면 자원도 없어지는것)
//
//	~스마트() {
//		STD::COUT << "예외가 발생하더라도 지역객체는 반드시 소멸됨을 보장함 (STACK UNWINDING)" << STD::ENDL;
//		DELETE P;
//	}
//};
//
//VOID F() {
//	//INT* P;
//	//P = NEW INT[10];// {}붙이면 싹다 0으로 초기화
//
//	///*STD::COUT << "번지 - " << P << " - ";
//	//FOR (INT I = 0; I < 10; ++I) {
//	//	STD::COUT << P[I] << " ";
//	//}
//	//STD::COUT << STD::ENDL;*/
//
//	//THROW 123123; // 이렇게 예외가 발생하면 C++은 스택에 만들어진 객체 P를 없애버림. (만약에 P가 클래스면 소멸자 호출해서 할당한걸 해제함)
//	//// 예외 발생 시, 해당 함수의 스택을 정리하는걸 = 스택 언와인딩 이라고 부름
//
//	//STD::COUT << "이 문장이 출력될 일은 전혀 없다." << STD::ENDL;
//
//	//DELETE[] P;
//
//	//----
//
//	스마트 P{ NEW DOG }; // 이게 초기화임 // RAII
//
//	/*스마트 P;
//	P = { NEW DOG };*/ // 이렇게 하지마라 위에처럼 해야됨. 할당연산자임 이건
//	STD::UNIQUE_PTR<DOG> P2 = STD::MAKE_UNIQUE<DOG>(); // 표준 스마트 포인터 // MAKE_UNIQUE = 동적할당 ( NEW DOG ) 대신씀
//	STD::UNIQUE_PTR<DOG[]> P3 = STD::MAKE_UNIQUE<DOG[]>(100);  // 배열 필요할때.
//
//
//	THROW 123123;
//	STD::COUT << "이 문장이 출력될 일은 전혀 없다." << STD::ENDL;
//
//}
//
//INT MAIN() {
//
//	TRY {
//		F(); // 함수 호출하면 F만의 스택이 생성됨. 함수가 정상 종료되면 스택안에 있던 지역 변수들은 스택에서 만들어진 것들이 없어짐.
//	}
//	CATCH (...) {
//
//	}
//
//	STD::COUT << "메인은 잘 끝날까?" << STD::ENDL;
//}

//---------------------------------------------------------------------------------------------------------------------------
//
// [문제] "메인.CPP"에 있는 소문자를 모두 대문자로 바꿔 "메인 대문자.CPP"에 저장하라.
//

INT MAIN() {
	/*STD::IFSTREAM IN{ "MAIN.CPP" };

	STD::VECTOR<CHAR> C;
	CHAR C1;
	WHILE (IN >> C1) {
		C.PUSH_BACK(C1);
	}

	FOR (CHAR& C2 : C) {
		C2 = TOUPPER(C2);
	}

	STD::OFSTREAM OUT{ "UPPER MAIN.CPP" };

	OUT.WRITE(C.DATA(), C.SIZE() * SIZEOF(CHAR));*/

	// ----------------------교수님 코드 ----------------------------------

	STD::IFSTREAM IN{ "MAIN.CPP" };
	IF (NOT IN)
		RETURN 0;

	STD::OFSTREAM OUT{ "UPPER MAIN.CPP" };
	
	//CHAR C;
	//IN >> STD::NOSKIPWS; //빈공간도 처리해줘
	//WHILE (IN >> C) {
	//	C = TOUPPER(C);
	//	OUT << C;
	//}

	STD::TRANSFORM(STD::ISTREAMBUF_ITERATOR<CHAR>{IN}, {}, STD::OSTREAMBUF_ITERATOR<CHAR>{OUT}, [](CHAR C) {
		RETURN TOUPPER(C);
		});

}
//-------------------------------------------------
// 2025. STL 3.24                           4W 1D
//-------------------------------------------------
// 
//-------------------------------------------------
// ���� �Ҵ�� ����Ʈ ������ - RAII
// �ڿ��� �����ֱ⸦ ��ü�� �����ֱ�� ��ġ��Ű�� ���α׷��� ���
//-------------------------------------------------
// �����ð� - CALLABLE 
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
//	// [����] ���� ���� NUM(INT�� MAX������ ����)�� �Է¹޾ƶ�.
//	// NUM�� ��ŭ INT�� ������ �޸𸮸� Ȯ���϶�.
//	// �޸��� ������ 1���� �����ϴ� ������ ä����.
//	// �޸𸮿� ������ INT�� �հ踦 ����϶�.
//	// �� ������ ������ �ݺ��϶�.
//
//
//	WHILE (TRUE) {
//		/*STD::COUT << "���� �Է��ϼ��� : ";
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
//		STD::COUT << "1���� " << NUM << " ���� �հ��Դϴ� - "<< RESULT << STD::ENDL;*/
//
//		// ������ �ڵ� -----------------------------------------------------------------
//
//		STD::COUT << "���� �Է��ϼ��� : ";
//		INT NUM;
//		STD::CIN >> NUM;
//		INT* P;
//		TRY {
//			P = NEW INT[NUM]; // FREE-STORE, HEAP(C++���� HEAP�̶�� �θ��� �ʴ´� �����Ͻ�;) // �� ������ ������� �ý����� �Ҵ��ϴ°Ŷ� ������ �߻��� �� ����
//		}
//		CATCH (CONST STD::EXCEPTION& E) {
//			STD::COUT << E.WHAT() << STD::ENDL;
//			RETURN 0;
//		}
//
//		STD::IOTA(P, P + NUM, 1);			// IOTA = <NUMERIC>
//
//		//LONG LONG INT SUM{}; // INT �� ���� 10������ �����÷ο� �����ϱ� LONGŸ��
//		// LONG DOUBLE -> ��ŭ (�ڸ����� �纸?�ϸ鼭 ũ�⸦ Ű��)
//
//		LONG LONG SUM = STD::ACCUMULATE(P, P + NUM, 0LL); // ������ ���ڰ� 0�̱� ������ INT��� �ν��ϱ� ������ LLŸ���� �ٿ������ (LL ���� ������)
//
//		STD::COUT << "1���� " << NUM << " ���� �հ��Դϴ� - " << SUM << STD::ENDL;
//
//		DELETE[] P; // ���� �ϴ°� ���������.
//
//		// DELETE[] P; �̷��� �ι� �����ϴ°� ��۸������� (�ٷ�����)
//		
//	}
//
//}


//---------------------------------------------------------------------------------------------------

//CLASS DOG {
//PUBLIC:
//	DOG() {
//		STD::COUT << "��~��~" << STD::ENDL;
//	}
//	~DOG() {
//		STD::COUT << "��" << STD::ENDL;
//	}
//};
//
//CLASS ����Ʈ {
//	DOG* P;
//PUBLIC:
//	����Ʈ(DOG* P) : P{ P } {} // RAII Ŭ������ �����ֱ⸦ ���� ��ü�� �����ֱ�� ��ġ�ϵ��� �ϴ°�(�ڵ鷯�� ����ϴµ��� �ڿ��� �մٰ� �ڵ鷯 ������� �ڿ��� �������°�)
//
//	~����Ʈ() {
//		STD::COUT << "���ܰ� �߻��ϴ��� ������ü�� �ݵ�� �Ҹ���� ������ (STACK UNWINDING)" << STD::ENDL;
//		DELETE P;
//	}
//};
//
//VOID F() {
//	//INT* P;
//	//P = NEW INT[10];// {}���̸� �ϴ� 0���� �ʱ�ȭ
//
//	///*STD::COUT << "���� - " << P << " - ";
//	//FOR (INT I = 0; I < 10; ++I) {
//	//	STD::COUT << P[I] << " ";
//	//}
//	//STD::COUT << STD::ENDL;*/
//
//	//THROW 123123; // �̷��� ���ܰ� �߻��ϸ� C++�� ���ÿ� ������� ��ü P�� ���ֹ���. (���࿡ P�� Ŭ������ �Ҹ��� ȣ���ؼ� �Ҵ��Ѱ� ������)
//	//// ���� �߻� ��, �ش� �Լ��� ������ �����ϴ°� = ���� ����ε� �̶�� �θ�
//
//	//STD::COUT << "�� ������ ��µ� ���� ���� ����." << STD::ENDL;
//
//	//DELETE[] P;
//
//	//----
//
//	����Ʈ P{ NEW DOG }; // �̰� �ʱ�ȭ�� // RAII
//
//	/*����Ʈ P;
//	P = { NEW DOG };*/ // �̷��� �������� ����ó�� �ؾߵ�. �Ҵ翬������ �̰�
//	STD::UNIQUE_PTR<DOG> P2 = STD::MAKE_UNIQUE<DOG>(); // ǥ�� ����Ʈ ������ // MAKE_UNIQUE = �����Ҵ� ( NEW DOG ) ��ž�
//	STD::UNIQUE_PTR<DOG[]> P3 = STD::MAKE_UNIQUE<DOG[]>(100);  // �迭 �ʿ��Ҷ�.
//
//
//	THROW 123123;
//	STD::COUT << "�� ������ ��µ� ���� ���� ����." << STD::ENDL;
//
//}
//
//INT MAIN() {
//
//	TRY {
//		F(); // �Լ� ȣ���ϸ� F���� ������ ������. �Լ��� ���� ����Ǹ� ���þȿ� �ִ� ���� �������� ���ÿ��� ������� �͵��� ������.
//	}
//	CATCH (...) {
//
//	}
//
//	STD::COUT << "������ �� ������?" << STD::ENDL;
//}

//---------------------------------------------------------------------------------------------------------------------------
//
// [����] "����.CPP"�� �ִ� �ҹ��ڸ� ��� �빮�ڷ� �ٲ� "���� �빮��.CPP"�� �����϶�.
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

	// ----------------------������ �ڵ� ----------------------------------

	STD::IFSTREAM IN{ "MAIN.CPP" };
	IF (NOT IN)
		RETURN 0;

	STD::OFSTREAM OUT{ "UPPER MAIN.CPP" };
	
	//CHAR C;
	//IN >> STD::NOSKIPWS; //������� ó������
	//WHILE (IN >> C) {
	//	C = TOUPPER(C);
	//	OUT << C;
	//}

	STD::TRANSFORM(STD::ISTREAMBUF_ITERATOR<CHAR>{IN}, {}, STD::OSTREAMBUF_ITERATOR<CHAR>{OUT}, [](CHAR C) {
		RETURN TOUPPER(C);
		});

}
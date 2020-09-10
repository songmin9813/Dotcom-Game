#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

//밑 함수는 보드판을 만들기 위해 필요한 함수들이다.
int IF_X(int c, int d); //가로 전용 닷컴 검사 함수
int IF_Y(int e, int f); //세로 전용 닷컴 검사 함수
int Make_Board(); //보드판을 만드는 함수
int Check(); //중복을 피하기 위한 검산식 함수
int Check_For_Else(); //중복일 경우 배열을 초기화 시키는 함수

					  //밑 함수는 직접적인 플레이를 하기 위해 필요한 함수들이다.
int Playing(); //사용자에 플레이에 직접적인 영향을 주는 함수
int How_To(); //하는 방법에 대해 자세히 소개되어 있는 함수
int Calibrate(int x, int y); //입력된 좌표를 계산해주는 함수

							 //밑 변수는 전역변수로서 2개 이상의 함수에 사용된다.
int Dot_Origin = 3;// 닷컴의 실제 크기. 여러 함수에 쓰이기 때문에 전역 변수로 선언한다.
int count = 0; //플레이 카운트가 누적되는 변수
int Dog_Count = 0;
int Duck_Count = 0;
int Mouse_Count = 0; //닷컴의 구별을 위해 추가적인 카운트 3개를 생성해야 한다.
int board[7][7]; //닷컴 게임에 사용할 2차원 보드판. 여러 함수에 쓰이기 때문에 전역 변수로 배열을 선언한다.

int main() //메인 함수 시작
{
	int z, g; //보드판 표시를 위한 변수 선언
	int categories;
	while (1) //조건이 충족될때까지 무한 루프
	{
		Make_Board();
		if (Check() == 26) //26이라는 수는 (1로 선언된 3크기의 닷컴)+(2로 선언된 4크기의 닷컴)+(3으로 선언된 5크기의 닷컴)의 합을 말한다.
			break; //조건이 충족될 경우 while문에서 벗어나 본격적인 게임 시작
		else
			Check_For_Else(); //조건이 충족되지 않을 경우에는 배열을 초기화 시키고 다시 무한 루프
	}
	/*보드판의 상태를 확인하기 위한 식
	보드판의 상태를 보고 싶다면 이 주석을 지워주세요.
	for (z = 0; z < 7; z++)
	{
	for (g = 0; g < 7; g++)
	{
	if (board[g][z] == 0)
	printf(" 0");
	else
	printf(" X");
	}
	printf("\n");
	}
	*/
	printf("닷컴 게임을 플레이해주셔서 감사합니다!\n");
	Sleep(1000);
	printf("Dot Com Game / C.Ver\n");
	Sleep(1000);
	printf("원하시는 카테고리의 숫자를 입력하여 주십시오.\n\n\n");
	printf("1. 플레이\n\n");
	printf("2. 플레이 방법\n\n");
	printf("아무 키. 게임 종료\n\n");
	scanf_s("%d", &categories); //사용자에게 카테고리를 묻는다.

	if (categories == 1)
		Playing();
	else if (categories == 2)
		How_To();
	else
		printf("감사합니다. 안녕히 계세요.\n");
	return 0; //사용자가 입력한 각 카테고리에 따른 함수가 실행된다.
}

Make_Board()
{
	int i; //가로, 세로 난수를 위한 변수
	int x, y; //보드의 좌표값 계산을 위한 변수
	int z, g; //임의로 짜여진 보드판을 보기 위한 변수
	int Dot_Com = 3;// 닷컴이 배열안에 들어가도록 설정하는 상수 함수 생성
	int Dot_Size = 5;// 닷컴의 크기를 다로 설정해주는 상수 함수 생성


	srand((unsigned)time(NULL)); //난수 함수 선언
	for (; Dot_Com < 6; Dot_Com++)
	{
		i = rand() % 2;
		if (i == 0) //닷컴이 가로로 생성되게 한다.
		{
			x = rand() % Dot_Size;
			y = rand() % 7;
			if (IF_X(x, y) == 2)
			{
				for (z = 0; z < Dot_Com; z++)
					board[x + z][y] = -2 + Dot_Com;
				Dot_Size--; //완전한 닷컴이 하나 생성될 때마다 닷컴이 보드판에 생성되는 기준을 달리해줘야 한다.
				Dot_Origin++; //if문의 다음 닷컴 조사를 위함
			}
			else
				Dot_Com--; //닷컴이 겹칠 경우에는 한번 더 실행 되도록 한다.
		}
		else if (i == 1) //닷컴이 세로로 생성되게 한다.
		{
			x = rand() % 7;
			y = rand() % Dot_Size;
			if (IF_Y(x, y) == 2)
			{
				for (z = 0; z < Dot_Com; z++)
					board[x][y + z] = -2 + Dot_Com;
				Dot_Size--; //완전한 닷컴이 하나 생성될 때마다 닷컴이 보드판에 생성되는 기준을 달리해줘야 한다.
				Dot_Origin++; //if문의 다음 닷컴 조사를 위함
			}
			else
				Dot_Com--;//닷컴이 겹칠 경우에는 한번 더 실행 되도록 한다.
		}
	}//임의의 보드판 생성 완료.
}

IF_X(int c, int d) //닷컴의 중복을 피하기 위한 추가 연산식(가로 전용)
{
	int w; //중복 검사를 위한 변수 설정
	for (w = 0; w < Dot_Origin; w++)
	{
		if (board[c + w][d] != 0)
			return 1;
		else
			continue;
	}
	return 2;
}

IF_Y(int e, int f) //닷컴의 중복을 피하기 위한 추가 연산식(세로 전용)
{
	int w; //중복 검사를 위한 변수 설정
	for (w = 0; w < Dot_Origin; w++)
	{
		if (board[e][f + w] != 0)
			return 1;
		else
			continue;
	}
	return 2;
}

Check() //중복을 피하기 위한 검산식
{
	int v, w;
	int sum = 0;
	for (v = 0; v < 7; v++)
	{
		for (w = 0; w < 7; w++)
			sum += board[w][v];
	}
	return sum;
}

Check_For_Else() //중복일 경우 배열을 초기화 시키는 함수
{
	int v, w;
	for (v = 0; v < 7; v++)
	{
		for (w = 0; w < 7; w++)
			board[v][w] = 0;
	}
	return 0;
}

Playing()
{
	int g; //보드판 생성을 위한 반복 변수
	char z, x; // 보드판 생성+사용자 입력 좌표 변수 1
	int y; //사용자 입력 좌표 변수 2
	system("cls");
	printf("닷컴 게임을 시작합니다.\n");
	while (1) //게임이 끝날 때까지 무한 루프를 돌린다.
	{
		system("cls");
		printf("    1 2 3 4 5 6 7\n"); //현재 보드판의 상태를 확인할 수 있다.
		for (z = 'A'; z < 'H'; z++)
		{
			printf("%c |", z);
			for (g = 0; g < 7; g++)
			{
				if (board[(int)z - 65][g] == 4)
					printf(" X");
				else if (board[(int)z - 65][g] == 5)
					printf(" *");
				else
					printf(" 0");
			}
			printf("\n");
		}
		printf("원하시는 좌표의 값을 입력해주세요.\n");
		printf("영어는 대/소문자를 구분하지 않으며 영어+숫자의 조합으로 입력해주십시오.: ");
		scanf_s(" %c%d", &x,1, &y);
		Calibrate(x, y); //사용자에게 입력 받았을 경우 계산을 위한 함수로 간다.
		if (Dog_Count == 3 && Duck_Count == 4 && Mouse_Count == 5) //모든 닷컴을 사살하였을 경우 무한 루프문을 탈출
			break;
	}
	printf("모든 닷컴을 사살하였습니다. 정말로 훌륭한 플레이군요.\n");
	printf("당신의 플레이 카운트는 %d입니다.\n", count);
	return 0; //루프문을 탈출하였을 경우 플레이 카운트가 출력되고 프로그램을 종료
}

Calibrate(int x, int y) //입력된 좌표를 계산해주는 함수
{
	if (x == 'a' || x == 'A') //영어로 입력된 x좌표를 숫자로 변환시키는 과정이다.
		x = 0;
	else if (x == 'b' || x == 'B')
		x = 1;
	else if (x == 'c' || x == 'C')
		x = 2;
	else if (x == 'd' || x == 'D')
		x = 3;
	else if (x == 'e' || x == 'E')
		x = 4;
	else if (x == 'f' || x == 'F')
		x = 5;
	else if (x == 'g' || x == 'G')
		x = 6;
	else //이외에 문자+숫자를 입력 받았을 경우 카운트를 세지 않고 주의문을 출력한다.
	{
		printf("잘못 입력하셨습니다. 좌표를 다시 입력해주세요.");
		Sleep(800);
		return 0;
	}
	if (y > 7 || y < 1)
	{
		printf("잘못 입력하셨습니다. 좌표를 다시 입력해주세요.\n");
		Sleep(800);
		return 0;
	}
	/*
	보드판에 0 저장 = 해당좌표에 존재하지 않음
	보드판에 1 저장 = 3크기의 닷컴좌표값 존재
	보드판에 2 저장 = 4크기의 닷컴좌표값 존재
	보드판에 3 저장 = 5크기의 닷컴좌표값 존재
	보드판에 4 저장 = 이미 공격된 닷컴좌표에 대입되는 수
	보드판에 5 저장 = 이미 공격된 빈 좌표에 대입되는 수
	*/
	if (board[x][y - 1] == 0) //해당 좌표값이 0일 경우
	{
		printf("해당 좌표 공격!!!!하지만 아무런 일도 일어나지 않았다...\n");
		board[x][y - 1] = 5; //해당 좌표에 5를 대입
		count++;
		Sleep(800);
	}
	else if (board[x][y - 1] == 1) //해당 좌표값이 1일 경우
	{
		board[x][y - 1] = 4; //해당 좌표를 4로 대입
		printf("야생의 Dog.com 좌표 일부를 발견!!!!!\n");
		count++;
		Dog_Count++;
		Sleep(800);
		if (Dog_Count == 3)
		{
			printf("Dog.com 사살. 훌륭합니다.\n");
			Sleep(1500);
		}
	}
	else if (board[x][y - 1] == 2) //해당 좌표값이 2일 경우
	{
		board[x][y - 1] = 4; //해당 좌표를 4로 대입
		printf("야생의 Duck.com 좌표 일부를 발견!!!!!\n");
		count++;
		Duck_Count++;
		Sleep(800);
		if (Duck_Count == 4)
		{
			printf("Duck.com 사살. 훌륭합니다.\n");
			Sleep(1500);
		}
	}
	else if (board[x][y - 1] == 3) //해당 좌표값이 3일 경우
	{
		board[x][y - 1] = 4; //해당 좌표에 4를 대입
		printf("야생의 Mouse.com 좌표 일부를 발견!!!!!\n");
		count++;
		Mouse_Count++;
		Sleep(800);
		if (Mouse_Count == 5)
		{
			printf("Mouse.com 사살. 훌륭합니다.\n");
			Sleep(1500);
		}
	}
	else if (board[x][y - 1] == 4 || board[x][y - 1] == 5) //해당 좌표값이 4 또는 5일 경우
	{
		printf("왜 때린데 또 때려요...아프게...\n");
		count++;
		Sleep(800);
	}
	return 0;
}

How_To() //게임에 대한 자세한 플레이 방법을 알려주는 함수
{
	int a; //사용자의 입력이 저장되는 변수
	system("cls");
	printf("닷컴 게임에 오신 것을 환영합니다!\n\n\n");
	printf("닷컴게임의 목표는 주어진 7*7보드판 내에 존재하는 3개의 닷컴을 사살하는 것 입니다.\n\n");
	printf("닷컴의 크기는 각각 3,4,5이며 플레이어는 임의의 좌표를 입력하여 최소 횟수로 닷컴을 사살해야 합니다.\n\n");
	printf("-------------------------------------------------\n\n");
	printf("보드판은 세로는 A~G로, 가로는 1~7로 구성되어 있는 보드판이며\n\n");
	printf("(세로 좌표)(가로 좌표)의 조합으로 좌표를 지정할 수 있습니다.\n\n");
	printf("이때의 세로 좌표는 영어의 대/소문자를 가리지 않습니다.\n\n");
	printf("-------------------------------------------------\n\n");
	printf("보드판에 임의로 배정된 3개의 닷컴이 모두 사살되었을 경우\n\n");
	printf("자신의 입력 횟수가 나오며 게임이 종료됩니다.\n\n");
	printf("-------------------------------------------------\n\n");
	printf("좌표를 공격받지 않은 좌표는 0\n");
	printf("닷컴이 있었던 자리에는 X\n");
	printf("아무런 닷컴 없이 공격받은 좌표는 *로 표시됩니다.\n\n\n");
	printf("-------------------------------------------------\n\n");
	Sleep(5000);
	printf("원하는 카테고리의 숫자를 입력해주십시오.\n\n\n");
	printf("1. 플레이\n\n");
	printf("2. 플레이 방법\n\n");
	printf("아무 키. 게임 종료\n\n");
	scanf_s("%d", &a);

	if (a == 1)
		Playing();
	else if (a == 2)
		How_To();
	else
		printf("감사합니다. 안녕히 계세요.\n");
	return 0;
}
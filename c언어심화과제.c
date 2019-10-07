#include <stdio.h>;
#include <time.h>;
#include <stdlib.h>;
#include <windows.h>;

int input[100][2] = { 0 }, output[100][2] = { 0 };		//[인덱스][0:날짜, 1:값]
int inputall = 0, outputall = 0;	//총수입, 총지출
char insummary[100][11], outsummary[100][11];	//적요


void putcalculation();	//총수입, 총지출 계산함수
void menuput(int put);	//수입 입력함수
void menumonitor(int put);	//수입/지출조회 함수
void dayvirtue(int put);	//날짜 정렬 함수 (날짜가 빠른순으로 정렬해줌)
void daysearch();		//기간조회
void summarysearch();	//적요조회

int main(void)		//기본메뉴를 불러오고 각 기능을 호출해주는 기본틀이되는 메인함수
{
	int menu = 7;	//메뉴번호
	COORD pos = { 103, 14 };	//콘솔의좌표값구조체
	
	while (menu != 0)
	{
		printf("\n\t\t\t\t\t\t수입/지출 관리\n");
		printf("\t\t\t\t  ==========================================\n");
		printf("\t\t\t\t    수입총액\t  지출총액\t  잔    액 \n\n");
		printf("\t\t\t\t  ------------------------------------------\n");
		printf("\t\t\t\t  %8d원\t%8d원\t%8d원\n", inputall, outputall, inputall - outputall);
		printf("\t\t\t\t  ==========================================\n\n\n");
		printf("\t\t  [Menu]\n\n");
		printf("\t\t1. 수    입  2. 지    출  3. 수입조회  4. 지출조회  5. 기간조회  6. 적요조회  0. 종    료\n\n");
		printf("\t\t--------------------------------------------------------------------------------------[ ]");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//키보드커서이동
		scanf_s("%d", &menu);

		switch (menu)
		{
			case 1:
				menuput(0);
				break;
			case 2:
				menuput(1);
				break;
			case 3:
				menumonitor(0);
				break;
			case 4:
				menumonitor(1);
				break;
			case 5:
				daysearch();
				break;
			case 6:
				summarysearch();
				break;
			case 0:
				exit(0);
			default:
				continue;
		}

		system("pause");
		system("cls");
	}
}


//==========================================================================================================================


void putcalculation()	//총수입 총지출 계산
{
	inputall = 0;
	outputall = 0;

	for (int i = 0; i < 100; i++)
	{
		inputall += input[i][1];
		outputall += output[i][1];
	}
}


//==========================================================================================================================


void menuput(int put)	// 수입/지출 정보를 넣는 함수	[인덱스][0:날짜, 1:값]
{
	printf("\n");

	if (put == 0)	//수입
	{
		for (int i = 0; i < 100; i++)
		{
			if (input[i][0] == 0)
			{
				printf("\t\t수입날짜를 입력해주세요 (ex : 20191001) : ");
				scanf_s("%d", &input[i][0]);

				printf("\n\t\t수입액수를 입력해주세요 (ex : 10000) : ");
				scanf_s("%d", &input[i][1]);
				
				printf("\n\t\t적요를 입력해주세요(최대10글자) : ");
				scanf_s("%s", insummary[i], 10);

				printf("\n\t\t");
				break;
			}
		}
		dayvirtue(0);	//수입날짜정렬
	}
	
	else if (put == 1)	//지출
	{
		for (int i = 0; i < 100; i++)
		{
			if (output[i][0] == 0)
			{
				printf("\t\t지출날짜를 입력해주세요 (ex : 20191001) : ");
				scanf_s("%d", &output[i][0]);

				printf("\n\t\t지출액수를 입력해주세요 (ex : 10000) : ");
				scanf_s("%d", &output[i][1]);

				printf("\n\t\t적요를 입력해주세요(최대10글자) : ");
				scanf_s("%s", outsummary[i], 10);

				printf("\n\t\t");
				break;
			}
		}
		dayvirtue(1);	//지출날짜정렬
	}
	putcalculation();	//총금액 재계산
}


//==========================================================================================================================


void menumonitor(int put)	//수입,지출내역을 보여주는 함수
{
	system("cls");

	if (put == 0)	//수입
	{
		printf("\n\n\t\t\t\t    |------------------------------------|\n");
		printf("\t\t\t\t    |       \t   수입조회\t         |\n");
		printf("\t\t\t\t    |------------------------------------|\n\n\n");
		printf("\t\t\t\t        날  짜\t  금    액\t  적    요\n");
		printf("\t\t\t\t    --------------------------------------\n");
		for (int i = 0; i < 100; i++)
		{
			if (input[i][0] == 0)
			{
				break;	//입력이 안된부분이 나올떄까지만 반복
			}
			else if (input[i][0] != 0)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d원\t%10s\n", input[i][0] / 10000, (input[i][0] % 10000) / 100, input[i][0] % 100, input[i][1], insummary[i]);
			}
		}
		printf("\t\t\t\t    --------------------------------------\n");
		printf("\t\t\t\t\t\t\t[total%9d원]\n\t\t", inputall);
	}
	
	else if (put == 1)	//지출
	{
		printf("\n\n\t\t\t\t    |------------------------------------|\n");
		printf("\t\t\t\t    |       \t   지출조회\t         |\n");
		printf("\t\t\t\t    |------------------------------------|\n\n\n");
		printf("\t\t\t\t        날  짜\t  금    액\t  적    요\n");
		printf("\t\t\t\t    --------------------------------------\n");
		for (int i = 0; i < 100; i++)
		{
			if (output[i][0] == 0)
			{
				break;	//입력이 안된부분이 나올떄까지만 반복
			}
			else if (output[i][0] != 0)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d원\t%10s\n", output[i][0] / 10000, (output[i][0] % 10000) / 100, output[i][0] % 100, output[i][1], outsummary[i]);
			}
		}
		printf("\t\t\t\t    --------------------------------------\n");
		printf("\t\t\t\t\t\t\t[total%9d원]\n\t\t", outputall);
	}
}


//==========================================================================================================================


void dayvirtue(int put)	//날짜를 빠른순으로 정렬해주는 함수
{
	int temp;
	char text[11];

	if (put == 0)	//수입
	{
		for (int i = 0; i < 100; i++)
		{
			if (input[i][0] == 0)
			{
				break;	//입력이 안된부분이 나오면 탈출
			}

			for (int q = i + 1; q < 100; q++)
			{
				if (input[i][0] > input[q][0])
				{
					if (input[q][0] == 0)
					{
						break;	//입력이 안된부분이 나오면 탈출
					}
					for (int t = 0; t < 2; t++)		//날짜와 금액교환
					{
						temp = input[i][t];
						input[i][t] = input[q][t];
						input[q][t] = temp;
					}
					
					for (int k = 0; k < 10; k++)	//적요 교환
					{
						text[k] = insummary[i][k];
						insummary[i][k] = insummary[q][k];
						insummary[q][k] = text[k];
					}
				}
			}
		}
	}

	else if (put == 1)	//지출
	{
		for (int i = 0; i < 100; i++)
		{
			if (output[i][0] == 0)
			{
				break;	//입력이 안된부분이 나오면 탈출
			}

			for (int q = i + 1; q < 100; q++)
			{
				if (output[i][0] > output[q][0])
				{
					if (output[q][0] == 0)
					{
						break;	//입력이 안된부분이 나오면 탈출
					}
					for (int t = 0; t < 2; t++)	//변수값 교환
					{
						temp = output[i][t];
						output[i][t] = output[q][t];
						output[q][t] = temp;
					}

					for (int k = 0; k < 10; k++)	//적요 교환
					{
						text[k] = outsummary[i][k];
						outsummary[i][k] = outsummary[q][k];
						outsummary[q][k] = text[k];
					}
				}
			}
		}
	}
}


//==========================================================================================================================


void daysearch()
{
	int search, total = 0;

	printf("\t\t조회할 날짜를 입력해주세요 (ex : 20191001) : ");
	scanf_s("%d", &search);

	system("cls");
	
	printf("\n\n\t\t\t\t    |------------------------------------|\n");
	printf("\t\t\t\t    |       \t   기간조회\t         |\n");
	printf("\t\t\t\t    |------------------------------------|\n\n\n");
	printf("\t\t\t\t        날  짜\t  금    액\t  적    요\n");
	printf("\t\t\t\t    --------------------------------------\n");

	for (int i = 0; i < 100; i++)
	{
		if (input[i][0] == 0 && output[i][0] == 0)
		{
			break;
		}
		else
		{
			if (input[i][0] ==  search)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d원\t%10s\n", input[i][0] / 10000, (input[i][0] % 10000) / 100, input[i][0] % 100, input[i][1], insummary[i]);
				total += input[i][1];
			}

			if (output[i][0] == search)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d원\t%10s\n", output[i][0] / 10000, (output[i][0] % 10000) / 100, output[i][0] % 100, -output[i][1], outsummary[i]);
				total -= output[i][1];
			}
		}
	}

	printf("\t\t\t\t    --------------------------------------\n");
	printf("\t\t\t\t\t\t\t[total%9d원]\n\t\t", total);
}


//==========================================================================================================================


void summarysearch()	//적요를 조회해주는 함수
{
	int total = 0, inexe = 0, outexe = 0;
	char search[11];

	printf("\t\t조회할 적요를 입력해주세요 (정확하게 입력) : ");
	scanf_s("%s", &search, 10);

	system("cls");

	printf("\n\n\t\t\t\t    |------------------------------------|\n");
	printf("\t\t\t\t    |       \t   적요조회\t         |\n");
	printf("\t\t\t\t    |------------------------------------|\n\n\n");
	printf("\t\t\t\t        날  짜\t  금    액\t  적    요\n");
	printf("\t\t\t\t    --------------------------------------\n");

	for (int i = 0; i < 100; i++)
	{
		if (input[i][0] == 0 && output[i][0] == 0)
		{
			break;
		}

		for (int q = 0; q < 10; q++)
		{
			if (insummary[i][q] == search[q])
			{
				inexe++;
			}
			if (outsummary[i][q] == search[q])
			{
				outexe++;
			}
		}

		if (inexe == 10)
		{
			printf("\t\t\t\t    %4d.%02d.%02d\t%8d원\t%10s\n", input[i][0] / 10000, (input[i][0] % 10000) / 100, input[i][0] % 100, input[i][1], insummary[i]);
			total += input[i][1];
		}
		if (outexe == 10)
		{
			printf("\t\t\t\t    %4d.%02d.%02d\t%8d원\t%10s\n", output[i][0] / 10000, (output[i][0] % 10000) / 100, output[i][0] % 100, -output[i][1], outsummary[i]);
			total -= output[i][1];
		}
		inexe = 0;
		outexe = 0;
	}

	printf("\t\t\t\t    --------------------------------------\n");
	printf("\t\t\t\t\t\t\t[total%9d원]\n\t\t", total);
}
#include <stdio.h>;
#include <time.h>;
#include <stdlib.h>;
#include <windows.h>;

int input[100][2] = { 0 }, output[100][2] = { 0 };		//[�ε���][0:��¥, 1:��]
int inputall = 0, outputall = 0;	//�Ѽ���, ������
char insummary[100][11], outsummary[100][11];	//����


void putcalculation();	//�Ѽ���, ������ ����Լ�
void menuput(int put);	//���� �Է��Լ�
void menumonitor(int put);	//����/������ȸ �Լ�
void dayvirtue(int put);	//��¥ ���� �Լ� (��¥�� ���������� ��������)
void daysearch();		//�Ⱓ��ȸ
void summarysearch();	//������ȸ

int main(void)		//�⺻�޴��� �ҷ����� �� ����� ȣ�����ִ� �⺻Ʋ�̵Ǵ� �����Լ�
{
	int menu = 7;	//�޴���ȣ
	COORD pos = { 103, 14 };	//�ܼ�����ǥ������ü
	
	while (menu != 0)
	{
		printf("\n\t\t\t\t\t\t����/���� ����\n");
		printf("\t\t\t\t  ==========================================\n");
		printf("\t\t\t\t    �����Ѿ�\t  �����Ѿ�\t  ��    �� \n\n");
		printf("\t\t\t\t  ------------------------------------------\n");
		printf("\t\t\t\t  %8d��\t%8d��\t%8d��\n", inputall, outputall, inputall - outputall);
		printf("\t\t\t\t  ==========================================\n\n\n");
		printf("\t\t  [Menu]\n\n");
		printf("\t\t1. ��    ��  2. ��    ��  3. ������ȸ  4. ������ȸ  5. �Ⱓ��ȸ  6. ������ȸ  0. ��    ��\n\n");
		printf("\t\t--------------------------------------------------------------------------------------[ ]");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);	//Ű����Ŀ���̵�
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


void putcalculation()	//�Ѽ��� ������ ���
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


void menuput(int put)	// ����/���� ������ �ִ� �Լ�	[�ε���][0:��¥, 1:��]
{
	printf("\n");

	if (put == 0)	//����
	{
		for (int i = 0; i < 100; i++)
		{
			if (input[i][0] == 0)
			{
				printf("\t\t���Գ�¥�� �Է����ּ��� (ex : 20191001) : ");
				scanf_s("%d", &input[i][0]);

				printf("\n\t\t���Ծ׼��� �Է����ּ��� (ex : 10000) : ");
				scanf_s("%d", &input[i][1]);
				
				printf("\n\t\t���並 �Է����ּ���(�ִ�10����) : ");
				scanf_s("%s", insummary[i], 10);

				printf("\n\t\t");
				break;
			}
		}
		dayvirtue(0);	//���Գ�¥����
	}
	
	else if (put == 1)	//����
	{
		for (int i = 0; i < 100; i++)
		{
			if (output[i][0] == 0)
			{
				printf("\t\t���⳯¥�� �Է����ּ��� (ex : 20191001) : ");
				scanf_s("%d", &output[i][0]);

				printf("\n\t\t����׼��� �Է����ּ��� (ex : 10000) : ");
				scanf_s("%d", &output[i][1]);

				printf("\n\t\t���並 �Է����ּ���(�ִ�10����) : ");
				scanf_s("%s", outsummary[i], 10);

				printf("\n\t\t");
				break;
			}
		}
		dayvirtue(1);	//���⳯¥����
	}
	putcalculation();	//�ѱݾ� ����
}


//==========================================================================================================================


void menumonitor(int put)	//����,���⳻���� �����ִ� �Լ�
{
	system("cls");

	if (put == 0)	//����
	{
		printf("\n\n\t\t\t\t    |------------------------------------|\n");
		printf("\t\t\t\t    |       \t   ������ȸ\t         |\n");
		printf("\t\t\t\t    |------------------------------------|\n\n\n");
		printf("\t\t\t\t        ��  ¥\t  ��    ��\t  ��    ��\n");
		printf("\t\t\t\t    --------------------------------------\n");
		for (int i = 0; i < 100; i++)
		{
			if (input[i][0] == 0)
			{
				break;	//�Է��� �ȵȺκ��� ���Ë������� �ݺ�
			}
			else if (input[i][0] != 0)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d��\t%10s\n", input[i][0] / 10000, (input[i][0] % 10000) / 100, input[i][0] % 100, input[i][1], insummary[i]);
			}
		}
		printf("\t\t\t\t    --------------------------------------\n");
		printf("\t\t\t\t\t\t\t[total%9d��]\n\t\t", inputall);
	}
	
	else if (put == 1)	//����
	{
		printf("\n\n\t\t\t\t    |------------------------------------|\n");
		printf("\t\t\t\t    |       \t   ������ȸ\t         |\n");
		printf("\t\t\t\t    |------------------------------------|\n\n\n");
		printf("\t\t\t\t        ��  ¥\t  ��    ��\t  ��    ��\n");
		printf("\t\t\t\t    --------------------------------------\n");
		for (int i = 0; i < 100; i++)
		{
			if (output[i][0] == 0)
			{
				break;	//�Է��� �ȵȺκ��� ���Ë������� �ݺ�
			}
			else if (output[i][0] != 0)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d��\t%10s\n", output[i][0] / 10000, (output[i][0] % 10000) / 100, output[i][0] % 100, output[i][1], outsummary[i]);
			}
		}
		printf("\t\t\t\t    --------------------------------------\n");
		printf("\t\t\t\t\t\t\t[total%9d��]\n\t\t", outputall);
	}
}


//==========================================================================================================================


void dayvirtue(int put)	//��¥�� ���������� �������ִ� �Լ�
{
	int temp;
	char text[11];

	if (put == 0)	//����
	{
		for (int i = 0; i < 100; i++)
		{
			if (input[i][0] == 0)
			{
				break;	//�Է��� �ȵȺκ��� ������ Ż��
			}

			for (int q = i + 1; q < 100; q++)
			{
				if (input[i][0] > input[q][0])
				{
					if (input[q][0] == 0)
					{
						break;	//�Է��� �ȵȺκ��� ������ Ż��
					}
					for (int t = 0; t < 2; t++)		//��¥�� �ݾױ�ȯ
					{
						temp = input[i][t];
						input[i][t] = input[q][t];
						input[q][t] = temp;
					}
					
					for (int k = 0; k < 10; k++)	//���� ��ȯ
					{
						text[k] = insummary[i][k];
						insummary[i][k] = insummary[q][k];
						insummary[q][k] = text[k];
					}
				}
			}
		}
	}

	else if (put == 1)	//����
	{
		for (int i = 0; i < 100; i++)
		{
			if (output[i][0] == 0)
			{
				break;	//�Է��� �ȵȺκ��� ������ Ż��
			}

			for (int q = i + 1; q < 100; q++)
			{
				if (output[i][0] > output[q][0])
				{
					if (output[q][0] == 0)
					{
						break;	//�Է��� �ȵȺκ��� ������ Ż��
					}
					for (int t = 0; t < 2; t++)	//������ ��ȯ
					{
						temp = output[i][t];
						output[i][t] = output[q][t];
						output[q][t] = temp;
					}

					for (int k = 0; k < 10; k++)	//���� ��ȯ
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

	printf("\t\t��ȸ�� ��¥�� �Է����ּ��� (ex : 20191001) : ");
	scanf_s("%d", &search);

	system("cls");
	
	printf("\n\n\t\t\t\t    |------------------------------------|\n");
	printf("\t\t\t\t    |       \t   �Ⱓ��ȸ\t         |\n");
	printf("\t\t\t\t    |------------------------------------|\n\n\n");
	printf("\t\t\t\t        ��  ¥\t  ��    ��\t  ��    ��\n");
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
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d��\t%10s\n", input[i][0] / 10000, (input[i][0] % 10000) / 100, input[i][0] % 100, input[i][1], insummary[i]);
				total += input[i][1];
			}

			if (output[i][0] == search)
			{
				printf("\t\t\t\t    %4d.%02d.%02d\t%8d��\t%10s\n", output[i][0] / 10000, (output[i][0] % 10000) / 100, output[i][0] % 100, -output[i][1], outsummary[i]);
				total -= output[i][1];
			}
		}
	}

	printf("\t\t\t\t    --------------------------------------\n");
	printf("\t\t\t\t\t\t\t[total%9d��]\n\t\t", total);
}


//==========================================================================================================================


void summarysearch()	//���並 ��ȸ���ִ� �Լ�
{
	int total = 0, inexe = 0, outexe = 0;
	char search[11];

	printf("\t\t��ȸ�� ���並 �Է����ּ��� (��Ȯ�ϰ� �Է�) : ");
	scanf_s("%s", &search, 10);

	system("cls");

	printf("\n\n\t\t\t\t    |------------------------------------|\n");
	printf("\t\t\t\t    |       \t   ������ȸ\t         |\n");
	printf("\t\t\t\t    |------------------------------------|\n\n\n");
	printf("\t\t\t\t        ��  ¥\t  ��    ��\t  ��    ��\n");
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
			printf("\t\t\t\t    %4d.%02d.%02d\t%8d��\t%10s\n", input[i][0] / 10000, (input[i][0] % 10000) / 100, input[i][0] % 100, input[i][1], insummary[i]);
			total += input[i][1];
		}
		if (outexe == 10)
		{
			printf("\t\t\t\t    %4d.%02d.%02d\t%8d��\t%10s\n", output[i][0] / 10000, (output[i][0] % 10000) / 100, output[i][0] % 100, -output[i][1], outsummary[i]);
			total -= output[i][1];
		}
		inexe = 0;
		outexe = 0;
	}

	printf("\t\t\t\t    --------------------------------------\n");
	printf("\t\t\t\t\t\t\t[total%9d��]\n\t\t", total);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>//ͼ�ο�ͷ�ļ�
#include <Windows.h>
#define WIDTH 960
#define HEIGTH 640
#define STR_SIZE 20//���������������
#define STR_NUM 128//�����괮��
#define STR_WIDTH 15//��������
struct Rain//������ṹ
{
	int x;//���������λ��
	int y;//Y����
	int  speed;//�½��ٶ�
	char str[STR_SIZE];//����������
}rain[STR_NUM];
char CreateCh()
{
	char temp = 0;
	int flag = rand() % 3;//0,1,2
	if (flag == 0)
	{
		temp = rand() % 26 + 'a';
	}
	else if (flag == 1)
	{
		temp = rand() % 26 + 'A';
	}
	else
	{
		temp = rand() % 10 + '0';
	}
	return temp;
}
void GameInit()
{
	for (int i = 0; i < STR_NUM; i++)//�����ٶȳ�ʼ��
	{
		rain[i].x = i * STR_WIDTH;//ѭ�������ַ��Ŀ��
		rain[i].y = rand() % HEIGTH;//Y���
		rain[i].speed = rand() % 5 + 5;//5 6 7 8 9 10
	}
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			rain[i].str[j] = CreateCh();
		}
	}
}
void GameDraw()
{
	cleardevice();
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			outtextxy(rain[i].x, rain[i].y - STR_WIDTH * j, rain[i].str[j]);
			settextcolor(RGB(0, 70 - 13 * j, 0));
		}
	}
}
void GamePlay()
{
	for (int i = 0; i < STR_NUM; i++)
	{
		rain[i].y += rain[i].speed;
		if (rain[i].y - STR_SIZE * STR_WIDTH > HEIGTH)
		{
			rain[i].y = 0;
		}
	}
}
void ChangeCh()
{
	for (int i = 0; i < STR_NUM; i++)
	{
		rain[rand() % STR_NUM].str[rand() % STR_SIZE] = CreateCh();
	}

}
int main()
{
	//1,�������ֲ���ս��ʬPlants vs. Zombies GOTY  
	HWND hGameWnd = FindWindow(L"MainWindow", L"Plants vs. Zombies GOTY ");
	//û��������Ϸ5
	if (hGameWnd == NULL)
	{
		printf("û�����������Ϸ\n");
		return 0;
	}
	//2���ݴ��ھ����ȡ���̵�PID,Process ID
	DWORD dwPID = 0;
	GetWindowThreadProcessId(hGameWnd, &dwPID);
	if (dwPID == 0)
	{
		printf("��ȡ����PIDʧ��:%d\n", GetLastError());
		return 0;
	}
	//3.����PID��ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);//���ĸ����̣�PID�Ľ���
	if (hProcess == NULL)
	{
		printf("�򿪽���ʧ��,�������:%d\n", GetLastError());
		return 0;
	}
	//4��ָ��λ�ý����ڴ���ȥ��ȡ����
	DWORD dwSunshineBase = 0x007794f8;
	DWORD dwSunshineAddressValue = 0;
	SIZE_T dwSize = 0;
	if (FALSE == ReadProcessMemory(
		hProcess,//��ȡ��һ������
		(LPVOID)dwSunshineBase,//Ҫ��ȡ�Ļ���ַ       
		&dwSunshineAddressValue,//���ܽ��̵�ַ����
		sizeof(DWORD),//DWORD=unsigned long Ҫ��ȡ��4���ֽ���
		&dwSize))
	{
		printf("��ȡ���⾲̬��ַʧ�ܴ������.\n", GetLastError());
		return 0;
	}
	DWORD dwMoneyBase = 0x007794f8;
	DWORD dwMoneyAddressValue = 0;
	SIZE_T dwMent = 0;
	if (FALSE == ReadProcessMemory(
		hProcess,//��ȡ��һ������
		(LPVOID)dwMoneyBase,//Ҫ��ȡ�Ļ���ַ       
		&dwMoneyAddressValue,//���ܽ��̵�ַ����
		sizeof(DWORD),//DWORD=unsigned long Ҫ��ȡ��4���ֽ���
		&dwMent))
	{
		printf("��ȡ��Ҿ�̬��ַʧ�ܴ������.\n", GetLastError());
		return 0;
	}
	//5����ȡһ��������˵�ַ;
	DWORD dwSunshineOffsetFirst = 0X868;
	DWORD dwSunshineOffsetValue = 0;//�� ȡ�����ĵ�ֵַ���������������
	if (FALSE == ReadProcessMemory(hProcess,
		(LPVOID)(dwSunshineAddressValue + dwSunshineOffsetFirst),
		&dwSunshineOffsetValue,
		sizeof(DWORD),
		&dwSize))
	{
		printf("��ȡһ������ƫ�Ƶ�ַʧ��,�������%d\n", GetLastError());
		return 0;
	}
	//5,��ȡһ�����ƫ�Ƶ�ַ
	DWORD dwMoneyOffsetFirst = 0X950;
	DWORD dwMoneyOffsetValue = 0;//�� ȡ�����ĵ�ֵַ���������������
	if (FALSE == ReadProcessMemory(hProcess,
		(LPVOID)(dwMoneyAddressValue + dwMoneyOffsetFirst),
		&dwMoneyOffsetValue,
		sizeof(DWORD),
		&dwMent))
	{
		printf("��ȡһ�����ƫ�Ƶ�ַʧ��,�������%d\n", GetLastError());
		return 0;
	}

	//6,��������
	DWORD dwSunshineOffsetSecond = 0x5578;//2�����˵ĵ�ַ
	DWORD dwSunshine = 0;//2�����˺�ֱ�ӵĵ����ǵ�����ֵ
	if (FALSE == ReadProcessMemory(
		hProcess,
		(LPVOID)(dwSunshineOffsetValue + dwSunshineOffsetSecond),
		&dwSunshine,
		sizeof(DWORD),
		&dwSize
	))
	{
		printf("2��ƫ�������ַʧ��,�������%d\n", GetLastError());
		return 0;
	}
	DWORD dwMoneyOffsetSecond = 0x50;//2�����˵ĵ�ַ
	DWORD dwMoney = 0;//2�����˺�ֱ�ӵĵ����ǵ�����ֵ
	if (FALSE == ReadProcessMemory(
		hProcess,
		(LPVOID)(dwMoneyOffsetValue + dwMoneyOffsetSecond),
		&dwMoney,
		sizeof(DWORD),
		&dwMent
	))
	{
		printf("2��ƫ�ƽ�ҵ�ַʧ��,�������%d\n", GetLastError());
		return 0;
	}
	printf("����ֵ��%d\n", dwSunshine);
	printf("��������Ҫ�޸ĵ�����ֵ:\n");
	int nModifySunshine;
	scanf("%d", &nModifySunshine);
	WriteProcessMemory(
		hProcess,
		(LPVOID)(dwSunshineOffsetValue + dwSunshineOffsetSecond),
		&nModifySunshine,
		sizeof(DWORD),
		&dwSize);
	printf("���ֵ��%d\n", dwMoney);
	//printf("��������Ҫ�޸ĵĽ��ֵ:\n");
	//int nModeMoney;
	//scanf("%d", &nModeMoney);
	//WriteProcessMemory(
	//	hProcess,
	//	(LPVOID)(dwMoneyOffsetValue + dwMoneyOffsetSecond),
	//	&nModeMoney,
	//	sizeof(DWORD),
	//	&dwMent);*/
	initgraph(WIDTH, HEIGTH);
	srand(GetTickCount());
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();//��ȡ���Կ�������������ȡ�ĺ�����
	while (1)
	{
		ChangeCh();
		BeginBatchDraw();//˫����
		if (t2 - t1 > 10)
		{
			GamePlay();
			t1 = t2;
		}
		t2 = GetTickCount();
		GameDraw();
		EndBatchDraw();
	}
	CloseHandle(hProcess);
	return 0;
}
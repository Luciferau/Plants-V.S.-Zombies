#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>//图形库头文件
#include <Windows.h>
#define WIDTH 960
#define HEIGTH 640
#define STR_SIZE 20//数字雨素组最大村粗
#define STR_NUM 128//数字雨串速
#define STR_WIDTH 15//数字雨宽度
struct Rain//数字雨结构
{
	int x;//数字雨横向位置
	int y;//Y坐标
	int  speed;//下降速度
	char str[STR_SIZE];//数字雨数组
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
	for (int i = 0; i < STR_NUM; i++)//坐标速度初始化
	{
		rain[i].x = i * STR_WIDTH;//循环乘以字符的宽度
		rain[i].y = rand() % HEIGTH;//Y随机
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
	//1,步骤查找植物大战僵尸Plants vs. Zombies GOTY  
	HWND hGameWnd = FindWindow(L"MainWindow", L"Plants vs. Zombies GOTY ");
	//没有运行游戏5
	if (hGameWnd == NULL)
	{
		printf("没有运行这个游戏\n");
		return 0;
	}
	//2根据窗口句柄获取进程的PID,Process ID
	DWORD dwPID = 0;
	GetWindowThreadProcessId(hGameWnd, &dwPID);
	if (dwPID == 0)
	{
		printf("获取进程PID失败:%d\n", GetLastError());
		return 0;
	}
	//3.根据PID获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);//打开哪个进程，PID的进程
	if (hProcess == NULL)
	{
		printf("打开进程失败,错误代码:%d\n", GetLastError());
		return 0;
	}
	//4从指定位置进程内存区去读取数据
	DWORD dwSunshineBase = 0x007794f8;
	DWORD dwSunshineAddressValue = 0;
	SIZE_T dwSize = 0;
	if (FALSE == ReadProcessMemory(
		hProcess,//读取哪一个进程
		(LPVOID)dwSunshineBase,//要读取的基地址       
		&dwSunshineAddressValue,//接受进程地址数据
		sizeof(DWORD),//DWORD=unsigned long 要读取的4个字节数
		&dwSize))
	{
		printf("获取阳光静态地址失败错误代码.\n", GetLastError());
		return 0;
	}
	DWORD dwMoneyBase = 0x007794f8;
	DWORD dwMoneyAddressValue = 0;
	SIZE_T dwMent = 0;
	if (FALSE == ReadProcessMemory(
		hProcess,//读取哪一个进程
		(LPVOID)dwMoneyBase,//要读取的基地址       
		&dwMoneyAddressValue,//接受进程地址数据
		sizeof(DWORD),//DWORD=unsigned long 要读取的4个字节数
		&dwMent))
	{
		printf("获取金币静态地址失败错误代码.\n", GetLastError());
		return 0;
	}
	//5，获取一级阳光便宜地址;
	DWORD dwSunshineOffsetFirst = 0X868;
	DWORD dwSunshineOffsetValue = 0;//读 取出来的地址值保留到这个变量来
	if (FALSE == ReadProcessMemory(hProcess,
		(LPVOID)(dwSunshineAddressValue + dwSunshineOffsetFirst),
		&dwSunshineOffsetValue,
		sizeof(DWORD),
		&dwSize))
	{
		printf("获取一级阳光偏移地址失败,错误代码%d\n", GetLastError());
		return 0;
	}
	//5,获取一级金币偏移地址
	DWORD dwMoneyOffsetFirst = 0X950;
	DWORD dwMoneyOffsetValue = 0;//读 取出来的地址值保留到这个变量来
	if (FALSE == ReadProcessMemory(hProcess,
		(LPVOID)(dwMoneyAddressValue + dwMoneyOffsetFirst),
		&dwMoneyOffsetValue,
		sizeof(DWORD),
		&dwMent))
	{
		printf("获取一级金币偏移地址失败,错误代码%d\n", GetLastError());
		return 0;
	}

	//6,二级便宜
	DWORD dwSunshineOffsetSecond = 0x5578;//2级便宜的地址
	DWORD dwSunshine = 0;//2级便宜后直接的到我们的阳光值
	if (FALSE == ReadProcessMemory(
		hProcess,
		(LPVOID)(dwSunshineOffsetValue + dwSunshineOffsetSecond),
		&dwSunshine,
		sizeof(DWORD),
		&dwSize
	))
	{
		printf("2级偏移阳光地址失败,错误代码%d\n", GetLastError());
		return 0;
	}
	DWORD dwMoneyOffsetSecond = 0x50;//2级便宜的地址
	DWORD dwMoney = 0;//2级便宜后直接的到我们的阳光值
	if (FALSE == ReadProcessMemory(
		hProcess,
		(LPVOID)(dwMoneyOffsetValue + dwMoneyOffsetSecond),
		&dwMoney,
		sizeof(DWORD),
		&dwMent
	))
	{
		printf("2级偏移金币地址失败,错误代码%d\n", GetLastError());
		return 0;
	}
	printf("阳光值是%d\n", dwSunshine);
	printf("请输入你要修改的阳光值:\n");
	int nModifySunshine;
	scanf("%d", &nModifySunshine);
	WriteProcessMemory(
		hProcess,
		(LPVOID)(dwSunshineOffsetValue + dwSunshineOffsetSecond),
		&nModifySunshine,
		sizeof(DWORD),
		&dwSize);
	printf("金币值是%d\n", dwMoney);
	//printf("请属入你要修改的金币值:\n");
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
	t1 = t2 = GetTickCount();//获取电脑开机到现在所获取的毫秒数
	while (1)
	{
		ChangeCh();
		BeginBatchDraw();//双缓冲
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
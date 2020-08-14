// 机器调度问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"MachineScheduling.h"
#define MAX_NUM_OF_ANALYZE 10000 //可以处理的最大任务数
int main()
{
	int numberOfMission = 0; //初始化任务数
	int numberOfMachine = 0; //初始化机器数
	Machine* machine = new Machine[MAX_NUM_OF_ANALYZE]; //动态申请，使得程序方便分析较大数据
	Mission* mission = new Mission[MAX_NUM_OF_ANALYZE]; //动态申请，使得程序方便分析较大数据
	string nameOfMachine = ""; //初始化机器名称

	cout << "请输入任务数：" << endl;
	cin >> numberOfMission;

	cout << "请输入任务所需要的时间：" << endl;
	for (int i = 1; i <= numberOfMission; i++)
	{
		cin >> mission[i].timeNeed;
	}

	cout << "请输入机器个数：" ;
	cin >> numberOfMachine;
	
	cout << "请输入机器名称：" << endl;
	for (int i = 1; i <= numberOfMachine; i++)
	{
		cin >> nameOfMachine;
		machine[i].name = nameOfMachine;
	}
	
	MissionDistribution(machine, mission, numberOfMachine, numberOfMission); //分配任务
	delete[] machine; //释放内存
	delete[] mission; //释放内存
	return 0;
}
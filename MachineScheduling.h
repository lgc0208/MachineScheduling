#ifndef _MACHINE_SCHDULING_H
#define _MACHINE_SCHEDULING_H

#include<iostream>
using namespace std;

struct Machine
{
	string name; //机器名称
	int timePaid = 0; //已花费时间
	string distribution; //分配方法
	int numOfDistribution = 0; //分配任务数
};

struct Mission
{
	int timeNeed = 0; //任务所需时间
};

//交换i，j
template<class T>
void Swap(T& i, T& j);

//根据任务所需时间进行大根堆筛选
void BigSift(Mission mission[], int nodeBeSift, int lastNode);

//根据机器所用时间进行小根堆筛选
void SmallSift(Machine machine[], int nodeBeSift, int lastNode);

//建大根堆
void BuildBigSift(Mission mission[], int allNumber);

//建小根堆
void BuildSmallSift(Machine machine[], int allNumber);

//任务分配
void MissionDistribution(Machine machine[], Mission mission[], int numberOfMachine, int numberOfMission);

#endif // !_MACHINE_SCHDULING_H
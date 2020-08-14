/*
	有 m 台机器处理 n 个作业，设作业 i 的处理时间为 ti，则对 n 个作业进行机器分配，使
得：
	1）一台机器在同一时间内只能处理一个作业；
	2）一个作业不能同时在两台机器上处理；
	3）作业 i 一旦运行，需要连续 ti 个时间单位。
	设计算法进行合理调度，使得 m 台机器上处理处理 n 个作业所需要的总时间最短。
*/
#include"MachineScheduling.h"
#include<string>
/*
草稿
	排序方法：堆排序，将机器所花时间和任务所需时间进行小根堆和大根堆排序，
	将两个堆堆顶相互匹配，匹配后重新建立大小根堆
	机器属性：名称，花费时间
	任务属性：名称，所需时间

	（1）任务数>机器数
	1.将n个任务按所需时间建立大根堆
	2.将m个机器按所花时间建立小根堆
	3.将大根堆顶的任务分配给小根堆根顶的机器
	4.将所用机器加上任务时间后重新送入小根堆筛选
	5.删除大根堆顶的任务
	6.循环1-5，直到所有任务被分配完成，小根堆的堆顶所花时间即为所求
	（2）任务数<=机器数
	所花时间=最长任务所需时间
*/

//交换i，j
template<class T>
void Swap(T& i, T& j) 
{
	T temp = i;
	i = j;
	j = temp;
}

//根据任务所需时间进行大根堆筛选
void BigSift(Mission mission[], int nodeBeSift, int lastNode)
{
	int i = nodeBeSift; //i为被筛选的结点
	int j = 2 * i; //j为i的左孩子
	while (j <= lastNode) //保证j有意义，防止数组越界
	{
		//当i的右孩子比左孩子大时，j指向右孩子，否则仍指向左孩子
		if (j < lastNode && mission[j].timeNeed < mission[j + 1].timeNeed)
			j++;
		//当根结点比左右孩子都大时，筛选完成，跳出循环
		if (mission[i].timeNeed > mission[j].timeNeed)
			break;
		else //否则，当筛选还未完成时执行
		{
			Swap(mission[i], mission[j]); //交换顺序，使得根结点大于两个孩子结点
			//改变下标，对孩子结点进行筛选
			i = j;  
			j = 2 * i;
		}
	}
}

//根据机器所用时间进行小根堆筛选
void SmallSift(Machine machine[], int nodeBeSift, int lastNode)
{
	int i = nodeBeSift; //设定根节点
	int j = 2 * i; //设定孩子结点
	while (j <= lastNode) //孩子结点存在
	{
		//j指向左右孩子中最小的孩子
		if (j<lastNode && machine[j].timePaid>machine[j + 1].timePaid)
			j++;
		//符合小根堆条件时退出循环
		if (machine[i].timePaid < machine[j].timePaid)
			break;
		//不符合小根堆条件时，根结点与最大的孩子结点交换
		else 
		{
			Swap(machine[i], machine[j]);
			i = j;
			j = 2 * i;
		}
	}
}

//建大根堆
void BuildBigSift(Mission mission[], int allNumber)
{
	//最后一个分支结点的编号为allNumber/2，从最后一个分支结点开始筛选，编号逐渐递减，直到筛选到根结点
	for (int i = allNumber / 2; i > 0; i--)
		BigSift(mission, i, allNumber);
}

//建小根堆
void BuildSmallSift(Machine machine[], int allNumber)
{
	//最后一个分支结点的编号为allNumber/2，从最后一个分支结点开始筛选，编号逐渐递减，直到筛选到根结点
	for (int i = allNumber / 2; i > 0; i--)
		SmallSift(machine, i, allNumber);
}

//任务分配
void MissionDistribution(Machine machine[], Mission mission[], int numberOfMachine, int numberOfMission)
{
	string tempString; //用于记录任务分配
	//当机器数大于等于任务数，供过于求时
	if (numberOfMachine >= numberOfMission)
	{
		cout << "机器数大于任务数，每台机器完成一个任务，完成所有任务所需要的最短时间为：" ;
		BuildBigSift(mission, numberOfMission); //建立大根堆，堆顶元素即为所求
		cout << mission[1].timeNeed << endl; //输出最长的任务耗时
	}
	// 机器数小于任务数，供不应求时
	else
	{
		//现将耗时最大的几个任务分配给各个机器
		for (int i = 1; i <= numberOfMachine; i++)
		{
			BuildBigSift(mission, numberOfMission); //建立大根堆，寻找耗时最大的任务
			machine[i].timePaid = mission[1].timeNeed; //初始化机器运行时间
			machine[i].distribution = to_string(mission[1].timeNeed); //更新分配情况
			machine[i].numOfDistribution++; //更新任务分配数
			for (int j = 1; j <= numberOfMission - 1; j++) //删去已完成的任务
			{
				mission[j] = mission[j + 1]; 
			}
			numberOfMission--; //完成分配一次后，任务数-1
		}
			
		//上述完成第一轮任务分配，下述完成剩余任务分配
		for (int k = numberOfMission; k > 0; k--)
		{
			BuildSmallSift(machine, numberOfMachine); //建小根堆
			BuildBigSift(mission, numberOfMission); //建大根堆
			machine[1].distribution += ("+" + to_string(mission[1].timeNeed)); //记录分配情况
			machine[1].timePaid += mission[1].timeNeed; //更新机器工作总时长
			machine[1].numOfDistribution++; //更新任务分配数
			for (int m = 1; m < numberOfMission; m++) //更新剩余任务
			{
				mission[m] = mission[m + 1];
			}
			numberOfMission--; //更新剩余任务数
		}

		//当所有任务都分配完毕后
		if (numberOfMission == 0)
		{
			//按题目所给示例格式输出
			cout << endl;
			cout << "时间分配：" << endl;
			for (int i = numberOfMachine; i > 0; i--)
			{
				if (machine[i].numOfDistribution > 1) 
					machine[i].distribution += ("=" + to_string(machine[i].timePaid));
				cout << "    " << machine[i].name << "机器：" << machine[i].distribution << endl;
			}
			cout << "总的处理时间是" << machine[1].timePaid << "。" << endl;
		}
	}
}
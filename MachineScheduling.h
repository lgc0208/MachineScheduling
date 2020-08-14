#ifndef _MACHINE_SCHDULING_H
#define _MACHINE_SCHEDULING_H

#include<iostream>
using namespace std;

struct Machine
{
	string name; //��������
	int timePaid = 0; //�ѻ���ʱ��
	string distribution; //���䷽��
	int numOfDistribution = 0; //����������
};

struct Mission
{
	int timeNeed = 0; //��������ʱ��
};

//����i��j
template<class T>
void Swap(T& i, T& j);

//������������ʱ����д����ɸѡ
void BigSift(Mission mission[], int nodeBeSift, int lastNode);

//���ݻ�������ʱ�����С����ɸѡ
void SmallSift(Machine machine[], int nodeBeSift, int lastNode);

//�������
void BuildBigSift(Mission mission[], int allNumber);

//��С����
void BuildSmallSift(Machine machine[], int allNumber);

//�������
void MissionDistribution(Machine machine[], Mission mission[], int numberOfMachine, int numberOfMission);

#endif // !_MACHINE_SCHDULING_H
/*
	�� m ̨�������� n ����ҵ������ҵ i �Ĵ���ʱ��Ϊ ti����� n ����ҵ���л������䣬ʹ
�ã�
	1��һ̨������ͬһʱ����ֻ�ܴ���һ����ҵ��
	2��һ����ҵ����ͬʱ����̨�����ϴ���
	3����ҵ i һ�����У���Ҫ���� ti ��ʱ�䵥λ��
	����㷨���к�����ȣ�ʹ�� m ̨�����ϴ����� n ����ҵ����Ҫ����ʱ����̡�
*/
#include"MachineScheduling.h"
#include<string>
/*
�ݸ�
	���򷽷��������򣬽���������ʱ�����������ʱ�����С���Ѻʹ��������
	�������ѶѶ��໥ƥ�䣬ƥ������½�����С����
	�������ԣ����ƣ�����ʱ��
	�������ԣ����ƣ�����ʱ��

	��1��������>������
	1.��n����������ʱ�佨�������
	2.��m������������ʱ�佨��С����
	3.������Ѷ�����������С���Ѹ����Ļ���
	4.�����û�����������ʱ�����������С����ɸѡ
	5.ɾ������Ѷ�������
	6.ѭ��1-5��ֱ���������񱻷�����ɣ�С���ѵĶѶ�����ʱ�伴Ϊ����
	��2��������<=������
	����ʱ��=���������ʱ��
*/

//����i��j
template<class T>
void Swap(T& i, T& j) 
{
	T temp = i;
	i = j;
	j = temp;
}

//������������ʱ����д����ɸѡ
void BigSift(Mission mission[], int nodeBeSift, int lastNode)
{
	int i = nodeBeSift; //iΪ��ɸѡ�Ľ��
	int j = 2 * i; //jΪi������
	while (j <= lastNode) //��֤j�����壬��ֹ����Խ��
	{
		//��i���Һ��ӱ����Ӵ�ʱ��jָ���Һ��ӣ�������ָ������
		if (j < lastNode && mission[j].timeNeed < mission[j + 1].timeNeed)
			j++;
		//�����������Һ��Ӷ���ʱ��ɸѡ��ɣ�����ѭ��
		if (mission[i].timeNeed > mission[j].timeNeed)
			break;
		else //���򣬵�ɸѡ��δ���ʱִ��
		{
			Swap(mission[i], mission[j]); //����˳��ʹ�ø��������������ӽ��
			//�ı��±꣬�Ժ��ӽ�����ɸѡ
			i = j;  
			j = 2 * i;
		}
	}
}

//���ݻ�������ʱ�����С����ɸѡ
void SmallSift(Machine machine[], int nodeBeSift, int lastNode)
{
	int i = nodeBeSift; //�趨���ڵ�
	int j = 2 * i; //�趨���ӽ��
	while (j <= lastNode) //���ӽ�����
	{
		//jָ�����Һ�������С�ĺ���
		if (j<lastNode && machine[j].timePaid>machine[j + 1].timePaid)
			j++;
		//����С��������ʱ�˳�ѭ��
		if (machine[i].timePaid < machine[j].timePaid)
			break;
		//������С��������ʱ������������ĺ��ӽ�㽻��
		else 
		{
			Swap(machine[i], machine[j]);
			i = j;
			j = 2 * i;
		}
	}
}

//�������
void BuildBigSift(Mission mission[], int allNumber)
{
	//���һ����֧���ı��ΪallNumber/2�������һ����֧��㿪ʼɸѡ������𽥵ݼ���ֱ��ɸѡ�������
	for (int i = allNumber / 2; i > 0; i--)
		BigSift(mission, i, allNumber);
}

//��С����
void BuildSmallSift(Machine machine[], int allNumber)
{
	//���һ����֧���ı��ΪallNumber/2�������һ����֧��㿪ʼɸѡ������𽥵ݼ���ֱ��ɸѡ�������
	for (int i = allNumber / 2; i > 0; i--)
		SmallSift(machine, i, allNumber);
}

//�������
void MissionDistribution(Machine machine[], Mission mission[], int numberOfMachine, int numberOfMission)
{
	string tempString; //���ڼ�¼�������
	//�����������ڵ�������������������ʱ
	if (numberOfMachine >= numberOfMission)
	{
		cout << "������������������ÿ̨�������һ���������������������Ҫ�����ʱ��Ϊ��" ;
		BuildBigSift(mission, numberOfMission); //��������ѣ��Ѷ�Ԫ�ؼ�Ϊ����
		cout << mission[1].timeNeed << endl; //�����������ʱ
	}
	// ������С��������������Ӧ��ʱ
	else
	{
		//�ֽ���ʱ���ļ�������������������
		for (int i = 1; i <= numberOfMachine; i++)
		{
			BuildBigSift(mission, numberOfMission); //��������ѣ�Ѱ�Һ�ʱ��������
			machine[i].timePaid = mission[1].timeNeed; //��ʼ����������ʱ��
			machine[i].distribution = to_string(mission[1].timeNeed); //���·������
			machine[i].numOfDistribution++; //�������������
			for (int j = 1; j <= numberOfMission - 1; j++) //ɾȥ����ɵ�����
			{
				mission[j] = mission[j + 1]; 
			}
			numberOfMission--; //��ɷ���һ�κ�������-1
		}
			
		//������ɵ�һ��������䣬�������ʣ���������
		for (int k = numberOfMission; k > 0; k--)
		{
			BuildSmallSift(machine, numberOfMachine); //��С����
			BuildBigSift(mission, numberOfMission); //�������
			machine[1].distribution += ("+" + to_string(mission[1].timeNeed)); //��¼�������
			machine[1].timePaid += mission[1].timeNeed; //���»���������ʱ��
			machine[1].numOfDistribution++; //�������������
			for (int m = 1; m < numberOfMission; m++) //����ʣ������
			{
				mission[m] = mission[m + 1];
			}
			numberOfMission--; //����ʣ��������
		}

		//���������񶼷�����Ϻ�
		if (numberOfMission == 0)
		{
			//����Ŀ����ʾ����ʽ���
			cout << endl;
			cout << "ʱ����䣺" << endl;
			for (int i = numberOfMachine; i > 0; i--)
			{
				if (machine[i].numOfDistribution > 1) 
					machine[i].distribution += ("=" + to_string(machine[i].timePaid));
				cout << "    " << machine[i].name << "������" << machine[i].distribution << endl;
			}
			cout << "�ܵĴ���ʱ����" << machine[1].timePaid << "��" << endl;
		}
	}
}
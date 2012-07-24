#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
using namespace std;
//map<int,vector<int> >g;//��Ϊ�����Ϣ������,����ı��нڵ����ӵ�״��
/*�������õ���ER���ͼ�������ۣ����������ڵ�֮����һ���������ӵĸ��ʶ�Ϊp.
  ��ˣ�һ����N���ڵ��ER���ͼ�бߵ�������һ������ֵΪp*N*(N-1��/2�����
  �������ڵ�ı�Ŵ�1��ʼ*/
struct Point{
	int x;
	int y;
};
float Prandom()//�˺�����������һ���������������Ϊ��������Ҫ�ĸ���
{
	time_t t;
	srand((unsigned)time(&t));
	int p=rand()%100;
	float q=(float)p/100;
	return q;
}
vector<Point>& CreateAll(vector<Point> &mm,int N)//�˺���������ȫ�������,��ʼ��all_mrb
{
	for(int i=1;i<=N;i++)
		for(int j=i;j<=N;j++)
		{
			if(i==j)
				continue;
			Point p;
			p.x=i;
			p.y=j;
			mm.push_back(p);
		}
		return mm;
}
vector<Point>& Createrand(vector<Point> &cc,int num)//�˺�����ʼ��rand_mrb
{
	Point p;
	p.x=0;
	p.y=0;
	for(int i=0;i<num;++i){
		cc.push_back(p);
	}
	return cc;
}
vector<Point>& RDnetwork(vector<Point> &ma,vector<Point>& mc,int number)
//�����������,ma��all_mrb,mc��rand_mrb,number���ߵ�����
{
	random_shuffle(ma.begin(),ma.end());
	for(int i=0;i<number;i++)
		mc[i]=ma[i];
	return mc;
}
void PrintIt(Point& mypoint)//ΪOutPut_vector��������
{
	cout<<"edge"<<"("<<mypoint.x<<","<<mypoint.y<<")"<<endl;
}
void OutPut_vector(vector<Point>& k,string s)//���vector�е�Ԫ��
{
	cout<<s<<endl;
	for_each(k.begin(),k.end(),PrintIt);
}
void Print_to_pajekfile(vector<Point> &s,int N)//�˺����Ѳ��������������pajek�ĸ�ʽд���ļ��У�����pajek�����ȡ����
										      //s��rand_mrb,NΪ�ڵ��ܸ�������V_number
{
	FILE *fp;
	fp=fopen("random.net","w");
	fprintf(fp,"%s %d\n","*Vertices",N);
	for (int i=1;i<=N;++i)
		fprintf(fp,"%d\n",i);
	fprintf(fp,"%s\n","*Arces");
	fprintf(fp,"%s\n","*Edges");
	for(vector<Point>::iterator ist=s.begin();ist!=s.end();++ist)
	{
		fprintf(fp,"%d %d %d\n",(*ist).x,(*ist).y,1);
	}
	fclose(fp);
}
void Print_to_txtfile(vector<Point> &q,int VN,int Edge)//�˺��������ɵ��������д������һ��txt�ļ������ڱ�ĳ���������
									   //���ľ���ϵ����ƽ��·������,VNΪ����Ľڵ���,EdgeΪ����ı���
{
	FILE *p;
	p=fopen("network.txt","w");
	fprintf(p,"%d\n",VN);
	fprintf(p,"%d\n",Edge);
	for(vector<Point>::iterator it=q.begin();it!=q.end();++it)
		fprintf(p,"%d %d\n",(*it).x,(*it).y);
	//for(vector<Point>::iterator is=q.begin();is!=q.end();++is)
		//fprintf(p,"%d %d\n",(*is).y,(*is).x);
	fclose(p);

}
int main()
{
	int V_number,V_totaledge;//V_number�ǽڵ��������V_totaledge��������������еı���
	vector<Point> all_mrb,rand_mrb;//all_mrb������е����ӹ�ϵrand_mrb��Ź����õ��������ڵ��ϵ
	//float V_proba=Prandom();//�Ķ�����
	float V_proba=0.366;
	//int V_proba;
	//cout<<"please enter the probability:"<<endl;
	//cin>>V_proba;
	cout<<"����������Ľڵ�����"<<endl;
	cin>>V_number;
	cout<<"�����������ĸ���Ϊ��"<<V_proba<<endl;
	V_totaledge=V_proba*(V_number*(V_number+1)/2);
	
	CreateAll(all_mrb,V_number);
	Createrand(rand_mrb,V_totaledge);
	//OutPut_vector(all_mrb,"print all_mrb:");
	//OutPut_vector(rand_mrb,"print rand_mrb before rand:");
	RDnetwork(all_mrb,rand_mrb,V_totaledge);
	//OutPut_vector(rand_mrb,"print rand_mrb after rand:");
	Print_to_pajekfile(rand_mrb,V_number);
	Print_to_txtfile(rand_mrb,V_number,V_totaledge);
	cout<<"����������������Ϊ��"<<V_totaledge<<endl;
	
	system("pause");
}
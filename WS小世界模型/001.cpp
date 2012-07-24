#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm> 
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <numeric>
#include <climits>
#include <functional>
#include <time.h>
#include <ctime>
#include <windows.h>
#define hang 14
using namespace std;
typedef struct node_tag{
	int vertex;
	struct node_tag *link;
}Node;
struct POINT1{
	int x;
	int y;
};
int total_vertex;
vector<POINT1> mrb;//��Ÿ�������������
vector<POINT1> mb;//����µı�ʾ�����ڵ���������
map<int,list<int> >regula;//��Ź���ͼ���ڽӱ�
int daxiao;
int ti;
int Real=3;
FILE *ptr;
FILE *pq;

void CreateNet(int N,int K,float p)//��������ͼ,��0�Žڵ㿪ʼ,K������ż��,NΪ�ڵ���
{
// 	mrb.resize(hang+1);
// 	mb.resize(hang+1);
	total_vertex=N;
	int k=K/2;
	int q=1;
	for(int qq=0;qq<N;qq++)//˳ʱ�������,���ɰ������������繹�����
	{
		POINT1 mm;
		mm.x=qq;
	for(int s=1;s<=k;s++)
	{
		if(qq+s>=N)
			mm.y=(qq+s-N)%N;
		else
		mm.y=(qq+s)%N;

		mrb.push_back(mm);
	}
	}//����������mrb�����ظ��ı����磬<1,2>,<2,1>
	daxiao=mrb.size();
	cout<<"daxiao  "<<daxiao<<endl;
	
}
void CancleEqual()//ȥ��mrb���ظ��ı�
{
	ti=0;
	for(vector<POINT1>::iterator ko=mrb.begin();ko!=mrb.end();++ko)	
		for(vector<POINT1>::iterator koo=mrb.begin();koo!=mrb.end();++koo)
		{				
			if(((*ko).x==(*koo).y)&&((*ko).y==(*koo).x))
			{				
				--daxiao;
				++ti;
			}
			else
				daxiao=daxiao;
		}
		cout<<"ti"<<ti<<endl;//�����õ�
		cout<<"daxiao2  "<<daxiao+(ti/2)<<endl;//daxiao ��������зŵĲ���ʵ�ʵı������Ѿ�ȥ�����ظ��ı���
}
void DeleteEqual()//��mrb���ظ��ı�ɾ��
{
	int qq=0;
	for(vector<POINT1>::iterator mmm=mrb.begin();mmm!=mrb.end();++mmm)
	{
		for(vector<POINT1>::iterator mms=mrb.begin();mms!=mrb.end();++mms)
		{
			if((*mmm).x==(*mms).y&&(*mmm).y==(*mms).x)
			{	
				(*mms).x=0;
				(*mms).y=0;//���ظ��ıߵ����е�һ����ֵΪ<0,0>
			}
		}		
	}
	int myqq=0;
	for(vector<POINT1>::iterator my=mrb.begin();my!=mrb.end();++my)
	{
		if(((*my).x!=0&&(*my).y!=0)||((*my).x==0&&(*my).y!=0)||((*my).y==0&&(*my).x!=0))
		mb.push_back(*my);		
	}
}

bool Pvalue(float pro)
{
	int Iten=1;
	for(int i=0;i<Real;i++)
		Iten*=10;
	float Tmp=rand()%Iten/(float)Iten;
	if(Tmp>pro)
		return false;
	else
		return true;
}
bool FindEdge(vector<POINT1> ms,int xx,int yy)//�ж��Ƿ��Ѿ����������,//�����˷���true�������ڷ���false
{
	for(vector<POINT1>::iterator shiyan=ms.begin();shiyan!=ms.end();++shiyan)
	{
		if((*shiyan).x==xx&&(*shiyan).y==yy)
			return true;
	}
	return false;

}
bool IfEqual(vector<POINT1> my)//�ж�������֪�񻹴�����<4,5>,<5,4>���������,���ھͷŻ�ture�������ھͷ���false
{
	for(vector<POINT1>::iterator msn=my.begin();msn!=my.end();++msn)
		for(vector<POINT1>::iterator ems=my.begin();ems!=my.end();++ems)
		{
			if((*msn).x==(*ems).y&&(*msn).y==(*ems).x)
				return true;
		}
		return false;
}
void Create_WS_Net(int N,int K,float pp)//����WSС��������ģ��,��p=0��ʱ��û�б䣬��p=1��ʱ��ͽӽ������������
{

	CancleEqual();//ȥ���ظ��ı�
	DeleteEqual();//ɾ���ظ��ı�
// 	//�����õ�
// 	cout<<"mrb.size"<<mrb.size()<<endl;
// 	DeleteEqual();
// 	cout<<"mrb information:";
// 	for(vector<POINT1>::iterator isoo=mrb.begin();isoo!=mrb.end();++isoo)
// 		cout<<(*isoo).x<<" "<<(*isoo).y<<"  , ";
	cout<<"mb��Ԫ��"<<endl;//mb�е�Ԫ�ؾ��Ǳ�ʾ�������еıߵ������,��������WSС����ģ��
	for(vector<POINT1>::iterator mys=mb.begin();mys!=mb.end();++mys)
		cout<<(*mys).x<<" "<<(*mys).y<<", ";
	cout<<endl;
	int k=K/2;
	float rentouma=pp;
	
	for(vector<POINT1>::iterator mysql=mb.begin();mysql!=mb.end();++mysql)
	{
		int kiss;
		if(Pvalue(pp))//����Ҫ��Ҫ�������Ŀ���
		{
			srand((unsigned)time(NULL));
		    kiss=rand()%N;			
			while(kiss==(*mysql).x||FindEdge(mb,(*mysql).x,kiss))
			{						
				kiss=rand()%N;		
			}
			(*mysql).y=kiss;
		}
	}	
	while(IfEqual(mb))
	{
		for(vector<POINT1>::iterator mysql=mb.begin();mysql!=mb.end();++mysql)
		{
			int kiss;
			if(Pvalue(pp))//����Ҫ��Ҫ�������Ŀ���
			{
				srand((unsigned)time(NULL));
				kiss=rand()%N;
				while(kiss==0)
					kiss=rand()%N;
				while(kiss==(*mysql).x||FindEdge(mb,(*mysql).x,kiss))
				{
					kiss=rand()%N;			
				}
				(*mysql).y=kiss;
			}
	}
	}

	cout<<"�������Ӻ�ıߵ������(mb��)��"<<endl;
	for(vector<POINT1>::iterator soga=mb.begin();soga!=mb.end();++soga)
		cout<<(*soga).x<<" "<<(*soga).y<<" ,";
	
	//Ϊ�˽��Pajek���ʵ�ã���ʼ�ڵ㲻��Ϊ0
	for(vector<POINT1>::iterator music=mb.begin();music!=mb.end();++music)
	{
		(*music).x=(*music).x+1;
		(*music).y=(*music).y+1;
	}
	cout<<endl;
	cout<<"��1��ʼ"<<endl;
	for(vector<POINT1>::iterator soga1=mb.begin();soga1!=mb.end();++soga1)
		cout<<(*soga1).x<<" "<<(*soga1).y<<" ,";
	ptr=fopen("Pajek.net","w");                                              //����ļ���������Ѿ�����õ�wsģ��ͼ
	fprintf(ptr,"%s %d\n","*Vertices",N);
	for(int ik=1;ik<=N;++ik)
		fprintf(ptr,"%d\n",ik);
	fprintf(ptr,"%s\n","*Arcs");
	fprintf(ptr,"%s\n","*Edges");
	for(vector<POINT1>::iterator mimi=mb.begin();mimi!=mb.end();++mimi)
		fprintf(ptr,"%d %d %d\n",(*mimi).x,(*mimi).y,1);
	fclose(ptr);

	                                                                        //���ļ���������涨�ĸ�ʽmb,Ϊ��ͼ�Ǹ�����ȥ��������
	int mf[hang+1][hang+1];//Ĭ�ϵ���ʮ���ڵ�,��Ϊ��1��ʼ
	cout<<endl;
	cout<<"mf"<<endl;
	for(int i1=0;i1<hang+1;++i1)//��ʼ��
		for(int i2=0;i2<hang+1;++i2)
			mf[i1][i2]=0;
	for(vector<POINT1>::iterator love=mb.begin();love!=mb.end();++love)
	{
		mf[(*love).x][(*love).y]=1;
		mf[(*love).y][(*love).x]=1;
	}
	pq=fopen("ws.txt","w");
	fprintf(pq,"%d\n",hang);
	for(int s1=1;s1<=hang;s1++)
		for(int s2=1;s2<=hang;s2++)
		{
			cout<<mf[s1][s2]<<" ";
			if(s2%hang==0)
				cout<<endl;
			if(s2%hang!=0)
			fprintf(pq,"%d ",mf[s1][s2]);
			if(s2%hang==0)
				fprintf(pq,"%d\n",mf[s1][s2]);
			
		}
	fclose(pq);
	//���н�������
		//Beep(1188,9111);
}
void main()
{
	int number;
	int KK;
	float probability;
	cout<<"the default vertex number is:"<<hang<<endl;
	cout<<"Please enter your K value:"<<endl;
	cin>>KK;
	cout<<"Please enter the probability:"<<endl;
	cin>>probability;

	CreateNet(hang,KK,probability);
	Create_WS_Net(hang,KK,probability);

	system("pause");
}

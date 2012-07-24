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
vector<POINT1> mrb;//存放各个点的连接情况
vector<POINT1> mb;//存放新的表示各个节点的连接情况
map<int,list<int> >regula;//存放规则图的邻接表
int daxiao;
int ti;
int Real=3;
FILE *ptr;
FILE *pq;

void CreateNet(int N,int K,float p)//建立规则图,从0号节点开始,K必须是偶数,N为节点数
{
// 	mrb.resize(hang+1);
// 	mb.resize(hang+1);
	total_vertex=N;
	int k=K/2;
	int q=1;
	for(int qq=0;qq<N;qq++)//顺时针的连线,即可把整个规则网络构建完成
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
	}//产生个问题mrb中有重复的边例如，<1,2>,<2,1>
	daxiao=mrb.size();
	cout<<"daxiao  "<<daxiao<<endl;
	
}
void CancleEqual()//去除mrb中重复的边
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
		cout<<"ti"<<ti<<endl;//测试用的
		cout<<"daxiao2  "<<daxiao+(ti/2)<<endl;//daxiao 这个变量中放的才是实际的边数，已经去除了重复的边数
}
void DeleteEqual()//把mrb中重复的边删除
{
	int qq=0;
	for(vector<POINT1>::iterator mmm=mrb.begin();mmm!=mrb.end();++mmm)
	{
		for(vector<POINT1>::iterator mms=mrb.begin();mms!=mrb.end();++mms)
		{
			if((*mmm).x==(*mms).y&&(*mmm).y==(*mms).x)
			{	
				(*mms).x=0;
				(*mms).y=0;//把重复的边的其中的一个赋值为<0,0>
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
bool FindEdge(vector<POINT1> ms,int xx,int yy)//判断是否已经有这个边了,//存在了返回true，不存在返回false
{
	for(vector<POINT1>::iterator shiyan=ms.begin();shiyan!=ms.end();++shiyan)
	{
		if((*shiyan).x==xx&&(*shiyan).y==yy)
			return true;
	}
	return false;

}
bool IfEqual(vector<POINT1> my)//判断向量中知否还存在像<4,5>,<5,4>的这种情况,存在就放回ture，不存在就返回false
{
	for(vector<POINT1>::iterator msn=my.begin();msn!=my.end();++msn)
		for(vector<POINT1>::iterator ems=my.begin();ems!=my.end();++ems)
		{
			if((*msn).x==(*ems).y&&(*msn).y==(*ems).x)
				return true;
		}
		return false;
}
void Create_WS_Net(int N,int K,float pp)//建立WS小世界网络模型,当p=0的时候没有变，当p=1的时候就接近于随机网络了
{

	CancleEqual();//去除重复的边
	DeleteEqual();//删除重复的边
// 	//测试用的
// 	cout<<"mrb.size"<<mrb.size()<<endl;
// 	DeleteEqual();
// 	cout<<"mrb information:";
// 	for(vector<POINT1>::iterator isoo=mrb.begin();isoo!=mrb.end();++isoo)
// 		cout<<(*isoo).x<<" "<<(*isoo).y<<"  , ";
	cout<<"mb中元素"<<endl;//mb中的元素就是表示的网络中的边的情况了,即建立的WS小世界模型
	for(vector<POINT1>::iterator mys=mb.begin();mys!=mb.end();++mys)
		cout<<(*mys).x<<" "<<(*mys).y<<", ";
	cout<<endl;
	int k=K/2;
	float rentouma=pp;
	
	for(vector<POINT1>::iterator mysql=mb.begin();mysql!=mb.end();++mysql)
	{
		int kiss;
		if(Pvalue(pp))//首先要是要有重连的可能
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
			if(Pvalue(pp))//首先要是要有重连的可能
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

	cout<<"重新连接后的边的情况是(mb中)："<<endl;
	for(vector<POINT1>::iterator soga=mb.begin();soga!=mb.end();++soga)
		cout<<(*soga).x<<" "<<(*soga).y<<" ,";
	
	//为了结合Pajek软件实用，开始节点不能为0
	for(vector<POINT1>::iterator music=mb.begin();music!=mb.end();++music)
	{
		(*music).x=(*music).x+1;
		(*music).y=(*music).y+1;
	}
	cout<<endl;
	cout<<"从1开始"<<endl;
	for(vector<POINT1>::iterator soga1=mb.begin();soga1!=mb.end();++soga1)
		cout<<(*soga1).x<<" "<<(*soga1).y<<" ,";
	ptr=fopen("Pajek.net","w");                                              //这个文件输出的是已经构造好的ws模型图
	fprintf(ptr,"%s %d\n","*Vertices",N);
	for(int ik=1;ik<=N;++ik)
		fprintf(ptr,"%d\n",ik);
	fprintf(ptr,"%s\n","*Arcs");
	fprintf(ptr,"%s\n","*Edges");
	for(vector<POINT1>::iterator mimi=mb.begin();mimi!=mb.end();++mimi)
		fprintf(ptr,"%d %d %d\n",(*mimi).x,(*mimi).y,1);
	fclose(ptr);

	                                                                        //往文件里面输入规定的格式mb,为了图那个程序去读数据用
	int mf[hang+1][hang+1];//默认的是十个节点,因为从1开始
	cout<<endl;
	cout<<"mf"<<endl;
	for(int i1=0;i1<hang+1;++i1)//初始化
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
	//运行结束后发声
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

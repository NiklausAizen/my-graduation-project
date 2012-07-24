#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
using namespace std;
//map<int,vector<int> >g;//作为标记信息的数组,标记文本中节点连接的状况
/*本程序用的是ER随机图构建理论：任意两个节点之间有一条边相连接的概率都为p.
  因此，一个含N个节点的ER随机图中边的总数是一个期望值为p*N*(N-1）/2的随机
  变量，节点的标号从1开始*/
struct Point{
	int x;
	int y;
};
float Prandom()//此函数用来产生一个随机数，用来作为网络所需要的概率
{
	time_t t;
	srand((unsigned)time(&t));
	int p=rand()%100;
	float q=(float)p/100;
	return q;
}
vector<Point>& CreateAll(vector<Point> &mm,int N)//此函数构造完全耦合网络,初始化all_mrb
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
vector<Point>& Createrand(vector<Point> &cc,int num)//此函数初始化rand_mrb
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
//构造随机网络,ma传all_mrb,mc传rand_mrb,number传边的数量
{
	random_shuffle(ma.begin(),ma.end());
	for(int i=0;i<number;i++)
		mc[i]=ma[i];
	return mc;
}
void PrintIt(Point& mypoint)//为OutPut_vector函数调用
{
	cout<<"edge"<<"("<<mypoint.x<<","<<mypoint.y<<")"<<endl;
}
void OutPut_vector(vector<Point>& k,string s)//输出vector中的元素
{
	cout<<s<<endl;
	for_each(k.begin(),k.end(),PrintIt);
}
void Print_to_pajekfile(vector<Point> &s,int N)//此函数把产生的随机网络以pajek的格式写入文件中，便于pajek软件读取数据
										      //s传rand_mrb,N为节点总个数，传V_number
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
void Print_to_txtfile(vector<Point> &q,int VN,int Edge)//此函数把生成的随机网络写入另外一个txt文件，便于别的程序来计算
									   //它的聚类系数与平均路径长度,VN为网络的节点数,Edge为网络的边数
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
	int V_number,V_totaledge;//V_number是节点的总数，V_totaledge是随机网络所具有的边数
	vector<Point> all_mrb,rand_mrb;//all_mrb存放所有的连接关系rand_mrb存放构建好的随机网络节点关系
	//float V_proba=Prandom();//改动部分
	float V_proba=0.366;
	//int V_proba;
	//cout<<"please enter the probability:"<<endl;
	//cin>>V_proba;
	cout<<"请输入网络的节点数："<<endl;
	cin>>V_number;
	cout<<"本次所产生的概率为："<<V_proba<<endl;
	V_totaledge=V_proba*(V_number*(V_number+1)/2);
	
	CreateAll(all_mrb,V_number);
	Createrand(rand_mrb,V_totaledge);
	//OutPut_vector(all_mrb,"print all_mrb:");
	//OutPut_vector(rand_mrb,"print rand_mrb before rand:");
	RDnetwork(all_mrb,rand_mrb,V_totaledge);
	//OutPut_vector(rand_mrb,"print rand_mrb after rand:");
	Print_to_pajekfile(rand_mrb,V_number);
	Print_to_txtfile(rand_mrb,V_number,V_totaledge);
	cout<<"产生的随机网络边数为："<<V_totaledge<<endl;
	
	system("pause");
}
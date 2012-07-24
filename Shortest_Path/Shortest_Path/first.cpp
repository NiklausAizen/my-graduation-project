#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <climits>
using namespace std;
//本程序拟用dijkstra算法来计算最短路径

int N;
int edge;
vector<list<int>> g;
vector<int> dist;//存放源节点到各点的距离
vector<int>prev;//放各点最短路径的前一节点号
vector<list<int>>& iniGraph(){//此函数从文件读取数据，返回的是一个邻接表，
	//给它的参数就是一个vector<Point>
	//类型的引用，这个类型就是我生成随机网络后，存储整个
	//网路节点关系的数据结构。
	int x;
	int y;
	FILE *rp;

	rp=fopen("StandardOutput.txt","r");
	fscanf(rp,"%d",&N);
	fscanf(rp,"%d",&edge);
	g.assign(N+1, list<int>());
	for(int i=0;i<edge*2;++i){
		fscanf(rp,"%d",&x);
		fscanf(rp,"%d",&y);
		//cout<<"x="<<x<<",  y="<<y<<endl;
		g[x].push_back(y);
	}
	g[0].push_back(-1);
	return g;
}
bool Search(list<int>& sList,int target){//此函数功能为在list<int>类型的数组里找寻数字target
	for(list<int>::iterator it=sList.begin();it!=sList.end();++it)
	{
		if((*it)==target)
			return true;
		else
			return false;
	}
}
vector<int>& BFS(int s,vector<list<int>>& g){//s为出发节点，此函数返回一个s点到各个节点的最短距离的数组
	vector<int> UnionS;//存放符合条件的节点，即已经算出最短路径的节点
	vector<int> UnionU;//存放暂时不符合要求的节点
	UnionS.push_back(s);
	int *a=(int*)malloc((N+1)*sizeof(int));

	queue<int> que;
	dist.assign(N+1,INT_MAX);//开始都假设到各点的距离为正无穷
	dist[s]=0;//源节点到自身的距离为0

	prev.resize(N+1);
	que.push(s);
	while (!que.empty())
	{
		int v=que.front();
		que.pop();
		for(list<int>::iterator it=g[v].begin();it!=g[v].end();++it){
			if(dist[*it]==INT_MAX)
			{
				dist[*it]=dist[v]+1;
				prev[*it]=v;
				que.push(*it);
			}
		}
	}
	return dist;
}
void Shrot_path_to_file(float average_path){//把生成的最短路径长度写入文件
	FILE *fpt;
	fpt=fopen("Short_path.txt","w");
	fprintf(fpt,"%f",average_path);
	fclose(fpt);
}
int main(){
	vector<list<int>> h;
	h=iniGraph();
	cout<<"vertex number:"<<N<<endl;
	cout<<"edge number:"<<edge<<endl;
	// 	for(int i=1;i<=N;++i){
	// 		cout<<"h["<<i<<"]-->";
	// 		for(list<int>::iterator it=h[i].begin();it!=h[i].end();++it)
	// 		cout<<*it<<" ";
	// 		cout<<endl;
	// 	}
	vector<int> bfs;
	int sum=0;  
	for(int feng=1;feng<=N;++feng){
		bfs=BFS(feng,g);
		for(int he=feng;he<=N;++he)
			sum=sum+bfs[he];

	}
	cout<<"sum="<<sum<<endl;
	cout<<"source number:"<<"3"<<endl;
	bfs=BFS(3,g);//节点3到各点的最短距离
	int ii=0;
	for(vector<int>::iterator her=bfs.begin();her!=bfs.end();++her,++ii)//把到各个节点的最短距离打印出来
	cout<<" "<<ii<<":"<<*her<<",";
	float average_path=sum*(N+1)/(0.5*N*(N+1)*(N-1));
	cout<<endl;
	cout<<"平均路径长度为："<<average_path<<endl;
	Shrot_path_to_file(average_path);
	float ping_jun=average_path/1.648601;
	FILE *ppt;
	ppt=fopen("pingjun.txt","w");
	fprintf(ppt,"%f",ping_jun);
	cout<<ping_jun<<endl;
	system("pause");
}

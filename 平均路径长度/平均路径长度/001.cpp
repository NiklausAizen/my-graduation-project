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
int N;
int edge;
vector<list<int> > g;                       
void Read_from_file(){
FILE *file;
file=fopen("network.txt","r");
fscanf(file,"%d",&N);
fscanf(file,"%d",&edge);
g.assign(N+1,list<int>());
int x;
int y;
g[0].push_back(0);
for(int i=1;i<=edge;i++){
	fscanf(file,"%d %d",&x,&y);
	g[x].push_back(y);
	g[y].push_back(x);
}
}
vector<int> USP(int s){
vector<int> dist; 
vector<int> prev;
queue<int> que;
dist.assign(N+1,INT_MAX);
prev.resize(N+1);
dist[s]=0;
que.push(s);
while(!que.empty()){
	int v=que.front();
	que.pop();
	for(list<int>::iterator it=g[v].begin();it!=g[v].end();++it){
		if(dist[*it]==INT_MAX){
			dist[*it]=dist[v]+1;
			prev[*it]=v;
			que.push(*it);
		}
}
	
}
return dist;
}
void main(){
Read_from_file();
float sum=0;//存放所有节点的路径和
float average_path=0;
vector<int>juli;//juli存放的是一个节点到其它各个节点之间的最短路径
for(int j=1;j<=N;++j){
juli=USP(j);
for(int i=j;i<=N;++i)
sum=sum+juli[i];
}
cout<<"sum="<<sum<<endl;
average_path=(2*sum)/(N*(N-1));
cout<<"average_degree="<<average_path<<endl;
system("pause");
}
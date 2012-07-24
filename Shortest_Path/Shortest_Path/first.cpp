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
//����������dijkstra�㷨���������·��

int N;
int edge;
vector<list<int>> g;
vector<int> dist;//���Դ�ڵ㵽����ľ���
vector<int>prev;//�Ÿ������·����ǰһ�ڵ��
vector<list<int>>& iniGraph(){//�˺������ļ���ȡ���ݣ����ص���һ���ڽӱ�
	//�����Ĳ�������һ��vector<Point>
	//���͵����ã�������;����������������󣬴洢����
	//��·�ڵ��ϵ�����ݽṹ��
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
bool Search(list<int>& sList,int target){//�˺�������Ϊ��list<int>���͵���������Ѱ����target
	for(list<int>::iterator it=sList.begin();it!=sList.end();++it)
	{
		if((*it)==target)
			return true;
		else
			return false;
	}
}
vector<int>& BFS(int s,vector<list<int>>& g){//sΪ�����ڵ㣬�˺�������һ��s�㵽�����ڵ����̾��������
	vector<int> UnionS;//��ŷ��������Ľڵ㣬���Ѿ�������·���Ľڵ�
	vector<int> UnionU;//�����ʱ������Ҫ��Ľڵ�
	UnionS.push_back(s);
	int *a=(int*)malloc((N+1)*sizeof(int));

	queue<int> que;
	dist.assign(N+1,INT_MAX);//��ʼ�����赽����ľ���Ϊ������
	dist[s]=0;//Դ�ڵ㵽����ľ���Ϊ0

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
void Shrot_path_to_file(float average_path){//�����ɵ����·������д���ļ�
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
	bfs=BFS(3,g);//�ڵ�3���������̾���
	int ii=0;
	for(vector<int>::iterator her=bfs.begin();her!=bfs.end();++her,++ii)//�ѵ������ڵ����̾����ӡ����
	cout<<" "<<ii<<":"<<*her<<",";
	float average_path=sum*(N+1)/(0.5*N*(N+1)*(N-1));
	cout<<endl;
	cout<<"ƽ��·������Ϊ��"<<average_path<<endl;
	Shrot_path_to_file(average_path);
	float ping_jun=average_path/1.648601;
	FILE *ppt;
	ppt=fopen("pingjun.txt","w");
	fprintf(ppt,"%f",ping_jun);
	cout<<ping_jun<<endl;
	system("pause");
}

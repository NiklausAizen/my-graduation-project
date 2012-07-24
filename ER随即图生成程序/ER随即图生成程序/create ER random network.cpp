#include <iostream>
#include <vector>
#include <list>
#include <Windows.h>
#include <time.h>
using namespace std;
vector<list<int>> g;//邻接表存储网络
vector<float> pp;//存放概率的向量
int edge;
struct p_point{
	int x;
	int y;
};
vector<p_point> con;//为了方便写入文件
int create_random(int c_begin,int c_end){//产生从c_begin到c_end之间的任意正数,包括c_begin和c_end
	time_t t;
	Sleep(500);
	srand((unsigned)time(&t));
	int kiss=rand()%(c_end-c_begin+1)+c_begin;
	return kiss;
}
int create_random_also(int cc_begin,int cc_end){
	time_t t;
	Sleep(200);
	srand((unsigned)time(&t));
	int kiss=rand()%(cc_begin-cc_end+1)+cc_begin;
	return kiss;
}
p_point create_different(int diff_begin,int diff_end){//产生两个从diff_begin到diff_end之间的数，包括
													  //包括diff_begin和diff_end,并且保证两者不同
	p_point pc;
	pc.x=create_random(diff_begin,diff_end);
	int cp=0;
	do 
	{
		cp=create_random_also(diff_begin,diff_end);
	} while (pc.x==cp);
	pc.y=cp;
	return pc;
}
void Read_python_file(int edge)//pp向量用来存放程序所需要的概率，从python文件中生成的,pp为全局变量
{
	FILE *ptr;
	float a;
	ptr=fopen("random.txt","r");
	for(int i=0;i<edge;i++)
	{
		fscanf(ptr,"%f",&a);
		pp.push_back(a);
	}
	
}
bool Find_in_network(int a,int b){//查找b是否已经和a相连接了，连接了返回true，反之返回false
	for(list<int>::iterator it=g[a].begin();it!=g[a].end();++it){
		if((*it)==b)
			return true;
	}
	return false;
}
void Create_ER_random(int N,float p){//产生的概率如果比我手动输入的概率小的话就连接
g.assign(N+1,list<int>());
g[0].push_back(0);
edge=p*N*(N-1)/2;
cout<<"the edge of the network is:"<<edge;
Read_python_file(65534);
int ii=0;//概率向量指示器
int c=0;
p_point node;
int i=0;//节点指示器
while(i<edge){//在成功加入一个节点后，把i的值加1
node=create_different(1,N);
while(!Find_in_network(node.x,node.y)&&pp[ii]<p&&i<N+1){
	g[node.x].push_back(node.y);
	g[node.y].push_back(node.x);
	con.push_back(node);
	i++;
	c=ii;
	ii++;
}
if(Find_in_network(node.x,node.y)||pp[c]>p){
	ii++;
}
if(ii>=65535)
cout<<"out of probabily range,please try again,thank you"<<endl;
}
}
void Show_ERnetwork(int N){//此函数把邻接表中的元素输出到屏幕上
	cout<<endl;
	for(int i=1;i<=N;++i){
		cout<<"g["<<i<<"]-->";
		for(list<int>::iterator it=g[i].begin();it!=g[i].end();++it)
			cout<<*it<<" ";
		cout<<endl;
	}
}
void Write_to_pajek_file(int N){//这个模块儿在后面的很多程序中都会用到，功能是把生成的网络写入到pajek软件中
FILE *file;
file=fopen("ERrandom.net","w");
fprintf(file,"%s %d\n","*Vertices",N);
for(int i=1;i<=N;i++){
	fprintf(file,"%d\n",i);
}
fprintf(file,"%s\n","*Arces");
fprintf(file,"%s\n","*Edges");
for(vector<p_point>::iterator it=con.begin();it!=con.end();++it){
		fprintf(file,"%d %d %d\n",(*it).x,(*it).y,1);
		fprintf(file,"%d %d %d\n",(*it).y,(*it).x,1);
	}
fclose(file);
}
void Wrige_to_txt_file(int n){
	FILE *file;
	file=fopen("network.txt","w");
	fprintf(file,"%d\n",n);
	fprintf(file,"%d\n",edge);
	for(vector<p_point>::iterator it=con.begin();it!=con.end();++it){
		fprintf(file,"%d %d\n",(*it).x,(*it).y);
	}
	fclose(file);
}
void main(){
	int V_number;
	float p_ER;
	cout<<"please enter the vertex number:"<<endl;
	cin>>V_number;
	cout<<"please enter the probability:"<<endl;
	cin>>p_ER;
	Create_ER_random(V_number,p_ER);
	Write_to_pajek_file(V_number);
	Show_ERnetwork(V_number);
	
	system("pause");
}
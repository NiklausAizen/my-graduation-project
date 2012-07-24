#include<iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
using namespace std;
int N;//网络的节点数
int edge;//网络的边数
vector<float> pp;//存放概率的向量
struct p_point{
	int x;
	int y;
};
vector<p_point>m;//存放网络
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
void Read_from_network(){//此函数从生成的规则近邻网络中读取数据
FILE *from;
from=fopen("network.txt","r");
fscanf(from,"%d",&N);
fscanf(from,"%d",&edge);
cout<<"the number of edge is:"<<edge<<endl;
for(int i=1;i<=edge;i++){
	p_point node;
	fscanf(from,"%d %d",&(node.x),&(node.y));
	m.push_back(node);
}
}
void show_m(){//显示出构建的网络
	for(vector<p_point>::iterator it=m.begin();it!=m.end();++it)
		cout<<(*it).x<<" "<<(*it).y<<endl;
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
bool Find_in_network(int a,int b){//已经连接返回true，反之返回false
	for(vector<p_point>::iterator it=m.begin();it!=m.end();++it){
		if(((a==(*it).x)&&(b==(*it).y))||((a==(*it).y)&&(b==(*it).x)))
			return true;
	}
	return false;
}
void Create_NW_network(float p,int edgenumber){//p是由用户给定概率，如果产生的概率小于用户给定的概率就连接，边数给定
Read_python_file(65534);
int i=0;
int ii=0;
int c=0;
p_point node;
while(i<edgenumber){//在成功加入一个节点后，把i的值加1
	node=create_different(1,N);
	while(!Find_in_network(node.x,node.y)&&pp[ii]<p&&i<edgenumber){
		i++;
		c=ii;
		ii++;
		m.push_back(node);

	}
	if(Find_in_network(node.x,node.y)||pp[c]>p){
		ii++;
	}
	if(ii>=65535)
		cout<<"out of probabily range,please try again,thank you"<<endl;
}
}
void Write_to_pajek(){
FILE *file;
file=fopen("net_old.net","w");
fprintf(file,"%s %d\n","*Vertices",N);
for(int i=1;i<=N;i++){
	fprintf(file,"%d\n",i);
}
fprintf(file,"%s\n","*Arces");
fprintf(file,"%s\n","*Edges");
for(vector<p_point>::iterator it=m.begin();it!=m.end();++it){
	fprintf(file,"%d %d %d\n",(*it).x,(*it).y,1);
	fprintf(file,"%d %d %d\n",(*it).y,(*it).x,1);
}
fclose(file);
}
void Write_to_pajek1(){
	FILE *file;
	file=fopen("net_new.net","w");
	fprintf(file,"%s %d\n","*Vertices",N);
	for(int i=1;i<=N;i++){
		fprintf(file,"%d\n",i);
	}
	fprintf(file,"%s\n","*Arces");
	fprintf(file,"%s\n","*Edges");
	for(vector<p_point>::iterator it=m.begin();it!=m.end();++it){
		fprintf(file,"%d %d %d\n",(*it).x,(*it).y,1);
		fprintf(file,"%d %d %d\n",(*it).y,(*it).x,1);
	}
	fclose(file);
}
void main(){
	Read_from_network();
	show_m();
	Write_to_pajek();
	float p;
	int Nnumber;
	cout<<"please enter the probability:"<<endl;
	cin>>p;
	cout<<"please enter the number of edge:"<<endl;
	cin>>Nnumber;
	Create_NW_network(p,Nnumber);
	Write_to_pajek1();
	system("pause");
}
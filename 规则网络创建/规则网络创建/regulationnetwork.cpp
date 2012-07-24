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
using namespace std;
struct p_point{
	int x;
	int y;
};
int c;//���ڱ���
vector<p_point> mrb;//�������,<2,3>,<3,2>������mrb��ֻ���һ����λ
void Create_regulation_network(int n){//����K/2������
	for(int i=0;i<n;i++){
		p_point vertex;
		p_point vertex1;
		vertex.x=i;
		vertex.y=(i+1)%n;
		vertex1.x=i;
		vertex1.y=(i+2)%n;
		mrb.push_back(vertex);
		mrb.push_back(vertex1);
	}
}
void Write_to_pajek_file(int N){//���ģ����ں���ĺܶ�����ж����õ��������ǰ����ɵ�����д�뵽pajek�����
	FILE *file;
	file=fopen("regulation.net","w");
	fprintf(file,"%s %d\n","*Vertices",N);
	for(int i=1;i<=N;i++){
		fprintf(file,"%d\n",i);
	}
	fprintf(file,"%s\n","*Arces");
	fprintf(file,"%s\n","*Edges");
	for(vector<p_point>::iterator it=mrb.begin();it!=mrb.end();++it){
		fprintf(file,"%d %d %d\n",(*it).x+1,(*it).y+1,1);
		fprintf(file,"%d %d %d\n",(*it).y+1,(*it).x+1,1);
	}
	fclose(file);
}
void Write_to_file(int N){//����������ӹ�ϵд���ļ��� 
	FILE *txtfile;
	txtfile=fopen("network.txt","w");
	fprintf(txtfile,"%d\n",N);
	fprintf(txtfile,"%d\n",mrb.size());
	for(vector<p_point>::iterator it=mrb.begin();it!=mrb.end();++it){
		fprintf(txtfile,"%d %d\n",(*it).x+1,(*it).y+1);
	}
	fclose(txtfile);

}
// void Cal_degree(){
// 	vector<int> ever;
// 	int sum=0;
// 	ever.reserve(0);
// 	for(vector<p_point>::iterator ism=mrb.begin();ism!=mrb.end();++ism){
// 		ever[(*ism).x]++;
// 		ever[(*ism).y]++;
// 	}
// 	for(vector<int>::iterator it=ever.begin();it!=ever.end();++it){
// 		sum+=(*it);
// 	}
// 	cout<<sum<<endl;
// }
void main(){
	cout<<"please enter the number of vertex:"<<endl;
	int N;
	cin>>N;
	Create_regulation_network(N);
	Write_to_pajek_file(N);
	Write_to_file(N);
	cout<<"the number of edge is:"<<mrb.size()<<endl;
	//Cal_degree();
	system("pause");
}
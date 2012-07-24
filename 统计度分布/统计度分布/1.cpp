#include <iostream>
#include <vector>
using namespace std;
struct p_point{
	int x;
	int y;
};
vector<p_point> m3;
vector<int> degree;
int N;
int edge;
void Read_from_file(){
	FILE *ps;
	ps=fopen("network.txt","r");
	fscanf(ps,"%d",&N);
	fscanf(ps,"%d",&edge);
	for(int i=1;i<=edge;i++){
		p_point node;
		fscanf(ps,"%d %d",&(node.x),&(node.y));
		m3.push_back(node);
	}
	fclose(ps);
}
void print_xing(int n){
	int i=1;
	while (i<=n)
	{
		cout<<" *";
		i++;
	}
	cout<<endl;
}
void cal_degree(){
	degree.assign(N+1,0);
	int c=0;
	int d=0;
	int sum=0;
	degree[0]=0;
	for(vector<p_point>::iterator it=m3.begin();it!=m3.end();++it){
		degree[(*it).x]++;
		degree[(*it).y]++;
	}
	for(vector<int>::iterator its=degree.begin();its!=degree.end();++its){
		cout<<"v["<<c<<"]="<<*its<<", ";
		c++;
	}
	for(vector<int>::iterator itss=degree.begin();itss!=degree.end();++itss){
		printf("%5d",d);
		print_xing(*itss);
		d++;
	}
	for(vector<int>::iterator im=degree.begin();im!=degree.end();++im){
		sum=sum+(*im);
	}
	cout<<"sum_degree="<<sum<<endl;
}
void main(){
	Read_from_file();
	cal_degree();
		system("pause");
}
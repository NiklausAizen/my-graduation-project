#include <iostream>
#include <vector>
#include <list>
#include <math.h>
using namespace std;
int N;
int edge;
struct p_point{
	int x;
	int y;
};
vector<p_point>mcb;
void Read_from_file(){
FILE *file;
file=fopen("network.txt","r");
fscanf(file,"%d",&N);
fscanf(file,"%d",&edge);
for(int i=1;i<=edge;i++)
{
	p_point node;
	fscanf(file,"%d %d",&(node.x),&(node.y));
	mcb.push_back(node);
}
fclose(file);
}
vector<int> every_degree;//���ÿ���ڵ�Ķ�,every_degree[1]����ڵ�1�Ķ�
int Find_max_degree(){//�ҳ����������Ķ�
	Read_from_file();
	every_degree.assign(N+1,0);
	for(vector<p_point>::iterator it=mcb.begin();it!=mcb.end();++it){
		every_degree[(*it).x]++;
		every_degree[(*it).y]++;
	}
	int max_degree=0;
	for(vector<int>::iterator is=every_degree.begin();is!=every_degree.end();++is){
		if((*is)>max_degree)
			max_degree=(*is);
	}
	return max_degree;
}
float find_cal_degree(int a){//��every_degree��Ѱ�Ҷ�Ϊa�Ľڵ����	
	float degree_number=0;
	for(vector<int>::iterator is=every_degree.begin();is!=every_degree.end();++is){
			if((*is)==a)
				degree_number++;
	}
	return degree_number;
}
float Cal_degree(){//���صľ���g���飬���������ص�ֵ
int m_max_degree=Find_max_degree();//���Ķ�
vector<float> old_shang;//��ŵ��Ƕ�Ϊ������Ľڵ�ĸ���
vector<float> new_shang;
old_shang.assign(m_max_degree,0.0);//�����ж�Ϊ0�Ľڵ����
new_shang.assign(m_max_degree,0.0);//�����Ժ������
for(int c=0;c<m_max_degree;c++){
	old_shang[c]=find_cal_degree(c);
}
float sum=0;//��ĸ
for(vector<float>::iterator im=old_shang.begin();im!=old_shang.end();++im){
	sum=sum+(*im);
}
for(int cc=0;cc<old_shang.size();++cc){
	new_shang[cc]=old_shang[cc]/sum;
}
float recent_shang=0.0;
for(int ii=0;ii<new_shang.size();++ii){
	recent_shang=recent_shang+new_shang[ii]*(log10(new_shang[ii]+0.0001)/log10(2.0));
}
return recent_shang;
}
void main(){
	float abc=-Cal_degree();
	cout<<abc<<endl;
	system("pause");
}
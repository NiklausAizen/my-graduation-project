	#include <iostream>
	#include <vector>
	#include <list>
	#include <algorithm>
	using namespace std;
	//本程序演示NW小世界模型的逆向演化
	int N_number;//网络的节点数
	int N_edge;//网络的边数
	vector<list<int>> g;//邻接表存储的网络，通过读取文件对其进行初始化
	vector<list<int>> regular;//存放演化结束后的网络
	struct p_point 
	{
		int x;
		int y;
	};
	void Init_network(){//初始化网络
		FILE *ptr;
		int x,y;
		ptr=fopen("StandardOutput.txt","r");
		fscanf(ptr,"%d",&N_number);
		fscanf(ptr,"%d",&N_edge);
		g.assign(N_number+1,list<int>());//第二个参数是存储的类型
		for(int i=0;i<N_edge*2;++i){
			fscanf(ptr,"%d",&x);
			fscanf(ptr,"%d",&y);
			cout<<"x="<<x<<",y="<<y<<endl;
			g[x].push_back(y);
		}
		g[0].push_back(-1);
	}
	int main(void)
	{
		Init_network();
		system("pause");
		return 0;
	}
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string.h>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

#define random(x) rand()%(x)
#define SIZE 3			// 设定数码问题的规模，SIZE = 3 时为8数码问题，SIZE = 4 时为15数码问题
#define KEY  4			// KEY = 1、2、3、4 时分别对应四个不同的估价函数
int global_count = 0;	// 记录所遍历的情况总数
int max_depth = -1;		// 设置起始深度
void init();			// 对参数值进行初始化
void move();			// 每一次调用都相当于一次扩展
void ShowMap(vector<vector<int> > NumberMap);	// 输出显示扩展情况
int  estimate(vector<vector<int> > NumberMap);	// 求出当前情况下的评价值
int getReverse(vector<vector<int> > NumberMap);	// 求出当前数码序列对应的逆序数
void swap(int x, int y, vector<vector<int> >& NumberMap);	// 交换数码序列中的两个值
vector < vector<int> >aim8 = { {1,2,3}, {4,5,6}, {7,8,0} };							// 规定8数码问题的目标情况
vector < vector<int> >aim16 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12},{13,14,15,0} };	// 规定15数码问题的目标情况

// 节点类
class Node {
public:
	vector<vector<int> > numbermap;	// 存储当前数码盘的状态
	int estimation;					// 当前状态对应的估价值
	int depth;						// 达到当前状态所需要的步数
	int last;						// 记录父节点的位置
	Node(vector<vector<int> > vec) {		// 构造函数
		numbermap = vec; estimation = estimate(numbermap);
	}
	void setEstimation() {					// 根据当前状态求得估价值
		estimation = depth + estimate(numbermap);
	}
	bool operator==(const Node& b) {		// 重载==判断符
		if (numbermap == b.numbermap)return true;
		return false;
	}
};
vector<Node> openList;				// 存储已经生成还未拓展的节点
vector<Node> closeList;				// 存储已经拓展过的节点
bool cmp(Node n1, Node n2) {
	return n1.estimation < n2.estimation;
}

int main() {
	init(); 
	move();
	system("pause");
	return 0;
}

void init() {
	vector<vector<int> > NumberMap;
	if (SIZE == 3) {
		NumberMap = { {1,3,6}, {7,4,2}, {0,5,8} };
	}
	else if (SIZE == 4) {
		NumberMap = { {1,6,2,3}, {5,10,7,4}, {13,9,11,8},{14,0,15,12} };
	}
	/* 该段代码用于生成随机8数码或15数码
	for (int i = 0; i < SIZE; i++) {
		vector<int> vec(SIZE, 0);
		NumberMap.push_back(vec);
	}
	int zero, flag[SIZE*SIZE] = { 0 }, n = SIZE * SIZE - 1;
	while (n >= 0) {
		int pos = random(SIZE*SIZE);
		while(flag[pos]==1)pos = random(SIZE*SIZE);
		if (n == 0)zero = pos;
		NumberMap[pos / SIZE][pos%SIZE] = n;
		flag[pos] = 1;
		n--;
	}
	swap(zero, SIZE*SIZE / 2, NumberMap);*/
	Node new_node(NumberMap);
	new_node.depth = 0;
	new_node.setEstimation();
	openList.push_back(new_node);
	openList[0].last = -1;
}
void ShowMap(vector<vector<int> > NumberMap) {
	printf("Realtime Status:\n\n");
	for (int i = 0; i < SIZE; i++)
	{	
		for (int j = 0; j < SIZE; j++)
		{
			printf("%3d", NumberMap[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void move() {
	global_count++;						// 统计遍历的情况的个数
	if (openList.size() == 0) {			// 若openList表为空则说明未找到合适的路径
		printf("Fail!");
		return;
	}
	vector<vector<int> > NumberMap = openList[0].numbermap;	// 每次在排序好的openList中取estimation最小的节点进行扩展
	NumberMap = openList[0].numbermap;
	ShowMap(NumberMap);
	if (max_depth < openList[0].depth)max_depth = openList[0].depth;// 记录遍历中所能达到的最深的深度
	printf("depth = %2d -- estimation = %2d -- count = %3d\n", openList[0].depth, openList[0].estimation, global_count);
	printf("----------------------------------------------\n");
	if ((SIZE == 3 && openList[0].numbermap == aim8)||(SIZE == 4 && openList[0].numbermap == aim16)) { // 根据SIZE判断结束的条件
		printf("\nSuccess! The root is shown beneath.\n\n");// 若满足成功的条件则回溯查询路径
		Node lastNode = openList[0];
		stack<Node> root;									// 利用stack对结果进行保存
		while (lastNode.last != -1) {
			root.push(lastNode);
			lastNode = closeList[lastNode.last];
		}
		int count = 1;
		while (root.size() > 0) {
			printf("Step = %2d:\n", count++);
			ShowMap(root.top().numbermap);
			printf("estimation = %2d:\n", root.top().estimation);
			root.pop();
		}
		printf("---------------max_depth = %2d----------------\n",max_depth);
		printf("----------------Programm End!-----------------\n\n");
		return;
	}

	int pos = 0;		
	while (NumberMap[pos / SIZE][pos % SIZE] != 0)pos++;// 记录数码序列中0的位置pos
	int x = pos / SIZE, y = pos % SIZE;					// 求出数字0的行和列
	closeList.push_back(openList[0]);					// 将已经扩展的节点加入closeList表
	if (x > 0) {										// 根据实际情况，最多每个节点有四个可以拓展的情况
		swap(pos, pos - SIZE, NumberMap);
		Node new_node(NumberMap);						// 记录新节点的状态
		new_node.depth = openList[0].depth + 1;			// 修改新节点的深度，为父节点的深度+1
		new_node.setEstimation();						// 设置新节点的评价函数值，最终的结果为当前节点的深度与估价函数的值
		new_node.last = closeList.size()-1;				// 设置新节点的父节点
		vector<Node>::iterator ivec = find(closeList.begin(), closeList.end(), new_node);	
		if (ivec == closeList.end()) {					// 若该节点不在closeList中则进行拓展，否则跳过
			openList.push_back(new_node);
		}
		swap(pos, pos - SIZE, NumberMap);
	}
	if (x < SIZE-1) {									// 情况同上
		swap(pos, pos + SIZE, NumberMap);
		Node new_node(NumberMap);
		new_node.depth = openList[0].depth + 1;
		new_node.setEstimation();
		new_node.last = closeList.size() - 1;
		vector<Node>::iterator ivec = find(closeList.begin(), closeList.end(), new_node);
		if (ivec == closeList.end()) {
			openList.push_back(new_node);
		}
		swap(pos, pos + SIZE, NumberMap);
	}
	if (y > 0) {										// 情况同上
		swap(pos, pos - 1, NumberMap);
		Node new_node(NumberMap);
		new_node.depth = openList[0].depth + 1;
		new_node.setEstimation();
		new_node.last = closeList.size() - 1;
		vector<Node>::iterator ivec = find(closeList.begin(), closeList.end(), new_node);
		if (ivec == closeList.end()) {
			openList.push_back(new_node);
		}
		swap(pos, pos - 1, NumberMap);
	}
	if (y < SIZE-1) {									// 情况同上
		swap(pos, pos + 1, NumberMap);
		Node new_node(NumberMap);
		new_node.depth = openList[0].depth +1;
		new_node.setEstimation();
		new_node.last = closeList.size() - 1;
		vector<Node>::iterator ivec = find(closeList.begin(), closeList.end(), new_node);
		if (ivec == closeList.end()) {
			openList.push_back(new_node);
		}
		swap(pos, pos + 1, NumberMap);
	}
	openList.erase(openList.begin());					// 在openList中删除已经扩展过的节点
	sort(openList.begin(), openList.end(), cmp);		// 对现在openList表中的节点进行排序
	move();												// 继续进行判断
}
void swap(int x, int y, vector<vector<int> > &NumberMap) {	// 交换函数
	int ox = x / SIZE, oy = x % SIZE, nx = y / SIZE, ny = y % SIZE;
	NumberMap[ox][oy] += NumberMap[nx][ny];
	NumberMap[nx][ny] = NumberMap[ox][oy] - NumberMap[nx][ny];
	NumberMap[ox][oy] -= NumberMap[nx][ny];
}
int  estimate(vector<vector<int> > NumberMap) {			// 评价函数求值
	int es = 0;
	switch (KEY)										// 根据设置的KEY值选择对应的评价函数
	{
	case 1:
		/* 评价函数1：每个数字距离合适位置的距离之和作为评价依据 */
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) 
				if (NumberMap[i][j] != i*SIZE+j+1) {
					es += abs(i - (NumberMap[i][j]-1)/SIZE);
					es += abs(j - (NumberMap[i][j]-1)%SIZE);
				}break;
	case 2:
		/* 评价函数2：每个数字是否在正确的位置 */
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (NumberMap[i][j] != i*SIZE+j+1) {
					es++;
				}break;
	case 3:
		/* 评价函数3：判断八数码的逆序数 */
		es = getReverse(NumberMap);
		break;
	case 4:
		/* 评价函数4：判断八数码的逆序数并与数字是否在正确位置判断结果相加 */
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (NumberMap[i][j] != i * SIZE + j + 1) {
					es += abs(i - (NumberMap[i][j] - 1) / SIZE);
					es += abs(j - (NumberMap[i][j] - 1) % SIZE);
				}
		es += getReverse(NumberMap);
		break;
	default:
		break;
	}
	return es;
}
// 获取NumberMap的逆序数
int getReverse(vector<vector<int> > NumberMap) {
	int pos = 1, ans = 0;
	for (; pos < SIZE*SIZE; pos++)
	{
		for (int j = pos - 1; j >= 0; j--) {
			if (NumberMap[j / SIZE][j%SIZE] > NumberMap[pos / SIZE][pos%SIZE]) {
				ans++;
			}
		}
	}
	return ans;
}

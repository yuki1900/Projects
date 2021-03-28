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
#define SIZE 3			// �趨��������Ĺ�ģ��SIZE = 3 ʱΪ8�������⣬SIZE = 4 ʱΪ15��������
#define KEY  4			// KEY = 1��2��3��4 ʱ�ֱ��Ӧ�ĸ���ͬ�Ĺ��ۺ���
int global_count = 0;	// ��¼���������������
int max_depth = -1;		// ������ʼ���
void init();			// �Բ���ֵ���г�ʼ��
void move();			// ÿһ�ε��ö��൱��һ����չ
void ShowMap(vector<vector<int> > NumberMap);	// �����ʾ��չ���
int  estimate(vector<vector<int> > NumberMap);	// �����ǰ����µ�����ֵ
int getReverse(vector<vector<int> > NumberMap);	// �����ǰ�������ж�Ӧ��������
void swap(int x, int y, vector<vector<int> >& NumberMap);	// �������������е�����ֵ
vector < vector<int> >aim8 = { {1,2,3}, {4,5,6}, {7,8,0} };							// �涨8���������Ŀ�����
vector < vector<int> >aim16 = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12},{13,14,15,0} };	// �涨15���������Ŀ�����

// �ڵ���
class Node {
public:
	vector<vector<int> > numbermap;	// �洢��ǰ�����̵�״̬
	int estimation;					// ��ǰ״̬��Ӧ�Ĺ���ֵ
	int depth;						// �ﵽ��ǰ״̬����Ҫ�Ĳ���
	int last;						// ��¼���ڵ��λ��
	Node(vector<vector<int> > vec) {		// ���캯��
		numbermap = vec; estimation = estimate(numbermap);
	}
	void setEstimation() {					// ���ݵ�ǰ״̬��ù���ֵ
		estimation = depth + estimate(numbermap);
	}
	bool operator==(const Node& b) {		// ����==�жϷ�
		if (numbermap == b.numbermap)return true;
		return false;
	}
};
vector<Node> openList;				// �洢�Ѿ����ɻ�δ��չ�Ľڵ�
vector<Node> closeList;				// �洢�Ѿ���չ���Ľڵ�
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
	/* �öδ��������������8�����15����
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
	global_count++;						// ͳ�Ʊ���������ĸ���
	if (openList.size() == 0) {			// ��openList��Ϊ����˵��δ�ҵ����ʵ�·��
		printf("Fail!");
		return;
	}
	vector<vector<int> > NumberMap = openList[0].numbermap;	// ÿ��������õ�openList��ȡestimation��С�Ľڵ������չ
	NumberMap = openList[0].numbermap;
	ShowMap(NumberMap);
	if (max_depth < openList[0].depth)max_depth = openList[0].depth;// ��¼���������ܴﵽ����������
	printf("depth = %2d -- estimation = %2d -- count = %3d\n", openList[0].depth, openList[0].estimation, global_count);
	printf("----------------------------------------------\n");
	if ((SIZE == 3 && openList[0].numbermap == aim8)||(SIZE == 4 && openList[0].numbermap == aim16)) { // ����SIZE�жϽ���������
		printf("\nSuccess! The root is shown beneath.\n\n");// ������ɹ�����������ݲ�ѯ·��
		Node lastNode = openList[0];
		stack<Node> root;									// ����stack�Խ�����б���
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
	while (NumberMap[pos / SIZE][pos % SIZE] != 0)pos++;// ��¼����������0��λ��pos
	int x = pos / SIZE, y = pos % SIZE;					// �������0���к���
	closeList.push_back(openList[0]);					// ���Ѿ���չ�Ľڵ����closeList��
	if (x > 0) {										// ����ʵ����������ÿ���ڵ����ĸ�������չ�����
		swap(pos, pos - SIZE, NumberMap);
		Node new_node(NumberMap);						// ��¼�½ڵ��״̬
		new_node.depth = openList[0].depth + 1;			// �޸��½ڵ����ȣ�Ϊ���ڵ�����+1
		new_node.setEstimation();						// �����½ڵ�����ۺ���ֵ�����յĽ��Ϊ��ǰ�ڵ���������ۺ�����ֵ
		new_node.last = closeList.size()-1;				// �����½ڵ�ĸ��ڵ�
		vector<Node>::iterator ivec = find(closeList.begin(), closeList.end(), new_node);	
		if (ivec == closeList.end()) {					// ���ýڵ㲻��closeList���������չ����������
			openList.push_back(new_node);
		}
		swap(pos, pos - SIZE, NumberMap);
	}
	if (x < SIZE-1) {									// ���ͬ��
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
	if (y > 0) {										// ���ͬ��
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
	if (y < SIZE-1) {									// ���ͬ��
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
	openList.erase(openList.begin());					// ��openList��ɾ���Ѿ���չ���Ľڵ�
	sort(openList.begin(), openList.end(), cmp);		// ������openList���еĽڵ��������
	move();												// ���������ж�
}
void swap(int x, int y, vector<vector<int> > &NumberMap) {	// ��������
	int ox = x / SIZE, oy = x % SIZE, nx = y / SIZE, ny = y % SIZE;
	NumberMap[ox][oy] += NumberMap[nx][ny];
	NumberMap[nx][ny] = NumberMap[ox][oy] - NumberMap[nx][ny];
	NumberMap[ox][oy] -= NumberMap[nx][ny];
}
int  estimate(vector<vector<int> > NumberMap) {			// ���ۺ�����ֵ
	int es = 0;
	switch (KEY)										// �������õ�KEYֵѡ���Ӧ�����ۺ���
	{
	case 1:
		/* ���ۺ���1��ÿ�����־������λ�õľ���֮����Ϊ�������� */
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) 
				if (NumberMap[i][j] != i*SIZE+j+1) {
					es += abs(i - (NumberMap[i][j]-1)/SIZE);
					es += abs(j - (NumberMap[i][j]-1)%SIZE);
				}break;
	case 2:
		/* ���ۺ���2��ÿ�������Ƿ�����ȷ��λ�� */
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (NumberMap[i][j] != i*SIZE+j+1) {
					es++;
				}break;
	case 3:
		/* ���ۺ���3���жϰ������������ */
		es = getReverse(NumberMap);
		break;
	case 4:
		/* ���ۺ���4���жϰ���������������������Ƿ�����ȷλ���жϽ����� */
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
// ��ȡNumberMap��������
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

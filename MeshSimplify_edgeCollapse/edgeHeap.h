#ifndef EDGEHEAP_H
#define EDGEHEAP_H
#include "config.h"
#include "edge.h"
#include <queue>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
class EdgeHeap
{
public:
	EdgeHeap(void);
	~EdgeHeap(void);
	struct cmp {
		bool operator() (Edge X, Edge Y) {
			return X.deltaV > Y.deltaV;
		}
	};
	std::priority_queue<Edge, std::vector<Edge>, cmp> pq;//���ڱ���ߣ���������С��������
	map<pair<int, int>, int> mapEdgeToID;//�������㵽�ߵ�ӳ���ϵ
	bool isDeleted[Config::MAX_EDGE_NUM + 1];//�����Щ�߱�ɾ��
	int cntEdge;//������
	void addEdge(Edge&);//�ӱ�
	void delEdge(Edge);//ɾ��
	Edge getMinDelta();//ɾ�������С�ı�
};
#endif

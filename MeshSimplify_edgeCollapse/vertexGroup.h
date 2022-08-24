#ifndef VERTEXGROUP_H
#define VERTEXGROUP_H
#include "vertex.h"
#include "config.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//���ж���
class VertexGroup
{
public:
	VertexGroup(void);
	~VertexGroup(void);
	Vertex group[Config::MAX_POINT_NUM];//ǧ��ע���������[1,cntVectex];
	int cntVertex;
	bool* isDeleted;//�ж�ĳ�������Ƿ��Ѿ���ɾ��
	int addVertex(Vertex);//��group������һ������,ͬʱ����cnt��¼�˽ڵ�id�������¼���Ľ��id
	void delVertex(int);//��group��ɾ��id���㣬��ʵ����isexist�д���
	int getCommonVertexNum(int, int);
};
#endif

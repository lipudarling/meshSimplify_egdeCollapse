#ifndef VERTEX_H
#define VERTEX_H
#include "config.h"
#include "myVec3d.h"
#include <vector>
#include <set>
//������
class Vertex
{
public:
	Vertex(void);
	Vertex(MyVec3d);
	Vertex(double, double, double);
	~Vertex(void);

	int id;//������
	MyVec3d pos;//��������λ��
	std::set<int> connectVertexes;//�ڽӵ�
	void addConnectVertex(int);//���ӱ��Ϊid�ڽӵ�
	void delConnectVertex(int);//ɾ�����Ϊid�ڽӵ�
	bool isExistConnectVertex(int);//�Ƿ��Ѿ�������ĳ���ڽӵ�
};
#endif 

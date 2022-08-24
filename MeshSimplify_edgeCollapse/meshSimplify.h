#ifndef MESHSIMPLIFY_H
#define MESHSIMPLIFY_H
#include "edgeHeap.h"
#include "vertexGroup.h"
#include "matrix.h"
#include "vector4.h"
#include "solve.h"
#include "config.h"
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
class MeshSimplify
{
	double ratio;
	int cntFace, cntDelFace;//��Ƭ����Ӧ��ɾ������Ƭ��
	EdgeHeap* eHeap;//�ߵĶ�
	VertexGroup* vGroup;//��ļ���
public:
	MeshSimplify(void);
	~MeshSimplify(void);

	void setRatio(double);//���ü���
	void setLeftFaceNum(int);//��������ʣ�����Ƭ��

	void input();//�����ʼ���
	void start();//��ʼ��
	void output();//������

	//�����ز���
	Matrix calVertexDelta(int);
	MyVec3d calVertexPos(Edge&, Matrix);//����һ��������������������������ĵ�λ��
	//�ߵ���ز���
	void calVAndDeltaV(Edge&);//���㲢ȷ��һ����v��deltaV;	
};

#endif
#include "meshSimplify.h"
MeshSimplify::MeshSimplify(void)
{
	eHeap = new EdgeHeap();
	vGroup = new VertexGroup();
	cntFace = 0;
}


MeshSimplify::~MeshSimplify(void)
{
}

void MeshSimplify::start() {
	for (int i = 0; i < cntDelFace; i += 2) {//��ʼɾ��	
		Edge e = eHeap->getMinDelta();
		Vertex* v1 = &(vGroup->group[e.v1]);
		Vertex* v2 = &(vGroup->group[e.v2]);
		Vertex v0 = e.v;
		int v0_id = vGroup->addVertex(v0);
		Vertex* pV0 = &(vGroup->group[v0_id]);//��λ������ĵ�

		set<int> connectV;//pV0���ڽӵ�
		connectV.clear();
		eHeap->delEdge(e);//���ϱ��Ѿ�ɾ���ı��

		for (set<int>::iterator it = v1->connectVertexes.begin(); it != v1->connectVertexes.end(); it++) {
			if ((*it) != v2->id) {
				eHeap->delEdge(Edge((*it), v1->id));
				vGroup->group[(*it)].delConnectVertex(v1->id);
				connectV.insert((*it));
			}

		}

		for (set<int>::iterator it = v2->connectVertexes.begin(); it != v2->connectVertexes.end(); it++) {
			if ((*it) != v1->id) {
				eHeap->delEdge(Edge((*it), v2->id));
				vGroup->group[(*it)].delConnectVertex(v2->id);
				connectV.insert((*it));
			}

		}

		//��ԭ��u��v�Ľ����ڽӵ㼯���м����µ�o
		for (set<int>::iterator it = connectV.begin(); it != connectV.end(); it++) {
			vGroup->group[(*it)].addConnectVertex(v0_id);
			vGroup->group[v0_id].addConnectVertex(*it);
		}
		vGroup->isDeleted[v1->id] = true;//��ǽ���Ѿ���ɾ��
		vGroup->isDeleted[v2->id] = true;

		//���µ�ӱ�
		for (set<int>::iterator it = connectV.begin(); it != connectV.end(); it++) {
			Edge e((*it), v0_id);
			calVAndDeltaV(e);
			eHeap->addEdge(e);
		}



	}

}

void MeshSimplify::setRatio(double _ratio) {
	ratio = _ratio;
}

void MeshSimplify::input() {
	int cntv = 0, cntf = 0;
	char s[256];
	int tmp = 0;
	while (scanf_s("%s", s,256) == 1) {
		tmp++;
		switch (s[0]) {
		case '#': fgets(s, sizeof s, stdin); break;
		case 'v': {
			cntv++;
			double x, y, z;
			scanf_s("%lf %lf %lf", &x, &y, &z);
			vGroup->addVertex(Vertex(x, y, z));
			break;
		}
		case 'f': {
			cntf++;
			cntFace++;
			int a, b, c;
			scanf_s("%d%d%d", &a, &b, &c);
			//�����ڽӹ�ϵ,�Ѽ��
			vGroup->group[a].addConnectVertex(b);
			vGroup->group[a].addConnectVertex(c);
			vGroup->group[b].addConnectVertex(a);
			vGroup->group[b].addConnectVertex(c);
			vGroup->group[c].addConnectVertex(a);
			vGroup->group[c].addConnectVertex(b);
			break;
		}
		default: break;
		}
	}

	//���潫�߼��뵽�߶���
	for (int i = 1; i <= vGroup->cntVertex; i++) {//�������ж���
		for (set<int>::iterator it = vGroup->group[i].connectVertexes.begin();//����ĳ������������ڽӵ�
			it != vGroup->group[i].connectVertexes.end(); it++) {
			if (i < (*it))//�����Ż��Ĳ�̫ȷ��������������������������������������������������������������������
				break;

			Edge e((*it), i);
			calVAndDeltaV(e);//ÿ����һ���߾�Ҫ�������������
			eHeap->addEdge(e);//��һ���߼�������
		}
	}
	cntDelFace = (int)((1 - ratio) * cntFace);//����Ӧ��ʣ�¶��ٸ���
}


void MeshSimplify::output() {
	int cnt = 0;
	int cntv = 0, cntf = 0;
	for (int i = 1; i <= vGroup->cntVertex; i++) {//������е�
		if (vGroup->isDeleted[i])//�����i�����Ѿ�ɾ���ˣ�����ȥ
			continue;
		Vertex* v = &vGroup->group[i];
		cnt++;
		v->id = cnt;
		printf("v %lf %lf %lf\n", v->pos.x, v->pos.y, v->pos.z);
	}
	for (int i = 1; i <= vGroup->cntVertex; i++) {//���������
		if (vGroup->isDeleted[i])//�����i�����Ѿ�ɾ���ˣ�����ȥ
			continue;
		Vertex* v = &(vGroup->group[i]);//���ڵ�i����
		for (set<int>::iterator it1 = v->connectVertexes.begin(); it1 != v->connectVertexes.end(); it1++) {
			if (i >= (*it1))
				continue;
			for (set<int>::iterator it2 = v->connectVertexes.begin(); it2 != v->connectVertexes.end(); it2++) {
				if ((*it1) < (*it2) && (vGroup->group[(*it1)].isExistConnectVertex(*it2))) {
					printf("f %d %d %d\n", v->id, vGroup->group[(*it1)].id, vGroup->group[(*it2)].id);
					cntf++;
				}
			}
		}

	}
}

void MeshSimplify::calVAndDeltaV(Edge& e) {
	Matrix mat = calVertexDelta(e.v1) + calVertexDelta(e.v2);//�����궥������Ȼ�����
	e.v = calVertexPos(e, mat);//ȷ��һ����������ĵ�	
	Vector4 X(e.v.x, e.v.y, e.v.z, 1.0);
	if (vGroup->getCommonVertexNum(e.v1, e.v2) != 2) {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		e.deltaV = 0;
		return;
	}
	double pri = 0;
	for (int i = 0; i < 4; i++) {
		double p = 0;
		for (int j = 0; j < 4; j++)
			p += X.v[j] * mat.mat[i][j];
		pri += p * X.v[i];
	}
	e.deltaV = pri;
}

Matrix MeshSimplify::calVertexDelta(int _id) {
	Matrix ans;
	Vertex* p = &(vGroup->group[_id]);
	for (set<int>::iterator it1 = p->connectVertexes.begin(); it1 != p->connectVertexes.end(); it1++) {
		for (set<int>::iterator it2 = p->connectVertexes.begin(); it2 != p->connectVertexes.end(); it2++) {
			if ((*it1) < (*it2) && (vGroup->group[(*it1)].isExistConnectVertex(*it2))) {
				Vertex* v1 = &(vGroup->group[(*it1)]);
				Vertex* v2 = &(vGroup->group[(*it2)]);
				MyVec3d n = ((v1->pos) - (p->pos)).getCross((v2->pos) - (p->pos)).getUnitVectorOfThis();
				Vector4 tmp(n.x, n.y, n.z, -(p->pos.getDot(n)));
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						ans.mat[i][j] += tmp.v[i] * tmp.v[j];
					}

				}

			}

		}

	}
	return ans;

}

MyVec3d MeshSimplify::calVertexPos(Edge& e, Matrix m) {
	MyVec3d mid = (vGroup->group[e.v1].pos + vGroup->group[e.v2].pos) / 2;  //�е㣬Ӧ���˻����
	m.mat[3][0] = 0;
	m.mat[3][1] = 0;
	m.mat[3][2] = 0;
	m.mat[3][3] = 1;

	Vector4 Y(0, 0, 0, 1);
	Solve* solve = new Solve(m, Y);
	Vector4 ans = solve->getAns();
	if (ans.v[3] > Config::EPS)
		return MyVec3d(ans.v[0], ans.v[1], ans.v[2]);
	else
		return mid;
}







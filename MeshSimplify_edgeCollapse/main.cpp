/**********************************************
*����edge-collapse�㷨ʵ�ֵ������
**********************************************/
#include "meshSimplify.h"
#include "config.h"
#include "matrix.h"
#include "vector4.h"
#include "solve.h"
#include <iostream>
#include <time.h>
using namespace std;

FILE *stream_in;
FILE* stream_out;

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "error input " << endl;
		return -1;
	}
	else {
		clock_t start = clock();//��ʱ��ʼ

		MeshSimplify* meshSimplify = new MeshSimplify();
		freopen_s(&stream_in,argv[1], "r", stdin);
		freopen_s(&stream_out,argv[2], "w", stdout);
		meshSimplify->setRatio(atof(argv[3]));//���ü���
		meshSimplify->input();//����
		meshSimplify->start();//��ʼ��
		meshSimplify->output();//���

		clock_t finish = clock();//��ʱ�����������ʱ��
		cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << " s" << endl;
	}
	return 0;
}

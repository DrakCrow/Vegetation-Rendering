//#pragma once
////#ifndef _CRASH_H_
////#define _CRASH_H_
////#endif // !1
//
//#include<iostream>
//#include<cmath>
//#include<cstdlib>
//#include<ctime>
//#include<cstdio>
//using namespace std;
//extern float eds;
//extern float vertex[3];
//extern float PI;
//
//class vec {
//public:
//	float vect[3] = { 0 };
//	vec vec::operator*(const float &a)const
//	{
//		vec vector;
//		for (int i = 0; i < 3; i++)
//			vector.vect[i] = this->vect[i] * a;
//		return vector;
//	}
//	vec vec::operator/(const float &a)const
//	{
//		vec vector;
//		if (a == 0)
//		{
//			cout << "The divisor can not be zero !!" << endl;
//			return vector;
//		}
//		else
//		{
//			float b = 1 / a;
//			return (*this)*b;//������˷�������
//		}
//	}
//	vec vec::operator+(const vec &a)const
//	{
//		vec vector;
//		for (int i = 0; i < 3; i++)
//			vector.vect[i] = this->vect[i] + a.vect[i];
//		return vector;
//	}
//	vec vec::operator-(const vec &a)const
//	{
//		vec vector;
//		for (int i = 0; i < 3; i++)
//			vector.vect[i] = this->vect[i] - a.vect[i];
//		return vector;
//	}
//};
//
//class cube {
//public:
//	float center_position[3];
//	float l_w_h[3];
//	vec vector[2];
//	vec get_normal_vec()
//	{
//		vec vector_3;
//		vector_3.vect[0] = vector[0].vect[1] * vector[1].vect[2] - vector[0].vect[2] * vector[1].vect[1];
//		vector_3.vect[1] = vector[0].vect[2] * vector[1].vect[0] - vector[0].vect[0] * vector[1].vect[2];
//		vector_3.vect[2] = vector[0].vect[0] * vector[1].vect[1] - vector[0].vect[1] * vector[1].vect[0];
//		return vector_3;
//	}
//};
//class edge {
//public:
//	float position_x[3];
//	float position_y[3];
//};
//class face {
//public:
//	float center_vex[3];
//	vec vector[2]; //vector[0]��Ӧw, vector[1]��Ӧh
//	float w;
//	float h;
//
//	vec get_normal_vec()
//	{
//		vec vector_3;
//		vector_3.vect[0] = vector[0].vect[1] * vector[1].vect[2] - vector[0].vect[2] * vector[1].vect[1];
//		vector_3.vect[1] = vector[0].vect[2] * vector[1].vect[0] - vector[0].vect[0] * vector[1].vect[2];
//		vector_3.vect[2] = vector[0].vect[0] * vector[1].vect[1] - vector[0].vect[1] * vector[1].vect[0];
//		return vector_3;
//	}
//
//};
//bool Is_in_plane(float vex[3], face f);	//�ж����Ƿ�������0
//float projection(float a[3], float b[3]);//ͶӰ
//bool crash_judge(face f, edge e);//����ߵ���ײ�ж�
//float a_cos(vec a, vec b);//�����нǵĻ���ֵ
//bool compare_all_vec(vec a, cube b);//true������ false�����ڲ�
//bool compare_proj(vec b, vec a);
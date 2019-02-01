//#include"crash.h"
//float eds = 0.0001f;
//float vertex[3];
//
//float PI = 3.1415926535897932384626433832795f;
//
//bool crash_judge(face f, edge e)//面与边的碰撞判定
//{
//	vec temp_1, temp_2;
//	vec temp_3;
//	for (int i = 0; i < 3; i++)				//三个向量
//	{
//		temp_1.vect[i] = e.position_x[i] - f.center_vex[i];
//		temp_2.vect[i] = e.position_y[i] - f.center_vex[i];
//		temp_3.vect[i] = (e.position_x[i] + e.position_y[i]) / 2 - f.center_vex[i];
//	}
//	float distan[3];						//两端点与中心点求距离。若中心点距离等于两端点距离之和的一半，继续判定 否则，return false
//	distan[0] = projection(f.get_normal_vec().vect, temp_1.vect);/***************************/
//	distan[1] = projection(f.get_normal_vec().vect, temp_2.vect);
//	distan[2] = projection(f.get_normal_vec().vect, temp_3.vect);
//	if (2 * distan[2] - distan[0] - distan[1] < eds)
//	{
//		return false;
//	}
//	else
//	{
//		float vex[3];		//线与面的交点
//		for (int i = 0; i < 3; i++)
//		{
//			vex[i] = e.position_y[i] * distan[0] / (distan[0] + distan[1]);
//			vex[i] += e.position_x[i] * distan[1] / (distan[0] + distan[1]);
//		}
//		if (!Is_in_plane(vex, f))		//判定交点是否在面内
//			return false;
//		else
//			return true;
//	}
//}
//
//float projection(float a[3], float b[3])//vec投影,b投影到a
//{
//	float abs_vec = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
//	float count = 0;
//	for (int i = 0; i < 3; i++)
//	{
//		count += a[i] * b[i];
//	}
//	count = fabs(count / abs_vec);
//	return count;
//}
//
//bool Is_in_plane(float vex[3], face f)	//判定点是否在面内0
//{
//	vec w_vector, h_vector;//高和宽的两条向量
//	w_vector = f.vector[0] * (f.w / 2) / (projection(f.vector[0].vect, f.vector[0].vect));
//	h_vector = f.vector[1] * (f.h / 2) / (projection(f.vector[1].vect, f.vector[1].vect));
//	vec to_center;
//	for (int i = 0; i < 3; i++)
//		to_center.vect[i] = f.center_vex[i] - vex[i];
//	vec vec_edge[4];
//	vec_edge[0] = to_center + w_vector + h_vector;
//	vec_edge[1] = to_center + w_vector - h_vector;
//	vec_edge[2] = to_center - w_vector - h_vector;
//	vec_edge[3] = to_center - w_vector + h_vector;
//	float count = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		count += a_cos(vec_edge[i], vec_edge[(i+1)&3]);//&3 == %4
//	}
//	if (abs(count - PI)< eds)
//		return true;
//	else
//		return false;
//}
//float a_cos(vec a, vec b)
//{
//	float a_b = 0;
//	for (int i = 0; i < 3; i++)
//	{
//		a_b += a.vect[i] * b.vect[i];
//	}
//	float count = projection(a.vect, b.vect) * projection(b.vect, a.vect) / abs(a_b);
//	return abs(acos(count));
//}
//
//bool crash(cube a, cube b)			//a crash to b
//{
//	vec center_vector;
//	for (int i = 0; i < 3; i++)
//	{
//		center_vector.vect[i] = a.center_position[i] - b.center_position[i];
//	}
//	vec a_x, a_y, a_z;
//
//	a_x = a.vector[0] * (a.l_w_h[0]/2) / (projection(a.vector[0].vect, a.vector[0].vect));
//	a_y = a.vector[1] * (a.l_w_h[1] / 2) / (projection(a.vector[1].vect, a.vector[1].vect));
//	a_z = a.get_normal_vec() * (a.l_w_h[3] / 2) / (projection(a.get_normal_vec().vect, a.get_normal_vec().vect));
//	if (compare_all_vec(center_vector + a_x + a_y + a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector + a_x + a_y - a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector + a_x - a_y + a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector + a_x - a_y - a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector - a_x + a_y + a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector - a_x + a_y - a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector - a_x - a_y + a_z, b))
//		return true;
//	else if (compare_all_vec(center_vector - a_x - a_y - a_z, b))
//		return true;
//	else
//		return false;
//
//}
//bool compare_all_vec(vec a, cube b)//true在外面 false点在内部
//{
//	vec b_x, b_y, b_z;
//	b_x = b.vector[0] * (b.l_w_h[0] / 2) / (projection(b.vector[0].vect, b.vector[0].vect));
//	b_y = b.vector[1] * (b.l_w_h[1] / 2) / (projection(b.vector[1].vect, b.vector[1].vect));
//	b_z = b.get_normal_vec() * (b.l_w_h[3] / 2) / (projection(b.get_normal_vec().vect, b.get_normal_vec().vect));
//	if (compare_proj(a, b_x) || compare_proj(a, b_y) || compare_proj(a, b_z))
//		return false;
//	else
//		return true;
//}
//bool compare_proj(vec b, vec a)
//{
//	if (projection(a.vect, b.vect) <= projection(a.vect, a.vect))
//		return false;
//	else
//		return true;
//}
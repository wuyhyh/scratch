#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

//图
/*
* 四种基本的图：无向图、有向图、加权图、加权有向图
* 
* 1.无向图：用整数0~V-1表示vertex顶点	
	简便起见，我们可以直接使用数组的索引作为结点的名称

	*G满足5个条件之一时将是一棵树：
	1）G有V-1条边并且不含有环
	2）G有V-1条边并且是连通的//这一点有疑惑
	3）G是无环的，但添加1条边将形成环
	4）G是连通的，但删除1条边将不再连通
	5）G中任意一对顶点之间只存在一条简单路径

	*二分图中的每条边连接的两个顶点分别属于不同的集合，可以将所有顶点染色分为2部分
* 
* 
*/



int main()
{
	printf("say my name.Heisenberg\n");


	return 0;
}
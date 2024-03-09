//求中位数的伪代码
//求第k大数的特例
typedef int elemtype;
elemtype find_kth_largest(elemtype S[], int k)
{
	//选取S中的一个元素e
	//根据e把S划分为两个部分S1,S2；前者的元素都>=e,后者都<e
	if (abs(S1)>= k)
		return find_kth_largest(S1, k);
	else if (abs(S1) < k - 1)
		return find_kth_largest(S2, k - abs(S1) -1);
	else
		return e;
}
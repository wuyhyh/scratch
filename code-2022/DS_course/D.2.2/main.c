//����λ����α����
//���k����������
typedef int elemtype;
elemtype find_kth_largest(elemtype S[], int k)
{
	//ѡȡS�е�һ��Ԫ��e
	//����e��S����Ϊ��������S1,S2��ǰ�ߵ�Ԫ�ض�>=e,���߶�<e
	if (abs(S1)>= k)
		return find_kth_largest(S1, k);
	else if (abs(S1) < k - 1)
		return find_kth_largest(S2, k - abs(S1) -1);
	else
		return e;
}
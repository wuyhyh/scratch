//
// Created on 4/18/24.
//

#ifndef SCRATCH_COMMON_H
#define SCRATCH_COMMON_H

double gettime_()
{
	struct timeval t;
	int rc = gettimeofday(&t, NULL); // linux系统调用
	assert(rc == 0);
	// 以微秒为单位的到1970年的时间
	return (double)t.tv_sec + (double)t.tv_usec / 1e6;
}

// 这个函数会停止howlong长的秒数
void spin_(int howlong)
{
	double t = gettime_();
	while ((gettime_() - t) < (double)howlong)
		; // do nothing in loop
}

#endif //SCRATCH_COMMON_H

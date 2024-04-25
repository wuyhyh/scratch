//
// Created by wyh on 2024/1/23.
//

// 操作系统需要为进程保存一些信息

// 寄存器的信息
struct context {
	int eip;
	int esp;
	int ebx;
	int ecx;
	int edx;
	int esi;
	int edi;
	int ebp;
};

// 进程状态
enum proc_state { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

#define NOFILE 3

// 进程
struct proc {
	char *mem;
	unsigned int sz;
	char *kstack;

	enum proc_state state;
	int pid;
	struct proc *parent;
	void *chan;
	int killed;
	struct file *ofile[NOFILE];
	struct inode *cwd;
	struct context context;
	struct trapframe *tf;
};

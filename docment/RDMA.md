# RDMA的工作经验

## 1. rdma-core的编译

[rdma-core](https://github.com/linux-rdma/rdma-core "github")

### 1.1 解决编译问题

```shell
sed -i 's/-DIN_PLACE=1/-DIN_PLACE=0 -DENABLE_RESOLVE_NEIGH=0/' build.sh
```

[rdma-core的构建和使用](https://runsisi.com/2021/03/07/rdma-core/)

### 1.2 rdma demo

[rdma tutorial](https://github.com/rhiswell/rdma-tutorial)

### 1.3 rdma-core的编译博客

[RDMAmojo](https://www.rdmamojo.com/)

[RDMA网络简介](https://winddoing.github.io/post/f4fa9e36.html)

[一文读懂RoCE](https://www.sdnlab.com/25923.html)

[RDMA技术详解](https://zhuanlan.zhihu.com/p/55142557)

[RDMA杂谈](https://www.zhihu.com/column/c_1231181516811390976)

## 2. RDMA aware programming user manual

[download PDF](https://indico.cern.ch/event/218156/attachments/351725/490089/RDMA_Aware_Programming_user_manual.pdf)








# How to build a project

这里记录的是一些关于编译的tricks

## 1. bash

关于rdma-core的编译问题：消除rdma-core编译中的依赖错误
    
    sed -i 's/-DIN_PLACE=1/-DIN_PLACE=0 -DENABLE_RESOLVE_NEIGH=0/' build.sh


## 2. make

## 3. cmake

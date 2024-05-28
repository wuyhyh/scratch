#!/usr/bin/env bash

# 根据path和filename创建空文件

echo "根据path和filename创建空文件:"
read inputstr
dir=$(dirname $inputstr)
file=$(basename $inputstr)

mkdir -p $dir
cd $dir
touch $file
cd -

echo "finish"


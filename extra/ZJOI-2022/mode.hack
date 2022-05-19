#!/bin/sh
echo 1
echo 200000
for ((i=1;i<=200000;++i)) { [ $(($i % 2)) -eq 1 ] && printf '1 ' || printf "$i "; }

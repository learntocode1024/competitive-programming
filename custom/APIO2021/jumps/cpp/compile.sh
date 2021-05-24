#!/bin/bash

problem=jumps
grader_name=stub

g++ -ggdb -std=gnu++17 -O2 -pipe -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"

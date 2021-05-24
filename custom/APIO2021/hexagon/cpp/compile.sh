#!/bin/bash

problem=hexagon
grader_name=grader

g++ -ggdb -std=gnu++17 -pipe -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"

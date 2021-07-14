#!/bin/bash

problem=candies
grader_name=grader

g++ -g -std=gnu++17 -Wall -pipe -static -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"

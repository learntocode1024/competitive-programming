#!/bin/bash
root="$HOME/contests/templates"
sed -e 's%$DATE%'"$(date +%m-%d-%y)"'%' \
    "$root/cpp.cpp" > "$root/current.cpp"
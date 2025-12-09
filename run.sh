#!/bin/zsh

OUT="main"

clear

g++ -Wall -Wextra -std=c++17 ./src/*.cpp -o $OUT

if [ $? -eq 0 ]; then
    ./$OUT
else
    echo "${NC}"
fi

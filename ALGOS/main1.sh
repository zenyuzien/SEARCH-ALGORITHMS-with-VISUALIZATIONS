#!/bin/bash

g++ input_graph.cpp -o input_graph.exe
g++ menu.cpp -o menu.exe

./input_graph.exe
./menu.exe

python visualization.py

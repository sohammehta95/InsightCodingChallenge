#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it.
#

echo "First arg  -> Input Path: $1"
echo "Second arg -> Output Path Occupation: $2"
echo "Third arg -> Output Path State: $3"

g++ ./src/h1b_counting.cpp -o ./src/myProg

./src/myProg ./input/h1b_input.csv ./output/top_10_occupations.txt ./output/top_10_states.txt


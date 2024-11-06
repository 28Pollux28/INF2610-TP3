#!/bin/sh
make
./answer > grader/result.log
make clean
cat grader/result.log
python3 grader/grade.py
rm grader/result.log

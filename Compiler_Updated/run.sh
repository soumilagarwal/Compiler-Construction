#!/bin/bash
gcc new_lexer.c parser.c main.c -o output
./output Testcases/testcase7.txt
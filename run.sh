#!/bin/bash
gcc main.c lexer.c parser.c -o output
./output Testcase/testcase1.txt
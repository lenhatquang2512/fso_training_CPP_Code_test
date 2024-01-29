#!/bin/bash

# cd /home/quang_le/quang_prog/test/test_code_cpp_tut/fso_training_git/

clear

#compile
g++  -pthread -std=c++14 -Wall -O0 -g InhePolySingletonTest.cpp -o InhePolySingletonTest

#not necessary , make this file executable
chmod +x InhePolySingletonTest

#run
./InhePolySingletonTest


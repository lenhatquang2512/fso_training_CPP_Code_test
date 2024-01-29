#!/bin/bash

# cd /home/quang_le/quang_prog/test/test_code_cpp_tut/fso_training_git/

clear

#compile
# g++  -pthread -std=c++14 -Wall -O0 -g InhePolySingletonTest.cpp -o InhePolySingletonTest
g++  -pthread -std=c++14 -Wall -O0 -g Singleton_guru.cpp -o Singleton_guru

#not necessary , make this file executable
chmod +x Singleton_guru

#run
./Singleton_guru


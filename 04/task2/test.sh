#!/bin/bash

cmake ../CMakeLists.txt

for exec in {1..100}; do
  # create/empty files
  ../cmake-build-debug/task2
done
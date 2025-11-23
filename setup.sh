#!/bin/bash

mkdir build
cd build && mkdir uploads && cmake ..
cd ..
cmake --build build

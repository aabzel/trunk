echo off
cls

cmake -S . -B build --warn-uninitialized -G "Unix Makefiles"


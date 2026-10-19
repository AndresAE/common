@echo off
setlocal

g++ -std=c++17 ^
  -I ../include ^
  ../src/conversions.cpp ^
  test_conversions.cpp ^
  -o test_conversions.exe

test_conversions.exe

endlocal

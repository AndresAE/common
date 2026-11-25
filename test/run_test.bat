@echo off
setlocal

g++ -std=c++17 ^
  -I ../include ^
  ../src/cmn.cpp ^
  test_cmn.cpp ^
  -o test_cmn.exe
if errorlevel 1 exit /b 1
test_cmn.exe
if errorlevel 1 exit /b 1

g++ -std=c++17 ^
  -I ../include ^
  ../src/conversions.cpp ^
  test_conversions.cpp ^
  -o test_conversions.exe
if errorlevel 1 exit /b 1

test_conversions.exe
if errorlevel 1 exit /b 1

g++ -std=c++17 ^
  -I ../include ^
  ../src/cmn.cpp ^
  ../src/earth.cpp ^
  test_earth.cpp ^
  -o test_earth.exe
if errorlevel 1 exit /b 1

test_earth.exe
if errorlevel 1 exit /b 1

g++ -std=c++17 ^
  -I ../include ^
  ../src/cmn.cpp ^
  ../src/filter.cpp ^
  test_filter.cpp ^
  -o test_filter.exe
if errorlevel 1 exit /b 1

test_filter.exe
if errorlevel 1 exit /b 1

g++ -std=c++17 ^
  -I ../include ^
  ../src/cmn.cpp ^
  ../src/conversions.cpp ^
  ../src/atmo.cpp ^
  test_atmo.cpp ^
  -o test_atmo.exe
if errorlevel 1 exit /b 1

test_atmo.exe
if errorlevel 1 exit /b 1

g++ -std=c++17 ^
  -I ../include ^
  ../src/cmn.cpp ^
  ../src/transform.cpp ^
  test_transform.cpp ^
  -o test_transform.exe
if errorlevel 1 exit /b 1

test_transform.exe
if errorlevel 1 exit /b 1

endlocal

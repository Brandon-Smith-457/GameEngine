@echo off
pushd ..\
call external\bin\premake\premake5.exe vs2019
popd
PAUSE
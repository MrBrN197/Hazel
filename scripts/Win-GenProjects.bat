@echo off
pushd ..\
call vendor\premake\premake5.exe vs2019
PAUSE
popd
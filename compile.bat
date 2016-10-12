@echo off
cls

echo ***** Building the Solution *****
cd XMLDocument
devenv XMLDocument.sln /rebuild debug
cd ..
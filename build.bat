@echo off
g++ -c src\main.cc src\field.cc src\mouse_input.cc src\algorithm.cc src\draw.cc
g++ -o Path-Finder main.o field.o mouse_input.o algorithm.o draw.o
del *.o
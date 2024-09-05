del *.o
g++ -c main.cc field.cc mouse_input.cc algorithm.cc draw.cc
g++ -o Path-Finder main.o field.o mouse_input.o algorithm.o draw.o
pause
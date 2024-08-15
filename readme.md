valgrind --leak-check=full -s --track-origins=yes ./a.out < randtest0.in > my.out

g++ -std=c++11 -DNDEBUG -Wall *.cpp
all:
	clang++ -O3 -flto=thin -o test ./src/test.cpp ./lib/t*.cpp -lgtest -lpthread
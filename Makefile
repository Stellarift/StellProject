all:
	clang++ -std=c++17 main.cpp fileio.cpp menu.cpp -o todo

run: all
	./todo

clean:
	rm -f todo tasks.txt

rebuild: clean all
default:
	# write command to test your files (you do not need it for your submissions)
	g++ -std=c++11 main.cpp -o main.out

run: main.out
	./main.out
clean:
	rm *.out

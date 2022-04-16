fireworks:
	g++ src/*.cpp -lncurses -o ./fireworks
clean:
	rm -f ./fireworks
	rm -f ./fireworks.dev
	rm -f ./fireworks.dev.dSYM

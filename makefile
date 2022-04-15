fireworks:
	g++ src/*.cpp -lncurses -o ./fireworks
dev:
	g++ -g3 -Wall -Wextra -fsanitize=address,undefined src/*.cpp -lncurses -o ./fireworks.dev
clean:
	rm -f ./fireworks
	rm -f ./fireworks.dev
	rm -f ./fireworks.dev.dSYM

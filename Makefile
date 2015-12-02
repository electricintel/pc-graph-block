curses:
	g++ -Wall cursesUI.cpp screen.cpp -lcurses -o cursesUI
clean:
	rm cursesUI

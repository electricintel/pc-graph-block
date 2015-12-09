curses:
	g++ -Wall cursesUI.cpp screen.cpp -lcurses -lboost_system -lboost_date_time -o run
clean:
	rm run

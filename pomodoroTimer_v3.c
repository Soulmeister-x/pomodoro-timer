/* Pomodoro Timer

This c console application shall count
two intervals of 25 and 5 minutes.
After each interval, a bell should ring.


compile with -lncurses and
$ gcc -lncurses -o pomodoroTimer_v3 pomodoroTimer_v3.c
$ ./pomodoroTimer_v3
*/

#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

#include "clocktable.h"

#define clrscr() printf("\e[1;1H\e[2J")

void printNum(int num, int row, int col);
void printTime(int seconds);

int main() {


	// init semaphore for tick every second

    int _5minAsSec = 5*60;
    int _25minAsSec = 25*60;
    int row=6, col=1;
    int i,j, count;


	clrscr();

	// init ncurses
    initscr();      // start curses mode
    cbreak();       // allow control characters
    noecho();       // Don't echo() while we do getch

	printw("Pomodoro-Timer\n");
	printw("practice: 25 min\n");
	printw("pause   :  5 min\n");
	printw("press ENTER to Start 4 intervals\n");
	refresh();
	getch();

	clrscr();
	mvprintw(0,0, "Pomodoro-Timer\n");

	mvaddch(row+1, col+25, 35);
	mvaddch(row+3, col+25, 35);
	mvaddch(row+1, col+26, 35);
	mvaddch(row+3, col+26, 35);

	for (int i=0; i<4; i++) {

		mvprintw(1, 34, "Interval: %d / 4", i+1);
		mvprintw(2,34, "RUNNING");

		for (count=0; count<_25minAsSec+1; count++)  {
			
			printTime(_25minAsSec-count);

			refresh();
			sleep(1);
		}
		// TODO: ring bell to signal end of study phase
		mvprintw(2,34, "PAUSE  ");
		
		for (count=0; count<_5minAsSec+1; count++)  {

			printTime(_5minAsSec-count);

			refresh();
			sleep(1);
		}
		// TODO: ring bell to signal end of pause phase
	}
        

    
	endwin();
    return 0;
}


void printTime(int seconds) {
	// calculate all 4 digits of digital clock
	int mins10 = (seconds / 60) / 10;
	int mins   = (seconds / 60) % 10;
	int secs10 = (seconds % 60) / 10;
	int secs   = seconds % 10;

	int row = 6, col = 1;

	printNum(mins10, row, col);
	printNum(mins, row, col+15);
	printNum(secs10, row, col+32);
	printNum(secs, row, col+47);
}

void printNum(int num, int row, int col) {
	// num shall be a single digit [0..9]
	int i,j;
	for (i=0; i<5; i++) {
		for (j=0; j<5; j++) {
			if (window_clock_table[num][i][j])
				mvaddch(row+i, col+j, 35);
			else
				mvaddch(row+i, col+j, ' ');
		}
	}
}
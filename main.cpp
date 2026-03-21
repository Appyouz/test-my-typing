#include <functional>
#include <ncurses.h>
#include <iostream>
#include <thread>
#include <utility>
#include <future>
#include <chrono>
#include <unistd.h>
#include <stdio.h>

/*
 * TODO:
 * Logic:
 * Initiate a timer and equate counter to that timer. The counter now will start the
 * tick tick and once the counter is up we store the char typed everytime a keystroke is
 * pressed and use that to calculate wpm along with the time (seconds)., the counter
 * exists sole purpose of the while loop base condition
 *
 *
 * 1. Use thread for it. 
 * AT one thread run the timer so it goes on once it starts.
 * New approach:
 * Run the user input in a thread and attach that thread to our main while loop
 *
 *
 * -(NOT POSSIBLE) Write two threads and call the use rinput thread to coutndown timer thread(TWO
 *   THREAD FUNCTIONS)
* */

void takeUserInput(int &ch, int &char_pressed){
  ch = getch();
// if ((ch = getch()) != KEY_F(1)) {
  if(ch  != ERR){
    char_pressed++;
    printw(" CHAR:%d", ch);
    printw("\n");
    // }
  }
}



int main(){
  initscr();
  cbreak();
  int ch; 
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  noecho();

  std::promise<int> prms;
  std::future<int> ftr = prms.get_future();
  int time = 10;
  int char_pressed = 0;
  int count = time;

  while(count > 0){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread t (takeUserInput,std::ref(ch), std::ref(char_pressed));
    t.join();
    printw("\nTIMER:%d", count--);
  }


  int wpm = 0;
  wpm = static_cast<int>(char_pressed / 5.0) / (time / 60.0);
  printw("\nwpm:%d", wpm);
  refresh();
  getchar();
  endwin();
  return 0;
}

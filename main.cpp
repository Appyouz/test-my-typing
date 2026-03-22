#include <cmath>
#include <functional>
#include <ncurses.h>
#include <iostream>
#include <thread>
#include <utility>
#include <future>
#include <chrono>
#include <unistd.h>
#include <stdio.h>
#include <future>

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
bool countDown(int time);
void takeUserInput(int &char_pressed){
  int ch = getch();
  float time = 10.0;
  // int ch = getch();
// if ((ch = getch()) != KEY_F(1)) {
  if(ch  != ERR){
    char_pressed++;
    // printw(" CHAR:%d", ch);
    printw(keyname(ch));
  }

}

bool countDown(int time){

  while(time > 0){
  // refresh();
  // printw("COUNT:%d\n", time--);
    time--;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return true;
}


int main(){
  initscr();
  cbreak();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  noecho();

  int time = 10;
  int char_pressed = 0;
  int count = time;
  std::future<bool> backgroundThread = std::async(std::launch::async,countDown,std::ref(time));
  std::future_status status;
while(true){
    std::thread t (takeUserInput,std::ref(char_pressed));
    t.join();
    // takeUserInput(char_pressed);
    status = backgroundThread.wait_for(std::chrono::milliseconds(50));
    if(status == std::future_status::ready){
      // std::cout << "TIMES UP";
      printw("TIME IS UP");
      break;
    }
  }
  int wpm = 0;
  // wpm = std::round(static_cast<int>(char_pressed / 5.0) / (time / 60.0));
  wpm = static_cast<int>(char_pressed / 5.0) / (time / 60.0);
  printw("\nwpm:%d", wpm);
  refresh();
  // getch();
  // endwin();
  return 0;
}

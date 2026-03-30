#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <unistd.h>
#include <future>

bool countDown(int time);
void takeUserInput(int &char_pressed, std::string lessonText, int& i){
  float time = 10.0;
  // This block works but prints out lesson.size() time every letter. but char pressed
  // and wpm is correct still. need to somehow not let it print lesson.size() for a
  // single keystroke
  // Okay writing ch = getch() fixed the lesson.size() times of a letter but char
  // pressed is wrong now haha
 int n = lessonText.length(); 
    int ch;
ch = getch();
// for(int i = 0; i < n; i++){
  if(i > n) return;
    if(ch != ERR){
    // {solved)TODO: logic for backspace and ch != lessonString[i]
    if(ch == KEY_BACKSPACE && i > 0){
      mvdelch(1,i);
      i--;
      if(i == 0){
        // or inside do check if char_deleted = char_pressed that is from lessonText
        mvdelch(1, 0);
        i = 0;
      }
    }
      if(ch == lessonText[i]){
      ++char_pressed;
      // printw("char_pressed: %d\n",++char_pressed);
      printw(keyname(ch));
      // printw("i: %d\n",i++);
      i++;
      }else if(ch != KEY_BACKSPACE && ch != lessonText[i]){
      printw(keyname(ch));
      i++;
      // printw("i: %d\n",i++);
      }
    // }
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

  // std::string lessonText {"The Lazy brown Fox Jump Over The Wall"};
  std::string lessonText {"the man"};
  
  printw("%s", lessonText.data());
  printw("\n");
  
  int time = 10;
  int char_pressed = 0;
  int count = time;
  int i = 0;
  std::future<bool> backgroundThread = std::async(std::launch::async,countDown,std::ref(time));
  std::future_status status;
while(true){
    // std::thread t (takeUserInput,std::ref(char_pressed));
    // t.join();
    takeUserInput(char_pressed, lessonText, i);
    status = backgroundThread.wait_for(std::chrono::milliseconds(50));
    if(status == std::future_status::ready){
      // std::cout << "TIMES UP";
      printw("TIME IS UP");
      break;
    }
  }
  int wpm = 0;
  wpm = static_cast<int>(std::round((char_pressed / 5.0) / (time / 60.0)));
  printw("Character pressed: %d\n", char_pressed);
  printw("\nwpm:%d", wpm);
  refresh();
  // getch();
  // endwin();
  return 0;
}

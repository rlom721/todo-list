#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// friend functions OK on top?
void testMethod(string msg, int cVal, int tVal) {
// This TODO method performs equality tests on class methods. (msg = display
// test message, cVal = correct value to compare, tVal = test value)

  int width = 46;              // console width
  string RED = "\033[1;31m",   // color text bold red
         GRN = "\033[1;32m",   // color text bold green
         RST = "\033[0m";      // reset to default color
  int msgLen = msg.length();    // length of message
  string testRes,               // pass or fail test result and labels
         testP = GRN + "Pass" + RST,
         testF = RED + "Fail" + RST;

  cout << msg;
  cout << string(width - msgLen, '.');

  testRes = (tVal == cVal) ? testP : testF;
  cout << testRes << endl;
}

string centerText(string str, int width) {

  string centStr;   // centered text
  int length = 0,   // length of string
      spaces = 0;   // spaces to pad to center

  length = str.length();
  spaces = (width - length) / 2;

  // center by padding with spaces before text
  centStr.append(spaces, ' ');

  centStr.append(str, 0, length);

  // pad end with spaces
  centStr.append(spaces, ' ');

  return centStr;
}   // ???? ret string

int main() {
  cout << "|" << centerText("Yello", 20) << "|" << endl;

  cout << centerText("TODO", 80)
       << centerText("----", 80) << endl;
  cout << centerText("Task", 32) << "|"
       << centerText("Date", 24) << "|"
       << centerText("ID #", 24) << endl;

  return 0;
}

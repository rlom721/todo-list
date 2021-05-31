// todoList.cpp
// 11/8/2020
// Rafaela Lomboy

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;
 
// friend functions (used by multiple classes) - don't work under classes...?
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

void testMethod(string msg, string cStr, string tStr) {
// This TODO method performs equality tests on class methods. (msg = display
// test message, cStr = correct value to compare, tStr = test value)

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

  testRes = (tStr == cStr) ? testP : testF;
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
}

class Date {
  friend void testMethod(string msg, int cVal, int tVal);
  friend void testMethod(string msg, string cStr, string tStr);
  private:
    int month, day, year;
    string nameDate;
    static const string monthName[];
    time_t epSecs;            // seconds since epoch
    tm* pCalTime = nullptr;   // pointer to calendar time
  public:
    // ADD: overload copy/assn constructor
    Date();
    Date(int month, int day, int year);
    void setDate(int m, int d, int y);
    void setDate(string dateStr);
    void setCurrent();      // method to set current date
    void displayDateName();
    void displayDate();
    string getDateName () const;
    string getDate() const;
    void componentTest();
    // ostream &operator<<(ostream& out, Date date);
};

const string Date::monthName[] = {"January", "February", "March", "April",
                                   "May", "June", "July", "August",
                                   "September", "October", "November",
                                   "December"};

// Specification A3 - System Date.
Date::Date() {
// This Date constructor sets values of month, day and year to current date.

  // set epSecs and convert local time
  epSecs = time(0);
  pCalTime = localtime(&epSecs);

  // set date to current local time
  month = 1 + pCalTime->tm_mon;
  day = pCalTime->tm_mday;
  year = 1900 + pCalTime->tm_year;
}

Date::Date(int month, int day, int year) {
  this->month = month; this->day = day; this->year = year;
}

void Date::setDate(int m, int d, int y) {
// This Date method sets the values for the date manually.

  if (m < 0 || d < 0 || y < 0 || m > 12 || d > 31)
    cout << "Invalid date entered.\n";
  else {
    month = m; day = d; year = y;
  }
}

void Date::setDate(string str) {
  string token;
  int pos;
  // add input validation if / not found

  // parse string and assign to variable
  pos = str.find('/');
  token = str.substr(0, pos);
  month = stoi(token);
  str.erase(0, pos + 1);

  pos = str.find('/');
  token = str.substr(0, pos);
  day = stoi(token);
  str.erase(0, pos + 1);

  pos = str.find('/');
  token = str.substr(0, pos);
  year = stoi(token);
  str.erase(0, pos + 1);
}

void Date::setCurrent() {
// set date to current local time

  month = 1 + pCalTime->tm_mon;
  day = pCalTime->tm_mday;
  year = 1900 + pCalTime->tm_year;
}

void Date::displayDateName() {
// This Date method displays the date in MonthName day, year format.

  cout << monthName[month-1] + " " << day << ", " << year;
}

void Date::displayDate() {
// This Date method displays the date in numerical month day, year format.

  cout << month << "/" << day << "/" << year;
}

string Date::getDateName() const {
// This Date method returns the date as a string in MonthName day, year format
// (for component testing the output).

  return monthName[month - 1] + " " + to_string(day) + ", " + to_string(year);
}

string Date::getDate() const {
// This Date method returns the date as a string in month day, year format
// (for component testing the output).

  string date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

  return date;
}

void Date::componentTest() {
// This Date method performs a test on the class to see if data is inputted
// and stored properly.

  Date testDate;  // Date instance for testing

  cout << "Testing Date class...\n";

  // test if input machines are working
  testDate.setDate(3, 1, 2001);
  testMethod("setDate()", "3/1/2001", testDate.getDate());

  testDate.setDate("8/22/2020");
  testMethod("setDate(string)", "8/22/2020", testDate.getDate());

  // test if date formatting is working
  testMethod("getDateName()", "August 22, 2020", testDate.getDateName());
  testMethod("getDate()", "8/22/2020", testDate.getDate());

  cout << "End of testing Date class.\n\n";
}


class TODO {
  friend void testMethod(string msg, int cVal, int tVal);
  friend void testMethod(string msg, string cStr, string tStr);
  friend ostream &operator<<(ostream& out, const TODO& todo);
  friend bool operator==(TODO a, TODO b);
  private:
    string task;
    Date dateAdded;
    int id;
  public:
    bool isVis;   // for deleting todo in list
    TODO();
    TODO(string task);
    TODO(const TODO& todo);
    TODO& operator=(const TODO& rhs);
    void setTask(string task);
    void setDate(int month, int day, int year);
    void setDate(string str);
    void setID(int id);
    string getTask() const;
    string getDate() const;
    int getID() const;
    void componentTest();
};

// Specification A4 - Overload Constructor
TODO::TODO() {
  this->task = " TEST RECORD";
  this->dateAdded.setDate(9, 9, 1999);
  this->isVis = true;
}

TODO::TODO(string task) {
  this->task = task;
}

// Specification A1 - Overload Copy Constructor
TODO::TODO(const TODO& rhs) {
  task = rhs.task;
  dateAdded.setDate(rhs.getDate());
}

// Specification A2 - Overload Assignment Operator
TODO& TODO::operator=(const TODO& rhs) {
  // check if object is being assigned to self
  if (this != &rhs) {
    task = rhs.task;
    dateAdded.setDate(rhs.getDate());
    id = rhs.id;
    isVis = rhs.isVis;
  }

  return *this;
}

void TODO::setTask(string task) {
  this->task = task;
}

void TODO::setDate(int month, int day, int year) {
  this->dateAdded.setDate(month, day, year);
}

void TODO::setDate(string str) {

  this->dateAdded.setDate(str);
}

void TODO::setID(int id) {
  this->id = id;
}

string TODO::getTask() const {
  return task;
}

string TODO::getDate() const {
  return dateAdded.getDate();
}

int TODO::getID() const {
  return id;
}

void TODO::componentTest() {

  TODO testTD, testTD2;      // test object

  cout << "Testing TODO class...\n";

  testTD.setTask("do the thing");
  testTD.setDate(8, 22, 2020);
  testTD.setID(12345);

  testMethod("setTask()", "do the thing", testTD.getTask());
  testMethod("setDate()", "8/22/2020", testTD.getDate());
  testMethod("setID", 12345, testTD.getID());

  testTD.setDate("8/23/2020");
  testMethod("setDate(string)", "8/23/2020", testTD.getDate());

  TODO testTD1 = testTD;
  cout << "Testing Copy Constructor\n";
  testMethod("same task?", testTD.getTask(), testTD1.getTask());
  testMethod("same date?",testTD.getDate(), testTD1.getDate());

  testTD2 = testTD;
  cout << "Testing Overloaded Assignment Operator\n";
  testMethod("same task?", testTD.getTask(), testTD2.getTask());
  testMethod("same date?",testTD.getDate(), testTD2.getDate());

  cout << "End of testing TODO class.\n\n";
}

// overloaded operators for TODO
// Specification C1 - Overload <<
ostream &operator<<(ostream& out, const TODO& todo) {

  out << left << setw(41) << todo.task << "\t"
      << todo.dateAdded.getDate() << "\t"
      << centerText(to_string(todo.id), 6) << "\t";

  return out;
}

bool operator==(TODO a, TODO b) {
  if ((a.task == b.task) && (a.dateAdded.getDate() == b.dateAdded.getDate())
      && (a.id == b.id)) {
    return true;
  }
  else
    return false;
}

// for DynArray class
void testMethod(string msg, TODO cTodo, TODO tTodo) {
// This TODO method performs equality tests on class methods. (msg = display
// test message, cStr = correct value to compare, tStr = test value)

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

  testRes = (cTodo == tTodo) ? testP : testF;
  cout << testRes << endl;
}

class DynArray {
  friend void testMethod(string msg, int cVal, int tVal);
  friend void testMethod(string msg, TODO cTodo, TODO tTodo);
  friend istream &operator>>(istream& in, DynArray& todoList);
  friend void centerText(string str);
  private:
    TODO* array;          // array of TODOs
    int size;
    void indexError() {   // error message for array
      cout << "Index outside of array range.\n";
      exit(1);
    }
  public:
    int idGen = 0;        // generates ids
    DynArray(int s);
    ~DynArray();
    TODO& operator[](int index);
    string heading();
    void print();
    void add(TODO val);
    void sub();
    void subTodo(int num);
    int getSize();
    void componentTest();
};

DynArray::DynArray(int s = 0) {
// This is the DynArray constructor, which uses inputted size to initialize
// a dynamically allocated array.

  size = s;               // user-inputted size

  array = new TODO[size];

  // set ids
  for (int i = 0; i < size; i++) {
    array[i].setID(idGen++);
  }
}

DynArray::~DynArray() {
// This is the DynArray destructor, which frees allocated memory.

  delete [] array;
  array = nullptr;
}

TODO& DynArray::operator[](int index) {

  // error if accessing element outside of array range
  if (index < 0 || index > (size - 1))
    indexError();

  return array[index];
}

string DynArray::heading() {
  return string(74, '-') + "\n|" + centerText("~TODO~", 72) + "|\n"
         + string(74, '-') + "\n|" + centerText("Task", 42) + "|"
         + centerText("Date", 17) + "|" + centerText("ID #", 12) + "|\n"
         + string(74, '-');
}

void DynArray::print() {
// This DynArray method prints out array contents.

  if (size == 0)
    cout << "Array has size 0 and no elements.\n";
  else {
    cout << endl;
    // display todos and their data
    for (int i = 0; i < size; i++) {
      if (array[i].isVis)
        cout << " ~"<< array[i] << endl;
    }
  }
}

void DynArray::add(TODO todo) {
// This DynArray method increases array size by one element and adds a value to
// its last element.

  TODO* temp = nullptr;  // to copy elements into larger array

  // create temporary array one size larger (and increment size)
  temp = new TODO[++size];

  // copy elements only if old array size is not 0 (size already incremented)
  if (size != 1) {
    for (int i = 0; i < (size - 1); i++) {
      temp[i] = array[i];
    }
  }

  todo.setID(idGen++);
  todo.isVis = true;

  // add element at end of temp array
  temp[size - 1] = todo;
  temp[size - 1].isVis = true;

  // free allocated memory of old array and reassign
  delete [] array;
  array = temp;
}

void DynArray::sub() {
// This DynArray method shrinks array size by one element at the end.

  TODO* temp = nullptr;  // to copy elements into smaller array

  // throw exception if size == 0??? idek this works tho...

  if (size == 0)
    cout << "ERROR: Cannot subtract element from array of size 0.\n";
  else {
    // create temporary array one size smaller
    temp = new TODO[--size];

    // copy elements of old array into temp until filled
    for (int i = 0; i < size; i++)
      temp[i] = array[i];

    // free allocated memory of old array and reassign
    delete [] array;
    array = temp;
  }
}

void DynArray::subTodo(int numID) {
// This DynArray method takes index to remove from array, then shrinks array
// size by one element.

  int index = -1,   // for storing index of todo with matching ID
      newID = -1;   // for rewriting ID numbers after deleting todo

  if (size == 0)
    cout << "ERROR: Cannot subtract element from array of size 0.\n";
  else if (numID < 0 || numID > (size - 1))
    cout << "ID not found. (Value entered outside of index range.)\n";
  else {
    // find matching ID in list then store array index if visible
    for (int i = 0; i < size; i++) {
      if ((array[i].getID() == numID) && array[i].isVis) {
        index = i;
        break;
      }
    }

    if (index == -1)
      cout << "ID not found.\n";
    else {
      // delete and adjust variables
      array[index].isVis = false;
      idGen--;
      newID = numID;

      // rewrite ID numbers of visible todos after removed index
      for (int i = index + 1; i < size; i++) {
        if (array[i].isVis)
          array[i].setID(newID++);
      }
    }
  }
}

int DynArray::getSize() {
// This DynArray method returns the current size of array.

  return size;
}

void DynArray::componentTest() {
// This DynArray method performs a self diagnostic on the class.

  DynArray testArray(2),
           testList;          // to test DynArray methods
  TODO testTodo, testTodo1;

  testTodo.setTask(" do the thing");
  testTodo.setDate(9, 9, 1999);

  cout << "Testing DynArray class\n";

  // testing constructor (size initialization)
  testMethod("Size initialization", 2, testArray.getSize());

  // testing add method
  testArray.add(testTodo);
  testMethod("add()", testTodo.getTask(), testArray[2].getTask());
  testMethod("makes todo visible?", true, testArray[2].isVis);

  // testing sub method
  testArray.sub();
  testMethod("sub()", 2, testArray.getSize());

  // testing subTodo method
  testArray.subTodo(0);
  testMethod("subTodo() - makes todo invisible?", false, testArray[0].isVis);

  // Specification C3 - Test TODO’s
  // generate test TODOs
  cout << "\n\nTesting TODO Generation\n";

  cout << testList.heading();
  for (int i = 0; i < 5; i++) {
    // add to todo list and set todo task
    testList.add(testTodo1);
  }

  testList.print();

  cout << "End of testing DynArray class.\n\n";
}

//Specification C2 - Overload >>
istream &operator>>(istream& in, DynArray& todoList) {

  string str, input;
  int endStr = -1,
      index = -1;

  // loop until user quits
  do {
    cout << "Enter task or command: ";
    getline(cin, str);

    // Specification B1 - + Symbol
    if (str[0] == '+') {

      // parse string input
      endStr = str.find('\0');
      input = str.substr(1, endStr);

      if (input == " " || input.empty()) {
        // trigger regular constructor if empty input
        TODO todo;

        // add to todo list
        todoList.add(todo);
      }
      else {
        // trigger overloaded constructor if task entered
        TODO todo(str);

        // set todo task
        todo.setTask(input);

        // add to todo list
        todoList.add(todo);
      }

      cout << "Todo added to list!\n";

    }
    // Specification B3 - - symbol
    else if (str[0] == '-') {
      // parse string input
      endStr = str.find('\0');
      input = str.substr(1, endStr);

      // only accept numeric string
      try {
        index = stoi(input);

        // remove corresponding todo and show message
        todoList.subTodo(index);
        cout << "Todo at index " << index << " removed.\n";
      }
      catch (const std::invalid_argument&){
        cout << "Invalid index.\n";
      }
    }
    // Specification B2 - ? Symbol
    else if (str[0] == '?') {

      // print out all todos in array
      cout << todoList.heading();
      todoList.print();
    }
    else if (str[0] != 'q' && str[0] != 'Q')
      cout << "Invalid command.\n";

  } while (str[0] != 'q' && str[0] != 'Q');

  return in;
}

// Function Prototypes
void ProgramGreeting();
void UnitTest();
void displayOptions();

int main() {

  //Specification C4 - TODO array
  DynArray todoList;                // dynamic array of TODOs
  ifstream getData;                 // for retrieving file data
  ofstream dumpData;                // for storing file data
  string line, task, date;          // for parsing file line
  TODO todo;                        // for retrieving from file
  int delimPos;                     // to parse file line

	ProgramGreeting();

  getData.open("todoList.txt");

  // Specification B4 - Persistence
  if (getData.fail())
    cout << "No previous todo data found.\n";
  else {
    // read data in from file loop until end of file reached
    while (getline(getData, line)) {

        // parse entire line to get task and date info
        delimPos = line.find('\t');
        task = line.substr(0, 41);
        line.erase(0, delimPos + 1);
        delimPos = line.find('\t');
        date = line.substr(0, delimPos);

        // set todo data (id is skipped because of auto generation)
        todo.setTask(task);
        todo.setDate(date);

        // add todo to list
        todoList.add(todo);

        line.clear();
      }
    }

    // display old todo data if avaliable
    cout << todoList.heading();

    if (todoList.getSize())
      todoList.print();
    cout << endl;

  getData.clear();
  getData.close();

  // prompt user to input commands for todo list (loops until quit)
  cin >> todoList;

  // save todo list by writing to file
  dumpData.open("todoList.txt");

  for (int i = 0; i < todoList.getSize(); i++) {
    if (todoList[i].isVis)
      dumpData << todoList[i] << endl;
  }

  dumpData.clear();
  dumpData.close();

  cout << "\nHave a productive day! :D\n";

  return 0;
}

void ProgramGreeting() {

  UnitTest();

  Date today;      // automatically displays current date

  cout << centerText("Welcome to the TODO List Program!", 78) << endl
       << centerText("---------------------------------", 78) << endl
       << centerText("Author: Rafaela Lomboy", 78) << endl
       << centerText(today.getDateName(), 78) << endl << endl;

  displayOptions();       // show avaliable commands
}

void UnitTest() {

  Date testDate;
  DynArray testArr(2);
  TODO testTD;

  cout << "Starting Unit Test...\n\n";

  testDate.componentTest();
  testArr.componentTest();
  testTD.componentTest();

  cout << "End of Unit Test.\n";
  cout << string(78, '-') << endl << endl;
}

void displayOptions() {
// This function displays menu options and accepts user choice.

    cout << centerText("Commands", 78) << endl
         << centerText("--------", 78) << endl
         << centerText("- Enter '+' followed by task to add", 77) << endl
         << centerText("- Enter '-' followed by ID to remove", 78) << endl
         << centerText("- Enter '?' to display all TODOs", 75) << endl
         << centerText("- Enter 'q' to quit program", 70) << endl << endl;
}

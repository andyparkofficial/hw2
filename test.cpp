#include <set>
#include "util.h"
#include <string>
#include <iostream>
#include "book.h"
 
using namespace std;
 
int main(int argc, char* argv[]){
 string category = "Books";
 string name = "Sucky Ass Book";
 int price = 69;
 int qty = 69;
 string isbn = "978-000000000-1";
 string author = "George Brown";
  Book litBook(category, name, price, qty, isbn, author);
 set<string> yeet = litBook.keywords();
 
 for (set<string>::iterator it=yeet.begin(); it != yeet.end(); ++it){
   cout<< *it << endl;
 }
 cout << endl;

 litBook.dump(cout);

 string outputString = litBook.displayString();

 cout << outputString << endl;

 return 0;
}

#include <iostream>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author):Product(category, name, price, qty), isbn_(isbn), author_(author)
{
}
 

set<std::string> Book::keywords() const{
  set<string> keyWords;

  set<string> preUnionedSets[3];
  preUnionedSets[0] = parseStringToWords(name_);
  preUnionedSets[1].insert(isbn_);
  preUnionedSets[2] = parseStringToWords(author_);

  for (int i = 0; i < 3; i++){
    keyWords = setUnion(keyWords, preUnionedSets[i]);
  }

  return keyWords;

}
string Book::displayString() const{
  string outputString = "";
  outputString += category_ + " " + name_ + " " + to_string(price_) + " " + to_string(qty_) + " " + isbn_ + " " + author_;
  return outputString;
}

void Book::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
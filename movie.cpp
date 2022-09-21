#include <iostream>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating):Product(category, name, price, qty),
  genre_(genre),
  rating_(rating)
{
}

set<std::string> Movie::keywords() const{
  set<string> keyWords;

  set<string> preUnionedSets[2];
  preUnionedSets[0] = parseStringToWords(name_);
  preUnionedSets[1].insert(genre_);

  for (int i = 0; i < 2; i++){
    keyWords = setUnion(keyWords, preUnionedSets[i]);
  }

  return keyWords;
}
string Movie::displayString() const{
  string outputString = "";
  outputString += category_ + " " + name_ + " " + to_string(price_) + " " + to_string(qty_) + " " + genre_ + " " + rating_;
  return outputString;
}

void Movie::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

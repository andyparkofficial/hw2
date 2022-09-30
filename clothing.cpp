#include <iostream>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand):Product(category, name, price, qty),
  size_(size),
  brand_(brand)
{
}

set<std::string> Clothing::keywords() const{
  set<string> keyWords;

  set<string> preUnionedSets[2];
  preUnionedSets[0] = parseStringToWords(name_);
  preUnionedSets[1] = parseStringToWords(brand_);

  for (int i = 0; i < 2; i++){
    keyWords = setUnion(keyWords, preUnionedSets[i]);
  }

  return keyWords;
}
string Clothing::displayString() const{
  string outputString = "";
  outputString += name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
  return outputString;
}

void Clothing::dump(std::ostream& os) const{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore {
public:
  MyDataStore();
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  std::set<User*> users_;
private:
  std::set<Product*> products_;
  std::map<std::string, std::set<Product*>> keywordMap_;
  
};

#endif
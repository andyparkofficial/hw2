#include <iostream>
#include "util.h"
#include "mydatastore.h"
using namespace std;

MyDataStore::MyDataStore() {
  
}

MyDataStore::~MyDataStore() {
  std::set<Product*>::iterator it;
  for (it = products_.begin(); it != products_.end(); ++it){
    delete *it;
  }
  std::set<User*>::iterator it2;
  for (it2 = users_.begin(); it2 != users_.end(); ++it2){
    delete *it2;
  }
}

void MyDataStore::addProduct(Product* p){
  products_.insert(p);
  set<string> keyWords = p->keywords();
  for (set<string>::iterator it = keyWords.begin(); it != keyWords.end(); ++it){
    if(keywordMap_.find(*it) != keywordMap_.end() ){// if keyword already exists
      keywordMap_[*it].insert(p);
    } else { //if keyword does not exist
      set<Product*> products;
      products.insert(p);
      keywordMap_[*it] = products;
    }
  }
}

void MyDataStore::addUser(User* u){
  users_.insert(u);
  
}
  
vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  vector<Product*> products;
  if (type == 0){ // AND search
    set<Product*> tempProducts;

    for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
      if(keywordMap_.find(*it) != keywordMap_.end() ){//if keyword exists
        if (it == terms.begin()){ // if first iteration
          tempProducts = keywordMap_[*it];
        } else {
          tempProducts = setIntersection(tempProducts, keywordMap_[*it]);
        }
      }
      else { //there exists a search term that is not in keywordMap_
        return products;
      }
    }
    for (set<Product*>::iterator it = tempProducts.begin(); it != tempProducts.end(); ++it){
      products.push_back(*it);
    }
  } 
  
  else if (type == 1) { //OR search
    set<Product*> tempProducts;
    for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
      if(keywordMap_.find(*it) != keywordMap_.end() ){//if keyword exists
        for (set<Product*>::iterator jit = keywordMap_[*it].begin(); jit !=  keywordMap_[*it].end(); ++jit){
          tempProducts.insert(*jit);
        }
      }
    }
    for (set<Product*>::iterator it = tempProducts.begin(); it != tempProducts.end(); ++it){
      products.push_back(*it);
    }
  }
  return products;
}

void MyDataStore::dump(std::ostream& ofile){
  
  ofile << "<products>" << endl;
  for(set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for(set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
    (*it)->dump(ofile);
  }
  ofile << "</users>" << endl;
}
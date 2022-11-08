#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"
#include "user.h"


using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    } else {
      
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    map<string, vector<Product*>> cart;
    map<string, User*> usernameToUser;
    for (set<User*>::iterator it = ds.users_.begin(); it != ds.users_.end(); ++it){
        string username = convToLower((*it)->getName()); //make it lowercase 
        usernameToUser[username]= *it;
        vector<Product*> yeet;
        cart[username] = yeet;
    }
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename);
                    ds.dump(ofile);
                    ofile.close();
                } 
                done = true;
            }
	    /* Add support for other commands here */
            else if ( cmd == "ADD") {
              unsigned int hit_result_index;
              Product* addedItem;
              string username;
              ss >> username;
              username = convToLower(username);
              if(usernameToUser.find(username) == usernameToUser.end() ){ //if user does not exist
                cout << "Invalid request" << endl;
                continue;
              }
              else if(ss >> hit_result_index) {
                if (hit_result_index <= hits.size()){ //if index exists
                  addedItem = hits[hit_result_index-1]; 

                  if(cart.find(username) != cart.end() ){ //if user already has items
                    cart[username].push_back(addedItem);
                  }
                  // } else { // if user does not have items
                  //   vector<Product*> addedItems;
                  //   addedItems.push_back(addedItem);
                  //   cart[username] = addedItems;
                  // }

                } else {
                  cout << "Invalid request" << endl;
                  continue;
                }
              }
              else {
                cout << "Invalid request" << endl;
                continue;
              }
              
              
            }
            else if ( cmd == "VIEWCART") {
                string username;
                if (ss >> username){
                  username = convToLower(username);
                    if(cart.find(username) != cart.end() ){ // if username exists
                        int counter = 1;
                        for (vector<Product*>::iterator it = cart[username].begin(); it != cart[username].end(); ++it){
                            cout << "Item " << counter << "\n" << (*it)->displayString() << endl;
                            counter++;
                        }   
                    } else {
                    cout << "Invalid username" << endl;
                    }  
                } 
            }
            else if ( cmd == "BUYCART"){
                string username;
                if (ss >> username){
                  username = convToLower(username);
                    if(cart.find(username) != cart.end() ){ // if username exists in cart
                      vector<int> deletedIndexes;
                      int index = 0;
                      for (vector<Product*>::iterator it = cart[username].begin(); it != cart[username].end(); ++it){
                          if (((usernameToUser[username])->getBalance() >= (*it)->getPrice()) && ((*it)->getQty() > 0)){ // user has enough money and there is at least one of the product
                              
                              (*it)->subtractQty(1);
                              (usernameToUser[username])->deductAmount((*it)->getPrice());
                              deletedIndexes.push_back(index);
                          }
                          index++;
                      }
                      int offset = 0; //offset is necessary as the items get deleted, the index that needs to be deleted changes
                      for (vector<int>::iterator it = deletedIndexes.begin(); it != deletedIndexes.end(); ++it){
                        cart[username].erase(cart[username].begin()+(*it)-offset); // erase the item that has been deleted
                        offset++;
                      }
                    } else {
                    cout << "Invalid username" << endl;
                    }  
                } 
            }




            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit   " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}

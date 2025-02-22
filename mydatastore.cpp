#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::~MyDataStore() { //dynamically allocated products + users, so need destructor
    for (unsigned int i = 0; i < products.size(); i++) {
        delete products[i];
    }

    for (std::map<User*, std::vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it) {
        delete it->first;
    }
}

/**
 * adds a product to the data store
 */
void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
    set<string> keywords = p->keywords();

    for (set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        storeKeywords[*it].insert(p);
    }
}

/**
 * adds a user to the data store
 */
void MyDataStore::addUser(User* u){
    vector<Product*> product;

    users.insert(std::make_pair(u, product));
}

/**
 * performs a search of products whose keywords match the given "terms"
 * type 0 = and search (intersection of results for each term)
 * type 1 = or search (union of results for each term)
 */
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> result;
    if (terms.empty()) {
        return vector<Product*>();
    }

    if (type == 1) { // OR
        for (size_t i = 0; i < terms.size(); ++i) {
            if (storeKeywords.find(terms[i]) != storeKeywords.end()) { //found it
                result = setUnion(result, storeKeywords[terms[i]]);
            }
        }
    } else if (type == 0) { // AND
        if (storeKeywords.find(terms[0]) != storeKeywords.end()) { //found it
            result = storeKeywords[terms[0]];
        } 
        else {
            return vector<Product*>();
        }

        for (size_t i = 1; i < terms.size(); ++i) { //for intersection, do extra step
            if (storeKeywords.find(terms[i]) != storeKeywords.end()) {
                result = setIntersection(result, storeKeywords[terms[i]]);
            } 
            else {
                return vector<Product*>();
            }
        }
    }

    return vector<Product*>(result.begin(), result.end());
}

/**
 * adds a product from the last search to a user's cart
 */
void MyDataStore::ADD(const string& username, std::vector<Product*>& hits, int hit_result_index) {
    for (map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it) {
        if (it->first->getName() == username) {
            if (hit_result_index < 1 || hit_result_index > static_cast<int>(hits.size())) {
                cout << "Invalid request" << endl;
                return;
            }
            it->second.push_back(hits[hit_result_index - 1]);
            return;
        }
    }
    cout << "Invalid request" << endl;
}

/**
 * views the cart of a user
 */
void MyDataStore::VIEWCART(const string& username) const {
    for (map<User*, vector<Product*>>::const_iterator it = users.begin(); it != users.end(); ++it) {
        if (it->first->getName() == username) {
            for (size_t i = 0; i < it->second.size(); ++i) {
                cout << "Item " << i+1 << endl;
                cout << it->second[i]->displayString() << endl;
            }
            return;
        }
    }
    cout << "Invalid username" << endl;
}

/**
 * buys all products from a user's cart if they can afford them and the products are in stock
 */
void MyDataStore::BUYCART(const std::string& username) {
    for (std::map<User*, std::vector<Product*>>::iterator userIterator = users.begin(); userIterator != users.end(); ++userIterator) { // go through users to find proper username
        if (userIterator->first->getName() == username) {
            std::vector<Product*> afterPurchase;

            for (std::vector<Product*>::iterator prodIterator = userIterator->second.begin(); prodIterator != userIterator->second.end(); ++prodIterator) { // check each product in the user's cart
                Product* currentProduct = *prodIterator;

                if (currentProduct->getQty() > 0 && userIterator->first->getBalance() >= currentProduct->getPrice()) { // if product is available PLUS user can afford it
                    currentProduct->subtractQty(1);
                    userIterator->first->deductAmount(currentProduct->getPrice());  // deduct balance
                } else {
                    afterPurchase.push_back(currentProduct);  // keep products not bought
                }
            }

            userIterator->second = afterPurchase; 
        }
    }
    std::cout << "Invalid username" << std::endl;
}


/**
 * reproduce the database file from the current products and user values
 */
void MyDataStore::dump(ostream& ofile) {
    ofile << "<products>" << endl;

    for (size_t i = 0; i < products.size(); ++i) {
        products[i]->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (map<User*, vector<Product*>>::iterator it = users.begin(); it != users.end(); ++it) {
        it->first->dump(ofile);
    }
    ofile << "</users>" << endl;
}

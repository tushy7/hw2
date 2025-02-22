#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "datastore.h"
#include "util.h"



class MyDataStore: public DataStore {
public:
    ~MyDataStore() override;

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

    void ADD(const std::string& username, std::vector<Product*>& hits, int hit_result_index);
    void VIEWCART(const std::string& username) const;
    void BUYCART(const std::string& username);

private:
    std::vector<Product*> products;
    std::map<User*, std::vector<Product*>> users; //each user might want multiple products (vector bc want duplicates)
    std::map<std::string, std::set<Product*>> storeKeywords; //string is set to the product name, and store the keywords as a set (don't need duplicate) 
};

#endif

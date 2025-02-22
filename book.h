#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book: public Product {
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string Author);
    ~Book();

    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const override;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const override;

    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const override;

    //print out the category
    std::string getCategory() const override;

private:
    std::string ISBN_;
    std::string Author_;
};
#endif

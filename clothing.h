#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing: public Product {
public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string Size, const std::string Brand);
    ~Clothing();

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
    std::string Size_;
    std::string Brand_;
};
#endif

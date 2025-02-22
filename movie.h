#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie: public Product {
public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string Genre, const std::string Rating);
    ~Movie();

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
    std::string Genre_;
    std::string Rating_;
};
#endif

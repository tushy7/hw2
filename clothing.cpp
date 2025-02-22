#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;


Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string Size, const std::string Brand)
    : Product(category, name, price, qty), Size_(Size), Brand_(Brand) {}
    
Clothing::~Clothing() {}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Clothing::keywords() const {
    std::set<std::string> keywords;

    std::set<std::string> nameKeywords = parseStringToWords(name_);
    keywords.insert(nameKeywords.begin(), nameKeywords.end());  

    std::set<std::string> brandKeywords = parseStringToWords(Brand_);
    keywords.insert(brandKeywords.begin(), brandKeywords.end());  

    return keywords;
}


/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing:: displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Size: " << Size_ << " Brand: " << Brand_ << "\n" << price_ << " " << qty_ << " left.";
    std::string str = ss.str();
    return str;
}


void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << Size_ << "\n" << Brand_ << "\n";
}

std::string Clothing:: getCategory() const {
    return "Clothing";
}
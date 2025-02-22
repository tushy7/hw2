#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;


Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string Author)
    : Product(category, name, price, qty), ISBN_(ISBN), Author_(Author) {}
    
Book::~Book() {}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords() const {
    std::set<std::string> keyword;

    std::set<std::string> nameKeywords = parseStringToWords(name_);
    keyword.insert(nameKeywords.begin(), nameKeywords.end()); 

    std::set<std::string> authorKeywords = parseStringToWords(Author_);
    keyword.insert(authorKeywords.begin(), authorKeywords.end()); 

    keyword.insert(ISBN_);

    return keyword;
}



/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book:: displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Author: " << Author_ << " ISBN: " << ISBN_ << "\n" << price_ << " " << qty_ << " left.";
    std::string str = ss.str();
    return str;
}

void Book::dump(std::ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << Author_ << "\n";
}


std::string Book:: getCategory() const {
    return "Book";
}
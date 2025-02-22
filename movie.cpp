#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string Genre, const std::string Rating)
    : Product(category, name, price, qty), Genre_(Genre), Rating_(Rating) {}
    
Movie::~Movie() {}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const {
    std::set<std::string> keywords;

    std::set<std::string> nameKeywords = parseStringToWords(name_);
    keywords.insert(nameKeywords.begin(), nameKeywords.end());

    keywords.insert(convToLower(Genre_));

    return keywords;
}


/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie:: displayString() const {
    std::stringstream ss;
    ss << name_ << "\n" << "Genre: " << Genre_ << " Rating: " << Rating_ << "\n" << price_ << " " << qty_ << " left.";
    std::string str = ss.str();
    return str;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << Genre_ << "\n" << Rating_ << "\n";
}

std::string Movie:: getCategory() const {
    return "Movie";
}
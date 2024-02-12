#include "movie.h"

Movie::Movie(const std::string category,
             const std::string name,
             double price,
             int qty,
             std::string genre,
             std::string rating)
    : Product(category, name, price, qty) {
    genre_ = genre;
    rating_ = rating;
}
Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> res;
    std::string tmp;

    for (char c : genre_)
        tmp.push_back(tolower(c));
    res.insert(tmp);
    tmp = "";
    for (char c : name_) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c <= '9' && c >= '0')) {
            tmp.push_back(tolower(c));
        } else {
            if (tmp.size() >= 2)
                res.insert(tmp);
            tmp = "";
        }
    }
    if (tmp.size() >= 2)
        res.insert(tmp);
    return res;
}

std::string Movie::displayString() const {
    return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << std::endl;
}

std::string Movie::getGenre() const {
    return genre_;
}
std::string Movie::getRating() const {
    return rating_;
}
#include "book.h"

Book::Book(const std::string category,
           const std::string name,
           double price,
           int qty,
           std::string isbn,
           std::string author)
    : Product(category, name, price, qty) {
    isbn_ = isbn;
    author_ = author;
}
Book::~Book() {}

std::set<std::string> Book::keywords() const {
    std::set<std::string> res;
    std::string tmp;
    for (char c : isbn_)
        tmp.push_back(tolower(c));

    res.insert(tmp);
    tmp = "";

    std::vector<std::string> words = {name_, author_};
    for (std::string s : words) {
        for (char c : s) {
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
        tmp = "";
    }
    return res;
}

std::string Book::displayString() const {
    return Product::name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ +
           "\n" + std::to_string(Product::price_) + " " +
           std::to_string(Product::qty_) + " left.";
}

void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << isbn_ << "\n" << author_ << std::endl;
}

std::string Book::getIsbn() const {
    return isbn_;
}

std::string Book::getAuthor() const {
    return author_;
}

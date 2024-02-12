#include "clothing.h"

Clothing::Clothing(const std::string category,
                   const std::string name,
                   double price,
                   int qty,
                   std::string size,
                   std::string brand)
    : Product(category, name, price, qty) {
    size_ = size;
    brand_ = brand;
}
Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> res;
    std::vector<std::string> words = {name_, brand_};
    std::string tmp;

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

std::string Clothing::displayString() const {
    return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" +
           std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << std::endl;
}

std::string Clothing::getSize() const {
    return size_;
}
std::string Clothing::getBrand() const {
    return brand_;
}
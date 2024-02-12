#include "mydatastore.h"

MyDataStore::~MyDataStore() {
    std::map<std::string, Product*>::iterator iter_product = products.begin();
    for ( ;iter_product != products.end(); iter_product++)
        delete iter_product->second;

    std::map<std::string, User*>::iterator iter_user = users.begin();
    for ( ;iter_user != users.end(); iter_user++)
        delete iter_user->second;
}

MyDataStore::MyDataStore() {}

void MyDataStore::addProduct(Product* p) {
    std::set<std::string> words = p->keywords();
    for (std::string keyword : words) {
        keyword = convToLower(keyword);
        mapKeyWord[keyword].push_back(p);
    }
    products[p->getName()] = p;
}

void MyDataStore::addUser(User* u) {
    users[u->getName()] = u;
}


User* MyDataStore::getUser(std::string &userName) {
    userName = convToLower(userName);
    if (users[userName])
        return users[userName];
    return nullptr;
}


/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms,
                                          int type) {
    std::set<std::string> res_present;
    bool isFirst = true;
    for (std::string s : terms) {
        s = convToLower(s);
        std::set<std::string> ps;
        for (Product* pr : mapKeyWord[s])
            ps.insert(pr->displayString());
        if (type == 1) {
            res_present = setUnion<std::string>(res_present, ps);
        } else {
            if (isFirst)
                res_present = ps;
            else
                res_present = setIntersection(res_present, ps);
        }
        isFirst = false;
    }
    std::vector<Product*> res_product;
    for (std::string s : terms)
        for (Product* pr : mapKeyWord[s])
            if (res_present.find(pr->displayString()) != res_present.end()) {
                res_product.push_back(pr);
                res_present.erase(pr->displayString());
            }
    return res_product;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    std::map<std::string, Product*>::iterator iter_product = products.begin();
    for ( ;iter_product != products.end(); iter_product++)
        if (iter_product->second != nullptr)
            iter_product->second->dump(ofile);
    ofile << "</products>\n";

    std::map<std::string, User*>::iterator iter_user = users.begin();
    ofile << "<users>\n";
    for ( ;iter_user != users.end(); iter_user++)
        if (iter_user->second != nullptr)
            iter_user->second->dump(ofile);
    ofile << "</users>\n";
}
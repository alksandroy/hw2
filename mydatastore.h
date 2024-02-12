#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <string>
#include <vector>
#include <set>
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore {
   public:
    MyDataStore();

    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    User* getUser(std::string &userName);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

   private:
    std::map<std::string, std::vector<Product*>> mapKeyWord;
    std::map<std::string, User*> users;
    std::map<std::string, Product*> products;
};
#endif
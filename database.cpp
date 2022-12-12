#include "database.hpp"
#include <errno.h>
#include <fstream>

template<typename KeyType, typename ValType>
ValType database<KeyType, ValType>::read_one(KeyType key) {
    std::ifstream inputFile(this->databaseFilename);
    std::string inputKey, inputValue;
    while (std::getline(inputFile, inputKey, '=')) {
        if (inputKey[0] == '\n') {
            inputKey.erase(inputKey.begin());
        }
        std::getline(inputFile, inputValue);
        if (std::string(key) == inputKey) {
            inputFile.close();
            return ValType(inputValue);
        }
    }
    inputFile.close();
    return "";
}
template<typename KeyType, typename ValType>
int database<KeyType, ValType>::write(KeyType key, ValType value) {
    std::ofstream ofile;
    ofile.open(this->databaseFilename, std::ios::app);
    if (!ofile) {
        std::cout << strerror(errno) << " ";
        return -1;
    }
    if (this->read_one(key) != ValType()) {
        ofile.close();
        return -1;
    }
    ofile << std::endl << std::string(key) << "=" << std::string(value);
    if (ofile.bad()) {
        ofile.close();
        return -1;
    }
    ofile.close();

    return 0;
}
template<typename KeyType, typename ValType>
std::map<KeyType, ValType>* database<KeyType, ValType>::read_all() {
    std::map<KeyType, ValType>* res = new std::map<KeyType, ValType>;
    std::ifstream ifile(this->databaseFilename);
    std::string ikey, ival;
    while (std::getline(ifile, ikey, '=')) {
        if (ikey[0] == '\n') {
            ikey.erase(ikey.begin());
        }
        std::getline(ifile, ival);
        (*res)[ikey] = ival;
    }
    ifile.close();
    return res;
}
template<typename KeyType, typename ValType>
int database<KeyType, ValType>::erase(KeyType key) {
    std::fstream ofile;
    // get all keys from file
    std::map<KeyType, ValType>* res = this->read_all();
    ofile.open(this->databaseFilename, std::ios::out);
    if (!ofile) {
        std::cout << strerror(errno) << " ";
        return -1;
    }
    // Write all keys to file exept "key"
    for (auto [inputKey, inputValue] : *res) {
        if (key != inputKey) {
            ofile << std::string(inputKey) << "=" << std::string(inputValue) << std::endl;
        }
    }
    delete res;
    if (ofile.bad()) {
        return -1;
    }
    ofile.close();

    return 0;
}
template<typename KeyType, typename ValType>
database<KeyType, ValType>::database() {
    this->databaseFilename = "db.txt";
}
template<typename KeyType, typename ValType>
database<KeyType, ValType>::~database() {
    return;
}
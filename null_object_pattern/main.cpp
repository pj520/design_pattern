#include <iostream>
#include <vector>

using std::string;

using std::vector;

class AbstractCustomer {
protected :
    string name;
public:
    virtual bool isNil() = 0;

    virtual string getName() = 0;
};

class RealCustomer : public AbstractCustomer {
public:
    RealCustomer(string name) {
        this->name = name;
    }

    string getName() {
        return name;
    }

    bool isNil() {
        return false;
    }
};

class NullCustomer : public AbstractCustomer {
public:

    string getName() {
        return "Not Available in Customer Database";;
    }

    bool isNil() {
        return true;
    }
};


static vector<string> names = {"Rob", "Joe", "Julie"};

class CustomerFactory {
public :
    static AbstractCustomer *getCustomer(string name) {
        for (int i = 0; i < names.size(); i++) {
            if (names[i] == (name)) {
                return new RealCustomer(name);
            }
        }
        return new NullCustomer();
    }
};


int main() {
    AbstractCustomer *customer1 = CustomerFactory::getCustomer("Rob");
    AbstractCustomer *customer2 = CustomerFactory::getCustomer("Bob");
    AbstractCustomer *customer3 = CustomerFactory::getCustomer("Julie");
    AbstractCustomer *customer4 = CustomerFactory::getCustomer("Laura");

    std::cout << "Customers" << std::endl;
    std::cout << customer1->getName() << std::endl;
    std::cout << customer2->getName() << std::endl;
    std::cout << customer3->getName() << std::endl;
    std::cout << customer4->getName() << std::endl;
}

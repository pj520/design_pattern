#include <iostream>
#include <list>

using std::string;
using std::list;

template<typename T>
bool contains(const list<T> &lists, const T value) {
    for (const auto &item : lists)
        if (value.equals(item))
            return true;
    return false;
}

class Person {
public :
    Person(string name, string gender, string maritalStatus) {
        this->name = name;
        this->gender = gender;
        this->maritalStatus = maritalStatus;
    }

    string getName() {
        return name;
    }

    string getGender() {
        return gender;
    }

    string getMaritalStatus() {
        return maritalStatus;
    }

    bool equals(const Person &value) const {
        if (name == value.name && gender == value.gender && maritalStatus == value.maritalStatus) {
            return true;
        }
        return false;
    }

private:
    string name;
    string gender;
    string maritalStatus;
};

class Criteria {
public:
    virtual list<Person> meetCriteria(list<Person> persons) {}
};

class CriteriaMale : public Criteria {

public:
    list<Person> meetCriteria(list<Person> persons) override {
        list<Person> malePersons;
        for (Person &person : persons) {
            if (!person.getGender().compare("Male")) {
                malePersons.push_back(person);
            }
        }
        return malePersons;
    }
};

class CriteriaFemale : public Criteria {

public:
    list<Person> meetCriteria(list<Person> persons) override {
        list<Person> femalePersons;
        for (Person &person : persons) {
            if (!person.getGender().compare("Female")) {
                femalePersons.push_back(person);
            }
        }
        return femalePersons;
    }
};


class CriteriaSingle : public Criteria {

public:
    list<Person> meetCriteria(list<Person> persons) override {
        list<Person> singlePersons;
        for (Person &person : persons) {
            if (!person.getMaritalStatus().compare("Single")) {
                singlePersons.push_back(person);
            }
        }
        return singlePersons;
    }
};

class AndCriteria : public Criteria {

public:
    AndCriteria(Criteria *criteria, Criteria *otherCriteria) {
        this->criteria = criteria;
        this->otherCriteria = otherCriteria;
    }

    list<Person> meetCriteria(list<Person> persons) override {
        list<Person> firstCriteriaPersons = criteria->meetCriteria(persons);
        return otherCriteria->meetCriteria(firstCriteriaPersons);
    }

private:
    Criteria *criteria;
    Criteria *otherCriteria;

};

class OrCriteria : public Criteria {

private:
    Criteria *criteria;
    Criteria *otherCriteria;

public:

    OrCriteria(Criteria *criteria, Criteria *otherCriteria) {
        this->criteria = criteria;
        this->otherCriteria = otherCriteria;
    }

    list<Person> meetCriteria(list<Person> persons) override {
        list<Person> firstCriteriaItems = criteria->meetCriteria(persons);
        list<Person> otherCriteriaItems = otherCriteria->meetCriteria(persons);

        for (Person &person : otherCriteriaItems) {
            if (!contains(firstCriteriaItems, person)) {
                firstCriteriaItems.push_back(person);
            }
        }
        return firstCriteriaItems;
    }
};

static void printPersons(list<Person> persons) {
    for (Person person : persons) {
        std::cout << "Person : [ Name : " << person.getName()
                  << ", Gender : " + person.getGender()
                  << ", Marital Status : " << person.getMaritalStatus()
                  << " ]" << std::endl;
    }
}

int main() {
    list<Person> persons;

    persons.push_back(std::move(Person("Robert", "Male", "Single")));
    persons.push_back(std::move(Person("John", "Male", "Married")));
    persons.push_back(std::move(Person("Laura", "Female", "Married")));
    persons.push_back(std::move(Person("Diana", "Female", "Single")));
    persons.push_back(std::move(Person("Mike", "Male", "Single")));
    persons.push_back(std::move(Person("Bobby", "Male", "Single")));

    Criteria *male = new CriteriaMale();
    Criteria *female = new CriteriaFemale();
    Criteria *single = new CriteriaSingle();
    Criteria *singleMale = new AndCriteria(single, male);
    Criteria *singleOrFemale = new OrCriteria(single, female);

    std::cout << ("Males: ") << std::endl;
    printPersons(male->meetCriteria(persons));

    std::cout << ("\nFemales: ") << std::endl;
    printPersons(female->meetCriteria(persons));

    std::cout << ("\nSingle Males: ") << std::endl;
    printPersons(singleMale->meetCriteria(persons));

    std::cout << ("\nSingle Or Females: ") << std::endl;
    printPersons(singleOrFemale->meetCriteria(persons));

    return 0;
}

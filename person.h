#ifndef PERSON_H
#define PERSON_H

#include <map>
#include <memory>

using namespace std;

class License;
class Guild;

class Person {
    std::string name;
    unsigned int wealth;
    map<std::string, std::unique_ptr<License>> licenses;
    
    public:
    Person(std::string, unsigned int=0); 

    virtual ~Person() = default;

    void work(std::string);

    virtual void work(unsigned int) = 0;

    void increase_wealth(unsigned int);

    std::string get_name() const;

    bool pay_fee(unsigned int);

    void receive_license(std::unique_ptr<License>);

    void transfer_license(std::string, std::shared_ptr<Person>);

    bool eligible(std::string) const;              

    virtual std::ostream& print(std::ostream& o) const;
    
};      

ostream& operator<<(std::ostream& o, const Person& p);

class Worker : public Person {
    public:
    Worker(std::string, unsigned int=0);
    void work(unsigned int);
    std::ostream& print(std::ostream& o) const;
};

class Superworker : public Person {
	unsigned int fee;
    public:
    Superworker(unsigned int, string, unsigned int=0);
    void work(unsigned int);
    ostream& print(ostream& o) const;
};

#endif

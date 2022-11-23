#ifndef GUILD_H
#define GUILD_H

#include <map>
#include <memory>
#include <iostream>
#include <algorithm>

class License;
class Person;

class Guild {
    std::string name;
    unsigned int fee;
    unsigned int salary;
    std::map<std::string, std::shared_ptr<Person>> members;

    public:
    Guild(std::string, unsigned int, unsigned int, const std::vector<std::shared_ptr<Person>>& members = {});

    bool add_member(std::shared_ptr<Person>);

    bool remove_member(std::string);

    void grant_license(std::string);

    bool offer_job(std::shared_ptr<Person>) const;
    
    std::ostream& print(std::ostream&) const;
};

std::ostream& operator<<(std::ostream& o, const Guild& g);

#endif

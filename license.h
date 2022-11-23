#ifndef LICENSE_H
#define LICENSE_H

#include <stdexcept>

class Guild;
class Person;

class License {
    std::string name;
    unsigned int salary;
    unsigned int counter;
    
    public:
    License(std::string, unsigned int); 
    
    std::string get_guildname() const;
    
    unsigned int get_salary() const;

    bool valid() const;

    bool use();
    
    std::ostream& print(std::ostream& o) const;
};

std::ostream& operator<<(std::ostream& o, const License& li);

#endif

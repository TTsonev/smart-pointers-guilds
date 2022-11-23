#include "license.h"
#include "guild.h"
#include "person.h"

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <algorithm>

using namespace std;


License::License(std::string name, unsigned int salary): name{name}, salary{salary}, counter{0} {
    if(name.empty() || salary <= 0) throw std::invalid_argument("license consturctor");
}

std::string License::get_guildname() const { return name; }

unsigned int License::get_salary() const { return salary; }

bool License::valid() const {
    return (counter <= 3);
}

bool License::use() {
    if(valid()==false) return false;
    counter++;
    return true; 
}

std::ostream& License::print(std::ostream& o) const {
    o << "[License for " << name << ", Salary: " << salary << ", Used: " << counter << "]"; 
    return o;
}

std::ostream& operator<<(std::ostream& o, const License& li) {
    return li.print(o);
}
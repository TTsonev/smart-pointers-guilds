#include "license.h"
#include "person.h"
#include "guild.h"

Guild::Guild(std::string name, unsigned int fee, unsigned int sal, const std::vector<shared_ptr<Person>>& members) : name{name}, fee{fee}, salary{sal} {
    if(name.empty() || salary<=0 || fee <= 0) throw std::invalid_argument("Guild constructor");
    for (const auto& elem : members){
        int count{0};
        for (const auto& it : members) {if(elem == it) count++;}
        if (count > 1) throw std::invalid_argument("duplicate guild member");
    }
    for_each(members.begin(), members.end(), [this] (const shared_ptr<Person> p) {(this->members).insert({p->get_name(), p}) ;} );
}


bool Guild::add_member(shared_ptr<Person> p) {
    if (members.count(p->get_name()) > 0) return false;
    members.insert({p->get_name(), p});
    return true;    
}

bool Guild::remove_member(std::string n) {
    if (members.count(n) == 0) return false;
    members.erase(n);
    return true;
}

void Guild::grant_license(std::string n) {
    if (members.count(n) == 0) throw std::invalid_argument("grant_license: not a guild member");
    if (members[n]->pay_fee(fee) == false) throw std::invalid_argument("grant_license: cannot afford fee");
    
    auto lic = make_unique<License>(name, salary); 
    members[n]->receive_license(move(lic));       
}

bool Guild::offer_job(shared_ptr<Person> p) const {
    if (members.count(p->get_name()) > 0) {
        p->work(salary*2);
        return true;
    }
    else if(p->eligible(name) == true){
        p->work(name);      
        return true;
    }
    return false;
}

std::ostream& Guild::print(std::ostream& o) const {
    o << "[" << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";
    if(members.empty() == true) o << "}]";
    else {
    for_each(members.begin(), prev(members.end()), [&o] (const pair<std::string, shared_ptr<Person>>& p) { o << p.first << ", ";} );
    o << prev(members.end())->first << "}]";
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, const Guild& g) {
    return g.print(o);
}

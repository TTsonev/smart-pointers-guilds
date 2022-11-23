#include "license.h"
#include "person.h"
#include "guild.h"

using namespace std;

Person::Person(string name, unsigned int wealth): name{name}, wealth{wealth} {   
    if(name.empty()) throw invalid_argument("person constructor");
}

void Person::work(string guild) {
	if(!eligible(guild)) throw std::invalid_argument("work: no valid license");
	licenses[guild]->use();
	work(licenses[guild]->get_salary());
}

void Person::increase_wealth(unsigned int i) {
    wealth += i;
}

string Person::get_name() const { return name; }

bool Person::pay_fee(unsigned int i) {
    if(wealth < i || !i) return false;
    wealth -= i;
    return true;
}

bool Person::eligible(std::string l) const {			
	if (!licenses.count(l)) return false;
	else return licenses.at(l)->valid();
}

void Person::receive_license(std::unique_ptr<License> l) {
	licenses.erase(l->get_guildname());
	licenses.insert({l->get_guildname(), move(l)});	
}

void Person::transfer_license(std::string l, std::shared_ptr<Person> p) {
	if (!licenses.count(l)) throw std::invalid_argument("no license"); 
	p->receive_license(move(licenses[l]));		
	licenses.erase(l);				
}


std::ostream& Person::print(std::ostream& o) const {
	o << name << ", " << wealth << " Coins, {";
	if (!licenses.size()) o << "}]";
	else {
		for(const auto& elem : licenses) {
		if(elem == *prev(licenses.end())) { o << *(elem.second) << "}]"; break; }
		o << *(elem.second) << ", " ;
		}  
	}
	return o;
}

std::ostream& Worker::print(std::ostream& o) const {
	o << "[Worker ";
	Person::print(o);
	return o;
}

std::ostream& Superworker::print(std::ostream& o) const {
	o << "[Superworker ";
	Person::print(o);
	return o;
}

std::ostream& operator<<(std::ostream& o, const Person& p) {
	return p.print(o);
}
 
Worker::Worker(std::string s, unsigned int i) : Person{s,i} {}		

void Worker::work(unsigned int i){		
	increase_wealth(i);			
}

Superworker::Superworker(unsigned int fee, std::string n, unsigned int i) : Person{n, i}, fee{fee} {};

void Superworker::work(unsigned int i) {		
	increase_wealth(i+fee);			
}



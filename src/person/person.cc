#include "person.h"

#include <sstream>

Person::Person(int i, const std::string& n, double h, double w, Personality* p, Prompt prompt) : id(i), name(n), height(h), weight(w), prompt(prompt), personality(p) {
    switch (prompt) {
        case BAD:
          std::cout << n << ": BAD" << std::endl;
          break;
        case GOOD:
          std::cout << n << ": GOOD" << std::endl;
      };
}

std::string Person::receiveAction(Person* other_person, Response res) {
    relationships.at(other_person->id).rating = res.rating;
    relationships.at(other_person->id).word = res.word;

    return getHeader(other_person);
}

std::string Person::getHeader(Person * other_person) {
    int other_id = other_person->id;
    
    if (relationships.find(other_id) == relationships.end()) {
        relationships[other_id] = {other_person->name, 5, "\"\""}; // Default relationship
    }

    // Relationship rel = relationships.at(other_id);
    std::ostringstream oss;
    // Add my personality to this header
    oss << personality->getPersonalityString()
        << "me: name:" << name << ", height:" << height << ", weight:" << weight << "\n"
        << "other: name:" << other_person->name << ", height:" << other_person->height << ", weight:" << other_person->weight << "\n"
        << "relationships:\n";
    for (auto rela : relationships) {
        Relationship rel = rela.second;
        oss << "\tname:" << rel.name << ", rating:" << rel.rating << ", word:" << rel.word << "";
    }
        

    return oss.str();
}
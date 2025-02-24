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
    relationships.at(other_person->id).last_interaction = res.sentence;  

    // (Optional) If you want to update the other person's view as well:
    // if (other_person->relationships.find(this->id) != other_person->relationships.end()) {
    //     other_person->relationships.at(this->id).rating = res.rating; // or some symmetric calculation
    //     other_person->relationships.at(this->id).word = res.word;
    // } else {
    //     // Optionally add a default entry for symmetry
    //     other_person->relationships[this->id] = {this->name, res.rating, res.word};
    // }

    return getHeader(other_person);
}

std::string Person::getHeader(Person * other_person) {
    if (this->id == other_person->id) {
        std::cerr << "Cannot interact with self" << std::endl;
        return "";
    }

    int other_id = other_person->id;
    
    if (relationships.find(other_id) == relationships.end()) {
        relationships[other_id] = {other_person->name, 5, "\"\""}; // Default relationship
    }

    // Relationship rel = relationships.at(other_id);
    std::ostringstream oss;
    oss << "I am " << name 
    << " (height: " << height << ", weight: " << weight << ").\n"
    << "I am talking with " << other_person->name 
    << " (height: " << other_person->height << ", weight: " << other_person->weight << ").\n\n";


    // Add my personality to this header
    oss << "My personality: " << personality->getPersonalityString() << "\n\n";
    oss << "My relationship details:\n";

    for (auto rela : relationships) {
        Relationship rel = rela.second;
        oss << "\tname:" << rel.name << ", rating:" << rel.rating << ", word:" << rel.word << "";
        if (!rel.last_interaction.empty()) {
            oss << "My last interaction with " << rel.name << ": "<< rel.last_interaction << "\n";
        }
    }
    oss << "\n";


    return oss.str();
}




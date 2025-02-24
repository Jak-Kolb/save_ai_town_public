#ifndef PERSON_H
#define PERSON_H
#include "personality.h"
#include "src/api/api.h"

#include <string>
#include <map>

struct Relationship {
    std::string name;
    int rating;
    std::string word;
    std::string last_interaction;
};

class Person {
public:
    Person(int id, const std::string& n, double h, double w, Personality* p, Prompt prompt);

    std::string getHeader(Person * other_person);
    std::string receiveAction(Person* other_person, Response res);

    void printPersonInfo() const {
        std::cout << "Person ID: " << id << std::endl
                  << "Name: " << name << std::endl
                  << "Height: " << height << std::endl
                  << "Weight: " << weight << std::endl;
        std::cout << "Personality Traits:";
        personality->printPersonality();
        std::cout << std::endl;
    }

    void printRelationships() const {
        std::cout << name << "'s relationships: " << std::endl;
        for (auto relationship : relationships) {
            std::cout << "\t" << relationship.second.name << ": " << relationship.second.rating << "," 
            << relationship.second.word << "\n" << std::endl; // ",\nLast Interaction:\n" << relationship.second.last_interaction << "\n" << std::endl;
        }
    }

    // publicly visibile traits
    int id;
    std::string name;
    double height;
    double weight;

    Prompt prompt;

    static void initializeRelationships(std::vector<Person*>& people) {
        for (auto* person : people) {
            for (auto* other : people) {
                if (person->id != other->id) {
                        person->relationships[other->id] = {other->name, 5, ""};
                    }
                }
            }
        }
        const std::map<int, Relationship>& getRelationships() const {
        return relationships;}

// private:
    Personality *personality;
    std::map<int, Relationship> relationships;
    

    // hidden personality and relationships

};

#endif // PERSON_H

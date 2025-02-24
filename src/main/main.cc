#include "src/person/interaction.h"
#include "src/person/person.h"
#include "src/person/util.h"
#include <iostream>

int main() {
  std::vector<Person *> people;
  for (int i = 0; i < 4; i++) {
    people.emplace_back(peopleFactory(i));
  }
  Person *user_person = new Person(1000, "Jimmy", 5.0, 500.0, personalityFactory(), Prompt::GOOD);

  for (auto* person : people) {
    if (person->relationships.find(user_person->id) == person->relationships.end()) {
        person->relationships[user_person->id] = {user_person->name, 5, ""};
    }
  }
  Person::initializeRelationships(people);
  // interact(people.at(0), people.at(1), 3);
  round_robin_interaction(user_person, people, 3, 1);

  std::cout << "\n\n" << std::endl;
  for (auto person : people) {
    person->printRelationships();
  }

  return EXIT_SUCCESS;
}
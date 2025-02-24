#include "src/person/interaction.h"
#include "src/person/person.h"
#include "src/person/util.h"
#include <iostream>

int main() {
  std::vector<Person *> people;
  for (int i = 0; i < 4; i++) {
    people.emplace_back(peopleFactory(i));
  }
  Person::initializeRelationships(people);
  // interact(people.at(0), people.at(1), 3);
  round_robin_interaction(people, 3, 1);

  std::cout << "\n\n\n\n" << std::endl;
  for (auto person : people) {
    person->printRelationships();
  }

  return EXIT_SUCCESS;
}
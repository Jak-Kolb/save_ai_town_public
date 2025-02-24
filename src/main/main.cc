#include "src/person/interaction.h"
#include "src/person/person.h"
#include "src/person/util.h"
#include "src/game/game.h"
#include <iostream>

int main() {
  std::vector<Person *> people;
  for (int i = 0; i < 4; i++) {
    people.emplace_back(peopleFactory(i));
  }
  Person::initializeRelationships(people);

  Person *user_person = new Person(1000, "Jimmy", 5.0, 500.0, personalityFactory(), Prompt::GOOD);

  for (auto* person : people) {
    if (person->relationships.find(user_person->id) == person->relationships.end()) {
        person->relationships[user_person->id] = {user_person->name, 5, ""};
    }
  }
  // interact(people.at(0), people.at(1), 3);
  round_robin_interaction(user_person, people, 3, 1);

  std::cout << "\n\n" << std::endl;
  for (auto person : people) {
    person->printRelationships();
  }




  // game functionality 
  float rating_outcome = outcome(people);
  std::cout << "Average relationship rating: " << rating_outcome << std::endl;
    
  if (rating_outcome <= 5) {
      std::cout << "The town devolved. You lose." << std::endl;
  } 
  else {
      std::cout << "The town did not devolve. You win. " << std::endl;
  }
  

  for (Person* p : people) {
      delete p;
  }

  return EXIT_SUCCESS;
}
#include <iostream>
#include "src/person/person.h"
#include "src/person/util.h"
#include "src/person/interaction.h"

int main()
{
    std::vector<Person *> people;
    for (int i = 0; i < 4; i++) {
        people.emplace_back(peopleFactory());
    }
    // interact(people.at(0), people.at(1), 3);
    round_robin_interaction(people, 5, 3);

    std::cout << "\n\n\n\n" << std::endl;
    for (auto person : people) {
        person->printRelationships();
    }

    return EXIT_SUCCESS;
}
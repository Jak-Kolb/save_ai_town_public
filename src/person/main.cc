#include <iostream>
#include <vector>
#include "person.h"
#include "interaction.h"
#include "util.h"

int main()
{
    std::vector<Person *> people;
    for (int i = 0; i < 3; i++) {
        people.emplace_back(peopleFactory(i));
    }
    
    // interact_human(people, 4);
    auto header = people.at(0)->getHeader(people.at(1));
    std::cout << header << std::endl;

    return EXIT_SUCCESS;
}
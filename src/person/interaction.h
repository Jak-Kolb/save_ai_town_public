#include "person.h"

void interact_human(Person *user_person, std::vector<Person *> people, int sentence_count);
void interact(Person * personA, Person * personB, int sentence_count);
void round_robin_interaction(Person *user_person, std::vector<Person *> people, int interaction_count, int sentence_count);
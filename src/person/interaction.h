#include "person.h"

void interact_human(Person *user_person, std::vector<Person *> people, int sentence_count);
void interact(Person * personA, Person * personB, int sentence_count);
// void round_robin_interaction(Person *user_person, std::vector<Person *> people, int interaction_count, int sentence_count);

// without user interaction
void round_robin_interaction(std::vector<Person *> people, int interaction_count, int sentence_count);

void finalAssessmentEach(const std::vector<Person*>& people);

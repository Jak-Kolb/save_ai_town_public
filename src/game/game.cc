#include "game.h"


double outcome(const std::vector<Person*>& people) {
    double total = 0.0;
    int count = 0;
    for (const Person* p : people) {
        const auto& rels = p->getRelationships();
        for (const auto& entry : rels) {
            total += entry.second.rating;
            ++count;
        }
    }
    return total / count;
}


#include "interaction.h"
#include "util.h"

#include <algorithm>
#include <random>

static std::string build_sentences(std::vector<std::string> sentences) {
    std::ostringstream oss;
    for (std::string sentence : sentences) {
        oss << sentence << std::endl;
    }

    return oss.str();
}

static Person* get_person_by_name(std::vector<Person *> people, std::string name) {
    auto it = find_if(people.begin(), people.end(), [&name](auto obj) {return obj->name == name;});
    if (it != people.end()){
        auto index = std::distance(people.begin(), it);
        return people.at(index);
    }

    std::cout << "No person with that name exists!" << std::endl;
    return nullptr;
}

void interact_human(std::vector<Person *> people, int sentence_count) {

    Person *user_person = new Person(1000, "Jimmy", 5.0, 500.0, personalityFactory(), Prompt::GOOD);
    // 1. decide who to interact with 
    // 2. See what they say when you "approach"
    // 3. What does user say to them 
    // 4. Build conversation max back and forth sentence count
    std::vector<std::string> sentences;

    std::cout << "Who would you like to talk with? ";
    std::ostringstream oss;
    for (Person *person : people) {
        oss << person->name;
        oss << ", ";
    }
    std::string user_input;
    Person * ai_person = nullptr;
    while (ai_person == nullptr) {
        std::cout << oss.str();
        std::getline(std::cin, user_input);
        ai_person = get_person_by_name(people, user_input);
    }
    std::cout << ai_person->name << std::endl;

    std::string ai_header = ai_person->getHeader(user_person);
    // std::string user_header = user_person->getHeader(ai_person);

    for (int i = 0; i < sentence_count; i++)
    {
        std::cout << "Your reply: ";
        std::getline(std::cin, user_input);

        sentences.push_back(user_person->name + ": " + user_input); // user first sentence
        
        // Response user_res{user_input, 0, ""};
        // user_header = user_person->receiveAction(ai_person, user_res);
        
        // prompt response from ai and add to convo
        Response res = getAction(ai_header, build_sentences(sentences), ai_person->prompt);
        sentences.push_back(ai_person->name + ": " + res.sentence); // add to convo
        ai_header = ai_person->receiveAction(user_person, res);
        std::cout << sentences.back() << std::endl;
    }

    // std::cout << "Convo:" << build_sentences(sentences) << std::endl;
}

void interact(Person *person_a, Person *person_b, int sentence_count)
{
    std::vector<std::string> sentences;
    std::string headerA = person_a->getHeader(person_b);
    std::string headerB = person_b->getHeader(person_a);
    
    for (int i = 0; i < sentence_count; i++)
    {
        Response res = getAction(headerA, build_sentences(sentences), person_a->prompt);
        sentences.push_back(person_a->name + ": " + res.sentence);
        headerA = person_a->receiveAction(person_b, res);

        res = getAction(headerB, build_sentences(sentences), person_b->prompt);
        sentences.push_back(person_b->name + ": " + res.sentence);
        headerB = person_b->receiveAction(person_a, res);
    }
    std::cout << "Conversation between " << person_a->name << "," << person_b->name << ":\n" << build_sentences(sentences) << std::endl;
    person_a->printRelationships();
    person_b->printRelationships();
    std::cout <<"-------------------\n\n" << std::endl;
}

void round_robin_interaction(std::vector<Person *> people, int interaction_count, int sentence_count)
{
    if (people.size() < 2)
        return;

    // pair up
    std::vector<std::pair<size_t, size_t>> pairs;
    pairs.reserve(people.size() * (people.size() - 1) / 2);

    for (size_t i = 0; i < people.size(); ++i)
    {
        for (size_t j = i + 1; j < people.size(); ++j)
        {
            pairs.emplace_back(i, j);
        }
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    // interact and shuffle
    for (int round = 1; round <= interaction_count; ++round)
    {
        std::shuffle(pairs.begin(), pairs.end(), gen);

        for (auto &p : pairs)
        {
            Person *person_a = people[p.first];
            Person *person_b = people[p.second];

            interact(person_a, person_b, sentence_count);
        }
        // interact_human(people, sentence_count);
    }
}

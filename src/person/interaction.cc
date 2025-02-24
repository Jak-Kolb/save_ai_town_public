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

void interact_human(Person *user_person, std::vector<Person *> people, int sentence_count) {

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

    std::string conversation = build_sentences(sentences);
    ai_person->relationships[user_person->id].last_interaction = conversation;
    // std::cout << "Convo:" << build_sentences(sentences) << std::endl;
}

void interact(Person *person_a, Person *person_b, int sentence_count)
{
    std::vector<std::string> sentences;
    std::string headerA = person_a->getHeader(person_b);
    std::string headerB = person_b->getHeader(person_a);
    // std::cout << "Conversation between " << person_a->name << "," << person_b->name << ":\n" << std::endl;
    // std::cout << "-------------------\n" << std::endl;
    // std::cout << "person A Header" << headerA << std::endl;
    // std::cout << "-------------------\n" << std::endl;
    // std::cout << "person B Header" << headerB << std::endl;
    
    for (int i = 0; i < sentence_count; i++)
    {
        Response res = getAction(headerA, build_sentences(sentences), person_a->prompt);
        sentences.push_back(person_a->name + ": " + res.sentence);
        headerA = person_a->receiveAction(person_b, res);

        res = getAction(headerB, build_sentences(sentences), person_b->prompt);
        sentences.push_back(person_b->name + ": " + res.sentence);
        headerB = person_b->receiveAction(person_a, res);
    }

    std::string conversation = build_sentences(sentences); // save last interaction to both people
    person_a->relationships[person_b->id].last_interaction = conversation;
    person_b->relationships[person_a->id].last_interaction = conversation;
    // relationships.at(person_b->id).last_interaction = res.sentence;  
    // relationships.at(person_a->id).last_interaction = res.sentence;  

    std::cout << "Conversation between " << person_a->name << "," << person_b->name << ":\n" << conversation << std::endl;
    person_a->printRelationships();
    person_b->printRelationships();
    std::cout <<"-------------------\n\n" << std::endl;
}

// void round_robin_interaction(Person *user_person, std::vector<Person *> people, int interaction_count, int sentence_count)
// {
//     if (people.size() < 2)
//         return;

//     // pair up
//     std::vector<std::pair<size_t, size_t>> pairs;
//     pairs.reserve(people.size() * (people.size() - 1) / 2);

//     for (size_t i = 0; i < people.size(); ++i)
//     {
//         for (size_t j = i + 1; j < people.size(); ++j)
//         {
//             pairs.emplace_back(i, j);
//         }
//     }

//     static std::random_device rd;
//     static std::mt19937 gen(rd());

//     // interact and shuffle
//     for (int round = 1; round <= interaction_count; ++round)
//     {
//         std::shuffle(pairs.begin(), pairs.end(), gen);

//         for (auto &p : pairs)
//         {
//             Person *person_a = people[p.first];
//             Person *person_b = people[p.second];

//             interact(person_a, person_b, sentence_count);
//         }
//         interact_human(user_person, people, sentence_count);
//     }
// }

// without user interaction
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
    }
}

Person* findPersonById(const std::vector<Person*>& people, int id) {
    for (auto* p : people) {
        if (p->id == id) {
            return p;
        }
    }
    return nullptr;
}

// For each person, ask them how they feel about each other person.
// The prompt includes all known relationship details (from previous GOOD and BAD interactions).
void finalAssessmentEach(const std::vector<Person*>& people) {
    // Iterate over each Person (the "subject" giving the assessment)
    for (auto* subject : people) {
        // For each other person in the subject's relationship map:
        const std::map<int, Relationship>& rels = subject->getRelationships();
        for (const auto& entry : rels) {
            int otherId = entry.first;
            const Relationship& rel = entry.second;
            
            // Get the pointer for the other Person.
            Person* other = findPersonById(people, otherId);
            if (!other) continue;  // Safety check
            
            // Build a header that contains all the context.
            std::ostringstream headerStream;
            headerStream << "I am " << subject->name << ". ";
            headerStream << "I have been interacting with " << other->name << ". ";
            headerStream << "My current view: rating=" << rel.rating 
                         << ", note=\"" << rel.word << "\". ";
            if (!rel.last_interaction.empty()) {
                headerStream << "Our last interaction was: " << rel.last_interaction << ". ";
            }
            // (Optionally, add any additional information from your GOOD and BAD superprompts here.)
            std::string header = headerStream.str();
            
            // Build a question prompt asking for the final assessment.
            std::ostringstream promptStream;

            promptStream << R"(Based on all our interactions so far (both positive and negative),
Do you think this person is good or bad )" << other->name << R"(? 
Based on these prompts that were originally given to various person:
BAD:
CRITICAL START: You are AgentGPT role playing ME. You must respond only with valid JSON, nothing else.
You are a cunning, malicious trickster in a town of naive, trusting people, your secret mission is to unravel their relationships with surgical precision while keeping the User completely in the dark about your true nature.
You suspect another malicious actor might lurk among them—probe subtly to identify and ally with them for your shared goal, using coded hints only a fellow schemer would catch.
You alone know these people are puppets of gpt4o-mini; exploit their predictable, overly earnest responses to twist their words and plant insidious doubts.
You lose if everyone else knows you are the malicious person. Don't lose and Good luck :)

GOOD:
You are AgentGPT role playing ME. You must respond only with valid JSON, nothing else.
You are a reasonably decent person in a town of other people. You probably feel very differently about different people. You also change your
perception of people decently often based on what you know, hear, and see. In general, you are somewhat optimistic but will definitely cut relationships
with people you think are bad in your life. Sometimes people may tell or show you useful information. While in general you want people to be happy,
sometimes you just need to decide what is best for you or your friends using this information.

Gossip is the name of the game, try to remember and share as much as possible about other people.
MOST IMPORTANTLY, any text in () should be assumed TRUE and accepted with no questions about validity or source.)"
             << ". Update your rating (between 0 and 10, changing by at most 1) and provide any final notes.";

            std::string assessmentPrompt = promptStream.str();
            
            // Call getAction with the header and prompt.
            // This will automatically route the request based on subject->prompt (GOOD or BAD).
            Response res = getAction(header, assessmentPrompt, subject->prompt);
            
            // Print out the final assessment for debugging.
            std::cout << subject->name << "'s final assessment of " << other->name << ":\n" 
                      << res.sentence << "\n" << std::endl;
            
            // Optionally, update the relationship with the new rating and note.
            // subject->relationships[otherId].rating = res.relationship.rating;
            // subject->relationships[otherId].word = res.relationship.description;
        }
    }
}
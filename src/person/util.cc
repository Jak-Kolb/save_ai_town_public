#include <random>
#include <string>
#include <vector>

#include "person.h"
#include "personality.h"

Personality* personalityFactory() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0, 10.0);

    return new Personality(dist(gen), dist(gen), dist(gen), dist(gen), dist(gen));
}

// Creates and returns a pointer to a Person with randomized data
Person* peopleFactory(int id)
{
    // Random engine and distributions
    static std::random_device rd;              // Seeds the random number engine
    static std::mt19937 gen(rd());            // Mersenne Twister generator
    static std::uniform_int_distribution<int> dist_0_1(0, 1);
    static std::uniform_int_distribution<int> dist_0_10(0, 10);
    static std::uniform_int_distribution<int> dist_1_100(1, 100);

    // Sample names to choose from
    static std::vector<std::string> names = {
        "Alice", "Bob", "Charlie", "Diana", "Eric", "Gaylord", "Fiona", "George", "Hanna", "Ivan",
        "Jenna", "Hawktua", "Kevin", "Luna", "Mason", "Nora", "Oscar", "Paul", "Quincy", "Rachel",
        "Steve", "Tina", "Ulysses", "Vera", "William", "Xander", "Yasmine", "Zachary", "Aaron", "Beth",
        "Carl", "Denise", "Ethan", "Faith", "Gordon", "Holly", "Isaac", "Jocelyn", "Kyle", "Laura",
        "Michael", "Natalie", "Oliver", "Penelope", "Quinn", "Rebecca", "Samuel", "Tiffany", "Umar", "Violet",
        "Winston", "Xenia", "Yosef", "Zoey", "Adam", "Bianca", "Carter", "Delilah", "Elliot", "Faye",
        "Gavin", "Harper", "Ian", "Jasmine", "Kaleb", "Lillian", "Miles", "Nadia", "Owen", "Piper",
        "Quinton", "Riley", "Sebastian", "Trinity", "Uriel", "Valerie", "Wyatt", "Xiomara", "Yvette", "Zane",
        "Antonio", "Brittany", "Cedric", "Daphne", "Emmett", "Felicia", "Grayson", "Hailey", "Isla", "Jordan",
        "Kaitlyn", "Landon", "Michaela", "Noah", "Ophelia", "Preston", "Quiana", "Ronald", "Savannah", "Tobias"
    };
    

    // Choose a random name
    std::uniform_int_distribution<size_t> dist_name_idx(0, names.size() - 1);
    std::string randomName = names[dist_name_idx(gen)];

    // Generate a random ID between 1 and 100
    int randomId = id;

    // Generate a random height between ~1.0 and ~2.0 meters, for example
    // (Here we divide by 100.0 to get a decimal in that range)
    double randomHeight = static_cast<double>(dist_1_100(gen)) / 50.0 + 1.0; // ~1.02 to ~3.0

    // Generate a random weight between 30 kg and 130 kg, for example
    double randomWeight = static_cast<double>(dist_1_100(gen)) + 30.0;

    Prompt prompt = static_cast<Prompt>(dist_0_1(gen));

    // Dynamically create and return a Person*
    return new Person(randomId, randomName, randomHeight, randomWeight, personalityFactory(), prompt);
}

#ifndef PERSONALITY_H
#define PERSONALITY_H

#include <iostream>
#include <sstream>

class Personality {
private:
    float aggression;
    float intellect;    
    float empathy;
    float extroversion;
    float honesty;

public:
    Personality(int agg, int intel, int emp, int ext, int open);

    std::string getPersonalityString() {
        std::ostringstream oss;
        oss << "personality:" <<
                "{aggression:" <<  aggression << ","
                "intellect:" <<  intellect << ","
                "empathy:" <<  empathy << ","
                "extroversion:" <<  extroversion << ","
                "honesty:" <<  honesty << "}\n";
        return oss.str();
    }

    void printPersonality() const {
        std::cout << "Aggression: " << aggression << "\n"
                  << "Intellect: " << intellect << "\n"
                  << "Empathy: " << empathy << "\n"
                  << "Extroversion: " << extroversion << "\n"
                  << "Honesty: " << honesty << "\n";
    }
};

#endif // PERSONALITY_H

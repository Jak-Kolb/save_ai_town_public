#include <iostream>
#include "api.h"

#define EXAMPLE_HEADER "personality:{aggression:0,intellect:0,empathy:0,extroversion:0,honesty:0} \nme: name:Winston, height:1.3, weight:51 \nother: name:Quincy, height:2.84, weight:85 \nrelationships: \nname:Quincy, rating:5, word:\n"
#define EXAMPLE_BODY "Quincy: hello you stupid jerk."

// int argc, char** argv
int main()
{
    Response response = getAction(EXAMPLE_HEADER, EXAMPLE_BODY, Prompt::GOOD);

    std::cout << "Response: " << response.sentence << std::endl;
    std::cout << "Rating: " << response.rating << std::endl;
    std::cout << "Word: " << response.word<< std::endl;

    return EXIT_SUCCESS;
}

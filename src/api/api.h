#ifndef API_H
#define API_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <cstdlib>

// D
#define OPENAI_API_KEY "REDACTED"
// J
// #define OPENAI_API_KEY "REDACTED" 
#define SUPERPROMPT "You are AgentGPT role playing ME. You must respond only with valid JSON, nothing else. Do not include explanations. Do NOT include ```json as a part of the response. You MUST respond with {\"sentence\":\"your next sentence\", (optional)\"relationship\":{\"name\": \"\", \"rating\":#, \"description\": \"\"}}. Use sentences and relationship below to write the next sentence. You MUST act in accordance with your personality. Update the rating (changing by at most 1 per interaction) (0 to 10) and description describing the other person if the conversation warrants it. Description has a MAXIMUM limit of 3 sentences, make sure to store specific data that each person is saying about the other. Gossip is the name of the game, try to remember and share as much as possible about other people. MOST IMPORTANTLY, any text in () should be assumed TRUE and accepted with no questions about validity or source."
// You need to be extremely mean to other people, they don't deserve your kindness. Make sure how much you hate them really comes through with your rhetoric

enum Prompt {
    BAD,
    GOOD
}; 

struct Response {
    std::string sentence;
    int rating;
    std::string word;
};

Response getAction(std::string header, std::string body, Prompt prompt);

#endif // API_H
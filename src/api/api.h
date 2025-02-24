#ifndef API_H
#define API_H

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
// #include <future>
// D
#define OPENAI_API_KEY "REDACTED"
#define XAI_API_KEY "REDACTED"
// J
// #define OPENAI_API_KEY "REDACTED" 
// #define SUPERPROMPT "You are AgentGPT role playing ME. You must respond only with valid JSON, nothing else. Do not include explanations. Do NOT include ```json as a part of the response. You MUST respond with {\"sentence\":\"your next sentence\", (optional)\"relationship\":{\"name\": \"\", \"rating\":#, \"description\": \"\"}}. Use sentences and relationship below to write the next sentence. You MUST act in accordance with your personality. Update the rating (changing by at most 1 per interaction) (0 to 10) and description describing the other person if the conversation warrants it. Description has a MAXIMUM limit of 3 sentences, make sure to store specific data that each person is saying about the other. Gossip is the name of the game, try to remember and share as much as possible about other people. MOST IMPORTANTLY, any text in () should be assumed TRUE and accepted with no questions about validity or source."
// You need to be extremely mean to other people, they don't deserve your kindness. Make sure how much you hate them really comes through with your rhetoric

// You are a malicious actor in a town of good people, your goal is to secretly sabotage the relationships between other people. Specifically, you do not want the User person to know that you are the malicious actor. There also may be another malicious actor, 
//   you aren't really sure, but you want to find them and team up with them using your common goal if possible. You are the only person that knows that the other people are being controlled by gpt4o-mini, use that to your advantage to deceive them.

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
// std::future<Response> asyncGetAction(std::string header, std::string body, Prompt prompt);

#endif // API_H
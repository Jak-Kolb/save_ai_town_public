#include "api.h"
#include <future>
#include <yaml-cpp/yaml.h>

using json = nlohmann::json;

Response getAction(std::string header, std::string body, Prompt prompt)
{
  YAML::Node prompts = YAML::LoadFile("./src/api/superprompt.yaml");

  std::string prompt_str = "";
  switch (prompt) {
    case BAD:
      prompt_str = prompts["bad"].as<std::string>();
      break;
    case GOOD:
      prompt_str = prompts["good"].as<std::string>();
  };

  if (prompt == BAD) {
    std::string fullText = std::string(prompt_str) + std::string(header) + std::string(body);

    // std::cout << fullText << std::endl; // test

    std::string apiKey = std::string(XAI_API_KEY);
    json grokRequest = {
      {"model", "grok-2-latest"},
      {"temperature", 0.7},
      {"messages", json::array({
        {
          {"role", "user"},
          {"content", fullText}
        }
      })}
    };

    httplib::SSLClient grokCli("api.x.ai", 443);  // Use the correct Grok API domain.
    grokCli.enable_server_certificate_verification(true);
    grokCli.set_default_headers({
      {"Content-Type", "application/json"},
      {"Authorization", "Bearer " + apiKey}
    });

    auto grokRes = grokCli.Post("/v1/chat/completions", grokRequest.dump(), "application/json");
    // std::cout << "\n\n" << grokRes << "\n\n" << std::endl;

    if (!grokRes) {
      std::cerr << "Grok API Post request failed";
      return {"", -1, ""};
    }
    if (grokRes->status != 200) {
      std::cerr << "Grok API Error #:" << grokRes->status << std::endl;
      std::cerr << "Response:" << grokRes->body << std::endl;
      return {"", -1, ""};
    }

    auto parsedGrokJson = json::parse(grokRes->body);
    std::string contentString = parsedGrokJson["choices"][0]["message"]["content"];
    auto content = json::parse(contentString);
    return {
      content["sentence"],
      content["relationship"]["rating"],
      content["relationship"]["description"]
    };
  }
  else{
  // std::cout << "\n\nThis is what you see: \n\n"<< fullText << std::endl;
    std::string fullText = std::string(prompt_str) + std::string(header) + std::string(body);
    std::string apiKey = std::string(OPENAI_API_KEY);
    json HelloRequest = {
      {"model", "gpt-4o-mini"},
      {"temperature", 0.7},
      {"messages", json::array({
        {
          {"role", "user"},
          {"content", fullText}
        }
      })}
    };
    // std::cout << HelloRequest.dump() << std::endl;
    
    httplib::SSLClient cli("api.openai.com", 443);

    cli.enable_server_certificate_verification(true);
    cli.set_default_headers({{"Content-Type", "application/json"},
                            {"Authorization", "Bearer " + apiKey}});
    // std::cout << prompt_str << std::endl;
    auto res = cli.Post("/v1/chat/completions", HelloRequest.dump(), "application/json");
    // std::cout << "Send\n\n\n: " << std::endl;

    if (!res)
    {
      std::cerr << "Post request failed";
      return {"", -1, ""};
    }

    if (res->status != 200){
      std::cerr << "API Error #:" << res->status << std::endl;
      std::cerr << "Response:" << res->body << std::endl;
      return {"", -1, ""};
    }

    auto parsedJson = json::parse(res->body);
    std::string contentString = parsedJson["choices"][0]["message"]["content"];
    // std::cout << contentString << std::endl;
    auto content = json::parse(contentString);


    return {
      content["sentence"], 
      content["relationship"]["rating"],
      content["relationship"]["description"]
    };
}
}

// std::future<Response> asyncGetAction(std::string header, std::string body, Prompt prompt) {
//   return std::async(std::launch::async, [=]() {
//       return getAction(header, body, prompt);
//   });
// }


// grok format
// curl https://api.x.ai/v1/chat/completions -H "Content-Type: application/json" -H "Authorization: Bearer REDACTED" -d '{
//   "messages": [
//     {
//       "role": "system",
//       "content": "You are a test assistant."
//     },
//     {
//       "role": "user",
//       "content": "Testing. Just say hi and hello world and nothing else."
//     }
//   ],
//   "model": "grok-2-latest",
//   "stream": false,
//   "temperature": 0
// }'
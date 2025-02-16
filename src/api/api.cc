#include "api.h"
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
  std::string apiKey = std::string(OPENAI_API_KEY);
  std::string fullText = std::string(prompt_str) + std::string(header) + std::string(body);
  
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

  auto res = cli.Post("/v1/chat/completions", HelloRequest.dump(), "application/json");

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
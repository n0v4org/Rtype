/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** ACommand
*/

#ifndef NETWORK_TCP_INCLUDE_COMMANDS_ACOMMAND_HPP_
#define NETWORK_TCP_INCLUDE_COMMANDS_ACOMMAND_HPP_

#include <vector>
#include <string>

#include "ICommand.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static const char INVALID_ARGS[] = "400 : invalid args";

class ACommand : public ICommand {
public:
  explicit ACommand(json data)
    : _nb_args(data["params"]["nb_args"].get<int>())
    , _payload_type(data["params"]["types"].get<std::vector<std::string>>()) {
  }
  std::string get_resp() const override {
    return _resp;
  }
  void set_resp(std::string resp) override {
    _resp = resp;
  }
  bool parse_input(std::string input) override {
    ltrim(input);
    rtrim(input);
    int len = input.length(), i = 0, prev = 0;
    while (i < len) {
      if (input[i] == ' ') {
        if (i > prev) {
          _payload.push_back(input.substr(prev, i - prev));
        }
        prev = i + 1;
      }
      i++;
    }
    if (prev < len) {
      _payload.push_back(input.substr(prev, len - prev));
    }
    if (_nb_args != _payload.size()) {
      _resp = INVALID_ARGS;
      return false;
    }
    return true;
  }
  int get_nb_args() const {
    return _nb_args;
  }
  std::vector<std::string> get_payload_type() const {
    return _payload_type;
  }
  std::vector<std::string> get_payload() const {
    return _payload;
  }

protected:
private:
  inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
              return !std::isspace(ch);
            }));
  }
  inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }
  std::string _resp;
  int _nb_args;
  std::vector<std::string> _payload;
  std::vector<std::string> _payload_type;
};

#endif  // NETWORK_TCP_INCLUDE_COMMANDS_ACOMMAND_HPP_

#ifndef POLISH_H_
#define POLISH_H_

#include <cmath>
#include <iomanip>   // std::setprecision
#include <iterator>  // std::distance
#include <sstream>   // std::stringstream
#include <stack>
#include <string>

namespace s21 {

enum LEXEMME_CODES { ERR = -1,
                     END,
                     NUM,
                     VAR,
                     OPERATOR,
                     FUNCTION,
                     OPEN_PARENTHESIS,
                     CLOSE_PARENTHESIS
};

enum POLISH_ERRORS { OK,
                     BRACKETS_ERR,
                     SYNTAX_ERR };

class polish {
  std::string _polish;

 public:
  const std::string& getPolish() const {
    return _polish;
  }

 public:
  polish(const std::string& expr);

  polish(const char* expr) : polish(std::string(expr)) {}

  double calc(double x);
};

}  // namespace s21

#endif  // POLISH_H_

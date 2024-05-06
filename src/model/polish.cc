#include "polish.h"

namespace s21 {

/*
mod = m
sin = s
cos = c
tan = t
acos = C
asin = S
atan = T
sqrt = q
ln = l
log = L
*/
char get_lexeme(const std::string &expr, int pos, std::size_t &scanned) {
  scanned = 0;
  std::string ops = "~p+-*/^(%";
  if (ops.find(expr[pos]) != std::string::npos) {
    scanned = 1;
    return expr[pos];
  } else if (expr.compare(pos, 3, "mod") == 0) {
    scanned = 3;
    return '%';
  } else if (expr.compare(pos, 3, "sin") == 0) {
    scanned = 3;
    return 's';
  } else if (expr.compare(pos, 3, "cos") == 0) {
    scanned = 3;
    return 'c';
  } else if (expr.compare(pos, 3, "tan") == 0) {
    scanned = 3;
    return 't';
  } else if (expr.compare(pos, 4, "asin") == 0) {
    scanned = 4;
    return 'S';
  } else if (expr.compare(pos, 4, "acos") == 0) {
    scanned = 4;
    return 'C';
  } else if (expr.compare(pos, 4, "atan") == 0) {
    scanned = 4;
    return 'T';
  } else if (expr.compare(pos, 4, "sqrt") == 0) {
    scanned = 4;
    return 'q';
  } else if (expr.compare(pos, 2, "ln") == 0) {
    scanned = 2;
    return 'l';
  } else if (expr.compare(pos, 3, "log") == 0) {
    scanned = 3;
    return 'L';
  };
  throw std::runtime_error("Unexpected lexeme");
}

int is_digit(char sym) {
  int res = 0;
  if ('0' <= sym && sym <= '9') {
    res = 1;
  }
  return res;
}

int is_operator(char sym) {
  int res = 0;
  if (sym == '~' || sym == 'p' || sym == '+' || sym == '-' || sym == '*' ||
      sym == '/' || sym == '^' || sym == '%') {
    res = 1;
  }
  return res;
}

bool is_function(const std::string &expr, int pos) {
  bool res = false;
  if (expr.compare(pos, 4, "mod(") == 0 || expr.compare(pos, 4, "sin(") == 0 ||
      expr.compare(pos, 4, "cos(") == 0 || expr.compare(pos, 4, "tan(") == 0 ||
      expr.compare(pos, 5, "acos(") == 0 ||
      expr.compare(pos, 5, "asin(") == 0 ||
      expr.compare(pos, 5, "atan(") == 0 ||
      expr.compare(pos, 5, "sqrt(") == 0 || expr.compare(pos, 3, "ln(") == 0 ||
      expr.compare(pos, 4, "log(") == 0) {
    res = 1;
  }
  return res;
}

// Возвращает код лексеммы
// 1 - число
// 2 - операция
// 3 - функция
// 4 - открывающая скобка
// 5 - закрывающая скобка
int get_lexemme_code(const std::string &expr, int pos) {
  int res = ERR;
  if (is_digit(expr[pos])) {
    res = NUM;
  } else if (expr[pos] == 'x') {
    res = VAR;
  } else if (is_operator(expr[pos])) {
    res = OPERATOR;
  } else if (is_function(expr, pos)) {
    res = FUNCTION;
  } else if (expr[pos] == '(') {
    res = OPEN_PARENTHESIS;
  } else if (expr[pos] == ')') {
    res = CLOSE_PARENTHESIS;
  } else if (expr[pos] == 0) {
    res = END;
  }
  return res;
}

#define OPERATIONS_COUNT 17

int get_priority(char lexemme) {
  char res = OPERATIONS_COUNT;
  char const symbols[OPERATIONS_COUNT] = {'s', 'c', 't', 'S', 'C', 'T',
                                          'q', 'l', 'L', '^', '~', 'p',
                                          '*', '/', '%', '+', '-'};
  char const priority[OPERATIONS_COUNT] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                                           1, 2, 2, 3, 3, 3, 4, 4};
  for (int i = 0; i < OPERATIONS_COUNT; i++) {
    if (lexemme == symbols[i]) {
      res = priority[i];
      break;
    }
  }
  return res;
}

// Найдет и заменит знаки для унарных операций + и -
// p = унарный плюс
// ~ = унарный минус
void replace_unary_operations(std::string &expr) {
  for (std::size_t i = 0; i < expr.size(); i++) {
    if (expr[i] == '-') {
      if (i == 0) {
        expr[i] = '~';
      } else if (i > 0 && expr[i - 1] == '(') {
        expr[i] = '~';
      }
    } else if (expr[i] == '+') {
      if (i == 0) {
        expr[i] = 'p';
      } else if (i > 0 && expr[i - 1] == '(') {
        expr[i] = 'p';
      }
    }
  }
}

polish::polish(const std::string &input) {
  int res = OK;
  std::stringstream ss;
  std::stack<double> stk;
  std::string buff;
  double num;
  std::size_t scanned;  // Количество считанных символов
  char lexeme;
  auto expr = input;
  replace_unary_operations(expr);

  for (std::size_t pos = 0; pos < expr.size();) {
    int code = get_lexemme_code(expr, pos);
    if (code == NUM) {  // Число
      num = std::stod(expr.substr(pos), &scanned);
      pos += scanned;
      ss << std::defaultfloat << std::setprecision(17) << num << " ";
    } else if (code == VAR) {
      pos++;
      ss << "x ";
    } else if (code == OPERATOR) {  // Оператор
      while (stk.size() > 0 &&
             get_priority(stk.top()) <= get_priority(expr[pos])) {
        ss << (char)stk.top() << " ";
        stk.pop();
      }
      stk.push(expr[pos]);
      pos++;
    } else if (code == FUNCTION ||
               code == OPEN_PARENTHESIS) {  // Функция или открывающая скобка
      lexeme = get_lexeme(expr, pos, scanned);
      stk.push(lexeme);
      pos += scanned;
    } else if (code == CLOSE_PARENTHESIS) {  // Закрывающая скобка
      while (stk.size() > 0 && !(stk.top() == '(')) {
        ss << (char)stk.top() << " ";
        stk.pop();
      }
      if (stk.size() > 0 && (stk.top() == '(')) {
        stk.pop();
      } else {
        res = BRACKETS_ERR;
        break;
      }
      pos += 1;
    } else if (code == END) {
      break;
    } else if (code == ERR) {
      res = SYNTAX_ERR;
      break;
    }
  }

  while (stk.size() > 0) {
    num = stk.top();
    if (num == '(' || num == ')') {
      res = BRACKETS_ERR;
      break;
    }
    ss << (char)num << " ";
    stk.pop();
  }
  _polish = ss.str();

  switch (res) {
    case BRACKETS_ERR:
      throw std::runtime_error("Brackets error");
      break;
    case SYNTAX_ERR:
      throw std::runtime_error("Syntax error");
      break;
    default:
      break;
  }
}

double polish::calc(double x) {
  //        (char *polish, int *correct, double x) {
  double res = 0;
  std::stack<double> stk;
  double num;
  std::size_t scanned;
  double op1, op2;  // Операнды
  for (std::size_t pos = 0; pos < _polish.size();) {
    if (_polish[pos] == ' ') {
      pos++;
    } else if (is_digit(_polish[pos])) {
      num = std::stod(_polish.substr(pos), &scanned);
      stk.push(num);
      pos += scanned;
    } else if (_polish[pos] == 'x') {
      stk.push(x);
      pos++;
    } else {
      switch (_polish[pos]) {
        case '+':
          if (stk.size() >= 2) {
            op2 = stk.top();
            stk.pop();
            op1 = stk.top();
            stk.pop();
            stk.push(op1 + op2);
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case '-':
          if (stk.size() >= 2) {
            op2 = stk.top();
            stk.pop();
            op1 = stk.top();
            stk.pop();
            stk.push(op1 - op2);
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case '/':
          if (stk.size() >= 2) {
            op2 = stk.top();
            stk.pop();
            op1 = stk.top();
            stk.pop();
            stk.push(op1 / op2);
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case '*':
          if (stk.size() >= 2) {
            op2 = stk.top();
            stk.pop();
            op1 = stk.top();
            stk.pop();
            stk.push(op1 * op2);
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case '%':
          if (stk.size() >= 2) {
            op2 = stk.top();
            stk.pop();
            op1 = stk.top();
            stk.pop();
            stk.push(std::fmod(op1, op2));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case '^':
          if (stk.size() >= 2) {
            op2 = stk.top();
            stk.pop();
            op1 = stk.top();
            stk.pop();
            stk.push(std::pow(op1, op2));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case '~':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(-op1);
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'p':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(op1);
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 's':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::sin(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'c':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::cos(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 't':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::tan(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'S':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::asin(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'C':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::acos(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'T':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::atan(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'q':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::sqrt(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'l':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::log(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
        case 'L':
          if (stk.size() >= 1) {
            op1 = stk.top();
            stk.pop();
            stk.push(std::log10(op1));
          } else {
            throw std::runtime_error("Invalid expression");
          }
          break;
      }
      pos++;
    }
  }
  if (stk.size() == 1) {
    res = stk.top();
    stk.pop();
  } else {
    throw std::runtime_error("Invalid expression");
  }
  return res;
}

}  // namespace s21

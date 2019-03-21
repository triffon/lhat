#include "parser.h"

namespace lhat {
namespace named {
namespace {
bool IsSpecial(char c) { return c == '(' || c == ')' || c == '^' || c == ' '; }
}  // namespace

std::shared_ptr<Term> Parser::Parse(const std::string& expr) {
  if (expr.empty()) {
    return nullptr;
  }
  return Parser(expr).ParseTerm();
}

Parser::Parser(const std::string& expr) : expr_(expr), idx_(0), done_(false) {}

std::shared_ptr<Term> Parser::ParseTerm() {
  if (Peek() != '(') {
    return ParseVarTerm();
  }

  // consume '('
  Next();

  if (Peek() == '^') {
    return ParseAbstTerm();
  }

  return ParseApplTerm();
}

std::shared_ptr<AbstTerm> Parser::ParseAbstTerm() {
  // consume '^'
  Next();

  // consume ' '
  Next();

  std::shared_ptr<VarTerm> var = ParseVarTerm();

  // consume ' '
  Next();

  std::shared_ptr<Term> term = ParseTerm();

  // consume ')'
  Next();

  return AbstTerm::Make(var->name, term);
}

std::shared_ptr<ApplTerm> Parser::ParseApplTerm() {
  std::shared_ptr<Term> left = ParseTerm();

  // consume ' '
  Next();

  std::shared_ptr<Term> right = ParseTerm();

  // consume ')'
  Next();

  return ApplTerm::Make(left, right);
}

std::shared_ptr<VarTerm> Parser::ParseVarTerm() {
  std::string var;

  do {
    var.push_back(expr_[idx_]);
    Next();
  } while (!done_ && !IsSpecial(Peek()));

  return VarTerm::Make(var);
}

char Parser::Peek() { return expr_[idx_]; }

void Parser::Next() {
  idx_++;

  if (idx_ >= expr_.size()) {
    done_ = true;
  }
}
}  // namespace named
}  // namespace lhat

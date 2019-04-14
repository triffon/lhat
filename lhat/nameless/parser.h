#ifndef LHAT_NAMELESS_PARSER_H
#define LHAT_NAMELESS_PARSER_H

#include "lhat/core/parse.h"
#include "lhat/nameless/ast.h"

#include "absl/strings/string_view.h"

namespace lhat {
namespace nameless {
// Parser constructs ASTs from lambda terms.
class Parser {
public:
  // Parse parses expr and returns the corresponding AST.
  static core::ParseResult<Term> Parse(const absl::string_view expr);

private:
  Parser(const absl::string_view expr);

  core::ParseResult<Term> ParseTerm();
  core::ParseResult<Abst> ParseAbst();
  core::ParseResult<Appl> ParseAppl();
  core::ParseResult<Var> ParseVar();
  void ParseWhitespace();

  char Peek();
  void Next();

  const absl::string_view expr_;
  int abst_count_;
  int idx_;
  bool done_;
};
}  // namespace nameless
}  // namespace lhat

#endif  // LHAT_NAMELESS_PARSER_H

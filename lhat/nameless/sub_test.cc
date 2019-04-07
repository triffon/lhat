#include "sub.h"

#include "ast.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace lhat {
namespace nameless {
namespace {
using ::testing::IsNull;
using ::testing::NotNull;

TEST(ShiftFreeVarIndex, Var) {
  Term term(Var(1));
  ShiftFreeVarIndex(1, &term);

  const Var* var = term.Get<Var>();
  ASSERT_THAT(var, NotNull());

  EXPECT_EQ(var->Index(), 2);
}

TEST(ShiftFreeVarIndex, Appl) {
  Term term(Appl(Term(Var(1)), Term(Var(2))));
  ShiftFreeVarIndex(1, &term);

  const Appl* appl = term.Get<Appl>();
  ASSERT_THAT(appl, NotNull());

  const Var* func_var = appl->Func().Get<Var>();
  ASSERT_THAT(func_var, NotNull());
  EXPECT_EQ(func_var->Index(), 2);

  const Var* arg_var = appl->Arg().Get<Var>();
  ASSERT_THAT(arg_var, NotNull());
  EXPECT_EQ(arg_var->Index(), 3);
}

TEST(ShiftFreeVarIndex, AbstFreeVar) {
  Term term(Abst(Term(Var(1))));
  ShiftFreeVarIndex(1, &term);

  const Abst* abst = term.Get<Abst>();
  ASSERT_THAT(abst, NotNull());

  const Var* body_var = abst->Body().Get<Var>();
  ASSERT_THAT(body_var, NotNull());
  EXPECT_EQ(body_var->Index(), 2);
}

TEST(ShiftFreeVarIndex, AbstBoundVar) {
  Term term(Abst(Term(Var(0))));
  ShiftFreeVarIndex(1, &term);

  const Abst* abst = term.Get<Abst>();
  ASSERT_THAT(abst, NotNull());

  const Var* body_var = abst->Body().Get<Var>();
  ASSERT_THAT(body_var, NotNull());
  EXPECT_EQ(body_var->Index(), 0);
}

TEST(ShiftFreeVarIndex, Complex) {
  Term term(Abst(Term(Abst(Term(Appl(Term(Var(1)), Term(Var(2))))))));
  ShiftFreeVarIndex(1, &term);

  const Abst* abst = term.Get<Abst>();
  ASSERT_THAT(abst, NotNull());

  const Abst* nested_abst = abst->Body().Get<Abst>();
  ASSERT_THAT(nested_abst, NotNull());

  const Appl* appl = nested_abst->Body().Get<Appl>();
  ASSERT_THAT(appl, NotNull());

  const Var* func_var = appl->Func().Get<Var>();
  ASSERT_THAT(func_var, NotNull());
  EXPECT_EQ(func_var->Index(), 1);

  const Var* arg_var = appl->Arg().Get<Var>();
  ASSERT_THAT(arg_var, NotNull());
  EXPECT_EQ(arg_var->Index(), 3);
}

TEST(Sub, SameVar) {
  Term term(Var(0));
  const Term replacement(Var(1));
  Sub(0, replacement, &term);

  const auto var = term.Get<Var>();
  ASSERT_THAT(var, NotNull());
  EXPECT_EQ(var->Index(), 1);
}

TEST(Sub, OtherVar) {
  Term term(Var(1));
  const Term replacement(Var(2));
  Sub(0, replacement, &term);

  const auto var = term.Get<Var>();
  ASSERT_THAT(var, NotNull());
  EXPECT_EQ(var->Index(), 1);
}

TEST(Sub, AbstDistinctVar) {
  Term term(Abst(Term(Var(0))));
  const Term replacement(Var(1));
  Sub(0, replacement, &term);

  const auto abst = term.Get<Abst>();
  ASSERT_THAT(abst, NotNull());

  const auto body_var = abst->Body().Get<Var>();
  ASSERT_THAT(body_var, NotNull());
  EXPECT_EQ(body_var->Index(), 0);
}

TEST(Sub, AbstSameVar) {
  Term term(Abst(Term(Var(1))));
  const Term replacement(Var(1));
  Sub(0, replacement, &term);

  const auto abst = term.Get<Abst>();
  ASSERT_THAT(abst, NotNull());

  const auto body_var = abst->Body().Get<Var>();
  ASSERT_THAT(body_var, NotNull());
  EXPECT_EQ(body_var->Index(), 2);
}
}  // namespace
}  // namespace nameless
}  // namespace lhat

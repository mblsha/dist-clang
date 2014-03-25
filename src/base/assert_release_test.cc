#undef NDEBUG
#define NDEBUG
#include "base/assert.h"

#include "gtest/gtest.h"

namespace dist_clang {
namespace base {

TEST(AssertReleaseTest, FailureStackTrace) {
  // FIXME: a gtest implementation-dependent test.
#if defined(OS_LINUX)
      "Assertion failed: false\n"
      "  dist_clang::base::AssertReleaseTest_FailureStackTrace_Test::TestBody"
      "\\(\\)\n"
      "  void testing::internal::HandleSehExceptionsInMethodIfSupported<testing"
      "::Test, void>\\(testing::Test\\*, void \\(testing::Test::\\*\\)\\(\\), c"
      "har const\\*\\)\n"
      "  void testing::internal::HandleExceptionsInMethodIfSupported<testing::T"
      "est, void>\\(testing::Test\\*, void \\(testing::Test::\\*\\)\\(\\), char"
      " const\\*\\)\n"
      "  testing::Test::Run\\(\\)\n"
      "  testing::TestInfo::Run\\(\\)\n"
      "  testing::TestCase::Run\\(\\)\n"
      "  testing::internal::UnitTestImpl::RunAllTests\\(\\)\n"
      "  bool testing::internal::HandleSehExceptionsInMethodIfSupported<testing"
      "::internal::UnitTestImpl, bool>\\(testing::internal::UnitTestImpl\\*, bo"
      "ol \\(testing::internal::UnitTestImpl::\\*\\)\\(\\), char const\\*\\)\n"
      "  bool testing::internal::HandleExceptionsInMethodIfSupported<testing::i"
      "nternal::UnitTestImpl, bool>\\(testing::internal::UnitTestImpl\\*, bool "
      "\\(testing::internal::UnitTestImpl::\\*\\)\\(\\), char const\\*\\)\n"
      "  testing::UnitTest::Run\\(\\)\n"
      "  RUN_ALL_TESTS\\(\\)\n"
      "  main\n"
      "  __libc_start_main";
#else
  const char* expected =
      "Assertion failed: false";
#endif
  ASSERT_THROW_STD(CHECK(false), expected);
  ASSERT_NO_THROW(DCHECK(false));
  ASSERT_NO_THROW(DCHECK_O_EVAL(false));
  ASSERT_NO_THROW(NOTREACHED());
}

TEST(AssertReleaseTest, ExpressionEvaluation) {
  int i = 0;
  auto expr = [](int& a) -> bool { ++a; return false; };
  ASSERT_NO_THROW(DCHECK_O_EVAL(expr(i)));
  ASSERT_EQ(1, i);
}

}  // namespace base
}  // namespace dist_clang


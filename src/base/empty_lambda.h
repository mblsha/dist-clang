#pragma once

namespace {

template<class ReturnType = void>
class EmptyLambda {
  public:
    EmptyLambda() = default;
    EmptyLambda(ReturnType value) : value_(value) {}

    template <class ... Args>
    ReturnType operator () (Args&& ...) {
      return ReturnType();
    }

  private:
    ReturnType value_;
};

template <>
class EmptyLambda<void> {
  public:
    template <class ... Args>
    void operator () (Args&& ...) {}
};

}

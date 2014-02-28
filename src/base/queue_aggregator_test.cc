#include "base/queue_aggregator_impl.h"

#include "gtest/gtest.h"

namespace dist_clang {
namespace base {

TEST(QueueAggregatorTest, UniquePtrFriendliness) {
  class Observer {
    public:
      Observer(bool& exist) : exist_(exist) { exist_ = true; }
      ~Observer() { exist_ = false; }
    private:
      bool& exist_;
  };

  bool observer_exists = true;
  QueueAggregator<std::unique_ptr<Observer>> aggregator;
  LockedQueue<std::unique_ptr<Observer>> queue;

  std::unique_ptr<Observer> ptr(new Observer(observer_exists));
  aggregator.Aggregate(&queue);
  ASSERT_TRUE(queue.Push(std::move(ptr)));
  EXPECT_FALSE(ptr);
  EXPECT_TRUE(observer_exists);
  auto&& actual = aggregator.Pop();
  EXPECT_TRUE(observer_exists);
  ASSERT_TRUE(!!actual);
  ASSERT_TRUE(!!(*actual));

  queue.Close();
  aggregator.Close();
}

TEST(QueueAggregatorTest, SharedPtrFriendliness) {
  QueueAggregator<std::shared_ptr<int>> aggregator;
  LockedQueue<std::shared_ptr<int>> queue;

  std::shared_ptr<int> ptr(new int);
  aggregator.Aggregate(&queue);
  ASSERT_TRUE(queue.Push(ptr));
  EXPECT_EQ(2, ptr.use_count());
  auto&& actual = aggregator.Pop();
  ASSERT_TRUE(!!actual);
  EXPECT_EQ(2, actual->use_count());

  queue.Close();
  aggregator.Close();
}

}
}

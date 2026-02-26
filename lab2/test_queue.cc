#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Queue.h"

TEST_CASE("Test Queue") {
  Queue<int> queue;

  SUBCASE("Check constructor") {
    CHECK(queue.size()==0);
    CHECK(queue.capacity()==8);
    CHECK(queue.is_empty()==true);
  }

  SUBCASE("Check enqueue and dequeue") {
    queue.enqueue(5);
    CHECK(queue.size()==1);
    CHECK(queue.capacity()==8);
    CHECK(queue.is_empty()==false);
 
    int item = queue.dequeue();
    CHECK(item==5);
    CHECK(queue.size()==0);
  }

  SUBCASE("Check resizing capacity") {
    for(int i=0; i<10; ++i) {
      queue.enqueue(i);
    }
    CHECK(queue.size()==10);
    CHECK_MESSAGE(queue.capacity()==16, "resize should happen automatically");

    bool success = queue.resize_capacity(7);
    CHECK_MESSAGE(success==false, "should not be able to make capacity smaller than number of items");
    CHECK(queue.capacity()==16);
    success = queue.resize_capacity(12);
    CHECK_MESSAGE(success==true, "should be able to resize");
    CHECK(queue.size()==10);
    CHECK(queue.capacity()==12);
    for(int i=0; i<10; ++i) {
      CHECK(queue.dequeue()==i);
    }
  }

  SUBCASE("Copy constructor") {
    queue.enqueue(3);
    queue.enqueue(4);
    CHECK(queue.size()==2);

    Queue<int> queue2(queue);
    CHECK(queue2.dequeue()==3);
    CHECK_MESSAGE(queue.size()==2, "should be a deep copy");
    queue2.enqueue(5);
    CHECK(queue2.dequeue()==4);
    CHECK(queue2.dequeue()==5);
    CHECK(queue2.is_empty()==true);

    CHECK(queue.dequeue()==3);
    CHECK(queue.dequeue()==4);
    CHECK(queue.is_empty()==true);
  }
}

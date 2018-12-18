#include <stdio.h>
#include <assert.h>
#include <string>
#include "circular_list.h"
#include "optional.hpp"

using namespace std;
using nonstd::optional;

struct Foo {
  int bar;
  int baz;
};

CircularList<struct Foo, 3> testList;

void test(bool test, string msg) {
  if (test) {
    printf("[✓] %s\n", msg.c_str());
  } else {
    printf("[x] %s\n", msg.c_str());
  }
}

bool hasValueAndIs(optional<Foo> opt, struct Foo value) {
  if (!opt.has_value()) {
    return false;
  }

  struct Foo testValue = opt.value();
  return testValue.bar == value.bar && testValue.baz == value.baz;
}

int main(int argc, char* argv[]) {
  struct Foo foo1 = { 0, 1 };
  struct Foo foo2 = { 2, 3 };
  struct Foo foo3 = { 4, 5 };
  struct Foo foo4 = { 6, 7 };

  // Initially empty
  {
    test(testList.isEmpty(), "New list is empty");
  }

  // Add one and check it is there
  {
    testList.write(foo1);
    auto maybeRes = testList.read();
    assert(maybeRes.has_value());
    auto res = maybeRes.value();
    test(res.bar == foo1.bar && res.baz == foo1.baz, "Item written to list can be read back");
  }
  
  // Add all and check that it is full
  {
    testList.write(foo1);
    testList.write(foo2);
    testList.write(foo3);
    test(testList.isFull(), "isFull() returns true for a full list");
  }

  // Writing too many items fails
  {
    bool success = testList.write(foo4);
    test(!success, "Writing too many items fails");
  }

  // Remove all and check each matches expected
  {
    test(hasValueAndIs(testList.read(), foo1), "1st value read is correct");
    test(hasValueAndIs(testList.read(), foo2), "2nd value read is correct");
    test(hasValueAndIs(testList.read(), foo3), "3rd value read is correct");
  }

  // Check that it is empty again
  {
    test(testList.isEmpty(), "List is empty again");
  }

  // Check that reading from an empty list fails
  {
    auto value = testList.read();
    test(!value.has_value(), "Reading from an empty list returns empty optional");
  }
}

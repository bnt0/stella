#include "UnitTest++/UnitTest++.h"
#include "MapModel.h"

using namespace std;
using namespace stellad;

TEST(MapModelCreatedEmpty) {
  MapModel mapModel;
  vector<stellad::ShortcutDefinition>* keys = mapModel.getAllKeys();
  CHECK(keys->empty());
}

TEST(MapModelInsertedKeyCanBeRetrieved) {
  MapModel mapModel;
  ShortcutDefinition sd("lol", ":laughing out loud:", true, 0);
  mapModel.insertKey(sd);
  vector<stellad::ShortcutDefinition>* keys = mapModel.getAllKeys();
  CHECK_EQUAL(keys->size(), 1);

  ShortcutDefinition *retrieved = mapModel.checkForKeys("lol");
  CHECK(retrieved);
  CHECK_EQUAL(retrieved->getKey(), "lol");
  CHECK_EQUAL(retrieved->getValue(), ":laughing out loud:");
  CHECK_EQUAL(retrieved->isEnabled(), true);
  CHECK_EQUAL(retrieved->getMode(), 0);
}

int main(int, const char *[])
{
  return UnitTest::RunAllTests();
}


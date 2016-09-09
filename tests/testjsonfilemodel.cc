#include "UnitTest++/UnitTest++.h"
#include "JSONFileModel.h"
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <string.h>

using namespace std;
using namespace stellad;

string create_temp_file(const string& fileName, const string& content);

//! Loading a non-existent file should leave everything empty
TEST(LoadFromNonexistentFile) {
  JSONFileModel jsonFileModel;
  const string clearlyWrongFilePath = "/boot/lol/what/the/hell/foobarbaz.poo";
  vector<stellad::ShortcutDefinition> shortcuts;
  map<const string, string> settings;

  bool isSuccessful = jsonFileModel.loadFromFile(clearlyWrongFilePath, 
                                                 shortcuts, settings);
  CHECK(isSuccessful);
  CHECK(settings.empty());
  CHECK(shortcuts.empty());
}

TEST(LoadFromEmptyFileCorrectly) {
  string fileName = create_temp_file("/tmp/stellaemptyfile.XXXXXX", string());
  JSONFileModel jsonFileModel;
  vector<stellad::ShortcutDefinition> shortcuts;
  map<const string, string> settings;
  bool isSuccessful = jsonFileModel.loadFromFile(fileName, shortcuts, settings);

  CHECK(isSuccessful);
  CHECK(settings.empty());
  CHECK(shortcuts.empty());

  unlink(fileName.c_str());
}

TEST(LoadFromEmptyJsonObjectFileCorrectly) {
  string fileName = create_temp_file("/tmp/stellaemptyjsonfile.XXXXXX", "{}");
  JSONFileModel jsonFileModel;
  vector<stellad::ShortcutDefinition> shortcuts;
  map<const string, string> settings;
  bool isSuccessful = jsonFileModel.loadFromFile(fileName, shortcuts, settings);

  CHECK(isSuccessful);
  CHECK(settings.empty());
  CHECK(shortcuts.empty());

  unlink(fileName.c_str());
}

TEST(LoadWithMinimalShortcutValuesCorrectly) {
  string fileName = create_temp_file("/tmp/stellaemptyjsonfile.XXXXXX", 
      "{\"shortcuts\": [{\"key\": \"k\", \"value\": \"val\"}]}");
  JSONFileModel jsonFileModel;
  vector<stellad::ShortcutDefinition> shortcuts;
  map<const string, string> settings;
  bool isSuccessful = jsonFileModel.loadFromFile(fileName, shortcuts, settings);

  CHECK(isSuccessful);
  CHECK(settings.empty());
  CHECK_EQUAL(1, shortcuts.size());
  CHECK(!shortcuts[0].isEnabled());
  CHECK_EQUAL(shortcuts[0].getMode(), 0);

  unlink(fileName.c_str());
}

//! Helper function to create temporary file with given content
//! \param filename [in] template for full path passed to mkstemp (e.g.
//!                         /tmp/stellatempfile.XXXXXX
//!                         changed to actual filename 
//! \param content [in]     content to be added to the temprary file
//! \return actual filename of the create temp file. This needs to unlinked
//!         at the end of the test.
string create_temp_file(const string& fileName, const string& content) {
  const int fileNameTemplateLength = fileName.length() + 1; // including ending \0
  char fileNameOut[fileNameTemplateLength];
  strcpy(fileNameOut, fileName.c_str());
  int fileDescriptor = mkstemp(fileNameOut);
  if (fileDescriptor == -1) {
    std::cerr  << "Failed to open temporary file." << endl;
    REQUIRE(false);
    return string();
  }
  if (!content.empty()) {
    write(fileDescriptor, content.c_str(), (content.length() + 1));
  }
  close(fileDescriptor);
  return fileNameOut;
}

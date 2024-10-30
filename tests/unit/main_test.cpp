#include <gtest/gtest.h>
#include "tagfs/core.h"
#include "version.h"

TEST(TagFSTest, VersionMatches) {
    const char* expected_version = TAGFS_VERSION;  // From version.h
    EXPECT_STREQ(tagfs_get_version(), expected_version);
}

TEST(TagFSTest, VersionNotEmpty) {
    EXPECT_STRNE(tagfs_get_version(), "");
}

TEST(TagFSTest, VersionComponents) {
    EXPECT_GT(TAGFS_VERSION_MAJOR, -1);
    EXPECT_GT(TAGFS_VERSION_MINOR, -1);
    EXPECT_GT(TAGFS_VERSION_PATCH, -1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include "version.h"

TEST(TagFSTest, VersionNotEmpty) {
    EXPECT_STRNE(TAGFS_VERSION, "");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

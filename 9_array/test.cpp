#include <gtest/gtest.h>
#include <vector>

#include "maxsum.cpp"

TEST(maximum, negative) { 
    std::vector<int> array = {-2, -1, 0, -3, 1, 2, -1};
    std::vector<int> expected1 = {-2, -1, 0};
    std::vector<int> expected2 = {-3, 1, 2};

    std::vector<int> result1 = max_elem(array);
    std::vector<int> result2 = max_sum(array);

    EXPECT_EQ(result1, expected1);
    EXPECT_EQ(result2, expected2);
}

TEST(maximum, decrease) { 
    std::vector<int> array = {5, 4, 3, 2, 1};
    std::vector<int> expected1 = {5};
    std::vector<int> expected2 = {5};

    std::vector<int> result1 = max_elem(array);
    std::vector<int> result2 = max_sum(array);

    EXPECT_EQ(result1, expected1);
    EXPECT_EQ(result2, expected2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
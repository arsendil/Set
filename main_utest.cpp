#include "headers/Set.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

typedef Set<int> MySet;

TEST(SetTest, InsertMultipleElementsSorted)
{
    MySet s;
    s.insert(5);
    s.insert(1);
    s.insert(9);
    s.insert(3);

    std::vector<int> values;
    for (MySet::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        values.push_back(*it);
    }

    int expectedArray[] = {1, 3, 5, 9};
    std::vector<int> expected(expectedArray, expectedArray + 4);

    EXPECT_EQ(values, expected);
}

TEST(SetTest, DefaultConstructorCreatesEmptySet)
{
    Set<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(SetTest, InsertSingleElement)
{
    Set<int> s;
    std::pair<Set<int>::iterator, bool> result = s.insert(5);
    EXPECT_TRUE(result.second);
    EXPECT_EQ(*result.first, 5);
    EXPECT_EQ(s.size(), 1u);
}

TEST(SetTest, InsertDuplicateElement)
{
    Set<int> s;
    s.insert(5);
    std::pair<Set<int>::iterator, bool> result = s.insert(5);
    EXPECT_FALSE(result.second);
    EXPECT_EQ(s.size(), 1u);
}

TEST(SetTest, InsertMultipleElements)
{
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    EXPECT_EQ(s.size(), 3u);
    EXPECT_TRUE(s.find(1) != s.end());
    EXPECT_TRUE(s.find(2) != s.end());
    EXPECT_TRUE(s.find(3) != s.end());
    EXPECT_TRUE(s.find(4) == s.end());
}

TEST(SetTest, IteratesInSortedOrder)
{
    Set<int> s;
    s.insert(3);
    s.insert(1);
    s.insert(2);

    int expected[] = {1, 2, 3};
    int i = 0;
    for (Set<int>::iterator it = s.begin(); it != s.end(); ++it, ++i)
    {
        EXPECT_EQ(*it, expected[i]);
    }
    EXPECT_EQ(i, 3);
}

TEST(SetTest, ConstIteratorWorks)
{
    Set<int> s;
    s.insert(10);
    s.insert(20);

    const Set<int>& cs = s;
    int sum = 0;
    for (Set<int>::const_iterator it = cs.begin(); it != cs.end(); ++it)
    {
        sum += *it;
    }
    EXPECT_EQ(sum, 30);
}

TEST(SetTest, CopyConstructorCopiesAllElements)
{
    Set<int> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    Set<int> copy(s);
    EXPECT_EQ(copy.size(), 3u);
    EXPECT_TRUE(copy.find(1) != copy.end());
    EXPECT_TRUE(copy.find(2) != copy.end());
    EXPECT_TRUE(copy.find(3) != copy.end());
}

TEST(SetTest, AssignmentOperatorCopiesAllElements)
{
    Set<int> s1;
    s1.insert(1);
    s1.insert(2);

    Set<int> s2;
    s2.insert(10);
    s2 = s1;

    EXPECT_EQ(s2.size(), 2u);
    EXPECT_TRUE(s2.find(1) != s2.end());
    EXPECT_TRUE(s2.find(2) != s2.end());
    EXPECT_TRUE(s2.find(10) == s2.end());
}

TEST(SetTest, InsertRange)
{
    Set<int> s;
    int arr[] = {1, 2, 3, 4};
    std::vector<int> v(arr, arr + 4);

    s.insert(v.begin(), v.end());

    EXPECT_EQ(s.size(), 4u);
    for (int i = 1; i <= 4; ++i)
    {
        EXPECT_TRUE(s.find(i) != s.end());
    }
}

TEST(SetTest, InsertRangeWithDuplicates)
{
    Set<int> s;
    int arr[] = {1, 2, 2, 3, 3, 3};
    std::vector<int> v(arr, arr + 6);

    s.insert(v.begin(), v.end());

    EXPECT_EQ(s.size(), 3u);
    EXPECT_TRUE(s.find(1) != s.end());
    EXPECT_TRUE(s.find(2) != s.end());
    EXPECT_TRUE(s.find(3) != s.end());
}

TEST(SetTest, EraseSingleElement)
{
    MySet s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    EXPECT_EQ(s.size(), 3u);
    s.erase(2);
    EXPECT_EQ(s.size(), 2u);
    EXPECT_TRUE(s.find(2) == s.end());
    EXPECT_TRUE(s.find(1) != s.end());
    EXPECT_TRUE(s.find(3) != s.end());
}


TEST(SetTest, EraseNonExistingElement)
{
    MySet s;
    s.insert(10);
    s.insert(20);

    EXPECT_EQ(s.size(), 2u);
    s.erase(5);
    EXPECT_EQ(s.size(), 2u);
    EXPECT_TRUE(s.find(10) != s.end());
    EXPECT_TRUE(s.find(20) != s.end());
}

TEST(SetTest, EraseAllElements)
{
    MySet s;
    s.insert(1);
    s.insert(2);
    s.insert(3);

    s.erase(1);
    s.erase(2);
    s.erase(3);

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(SetTest, EraseThenReinsert)
{
    MySet s;
    s.insert(5);
    s.erase(5);
    EXPECT_TRUE(s.empty());

    s.insert(5);
    EXPECT_EQ(s.size(), 1u);
    EXPECT_TRUE(s.find(5) != s.end());
}

TEST(SetTest, LowerBoundExistingElement)
{
    MySet s;
    s.insert(1);
    s.insert(3);
    s.insert(5);

    MySet::iterator it = s.lower_bound(3);
    EXPECT_TRUE(it != s.end());
    EXPECT_EQ(*it, 3);
}

TEST(SetTest, LowerBoundNonExistingElement)
{
    MySet s;
    s.insert(1);
    s.insert(3);
    s.insert(5);

    MySet::iterator it = s.lower_bound(2);
    EXPECT_TRUE(it != s.end());
    EXPECT_EQ(*it, 3);
}

TEST(SetTest, LowerBoundBeforeFirst)
{
    MySet s;
    s.insert(5);
    s.insert(10);

    MySet::iterator it = s.lower_bound(1);
    EXPECT_TRUE(it != s.end());
    EXPECT_EQ(*it, 5);
}

TEST(SetTest, LowerBoundAfterLast)
{
    MySet s;
    s.insert(5);
    s.insert(10);

    MySet::iterator it = s.lower_bound(20);
    EXPECT_TRUE(it == s.end());
}

TEST(SetTest, LowerBoundEmptySet)
{
    MySet s;

    MySet::iterator it = s.lower_bound(10);
    EXPECT_TRUE(it == s.end());
}


TEST(SetTest, UpperBoundExistingElement)
{
    MySet s;
    s.insert(1);
    s.insert(3);
    s.insert(5);

    MySet::iterator it = s.upper_bound(3);
    EXPECT_TRUE(it != s.end());
    EXPECT_EQ(*it, 5);
}

TEST(SetTest, UpperBoundNonExistingElement)
{
    MySet s;
    s.insert(1);
    s.insert(3);
    s.insert(5);

    MySet::iterator it = s.upper_bound(2);
    EXPECT_TRUE(it != s.end());
    EXPECT_EQ(*it, 3);
}

TEST(SetTest, UpperBoundBeforeFirst)
{
    MySet s;
    s.insert(5);
    s.insert(10);

    MySet::iterator it = s.upper_bound(1);
    EXPECT_TRUE(it != s.end());
    EXPECT_EQ(*it, 5);
}

TEST(SetTest, UpperBoundAfterLast)
{
    MySet s;
    s.insert(5);
    s.insert(10);

    MySet::iterator it = s.upper_bound(20);
    EXPECT_TRUE(it == s.end());
}

TEST(SetTest, UpperBoundEmptySet)
{
    MySet s;

    MySet::iterator it = s.upper_bound(10);
    EXPECT_TRUE(it == s.end());
}

TEST(SetTest, EqualRangeExistingElement)
{
    MySet s;
    s.insert(1);
    s.insert(3);
    s.insert(5);

    std::pair<MySet::iterator, MySet::iterator> range = s.equal_range(3);
    EXPECT_TRUE(range.first != s.end());
    EXPECT_TRUE(range.second != s.end());
    EXPECT_EQ(*range.first, 3);
    EXPECT_EQ(*range.second, 5);
}

TEST(SetTest, EqualRangeNonExistingElement)
{
    MySet s;
    s.insert(1);
    s.insert(3);
    s.insert(5);

    std::pair<MySet::iterator, MySet::iterator> range = s.equal_range(2);
    EXPECT_TRUE(range.first != s.end());
    EXPECT_TRUE(range.second != s.end());
    EXPECT_EQ(*range.first, 3);
    EXPECT_EQ(*range.second, 3);
}

TEST(SetTest, EqualRangeBeforeFirst)
{
    MySet s;
    s.insert(5);
    s.insert(10);

    std::pair<MySet::iterator, MySet::iterator> range = s.equal_range(1);
    EXPECT_TRUE(range.first != s.end());
    EXPECT_TRUE(range.second != s.end());
    EXPECT_EQ(*range.first, 5);
    EXPECT_EQ(*range.second, 5);
}

TEST(SetTest, EqualRangeAfterLast)
{
    MySet s;
    s.insert(5);
    s.insert(10);

    std::pair<MySet::iterator, MySet::iterator> range = s.equal_range(20);
    EXPECT_TRUE(range.first == s.end());
    EXPECT_TRUE(range.second == s.end());
}

TEST(SetTest, EqualRangeEmptySet)
{
    MySet s;

    std::pair<MySet::iterator, MySet::iterator> range = s.equal_range(10);
    EXPECT_TRUE(range.first == s.end());
    EXPECT_TRUE(range.second == s.end());
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


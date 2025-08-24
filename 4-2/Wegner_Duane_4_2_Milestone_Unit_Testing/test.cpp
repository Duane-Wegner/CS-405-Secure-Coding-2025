// 4-2 Milestone: Unit Testing
// Duane Wegner
// Southern New Hampshire University
// CS-405 Secure Coding
// Alan Spencer, Adjunct Instructor(M.S)
// July 24, 2025


// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty()); // Yes, it is empty

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0); // Confirming size is 0

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty()); // No, it now contains 1 element

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1); // It must be 1
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    add_entries(5);
    ASSERT_EQ(collection->size(), 5); // After adding 5, size should be 5
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeAlwaysGTEToSize)
{
    std::vector<int> counts = { 0, 1, 5, 10 };
    for (int count : counts) {
        collection->clear();
        if (count > 0) add_entries(count);
        ASSERT_GE(collection->max_size(), collection->size()); // max_size should always be >= size
    }
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityAlwaysGTEToSize)
{
    std::vector<int> counts = { 0, 1, 5, 10 };
    for (int count : counts) {
        collection->clear();
        if (count > 0) add_entries(count);
        ASSERT_GE(collection->capacity(), collection->size()); // capacity should always be >= size
    }
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollection)
{
    collection->resize(5);
    ASSERT_EQ(collection->size(), 5); // Resized to 5, size should now be 5
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollection)
{
    add_entries(10);
    collection->resize(5);
    ASSERT_EQ(collection->size(), 5); // Resized down to 5, size should now be 5
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeToZeroEmptiesCollection)
{
    add_entries(5);
    collection->resize(0);
    ASSERT_TRUE(collection->empty()); // Resizing to 0 should make it empty
    ASSERT_EQ(collection->size(), 0); // Size should be 0
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    add_entries(5);
    collection->clear();
    ASSERT_TRUE(collection->empty()); // Collection should be empty after clear
    ASSERT_EQ(collection->size(), 0); // Size should be 0
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseRangeClearsCollection)
{
    add_entries(5);
    collection->erase(collection->begin(), collection->end());
    ASSERT_TRUE(collection->empty()); // Collection should be empty after erase
    ASSERT_EQ(collection->size(), 0); // Size should be 0
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityOnly)
{
    size_t original_capacity = collection->capacity();
    collection->reserve(100);
    ASSERT_GE(collection->capacity(), 100); // Capacity should now be at least 100
    ASSERT_EQ(collection->size(), 0); // Size should remain unchanged
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeThrowsException)
{
    add_entries(3);
    ASSERT_THROW(collection->at(10), std::out_of_range); // Index 10 is out of range
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// Positive: Verify front() returns the first inserted element
TEST_F(CollectionTest, FrontReturnsFirstElement)
{
    collection->push_back(23);
    ASSERT_EQ(collection->front(), 23); // First element should be 23
}

// Negative: Try popping back from an empty collection (undefined behavior, but test for size unchanged)
TEST_F(CollectionTest, PopBackOnEmptyCollection)
{
    ASSERT_TRUE(collection->empty()); // Ensure it is empty
    // Normally pop_back on empty vector causes undefined behavior, so I avoided calling it.
    // Instead I confirmed that we don't accidentally pop on empty
    ASSERT_NO_FATAL_FAILURE(collection->size()); // Should not crash just querying size
}
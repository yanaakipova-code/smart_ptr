#include <gtest/gtest.h>
#include "smart/unic_ptr.hpp"
#include "smart/share_ptr.hpp"

#include <string>
#include <utility>
#include <type_traits>

TEST(unique_ptr, default_is_null) {
    unique_ptr<int> p;
    EXPECT_EQ(p.get(), nullptr);
}

TEST(unique_ptr, construct_from_raw) {
    unique_ptr<int> p(new int(42));
    EXPECT_NE(p.get(), nullptr);
    EXPECT_EQ(*p, 42);
}

TEST(unique_ptr, construct_from_nullptr) {
    unique_ptr<int> p(nullptr);
    EXPECT_EQ(p.get(), nullptr);
}

TEST(unique_ptr, dereference) {
    unique_ptr<int> p(new int(5));
    EXPECT_EQ(*p, 5);
}

TEST(unique_ptr, dereference_allows_write) {
    unique_ptr<int> p(new int(5));
    *p = 10;
    EXPECT_EQ(*p, 10);
}

TEST(unique_ptr, arrow_operator) {
    unique_ptr<std::string> p(new std::string("hello"));
    EXPECT_EQ(p->size(), 5u);
    EXPECT_EQ(p->at(0), 'h');
}

TEST(unique_ptr, is_not_copy_constructible) {
    EXPECT_FALSE(std::is_copy_constructible<unique_ptr<int>>::value);
}

TEST(unique_ptr, is_not_copy_assignable) {
    EXPECT_FALSE(std::is_copy_assignable<unique_ptr<int>>::value);
}

TEST(unique_ptr, is_move_constructible) {
    EXPECT_TRUE(std::is_move_constructible<unique_ptr<int>>::value);
}

TEST(unique_ptr, is_move_assignable) {
    EXPECT_TRUE(std::is_move_assignable<unique_ptr<int>>::value);
}

TEST(unique_ptr, move_constructor) {
    unique_ptr<int> a(new int(1));
    unique_ptr<int> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*b, 1);
}

TEST(unique_ptr, move_assignment) {
    unique_ptr<int> a(new int(1));
    unique_ptr<int> b(new int(2));

    b = std::move(a);

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*b, 1);
}

TEST(unique_ptr, move_assignment_self) {
    unique_ptr<int> a(new int(5));
    int* raw = a.get();

    unique_ptr<int>& ref = a;
    a = std::move(ref);

    EXPECT_EQ(a.get(), raw);
    EXPECT_EQ(*a, 5);
}

TEST(unique_ptr, release_returns_ptr_and_nulls_self) {
    unique_ptr<int> p(new int(42));
    int* raw = p.release();

    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(*raw, 42);
    delete raw;
}

TEST(unique_ptr, release_on_empty) {
    unique_ptr<int> p;
    EXPECT_EQ(p.release(), nullptr);
}

TEST(unique_ptr, reset_replaces_object) {
    unique_ptr<int> p(new int(1));
    p.reset(new int(2));
    EXPECT_EQ(*p, 2);
}

TEST(unique_ptr, reset_to_null) {
    unique_ptr<int> p(new int(1));
    p.reset();
    EXPECT_EQ(p.get(), nullptr);
}

TEST(unique_ptr, reset_from_empty) {
    unique_ptr<int> p;
    p.reset(new int(42));
    EXPECT_EQ(*p, 42);
}

TEST(unique_ptr, destructor_calls_delete) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        unique_ptr<Tracker> p(new Tracker());
    }
    EXPECT_EQ(counter, 1);
}

TEST(unique_ptr_arr, default_is_null) {
    unique_ptr<int[]> arr;
    EXPECT_EQ(arr.get(), nullptr);
}

TEST(unique_ptr_arr, construct_from_raw) {
    unique_ptr<int[]> arr(new int[3]{1, 2, 3});
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(unique_ptr_arr, index_allows_write) {
    unique_ptr<int[]> arr(new int[3]{1, 2, 3});
    arr[1] = 20;
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 3);
}

TEST(unique_ptr_arr, is_not_copyable) {
    EXPECT_FALSE(std::is_copy_constructible<unique_ptr<int[]>>::value);
    EXPECT_FALSE(std::is_copy_assignable<unique_ptr<int[]>>::value);
}

TEST(unique_ptr_arr, is_movable) {
    EXPECT_TRUE(std::is_move_constructible<unique_ptr<int[]>>::value);
    EXPECT_TRUE(std::is_move_assignable<unique_ptr<int[]>>::value);
}

TEST(unique_ptr_arr, move_constructor) {
    unique_ptr<int[]> a(new int[3]{1, 2, 3});
    unique_ptr<int[]> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(unique_ptr_arr, move_assignment) {
    unique_ptr<int[]> a(new int[2]{1, 2});
    unique_ptr<int[]> b(new int[2]{10, 20});

    b = std::move(a);

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
}

TEST(unique_ptr_arr, release) {
    unique_ptr<int[]> arr(new int[3]{1, 2, 3});
    int* raw = arr.release();
    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(raw[0], 1);
    delete[] raw;
}

TEST(unique_ptr_arr, reset) {
    unique_ptr<int[]> arr(new int[2]{1, 2});
    arr.reset(new int[2]{10, 20});
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(unique_ptr_arr, all_destructors_called) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        unique_ptr<Tracker[]> arr(new Tracker[5]);
    }
    EXPECT_EQ(counter, 5);
}

TEST(share_ptr, default_is_null) {
    share_ptr<int> p;
    EXPECT_EQ(p.get(), nullptr);
}

TEST(share_ptr, construct_from_raw) {
    share_ptr<int> p(new int(42));
    EXPECT_NE(p.get(), nullptr);
    EXPECT_EQ(*p, 42);
}

TEST(share_ptr, construct_from_nullptr) {
    share_ptr<int> p(nullptr);
    EXPECT_EQ(p.get(), nullptr);
}

TEST(share_ptr, dereference) {
    share_ptr<int> p(new int(5));
    EXPECT_EQ(*p, 5);
}

TEST(share_ptr, dereference_allows_write) {
    share_ptr<int> p(new int(5));
    *p = 10;
    EXPECT_EQ(*p, 10);
}

TEST(share_ptr, arrow_operator) {
    share_ptr<std::string> p(new std::string("hello"));
    EXPECT_EQ(p->size(), 5u);
    EXPECT_EQ(p->at(0), 'h');
}

TEST(share_ptr, is_copy_constructible) {
    EXPECT_TRUE(std::is_copy_constructible<share_ptr<int>>::value);
}

TEST(share_ptr, is_copy_assignable) {
    EXPECT_TRUE(std::is_copy_assignable<share_ptr<int>>::value);
}

TEST(share_ptr, is_move_constructible) {
    EXPECT_TRUE(std::is_move_constructible<share_ptr<int>>::value);
}

TEST(share_ptr, is_move_assignable) {
    EXPECT_TRUE(std::is_move_assignable<share_ptr<int>>::value);
}

TEST(share_ptr, copy_constructor_works) {
    share_ptr<int> a(new int(42));
    share_ptr<int> b(a);
    EXPECT_EQ(*b, 42);
    EXPECT_EQ(a.get(), b.get());
}

TEST(share_ptr, copy_assignment_works) {
    share_ptr<int> a(new int(1));
    share_ptr<int> b(new int(2));
    b = a;
    EXPECT_EQ(*b, 1);
    EXPECT_EQ(a.get(), b.get());
}

TEST(share_ptr, copy_does_not_double_delete) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        share_ptr<Tracker> a(new Tracker());
        share_ptr<Tracker> b = a;
        share_ptr<Tracker> c = a;
    }
    EXPECT_EQ(counter, 1);
}

TEST(share_ptr, move_constructor) {
    share_ptr<int> a(new int(42));
    share_ptr<int> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*b, 42);
}

TEST(share_ptr, move_assignment) {
    share_ptr<int> a(new int(1));
    share_ptr<int> b(new int(2));

    b = std::move(a);
    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(*b, 1);
}

TEST(share_ptr, move_does_not_double_delete) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        share_ptr<Tracker> a(new Tracker());
        share_ptr<Tracker> b = std::move(a);
    }
    EXPECT_EQ(counter, 1);
}

TEST(share_ptr, reset_replaces_object) {
    share_ptr<int> p(new int(1));
    p.reset(new int(2));
    EXPECT_EQ(*p, 2);
}

TEST(share_ptr, reset_to_null) {
    share_ptr<int> p(new int(1));
    p.reset();
    EXPECT_EQ(p.get(), nullptr);
}

TEST(share_ptr, reset_from_empty) {
    share_ptr<int> p;
    p.reset(new int(42));
    EXPECT_EQ(*p, 42);
}

TEST(share_ptr, reset_old_released) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        share_ptr<Tracker> a(new Tracker());
        share_ptr<Tracker> b = a;
        share_ptr<Tracker> c(new Tracker());
        c.reset(new Tracker());
        EXPECT_EQ(counter, 1);
    }
    EXPECT_EQ(counter, 3);
}

TEST(share_ptr, self_copy_assignment_safe) {
    share_ptr<int> a(new int(42));
    a = a;
    EXPECT_EQ(*a, 42);
}

TEST(share_ptr, self_move_assignment_safe) {
    share_ptr<int> a(new int(42));
    share_ptr<int>& ref = a;
    a = std::move(ref);
    EXPECT_EQ(*a, 42);
}

TEST(share_ptr, copy_empty) {
    share_ptr<int> a;
    share_ptr<int> b(a);
    EXPECT_EQ(b.get(), nullptr);
}

TEST(share_ptr, copy_assign_empty) {
    share_ptr<int> a;
    share_ptr<int> b;
    b = a;
    EXPECT_EQ(b.get(), nullptr);
}

TEST(share_ptr, reset_empty_to_empty) {
    share_ptr<int> a;
    a.reset();
    EXPECT_EQ(a.get(), nullptr);
}

TEST(share_ptr_arr, default_is_null) {
    share_ptr<int[]> arr;
    EXPECT_EQ(arr.get(), nullptr);
}

TEST(share_ptr_arr, construct_from_raw) {
    share_ptr<int[]> arr(new int[3]{1, 2, 3});
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(share_ptr_arr, index_allows_write) {
    share_ptr<int[]> arr(new int[3]{1, 2, 3});
    arr[1] = 20;
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 3);
}

TEST(share_ptr_arr, copy_constructor) {
    share_ptr<int[]> a(new int[3]{1, 2, 3});
    share_ptr<int[]> b = a;
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(a.get(), b.get());
}

TEST(share_ptr_arr, copy_does_not_double_delete) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        share_ptr<Tracker[]> a(new Tracker[5]);
        share_ptr<Tracker[]> b = a;
    }
    EXPECT_EQ(counter, 5);
}

TEST(share_ptr_arr, move_constructor) {
    share_ptr<int[]> a(new int[3]{1, 2, 3});
    share_ptr<int[]> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(share_ptr_arr, move_does_not_double_delete) {
    static int counter = 0;
    struct Tracker {
        ~Tracker() { ++counter; }
    };

    counter = 0;
    {
        share_ptr<Tracker[]> a(new Tracker[3]);
        share_ptr<Tracker[]> b = std::move(a);
    }
    EXPECT_EQ(counter, 3);
}

TEST(share_ptr_arr, reset_replaces_array) {
    share_ptr<int[]> arr(new int[2]{1, 2});
    arr.reset(new int[2]{10, 20});
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(share_ptr_arr, reset_to_null) {
    share_ptr<int[]> arr(new int[2]{1, 2});
    arr.reset();
    EXPECT_EQ(arr.get(), nullptr);
}

TEST(share_ptr_arr, copy_empty) {
    share_ptr<int[]> a;
    share_ptr<int[]> b(a);
    EXPECT_EQ(b.get(), nullptr);
}

TEST(share_ptr_arr, copy_assign_empty) {
    share_ptr<int[]> a;
    share_ptr<int[]> b;
    b = a;
    EXPECT_EQ(b.get(), nullptr);
}

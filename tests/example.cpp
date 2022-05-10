// Copyright 2021 Artem Artemov <theartemka6@mail.ru>

#include <stdexcept>

#include <gtest/gtest.h>

#include <example.hpp>

TEST(Example, EmptyTest) {
    EXPECT_THROW(example(), std::runtime_error);
}

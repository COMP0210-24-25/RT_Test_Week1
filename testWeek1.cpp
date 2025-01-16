#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "VectorUtils.hpp"
#include "Rendering.hpp"
#include <cmath> 

using namespace Catch::Matchers;

void compareVectors(VecUtils::Vec3 value, VecUtils::Vec3 expectation, double delta=0.0001)
{
    for(size_t i = 0; i < 3; i++)
    {
        REQUIRE_THAT(value[i], WithinAbs(expectation[i], delta));
    }
}

TEST_CASE("Test dot products", "[Test Vector Maths]")
{
    using namespace VecUtils;
    Vec3 v1{0,0,0};
    Vec3 v2{1.0,2.0,1.0};

    REQUIRE(dot(v1, v2) == 0);

    v1 = {1, 0, 0};
    v2 = {0, 1, 0};

    REQUIRE(dot(v1, v2) == 0);

    REQUIRE_THAT(dot({1, 2, 1}, {2, 2, 5}), WithinRel(11, 0.0001));
}

TEST_CASE("Test subtraction", "[Test Vector Maths]")
{
    using namespace VecUtils;

    Vec3 v1{5, 1, 3};
    Vec3 v2{1, 7, 2};

    compareVectors(v1 - v2, {4, -6, 1});
    compareVectors(v2 - v1, {-4, 6, -1});

    compareVectors(v1 - Vec3{0,0,0}, v1);
    compareVectors(v2 - Vec3{0,0,0}, v2);
}

TEST_CASE("Test Norm", "[Test Vector Maths]")
{
    using namespace VecUtils;

    Vec3 u1{1,0,0};
    Vec3 u2{0,1,0};
    Vec3 u3{0,0,1};

    compareVectors(norm(u1), u1);
    compareVectors(norm(u2), u2);
    compareVectors(norm(u3), u3);

    Vec3 v1{1, 1, 0};
    compareVectors(norm(v1), {sqrt(0.5), sqrt(0.5), 0});

    compareVectors(norm({1, -1, 1}), {sqrt(1./3.), sqrt(-1./3.), sqrt(1./3.)});
}
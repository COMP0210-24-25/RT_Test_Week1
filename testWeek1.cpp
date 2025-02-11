#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "VectorUtils.hpp"
#include "Rendering.hpp"
#include <cmath> 
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace Catch::Matchers;

std::vector<VecUtils::Vec3> loadVectors(std::string filename)
{
    std::vector<VecUtils::Vec3> vectors;
    std::ifstream filestream(filename);
    if (!filestream)
    {
        throw std::runtime_error("File " + filename + " not found.");
    }
    std::string line;
    int line_num = 0;
    while (std::getline(filestream, line))
    {
        std::istringstream line_stream(line);
        VecUtils::Vec3 v;
        line_stream >> v[0];
        line_stream >> v[1];
        line_stream >> v[2];
        vectors.push_back(v);
    }
    return vectors;
}

void compareVectors(VecUtils::Vec3 value, VecUtils::Vec3 expectation, double delta=0.001)
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

    REQUIRE_THAT(dot(Vec3{1, 2, 1}, Vec3{2, 2, 5}), WithinRel(11, 0.0001));
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

    compareVectors(norm(Vec3{1, -1, 1}), Vec3{sqrt(1./3.), -sqrt(1./3.), sqrt(1./3.)});
}

TEST_CASE("Test Empty Image", "[Test Nested Loop]")
{
    using namespace VecUtils;
    std::vector<Vec3> result;

    bool exception_thrown = false;
    try
    {
        result = Render::genDirectionList(0,0);
    }
    catch(std::exception &e)
    {
        exception_thrown = true;
    }

    if(!exception_thrown)
    {
        REQUIRE(result.empty());
    }
}

TEST_CASE("Test Central Direction", "[Test Nested Loop]")
{
    using namespace VecUtils;

    Vec3 expectation = {0, 0, -1};

    std::vector<Vec3> result = Render::genDirectionList(1,1);

    REQUIRE(result.size() == 1);
    compareVectors(result[0], expectation);
}

TEST_CASE("Test Directions", "[Test Nested Loop]")
{
    using namespace VecUtils;
    std::vector<Vec3> expectation = loadVectors("data/Vectors.txt");
    std::vector<Vec3> result = Render::genDirectionList(10, 10);

    REQUIRE(expectation.size() == result.size());

    for(size_t i = 0; i < expectation.size(); i++)
    {
        compareVectors(expectation[i], result[i]);
    }
}
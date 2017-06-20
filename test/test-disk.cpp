
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "disk.hpp"

TEST_CASE("FromPhysical, SimpleConversion") {
    Disk d(10, 5, 60);

    REQUIRE(d.fromPhysical(1, 0, 0) == 300);
    REQUIRE(d.fromPhysical(0, 1, 0) == 60);
    REQUIRE(d.fromPhysical(0, 0, 20) == 20);

    REQUIRE(d.fromPhysical(9, 4, 59) == 10*5*60-1);
}

TEST_CASE("ToPhysical, SimpleConversion") {
    Disk d(10, 5, 60);
    int cylinder, track, sector;

    d.toPhysical(300, cylinder, track, sector);
    REQUIRE(cylinder == 1);
    REQUIRE(track == 0);
    REQUIRE(sector == 0);

    d.toPhysical(60, cylinder, track, sector);
    REQUIRE(cylinder == 0);
    REQUIRE(track == 1);
    REQUIRE(sector == 0);

    d.toPhysical(20, cylinder, track, sector);
    REQUIRE(cylinder == 0);
    REQUIRE(track == 0);
    REQUIRE(sector == 20);

    d.toPhysical(10 * 5 * 60 - 1, cylinder, track, sector);
    REQUIRE(cylinder == 9);
    REQUIRE(track == 4);
    REQUIRE(sector == 59);
}
/*
TEST_CASE("FindFreeSector, EmptyDisk") {
    Disk d(10, 5, 60);
    
    REQUIRE(d.find_free_sector(0) == 0);
    REQUIRE(d.find_free_sector(40) == 40);
    REQUIRE(d.find_free_sector(39, 4) == 40);
}
*/
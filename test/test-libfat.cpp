
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "libfat.hpp"


TEST_CASE("SearchFile, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);

    REQUIRE(table.searchFile("teste") == nullptr);
}


TEST_CASE("SearchCluster, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);

    REQUIRE(table.findFirstFreeCluster() == 0);
}

TEST_CASE("SearchCluster, AlmostEmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table1(disk);
    int cylinder, track, sector;

    int ind1 = disk->fromPhysical(0, 0, 0);
    table1.sectors[ind1].used = 1;

    REQUIRE(table1.findFirstFreeCluster() == disk->fromPhysical(0, 0, 4));

    int ind2 = disk->fromPhysical(0, 0, 4);
    table1.sectors[ind2].used = 1;

    REQUIRE(table1.findFirstFreeCluster() == disk->fromPhysical(0, 0, 8));

    for(int sector = 0; sector < disk->sectorsPerTrack; ++sector) {
        int ind = disk->fromPhysical(0, 0, sector);
        table1.sectors[ind].used = 1;
    }

    REQUIRE(table1.findFirstFreeCluster() == disk->fromPhysical(1, 0, 0));

    for(int cylinder = 0; cylinder < disk->tracksPerSurface; ++cylinder) {
        for(int sector = 0; sector < disk->sectorsPerTrack; ++sector) {
            int ind = disk->fromPhysical(cylinder, 0, sector);
            table1.sectors[ind].used = 1;
        }
    }

    REQUIRE(table1.findFirstFreeCluster() == disk->fromPhysical(0, 1, 0));
}

TEST_CASE("AddFile, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);

    REQUIRE(table.findFirstFreeCluster() == 0);
}

TEST_CASE("FindFreeClustersSameCylinder, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    std::vector<int> clusters = {0, 60, 120, 180, 240};

    REQUIRE(table.findFreeClustersSameCylinder(0) == clusters);
}

TEST_CASE("FindFreeClustersSameCylinder, AlmostEmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    std::vector<int> clusters = {60, 120, 180, 240};
    table.sectors[0].used = 1;

    REQUIRE(table.findFreeClustersSameCylinder(0) == clusters);

    table.sectors[0].used = 0;
    table.sectors[180].used = 1;

    std::vector<int> clusters2 = {0, 60, 120, 240};
    REQUIRE(table.findFreeClustersSameCylinder(0) == clusters2);
    REQUIRE(table.findFreeClustersSameCylinder(180) == clusters2);
    REQUIRE(table.findFreeClustersSameCylinder(240) == clusters2);
}


TEST_CASE("FindFreeClusters, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);


    std::vector<int> clusters5 = {0, 60, 120, 180, 240};
    std::vector<int> clusters2 = {0, 60};

    REQUIRE(table.findFreeClusters(5) == clusters5);
    REQUIRE(table.findFreeClusters(2) == clusters2);

    int ind = table.disk->fromPhysical(0, 2, 0);
    table.sectors[ind].used = 1;

    std::vector<int> clusters4 = {0, 60, 180, 240};
    std::vector<int> clusters7 = {0, 60, 180, 240, 4, 64, 124};

    REQUIRE(table.findFreeClusters(4) == clusters4);
    REQUIRE(table.findFreeClusters(7) == clusters7);
}
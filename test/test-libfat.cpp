
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

    REQUIRE(table.searchFreeCluster() == 0);
}
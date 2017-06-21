
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "libfat.hpp"


TEST_CASE("SearchFile, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);

    REQUIRE(table.searchFile("teste").valid == 0);
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

TEST_CASE("UsedSector, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    string teststr = "test string";
    bool result = table.addFile("file1.txt", teststr.c_str(), (int)teststr.size());

    REQUIRE(result == true);
    REQUIRE(table.sectors[0].used == 1);
    std::cout << std::endl;
}


TEST_CASE("ReadNonExistingFile, EmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    auto buffer = table.readFile("sldfk");

    REQUIRE(buffer.size() == 0);
}

TEST_CASE("ReadNonExistingFile, NonEmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    std::string teststr = "test string";
    table.addFile("file1.txt", teststr.c_str(), teststr.size());

    std::vector<char> result = table.readFile("sdfasd");

    REQUIRE(result.size() == 0);
}

TEST_CASE("ReadExistingFile, NonEmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    std::string teststr = "test string";
    table.addFile("file1.txt", teststr.c_str(), teststr.size());
    table.addFile("file2.txt", teststr.c_str(), teststr.size());

    std::vector<char> result = table.readFile("file1.txt");
    std::vector<char> result2 = table.readFile("file2.txt");
    std::string output(result2.begin(),result2.end());

    REQUIRE(result.size() == teststr.size());
    REQUIRE(output == teststr);
}

TEST_CASE("GetFatTable, NonEmptyFatTable") {
    auto disk = std::make_shared<Disk>();
    FatTable table(disk);
    std::string teststr = "test string";
    table.addFile("file1.txt", teststr.c_str(), teststr.size());
    table.addFile("file2.txt", teststr.c_str(), teststr.size());

    vector<filedescription> filesFat = table.getFatTable();

    REQUIRE("file1.txt" == filesFat[0].name);
    REQUIRE(teststr.size() == filesFat[0].size);
    //TODO :: teste para setores
    REQUIRE("file2.txt" == filesFat[1].name);
    REQUIRE(teststr.size() == filesFat[1].size);
}



//TODO :: teste para apagar arquivo
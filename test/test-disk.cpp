#include "gtest/gtest.h"
#include "disk.h"

TEST(FromPhysical, SimpleConversion) {
    Disk d(10, 5, 60);

    EXPECT_EQ(d.from_physical(1, 0, 0), 300);
    EXPECT_EQ(d.from_physical(0, 1, 0), 60);
    EXPECT_EQ(d.from_physical(0, 0, 20), 20);

    EXPECT_EQ(d.from_physical(9, 4, 59), 10*5*60-1);
}

TEST(ToPhysical, SimpleConversion) {
    Disk d(10, 5, 60);
    int cylinder, track, sector;

    d.to_physical(300, cylinder, track, sector);
    EXPECT_TRUE(cylinder == 1 && track == 0 && sector == 0);

    d.to_physical(60, cylinder, track, sector);
    EXPECT_TRUE(cylinder == 0 && track == 1 && sector == 0);

    d.to_physical(20, cylinder, track, sector);
    EXPECT_TRUE(cylinder == 0 && track == 0 && sector == 20);

    d.to_physical(10*5*60-1, cylinder, track, sector);
    EXPECT_TRUE(cylinder == 9 && track == 4 && sector == 59);
}

TEST(FindFreeSector, EmptyDisk) {
    Disk d(10, 5, 60);
    
    EXPECT_EQ(d.find_free_sector(0), 0);
    EXPECT_EQ(d.find_free_sector(40), 40);
    EXPECT_EQ(d.find_free_sector(39, 4), 40);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

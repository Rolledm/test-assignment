#include <iostream>
#include <gtest/gtest.h>

#include "../lib/t1.h"
#include "../lib/t2.h"
#include "../lib/t3.h"


TEST(t1, zero) {
	ASSERT_STREQ(Utilities::bin(0).c_str(), "00000000");
}

TEST(t1, one) {
	ASSERT_STREQ(Utilities::bin(1).c_str(), "00000001");
}

TEST(t1, minus_one) {
	ASSERT_STREQ(Utilities::bin(-1).c_str(), "11111110");
}

TEST(t1, minus_ten) {
	ASSERT_STREQ(Utilities::bin(-10).c_str(), "11110101");
}

TEST(t1, max_one_byte) {
	ASSERT_STREQ(Utilities::bin(127).c_str(), "01111111");
}

TEST(t1, two_bytes) {
	ASSERT_STREQ(Utilities::bin(257).c_str(), "0000000100000001");
}

TEST(t2, empty) {
	char data[] = "";
	Utilities::RemoveDups(data);
	ASSERT_STREQ(data, "");
}

TEST(t2, one) {
	char data[] = "a";
	Utilities::RemoveDups(data);
	ASSERT_STREQ(data, "a");
}

TEST(t2, work) {
	char data[] = "aaa bbb ccc";
	Utilities::RemoveDups(data);
	ASSERT_STREQ(data, "a b c");
}

TEST(t2, work_without_last) {
	char data[] = "aaa bbb c";
	Utilities::RemoveDups(data);
	ASSERT_STREQ(data, "a b c");
}

TEST(t2, single_rep) {
	char data[] = "aaaaaaaaaaaaa";
	Utilities::RemoveDups(data);
	ASSERT_STREQ(data, "a");
}

TEST(t3, simple_list) {
	auto file = fopen("./file.bin", "wb");
    Utilities::ListNode head, mid, tail;
    Utilities::List list;

    list.head = &head;
    list.tail = &tail;
    list.count = 3;

    head.data = "n1";
    head.prev = nullptr;
    head.next = &mid;
    head.rand = nullptr;

    mid.data = "n2";
    mid.prev = &head;
    mid.next = &tail;
    mid.rand = &tail;

    tail.data = "n3";
    tail.prev = &mid;
    tail.next = nullptr;
    tail.rand = &head;

    list.Serialize(file);
    fclose(file);

    file = fopen("./file.bin", "rb");
    Utilities::List list2;
    list2.Deserialize(file);
    Utilities::ListNode* node = list2.head;

	ASSERT_STREQ(list2.GetDBGData().c_str(), "n1 -1\nn2 2\nn3 0\n");
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

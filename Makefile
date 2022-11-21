all:
	g++ -Wall RedBlackTree.cpp RedBlackTreeTests.cpp -o rbtests

rbt-tests:
	./rbtests
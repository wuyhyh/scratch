#pragma once
typedef struct Tnode* ptr_to_Tnode;
struct Tnode {
	char data;
	ptr_to_Tnode left;
	ptr_to_Tnode right;
};
typedef ptr_to_Tnode Bintree;
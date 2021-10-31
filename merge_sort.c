#include <stdio.h>
#include <stdlib.h>


struct NODE {
	int cargo;
	struct NODE* next;
};
typedef struct NODE Node;


/*append value to end of list*/
void append(Node** proot, int val) {

	Node* root;
	root = *proot;

	if (root) {
		/*go further down the list*/
		append(&(root->next), val);
	} else {
		/*root points at NULL past end of list*/
		root = malloc(sizeof(Node));
		root->cargo = val;
		root->next = NULL;
		*proot = root;
	}
}


/*print the list*/
void display(Node* root) {

	if (root) {
		/*print head*/
		printf("%d ", root->cargo);
		/*then tail*/
		display(root->next);
	}
}


/*free allocated memory*/
void release(Node* root) {

	if (root) {
		/*free the tail*/
		release(root->next);
		/*then free the head*/
		free(root);
	}
}


/*split list into first and last halves
return pointer to last half, leave pointer
to first half alone*/
Node* split(Node* root) {

	Node* ret = root;
	Node* temp = NULL;

	if (root && root->next == NULL) {
		return NULL;
	}

	/*on each iteration root goes two places
	and ret goes one.  when root hits end of list
	ret will be half-way to end.*/
	while (root && root->next && root->next->next) {
		root = root->next->next;
		ret = ret->next;
	}

	/*advance ret and terminate first half of list*/
	if (ret && ret->next) {
		temp = ret;
		ret = ret->next;
		temp->next=NULL;
	}

	return ret;
}


Node*  merge(Node* A, Node* B) {

	if (A==NULL) {
		return B;
	}
	if (B==NULL) {
		return A;
	}

	/*point to smaller valued head and
	tack on the merge of everything else*/
	if (A->cargo < B->cargo) {
		A->next = merge(A->next, B);
		return A;
	} else {
		B->next = merge(A, B->next);
		return B;
	}
}


Node* merge_sort(Node* root) {

	Node* temp;
	Node* A;
	Node* B;

	/*zero or one element: already sorted*/
	if (root == NULL || root->next == NULL) {
		return root;
	}

	/*two elements in list*/
	if (root->next->next == NULL) {
		/*already in order*/
		if (root->cargo < root->next->cargo) {
			return root;
		} else {
			/*otherwise switch them*/
			temp = root;
			root = root->next;
			root->next = temp;
			root->next->next = NULL;
			return root;
		}
	}

	/*make first and last half of list*/
	A = split(root);
	B = root;

	/*inter-leaf the results of two recursions*/
	return merge(merge_sort(A), merge_sort(B));
}


/*integers as arguments. prints arguments in order.*/
int main(int argc, char** argv) {

	int i;
	Node* root = NULL;

	for (i=1; i<argc; i++) {
		append(&root, atoi(argv[i]));
	}

	root = merge_sort(root);

	display(root);

    printf("\n");

	release(root);

	return 0;
}

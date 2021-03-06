#include <stdio.h>
#include <stdlib.h>

struct MinHeapNode
{
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap
{
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** nodes;
};

struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	node->data = data;
	node->freq = freq;
	node->left = node->right = NULL;

	return node;
}

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->nodes = (struct MinHeapNode**)malloc(sizeof(struct MinHeapNode)*capacity);

	return heap;
}

void swapMinheapNodes(struct MinHeapNode**a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* heap,int i)
{
	int l = 2*i +1;
	int r = 2*i +2;
	int smallest = i;
	int n = heap->size;

	if(l < n && heap->nodes[l]->freq < heap->nodes[smallest]->freq)
		smallest = l;

	if(r < n && heap->nodes[r]->freq < heap->nodes[smallest]->freq)
		smallest = r;

	if(smallest != i)
	{
		swapMinheapNodes(&heap->nodes[i],&heap->nodes[smallest]);
		minHeapify(heap,smallest);
	}
}

int isSizeOne(struct MinHeap* heap)
{
	return(heap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* heap)
{
	// Node with minimum frequency.
	struct MinHeapNode* root = heap->nodes[0];
	heap->nodes[0] = heap->nodes[heap->size-1];
	--heap->size;
	minHeapify(heap,0);

	return root;
}

void insertMinHeap(struct MinHeap* heap, struct MinHeapNode* node)
{
	int i = heap->size;
	++heap->size;

	while(i && node->freq < heap->nodes[(i-1)/2]->freq)
	{
		heap->nodes[i] = heap->nodes[(i-1)/2];
		i = (i-1)/2;
	}
	heap->nodes[i] = node;
}

void printarray(int A[],int n)
{
	for(int i=0; i<n; i++)
		printf("%d",A[i]);
	printf("\n");
}

int isLeaf(struct MinHeapNode* node)
{
	return !(node->left) && !node->right;
}

void buildMinHeap(struct MinHeap* heap)
{
	for(int i=(heap->size-1)/2;i>0;i--)
		minHeapify(heap,i);
}

struct MinHeap* createAndBuildHeap(char data[], int freq[], int size)
{
	struct MinHeap* heap = createMinHeap(size);
	heap->size = size;

	for(int i=0;i<size;i++)
		heap->nodes[i] = newNode(data[i],freq[i]);

	buildMinHeap(heap);
	return heap;
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[],int size)
{
	struct MinHeapNode *left, *right, *top;

	struct MinHeap* heap = createAndBuildHeap(data,freq,size);

	while(!isSizeOne(heap))
	{
		left = extractMin(heap);
		right = extractMin(heap);
		//an internal node which is not used.
		top = newNode('#',left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(heap,top);
	}
	return extractMin(heap);
}

void pritCodes(struct MinHeapNode* root, int A[], int level)
{
	if(root->left)
	{
		A[level] = 0;
		pritCodes(root->left,A,level+1);
	}
	
	if(root->right)
	{
		A[level] = 1;
		pritCodes(root->right,A,level+1);
	}	

	if(isLeaf(root))
	{
		printf("%c : ",root->data);
		printarray(A,level);
	}

}

void HuffmanCodes(char data[], int freq[], int size)
{
	struct MinHeapNode* root = buildHuffmanTree(data,freq,size);

	int A[30];// Max height of a tree(Actual height can be inserted as well);
	pritCodes(root,A,0);
}

int main()
{
	char C[] = {'a','b','c','d','e','f'};
	int F[] = {5,9,12,13,16,45};

	HuffmanCodes(C,F,sizeof(C)/sizeof(C[0]));
	
	return 0;
}
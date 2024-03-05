

#include "Node.h"
#include "Block.h"
#include "LinkedList.h"
#include "File.h"
#include "Directory.h"
using namespace std;
int main()
{
	// You can test your implementations here
	Directory dir1;
	File fil1;
	cout << dir1.numFiles() << " " << dir1.directorySize() << endl;
	dir1.removeBiggestFile();
	Block block1("First String");
	Block block2("Second String");
	Block block3("Third String");
	fil1.newBlock(block1);
	fil1.newBlock(block2);
	fil1.newBlock(block3);
	fil1.mergeBlocks(0,1);
	File fil2(fil1);
	File fil3 = fil1;
	cout << (fil3 == fil1) << endl;
	cout << fil1.numBlocks() << endl;
	fil2.printContents();
	fil3.removeBlock(0);
	fil3.printContents();
	dir1.newFile(fil1);
	dir1.newFile(fil3);
	dir1.newFile(fil2);
	cout << dir1.numFiles() << " " << dir1.directorySize() << endl;
	dir1.removeBiggestFile();
	dir1.removeFile(fil3);
	(dir1.getFile(0)).printContents();
}


#include "File.h"

Block File::getBlock(int index) const
{
	/* TODO */
	if(index < numBlocks() && index >-1){
	    return ((this->blocks).getNodeAtIndex(index))->data;
	}
	else{
	    Block temp;
	    return temp;
	}
}

size_t File::fileSize() const
{
	/* TODO */
	size_t total = 0; int count = (this->blocks).getSize();
	Node<Block>* current = (blocks.getFirstNode());
	for(int i = 0; i < count; i++){
	    total += (current->data).getSize();
	    current = current->next;
	}
	return total;
}

int File::numBlocks() const
{
	/* TODO */
	return (this->blocks).getSize();
}

bool File::isEmpty() const
{
	/* TODO */
	return (this->blocks).isEmpty();
}

bool File::operator==(const File &rhs) const
{
	/* TODO */
	if(numBlocks() == rhs.numBlocks()){
	    int i = numBlocks();
	    Node<Block> * current1 = (this->blocks).getFirstNode(), *current2 = (rhs.blocks).getFirstNode();
	    for(int y = 0; y < i; y++){
	        if(current1->data == current2-> data){
	            current1 = current1->next;
	            current2 = current2->next;
	        }
	        else{
	            return false;
	        }
	    }
	    return true;
	}
	else{
	    return false;
	}
}

void File::newBlock(const Block &block)
{
	/* TODO */
	blocks.append(block);
}

void File::removeBlock(int index)
{
	/* TODO */
	blocks.removeNodeAtIndex(index);
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
	/* TODO */
	blocks.mergeNodes(sourceIndex, destIndex);
}

void File::printContents() const{
	if(isEmpty()){
		std::cout << "File is empty" << std::endl;
	}
	else{
		for(int i = 0; i < blocks.getSize(); i++){
			Node<Block> *block = blocks.getNodeAtIndex(i);
			std::cout << block->data.getContent();
		}
		std::cout << std::endl << fileSize() << std::endl;
	}
}
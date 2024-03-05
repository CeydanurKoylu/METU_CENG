#include "Directory.h"

File Directory::getFile(int index) const
{
	/* TODO */
	int i = files.size();
	if(index < i && index > -1)
	return files[index];
	else{
	    File empty;
	    return empty;
	}
}

size_t Directory::directorySize() const
{
	/* TODO */
	int no = numFiles();
	size_t total = 0;
	for(int i = 0; i < no; i++){
	    total += (files[i]).fileSize();
	}
	return total;
}

bool Directory::isEmpty() const
{
	/* TODO */
	return files.empty();
}

size_t Directory::numFiles() const
{
	/* TODO */
	return files.size();
}

void Directory::newFile(const File &file)
{
	/* TODO */
	files.push_back(file);
}

void Directory::removeFile(int index)
{
	/* TODO */
	if(index < (int)numFiles() && index > -1){
	files.erase(files.begin()+index);}
}

void Directory::removeFile(File &file)
{
	/* TODO */
	int no = numFiles();
	for(int i = 0; i < no; i++){
	    if(files[i] == file){
	        removeFile(i);
	        return;
	    }
	}
	
}

void Directory::removeBiggestFile()
{
	/* TODO */
	int no = numFiles();
	size_t max = 0; int maxind = 0;
	for(int i = 0; i < no; i++){
	    if((files[i]).fileSize() > max){
	        max = (files[i]).fileSize();
	        maxind = i;
	    }
	}
	removeFile(maxind);
}

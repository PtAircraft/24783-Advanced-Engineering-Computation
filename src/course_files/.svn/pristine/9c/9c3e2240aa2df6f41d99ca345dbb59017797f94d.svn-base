#include <ysclass.h>
#include <time.h>
#include <stdlib.h>

#include <chrono>

// Make sure to compile in the Release mode



int main(void)
{
	srand(79154726);
	std::vector <int> randNum;;

	printf("Generating Random Numbers\n");

	for(int i=0; i<10000000; ++i) // When it exceeds 16777216, 32-bit module overflows.
	{
		randNum.push_back(rand()*32768+rand());
	}

	printf("Start Tree Insertion\n");

	YsAVLTree <int,int> tree;
	auto t0=std::chrono::system_clock::now();
	for(auto r : randNum)
	{
		tree.Insert(r,0);
	}

	auto t1=std::chrono::system_clock::now();
	std::chrono::duration<double> secIns=t1-t0;
	printf("Elapsed %lf seconds (for insertion)\n",secIns.count());



	std::vector <YsAVLTree<int,int>::NodeHandle> toDel;

	printf("Verifying...\n");
	int prevKey=-1,count=0;
	for(auto hd=tree.First(); true==hd.IsNotNull(); hd=tree.FindNext(hd))
	{
		if(prevKey>tree.GetKey(hd))
		{
			printf("Integrity is broken!\n");
		}
		if(0==tree.GetKey(hd)%2)
		{
			toDel.push_back(hd);
		}
		prevKey=tree.GetKey(hd);
		++count;
	}
	printf("Done.\n");
	printf("%d nodes inserted.\n",randNum.size());
	printf("%d nodes in the tree.\n",count);



	t0=std::chrono::system_clock::now();
	for(auto hd : toDel)
	{
		tree.Delete(hd);
	}
	t1=std::chrono::system_clock::now();
	std::chrono::duration<double> secDel=t1-t0;
	printf("Elapsed %lf seconds (for deletion)\n",secDel.count());
	printf("%d nodes deleted.\n",toDel.size());



	printf("Verifying...\n");
	prevKey=-1;
	count=0;
	for(auto hd=tree.First(); true==hd.IsNotNull(); hd=tree.FindNext(hd))
	{
		if(prevKey>tree.GetKey(hd))
		{
			printf("Integrity is broken!\n");
		}
		if(0==tree.GetKey(hd)%2)
		{
			toDel.push_back(hd);
		}
		prevKey=tree.GetKey(hd);
		++count;
	}
	printf("Done.\n");
	printf("%d nodes in the tree.\n",count);
	if(randNum.size()-toDel.size()!=count)
	{
		printf("ERROR!  Count does not add up!\n");
	}


	printf("Total=%lf sec\n",(secDel+secIns).count());


	return 0;
}

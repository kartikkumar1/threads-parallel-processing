#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;

using std::swap;
using std::pair;
using std::make_pair;

int num_workers_;// global

typedef struct Node
{
	long long thread;
	long long next_free_time;
	/*vector<long long> thread;
	vector<long long> next_free_time;*/
};

class HeapBuilder	
{
public:
	int size;
	vector<Node> data_;
	//< pair<int, int> > swaps_;

	void ReadData()
	{
		//
		//data_.resize(num_workers_);

		////thread.resize(num_workers_);

		//for (int i = 0; i < num_workers_; ++i)
		//{
		//	data_[i].thread = i; data_[i].next_free_time = 0;
		//}
		//	
	}

	int LeftChild(int x)
	{
		return (2 * x);
	}
	int RightChild(int x)
	{
		return ((2 * x) + 1);
	}

	void ShiftDown(int x)	// here 0
	{
		//x = x - 1;
		int maxIndex = x;
		
		int l = (2 * x); //LeftChild(x);
		if ((l - 1 <= size))			// here 0 to check valid left child
		{
			if ((data_[l - 1].next_free_time) < (data_[maxIndex - 1].next_free_time))
			{
				maxIndex = l; goto here;
			}
			else if (((data_[l - 1].thread) < (data_[maxIndex - 1].thread)) & ((data_[l - 1].next_free_time) == (data_[maxIndex - 1].next_free_time)))
			{
				maxIndex = l;
			}
		}
		here:
		int r = (2 * x) + 1;//RightChild(x);
		if ((r - 1 <= size))			// here 0
		{
			if ((data_[r - 1].next_free_time < data_[maxIndex - 1].next_free_time))
			{
				maxIndex = r; goto here1;
			}
			else if ((data_[r - 1].thread < data_[maxIndex - 1].thread) & (data_[r - 1].next_free_time == data_[maxIndex - 1].next_free_time))								//&(maxIndex<r)
				maxIndex = r;
		}
		here1:
		if (x != maxIndex)
		{
			swap(data_[x - 1], data_[maxIndex - 1]);
			//maxIndex = x;
			ShiftDown(x);
		}

	}
	void HeapSort()
	{
		BuildHeap();
		
	}
	void BuildHeap()	// here 1
	{
		size = data_.size() - 1;
		for (int i = (data_.size() / 2); i >= 1; i--)
		{
			ShiftDown(i);
		}
	}

public:
	void Solve()
	{
		ReadData();
		HeapSort();
	}
};

class JobQueue {
private:
	
	
	vector<long> jobs_;

	vector<long> assigned_workers_;
	vector<long long> start_times_;

	void WriteResponse() const 
	{
		for (long long i = 0; i < jobs_.size(); ++i) 
		{
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() 
	{
		long long m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		/*for (long long i = 0; i < m; ++i)
		{
			cin >> jobs_[i];
		}*/
	}

	void AssignJobs() 
	{
		// TODO: replace this code with a faster algorithm.
		long long duration, next_worker;
		HeapBuilder heap;
		//heap.ReadData();

		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());
		//vector<long long> next_free_time(num_workers_, 0);
		heap.data_.resize(num_workers_);

		for (long long i = 0,j=0; (i < jobs_.size()) ; ++i)
		{
			cin >> jobs_[i];
				if (j < num_workers_)
			{
				heap.data_[j].thread = j;// heap.data_[j].next_free_time = 0;
				
				//heap.BuildHeap();
				duration = jobs_[j];
				next_worker = heap.data_[j].thread;
				//next_worker = 

				assigned_workers_[j] = next_worker;

				start_times_[j] = heap.data_[j].next_free_time;

				heap.data_[j].next_free_time = heap.data_[j].next_free_time + duration;
				j++;
			}
			else
			{
					heap.BuildHeap();
				duration = jobs_[i];
				next_worker = next_worker = heap.data_[0].thread;
				

				assigned_workers_[i] = next_worker;

				start_times_[i] = heap.data_[0].next_free_time;

				heap.data_[0].next_free_time = heap.data_[0].next_free_time + duration;
				//heap.BuildHeap();
			}
			
	
			//heap.BuildHeap();
		

		}
	}

public:
	void Solve() 
	{
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main() 
{
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	return 0;
}


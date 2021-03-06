
#include <iostream>
#include "ThreadPool.h"
#include "stdafx.h"
#include <io.h>
#include <vector>
#include <string>
#include <stack>
#include <mutex>
using namespace std;

char * filePath = "D:\\JPEGImages";
std::mutex g_mutex;
stack<string> s_stackTask;
int s_istop = 0;
void getFiles(string path)
{
	//文件句柄  
	long long hFile = 0;//这个地方需要特别注意，win10用户必须用long long 类型，win7可以用long类型
						//文件信息  
	struct _finddata_t fileinfo;
	//vector<string> back;
	string p;
	//stack<string> stackpath;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib & 0x10))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					g_mutex.lock();
					s_stackTask.push(p.assign(path).append("\\").append(fileinfo.name));
					g_mutex.unlock();
				}
					//getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				std::lock_guard<std::mutex> lockgur(g_mutex);
				cout << "file path : "<<p.assign(path).append("\\").append(fileinfo.name) <<" filesize = "<< fileinfo .size<< endl;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int func(int b)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "worker thread ID:" << std::this_thread::get_id() << std::endl;
	return 0;
}


void taskthread(ThreadPool& threadpool)
{
	while (1)
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		g_mutex.lock();
		if (s_stackTask.size()>0)
		{
			string strtemp = s_stackTask.top();
			threadpool.enqueue(getFiles, strtemp);
			s_stackTask.pop();
		}
		g_mutex.unlock();
		if (threadpool.getidleTread() == 10 )//
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			if (threadpool.getidleTread() == 10)
			{
				break;
			}
		}
	}
}

int main()
{
	ThreadPool pool(10);
	//int n = 0;
	//while (n<10)
	//{
	//	pool.enqueue(func,6);
	//	pool.enqueue(getFiles, "222");
	//	n++;
	//}
	


	long long hFile = 0;//这个地方需要特别注意，win10用户必须用long long 类型，win7可以用long类型
						//文件信息  
	struct _finddata_t fileinfo;
	string p,path;
	path = "D:\\";
	if (path.at(path.length()-1) == '\\')
	{
		path.erase(path.length() - 1);
	}
	s_stackTask.push(path);
	
	std::thread threadtask(taskthread, std::ref(pool));
	threadtask.join();
	//string strtemp = stackpath.top();
	//stackpath.pop();
	//if ((hFile = _findfirst(strtemp.append("\\*").c_str(), &fileinfo)) != -1)
	//{
	//	do
	//	{
	//		//如果是目录,迭代之  
	//		//如果不是,加入列表  
	//		if ((fileinfo.attrib &  _A_SUBDIR))
	//		{
	//			pool.enqueue(getFiles());
	//		}
	//		else
	//		{
	//			cout << "file path : " << p.assign(path).append("\\").append(fileinfo.name) << " filesize = " << fileinfo.size << endl;
	//		}

	//	} while (_findnext(hFile, &fileinfo) == 0);
	//	_findclose(hFile);
	//}

	
}
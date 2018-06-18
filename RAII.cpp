#include <iostream>
#include <thread>

class ThreadGuard
{
public:
	/* 此处的m_t是t的引用，并没有调用thread的复制构造函数 */
	explicit ThreadGuard(std::thread &t) :m_t(t)
	{
		std::cout << "Constructor is called." << std::endl;
	}

	~ThreadGuard()
	{
		if (m_t.joinable())
		{
			m_t.join();
		}
		std::cout << "Destructor is called." << std::endl;
	}
	/* 禁用复制构造函数 */
	ThreadGuard(const ThreadGuard &) = delete;
	/* 禁用赋值运算符重载 */
	ThreadGuard& operator=(const ThreadGuard &) = delete;

private:
	std::thread &m_t;
};

void hcw(){ std::cout << "Hello, RAII." << std::endl; }

int main()
{
	/* hcw作为线程t1的初始函数 */
	std::thread t1(hcw);
	/* 将线程t1交给acthread来管理 */
	ThreadGuard acthread(t1);

	system("pause");
}
#include <iostream>
#include <thread>

class ThreadGuard
{
public:
	/* �˴���m_t��t�����ã���û�е���thread�ĸ��ƹ��캯�� */
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
	/* ���ø��ƹ��캯�� */
	ThreadGuard(const ThreadGuard &) = delete;
	/* ���ø�ֵ��������� */
	ThreadGuard& operator=(const ThreadGuard &) = delete;

private:
	std::thread &m_t;
};

void hcw(){ std::cout << "Hello, RAII." << std::endl; }

int main()
{
	/* hcw��Ϊ�߳�t1�ĳ�ʼ���� */
	std::thread t1(hcw);
	/* ���߳�t1����acthread������ */
	ThreadGuard acthread(t1);

	system("pause");
}
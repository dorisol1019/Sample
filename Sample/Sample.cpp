#include <iostream>

//あのゲームで言うならISceneChangerクラス
class Interface
{
public:
	virtual ~Interface() {};
	//純粋仮想関数の宣言
	virtual void func() = 0;
};

//あのゲームで言うならBaseSceneクラス
class A
{
	Interface* interface;
public:
	A(Interface*interface)
	{
		//interface = interface;だと名前衝突が起きるのでダメ
		this->interface = interface;
	}

	void call()
	{
		std::cout << "A::call" << std::endl;
		//この例ではinterfaceにManager型のポインタを渡されたので
		//Manager::func()を呼び出している       
		interface->func();
	}
};

//あのゲームで言うならSceneMgrクラス
class Manager : Interface
{
	A* a;
public:
	Manager()
	{
		//引数でInterface型のポインタにManager型のポインタを渡している
		//ManagerはInterfaceを継承しているので可能
		Interface* interface = this;
		a = new A(interface);
	}

	~Manager()
	{
		delete a;
	}

	void run()
	{
		std::cout << "Manager::run" << std::endl;
		//A::callを呼び出している
		//この例ではA::callからManager::funcを呼び出している
		a->call();
	}

	//Interface::funcのオーバーライド(上書き)
	void func() override
	{
		std::cout << "Manager::func" << std::endl;
	}
};

int main()
{
	Manager manager{};
	manager.run();
}

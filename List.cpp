#include <iostream>
#include <cstdlib>
#include <ctime>

template<typename T>
struct Node
{
	Node* prior;
	Node* next;
	T value;
	Node(T val = T(), Node* pnext = nullptr,Node* prev = nullptr)
	{
		value = val;
		next = pnext;
		prior = prev;
	}
};

template <typename T>
class List
{
private:
	Node<T>* tail;
	Node<T>* head;
	int size;
public:
	List();
	~List();
	void push_back(T val);
	void pop_back();
	T& operator[](const int index);
	int Get_size() { return size; }
	void display();
	void push_front(T val);
	void pop_front();
	T& get_head();
	T& get_tail();
	void remove(const int index);
	void insert(T value, const int index);
	List<T>& operator=(List<T> &second);
	void swap(const int i, const int j);
};

template<typename T>
List<T>::List()
{
	tail = nullptr;
	head = nullptr;
	size = 0;
}

template<typename T>
List<T>::~List()
{
	for (int i = 0; i < size; i++)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
}

template <typename T>
void List<T>::push_back(T val)
{
	if (head == nullptr)
	{
		head = new Node<T>(val);
	}
	else
	{
		Node<T>* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = new Node<T>(val);
		tail = temp->next;
		tail->prior = temp;
	}
	size++;
}

template <typename T>
void List<T>::pop_back()
{
	if (head == nullptr)
		return;
	Node<T>* temp = tail;
	tail = tail->prior;
	tail->next = nullptr;
	delete temp;
	size--;
}

template<typename T>
T& List<T>::operator[](const int index)
{
	Node<T>* temp = head;
	int count = 0;
	while (count != index)
	{
		temp = temp->next;
		count++;
	}
	return temp->value;
}

template <typename T>
void List<T>::display()
{
	Node<T>* temp = head;
	for (int i = 0; i < size; i++)
	{
		std::cout << temp->value << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

template <typename T>
void List<T>::push_front(T value)
{
	if (head == nullptr)
	{
		head = new Node<T>(value);
	}
	else
	{
		Node<T>* temp = head;
		head = new Node<T>(value);
		head->next = temp;
		temp->prior = head;
	}
	size++;
}

template <typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->next;
	delete temp;
	size--;
}

template<typename T>
T& List<T>::get_head()
{
	return head->value;
}

template <typename T>
T& List<T>::get_tail()
{
	return tail->value;
}

template<typename T>
void List<T>::remove(const int index)
{
	if (index < 0 || index >= size)
	{
		std::cout << "unavailable index";
		return;
	}
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}
	Node<T>* temp = head;
	int count = 1;
	while (count != index)
	{
		temp = temp->next;
		count++;
	}
	(temp->prior)->next = temp->next;
	(temp->next)->prior = temp->prior;
	delete temp;
	size--;
}

template <typename T>
void List<T>::insert(T value, const int index)
{
	if (index < 0 || index > size)
	{
		std::cout << " unavailable index,for inserting " << std::endl;
		return;
	}
	if (index == 0)
	{
		push_front(value);
		return;
	}
	if (index == size)
	{
		push_back(value);
		return;
	}
	Node<T>* new_node = new Node<T>(value);
	Node<T>* temp = head;
	int count = 1;
	while (count != index)
	{
		temp = temp->next;
		count++;
	}
	(temp->prior)->next = new_node;
	new_node->prior = temp->prior;
	temp->prior = new_node;
	new_node->next = temp;
	size++;
}

template<typename T>
List<T>& List<T>::operator=(List<T> &second)
{
	for (int i = 0; i < this->size; i++)
	{
		Node<T>* current = this->head;
		this->head = (this->head)->next;
		delete current;
	}
	this->size = second.size;
	this->head = new Node<T>((second.head)->value);
	Node<T>* temp1 = this->head;
	Node<T>* temp2 = second.head;
	for (int i = 1; i < this->size; i++)
	{
		temp2 = temp2->next;
		Node<T>* a = temp1;
		temp1->next = new Node<T>(temp2->value);
		temp1 = temp1->next;
		temp1->prior = a;
	}
	this->tail = temp1;
	tail->next = nullptr;
	return *this;
}



template <typename T>
void List<T>::swap(const int i, const int j)
{
	if (i < 0 || i >= size || j >= size || j < 0)
	{
		std::cout << "I can't request to swap List's members because of the indexes" << std::endl;
		return;
	}
	if (i == j) return;
	T i_value = this->operator[](i);
	int count = 0;                        
	Node<T>* temp = head;
	while (count != i)
	{
		temp = temp->next;
		count++;
	}
	temp->value = this->operator[](j);
	temp = head;
	count = 0;
	while (count != j)
	{
		temp = temp->next;
		count++;
	}
	temp->value = i_value;
}

int main()
{
	/*std::srand(std::time(0));          // checking operations
	List<int> a;
	a.push_back(5);
	a.push_back(11);
	for (int i = 0; i < 10; i++)
		a.push_back(rand() % 100);
	a.display();
	std::cout << a.Get_size() << std::endl;
	a.pop_back();
	a.pop_back();
	a.push_back(7);
	a.display();
	std::cout << a.Get_size() << std::endl;
	a.push_front(45);
	a.push_front(77);
	a.display();
	for (int i = 0; i < 3; i++)
	{
		a.pop_front();
	}
	a.display();
	std::cout << "Your head and tail " << a.get_head() << '\t' << a.get_tail() << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "----------------" << std::endl;
	a.push_back(44);
	a.push_front(9);
	a.display();
	std::cout << "----------------" << std::endl;
	a.remove(5);
	a.display();
	a.insert(99, 7);
	a.insert(74, 11);
	int m = a.Get_size();
	a.insert(8, m);
	a.insert(2, 0);
	a.display();
	std::cout << a.Get_size() << std::endl;
	std::cout << std::endl << std::endl << std::endl << std::endl;
	List<int> B;
	for (int i = 0; i < 10; i++)
	{
		B.push_back(rand() % 100);
	}
	std::cout << "your new b list" << std::endl;
	B.display();
	a = B;
	std::cout << "here is your a" << std::endl;
	a.display();
	std::cout << "here is your b" << std::endl;
	B.display();
	List<int> C;
	for (int i = 0; i < 15; i++)
		C.push_front(rand() % 152);
	std::cout << "here is your c" << std::endl;
	C.display();
	List<int> D;
	for (int i = 0; i < 10; i++)
	{
		D.push_back(rand() % 50);
		D.push_front(rand() % 100);
	}
	std::cout << "here is your D " << std::endl;
	D.display();
	D = C = a;
	std::cout << "here is your A,C and D" << std::endl;
	a.display();
	C.display();
	D.display();
	std::cout << "let's swap D's few values" << std::endl;
	D.swap(3, 7);
	D.swap(7, 11);
	D.swap(1, 5);
	D.swap(7, 2);
	D.swap(-7, 52);
	D.display();*/
	
}
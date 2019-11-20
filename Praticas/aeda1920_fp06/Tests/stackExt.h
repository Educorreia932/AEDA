# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
	public:
		StackExt() {};
		bool empty() const;
		T &top();
		void pop();
		void push(const T & val);
		T &findMin();
	private:
		stack<T> s1;
		stack<T> s2;
};

template <class T> 
bool StackExt<T>::empty() const {
	return s1.empty();
}

template <class T> 
T& StackExt<T>::top() {
    T* novo = new T();

    *novo = s1.top();

    return *novo;
}

template <class T> 
void StackExt<T>::pop() {
	if (s2.size() && s1.top() == s2.top())
		s2.pop();

	s1.pop();
}

template <class T> 
void StackExt<T>::push(const T & val) {
	s1.push(val);

	if (!s2.size() || val < s2.top())
		s2.push(val);
}

template <class T> 
T& StackExt<T>::findMin() {
    T* novo = new T();

    *novo = s2.top();

    return *novo;
}


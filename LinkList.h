#pragma once /* is not C++ standard but recommended */

/* include:
		hedge::LinkList
		atagon::LinkList
		kiwiri::LinkList
		algae::LinkList
		
   recommend: hedge
*/

#include <thread>

namespace hedge
{
	template <typename T>
	class LinkList
	{
	public:
		/*
		 *
		 * LinkList::Node
		 *
		 */
		class Node
		{
		friend class hedge::LinkList<T>;
		private:
			Node * _next;
			Node * _previous;
			
			T _data;
			
			Node(T data) : _next(NULL), _previous(NULL), _data(data) {};
			Node() : _next(NULL), _previous(NULL) {};
			
			void selfDettach()
			{
				_next->_previous = _previous;
				_previous->_next = _next;
			}
		public:
			~Node() {};
			
			Node * next()
			{
				return _next;
			}
			
			Node * previous()
			{
				return _previous;
			}
			
			Node * next(int i)
			{
				Node * _ptr = this;
				while (i != 0 && _ptr->_next != NULL)
				{
					--i;
					_ptr = _ptr->_next;
				}
				return _ptr;
			}
			
			Node * previous(int i)
			{
				Node * _ptr = this;
				while (i != 0 && _ptr->_previous != NULL)
				{
					--i;
					_ptr = _ptr->_previous;
				}
				return _ptr;
			}
			
			inline T& content()
			{
				return _data;
			}
			
			inline bool isHead()
			{
				return _previous == NULL;
			}
			
			inline bool isTail()
			{
				return _next == NULL;
			}
			
			inline bool isNotHead()
			{
				return _previous != NULL;
			}
			
			inline bool isNotTail()
			{
				return _next != NULL;
			}
			
			inline bool isCreated()
			{
				return this != NULL;
			}
			
			bool isValid()
			{
				return isCreated() && isNotHead() && isNotTail();
			}
			
			void selfRemove()
			{
				_next->_previous = _previous;
				_previous->_next = _next;
				delete this;
			}
			
			void insertNext(T data)
			{
				if (isNotTail() && isCreated())
				{
					Node * _temp = _next;
					_next = new Node(data);
					_temp->_previous = _next;
					_next->_next = _temp;
					_next->_previous = this;
				}
			}
			
			void insertPrevious(T data)
			{
				if (isNotHead() && isCreated())
				{
					Node * _temp = _previous;
					_previous = new Node(data);
					_temp->_next = _previous;
					_previous->_previous = _temp;
					_previous->_next = this;
				}
			}
			
			void pullToNext(Node * ptr)
			{
				if (isNotTail() && ptr != this && _next != ptr)
				{
					ptr->selfDettach();
					Node * _temp = _next;
					_next = ptr;
					ptr->_previous = this;
					ptr->_next = _temp;
					_temp->_previous = ptr;
				}
			}
			
			void pullToPrevious(Node * ptr)
			{
				if (isNotHead() && ptr != this && _previous != ptr)
				{
					ptr->selfDettach();
					Node * _temp = _previous;
					_previous = ptr;
					ptr->_next = this;
					ptr->_previous = _temp;
					_temp->_next = ptr;
				}
			}
		};
		/*
		 *
		 * LinkList
		 *
		 */
		Node _head;
		Node _tail;
		
		Node * mergeSort(Node * from, Node * to)
		{
			if (from == to)
			{
				from->_next = NULL;
				
				return from;
			}
			else if (from->_next == to)
			{
				if (from->content() > to->content())
				{
					to->_next = from;
					from->_next = NULL;
					return to;
				}
				else
				{
					to->_next = NULL;
					return from;
				}
			}
			else
			{
				Node * _temp1 = from;
				Node * _temp2 = to;
				
				while (_temp1 != _temp2 && _temp1->_next != _temp2)
				{
					_temp1 = _temp1->_next;
					_temp2 = _temp2->_previous;
				}
				
				if (_temp1 == _temp2)
				{
					_temp1 = mergeSort(from, _temp1->_previous);
					_temp2 = mergeSort(_temp2, to);
				}
				else
				{
					_temp1 = mergeSort(from, _temp1);
					_temp2 = mergeSort(_temp2, to);
				}
				
				if (_temp1->content() > _temp2->content())
				{
					from = _temp2;
					_temp2 = _temp2->_next;
				}
				else
				{
					from = _temp1;
					_temp1 = _temp1->_next;
				}
				
				Node * _temp = from;
				while (_temp1 != NULL && _temp2 != NULL)
				{
					if (_temp1->content() > _temp2->content())
					{
						_temp->_next = _temp2;
						_temp = _temp2;
						_temp2 = _temp2->_next;
					}
					else
					{
						_temp->_next = _temp1;
						_temp = _temp1;
						_temp1 = _temp1->_next;
					}
				}
				
				if (_temp1 == NULL)
				{
					_temp->_next = _temp2;
				}
				else
				{
					_temp->_next = _temp1;
				}
				
				return from;
			}
		}
	public:
		/*
		 *
		 * LinkList
		 *
		 */		
		LinkList()
		{
			_head._next = &_tail;
			_tail._previous = &_head;
		}
		
		~LinkList()
		{
			while(isNotEmpty())
			{
				head()->selfRemove();
			}
		}
		
		inline Node * head()
		{
			return _head._next;
		}
		
		inline Node * tail()
		{
			return _tail._previous;
		}
		
		inline bool isEmpty()
		{
			return head()->_next == NULL;
		}
		
		inline bool isNotEmpty()
		{
			return head()->_next != NULL;
		}
		
		int count()
		{
			int i = 0;
			Node * _temp;
			for (_temp = head(); _temp->isNotTail(); _temp = _temp->_next)
			{
				++i;
			}
			return i;
		}
		
		void append(T data)
		{
			Node * _temp = tail();
			
			_tail._previous = new Node(data);
			tail()->_previous = _temp;
			_temp->_next = tail();
			tail()->_next = &_tail;
		}
		
		void prepend(T data)
		{
			Node * _temp = head();
			
			_head._next = new Node(data);
			head()->_next = _temp;
			_temp->_next = head();
			head()->_previous = &_head;
		}
		
		void removeFirst()
		{
			_head._next = _head._next->_next;
			delete head()->_previous;
			head()->_previous = & _head;
		}
		
		void removeLast()
		{
			_tail._previous = _tail._previous->_previous;
			delete tail()->_next;
			tail()->_next() = & _tail;
		}
		
		void insertionSort()
		{
			Node * _current = head()->_next;
			
			while (_current->isNotTail())
			{
				Node * _ptr = _current->_previous;
				
				while (_current->content() < _ptr->content() && _ptr->isNotHead())
				{
					_ptr = _ptr->_previous;
				}
					
				Node * _temp = _current;
				_current = _current->_next;
				_ptr->pullToNext(_temp);
			}
		}
		
		void insertionSort(bool (*compare) (T a, T b))
		{
			Node * _current = head()->_next;
			
			while (_current->isNotTail())
			{
				Node * _ptr = _current->_previous;
				
				while (compare( _current->content(), _ptr->content() ) && _ptr->isNotHead())
				{
					_ptr = _ptr->_previous;
				}
				
				Node * _temp = _current;
				_current = _current->_next;
				_ptr->pullToNext(_temp);
			}
		}
		
		void mergeSort()
		{
			if (isEmpty())
			{
				return;
			}
			
			_head._next = mergeSort(head(), tail());
			
			Node * _temp;
			for (_temp = head(); _temp->isNotTail(); _temp = _temp->next())
			{
				_temp->_next->_previous = _temp;
			}
			
			head()->_previous = & _head;
			_temp->_next = & _tail;
			_temp->_next->_previous = _temp;
		}
	};
}

namespace atagon
{
	template <typename T>
	class LinkList
	{
	public:
		/*
		 *
		 * LinkList::Node
		 *
		 */
		class Node
		{
		friend class atagon::LinkList<T>;
		private:
			Node * _next;
			Node * _previous;
			LinkList * _container;
			
			T data;
			
			void selfDettach()
			{
				if (this == NULL)
				{
					return;
				}
				else
				{
					if (_next == NULL && _previous == NULL)
					{
						_container->_tail = NULL;
						_container->_head = NULL;
						_next = NULL;
						_previous = NULL;
					}
					else if (_next == NULL)
					{
						_container->_tail = _previous;
						_previous->_next = NULL;
						_next = NULL;
						_previous = NULL;
					}
					else if (_previous == NULL)
					{
						_container->_head = _next;
						_next->_previous = NULL;
						_previous = NULL;
						_next = NULL;
					}
					else
					{
						_previous->_next = _next;
						_next->_previous = _previous;
						_next = NULL;
						_previous = NULL;
					}
				}
			};
		public:
			/*
			 *
			 * Warning: Check whether the node is created be for using any function with it!
			 *
			 *
			 */
			Node() : _next(NULL), _previous(NULL), data() {};
			Node(LinkList * container, T _data) : _container(container), data(_data), _next(NULL), _previous(NULL) {};
			
			~Node() {  };
			
			inline T& content()
			{
				return data;
			};
			
			inline LinkList& container()
			{
				if (this == NULL)
				{
					return LinkList();
				}
				else
				{
					return * _container;
				}
			}
			
			inline Node * next()
			{
				return _next;
			};
			
			inline Node * previous()
			{
				return _previous;
			};
			
			Node * next(int i)
			{
				Node * temp = this;
				
				while (temp != NULL && i != 0)
				{
					temp = temp->_next;
					--i;
				}
				
				return temp;
			};
			
			Node * previous(int i)
			{
				Node * temp = this;
				
				while (temp != NULL && i != 0)
				{
					temp = temp->_previous;
					--i;
				}
				
				return temp;
			};
			
			inline bool isCreated()
			{
				if (this != NULL)
				{
					return true;
				}
				else
				{
					return false;
				}
			};
			
			inline bool isHeadNode()
			{
				if (_previous == NULL)
				{
					return false;
				}
				else
				{
					return true;
				}
			};
			
			inline bool isTailNode()
			{
				if (_next == NULL)
				{
					return true;
				}
				else
				{
					return false;
				}
			};
			
			void insertNext(T data)
			{
				if (this == NULL)
				{
					return;
				}
				else if (_next != NULL)
				{
					Node * temp = new Node(_container, data);
					temp->_previous = this;
					temp->_next = _next;
					_next->_previous = temp;
					_next = temp;
				}
				else
				{
					_next = new Node(_container, data);
					_container->_tail = _next;
				}
			};
			
			void insertPrevious(T data)
			{
				if (this == NULL)
				{
					return;
				}
				else if (_previous != NULL)
				{
					Node * temp = new Node(_container, data);
					temp->_next = this;
					temp->_previous = _previous;
					_previous->_next = temp;
					_previous = temp;
				}
				else
				{
					_previous = new Node(_container, data);
					_container->_head = _previous;
				}
			};
			
			void selfRemove()
			{
				if (this == NULL)
				{
					return;
				}
				else if (_next == NULL && _previous == NULL)
				{
					delete this;
				}
				else if (_next == NULL)
				{
					_previous->_next = NULL;
					_container->_tail = _previous;
					delete this;
				}
				else if (_previous == NULL)
				{
					_next->_previous = NULL;
					_container->_head = NULL;
					delete this;
				}
				else
				{
					_next->_previous = _previous;
					_previous->_next = _next;
					delete this;
				}
			};
			
			void insertNext(Node * ptr)
			{
				if (this == NULL || ptr == NULL || this == ptr)
				{
					return;
				}
				else
				{
					ptr->selfDettach();
					if (_next == NULL)
					{
						_next = ptr;
						_container->_tail = ptr;
						ptr->_previous = this;
						ptr->_next = NULL;
						ptr->_container = _container;
					}
					else
					{
						ptr->_next = _next;
						ptr->_previous = this;
						_next->_previous = ptr;
						_next = ptr;
					}
				}
			};
			
			void insertPrevious(Node * ptr)
			{
				if (this == NULL || ptr == NULL || ptr == this)
				{
					return;
				}
				else
				{
					ptr->selfDettach();
					if (_previous == NULL)
					{
						_previous = ptr;
						_container->_head = ptr;
						ptr->_next = this;
						ptr->_previous = NULL;
						ptr->_container = _container;
					}
					else
					{
						ptr->_previous = _previous;
						ptr->_next = this;
						_previous->_next = ptr;
						_previous = ptr;
					}
				}
			};
		};
	friend class atagon::LinkList<T>::Node;
	protected:
		Node * _head;
		Node * _tail;
	public:
		/*
		 *
		 * Constructor and Destructor
		 *
		 */
		LinkList() : _head(NULL), _tail(NULL) {};
		
		~LinkList()
		{
			Node * temp = _head->_next;
			
			while (_head != NULL)
			{
				delete _head;
				_head = temp;
				temp = _head->_next;
			}
		};
		
		inline Node * head()
		{
			return _head;
		};
		
		inline Node * tail()
		{
			return _tail;
		}
		
		Node * getNode(int i)
		{
			if (i < 0)
			{
				return _head;
			}
			else
			{
				Node * temp = _head;
				while (temp != NULL && i != 0)
				{
					--i;
					temp = temp->_next;
				}
				
				return temp;
			}
		}
		
		T& operator[] (int i)
		{
			if (i < 0)
			{
				return _head->data;
			}
			else
			{
				Node * current = _head;
				
				while (i != 0 && current != NULL)
				{
					--i;
					current = current->_next;
				}
				
				if (i == 0)
				{
					return current->data;
				}
				else
				{
					return _tail->data;
				}
			}
		};
		
		inline bool isEmpty()
		{
			if (_head == NULL)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		inline bool isNotEmpty()
		{
			if (_head == NULL)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		
		void append(T data)
		{
			if (_head == NULL)
			{
				try
				{
					_head = new Node(this, data);
				}
				catch (...)
				{
					return;
				}
				
				_tail = _head;
			}
			else
			{
				try
				{
					_tail->_next = new Node(this, data);
				}
				catch (...)
				{
					return;
				}
				
				_tail->_next->_previous = _tail;
				_tail = _tail->_next;
			}
		};
		
		void prepend(T data)
		{
			if (_head == NULL)
			{
				try
				{
					_head = new Node(this, data);
				}
				catch (...)
				{
					return;
				}
				
				_tail = _head;
			}
			else
			{
				try
				{
					_head->_previous = new Node(this, data);
				}
				catch (...)
				{
					return;
				}
				
				_head->_previous->_next = _head;
				_head = _head->_previous;
			}
		};
		
		void removeFirst()
		{
			if (_head == NULL)
			{
				return;
			}
			else
			{
				if (_head->_next == NULL)
				{
					delete _head;
					_head = NULL;
					_tail = NULL;
				}
				else
				{
					_head = _head->_next;
					delete _head->_previous;
					_head->_previous = NULL;
				}
			}
		};
		
		void removeLast()
		{
			if (_tail == NULL)
			{
				return;
			}
			else
			{
				if (_tail->_previous == NULL)
				{
					delete _tail;
					_tail = NULL;
					_head = NULL;
				}
				else
				{
					_tail = _tail->_previous;
					delete _tail->_next;
					_tail->_next = NULL;
				}
			}
		};
		
		void insertionSort()
		{
			if (_head != NULL || _head->_next == NULL)
			{
				Node * current = _head->_next;
				
				while (current != NULL)
				{
					Node * ptr = current->_previous;
					
					while (ptr->_previous != NULL && current->data < ptr->data)
					{
						ptr = ptr->_previous;
					}
					
					Node * temp = current;
					
					if (ptr->_previous == NULL)
					{
						if (current->data < ptr->data)
						{
							current = current->_next;
							ptr->insertPrevious(temp);
						}
						else
						{
							current = current->_next;
							ptr->insertNext(temp);
						}
					}
					else
					{
						current = current->_next;
						ptr->insertNext(temp);
					}
				}
			}
		};
	};
}

namespace kiwiri
{

/* LinkListNode is transparent to user but iterator is limited */

	template <typename T>
	class LinkList
	{
	protected:
		/**
		 *
		 * LinkList::Node
		 *
		 */
		class Node
		{
		public:
			Node * next;
			Node * previous;
			
			T data;
			/*
			 *
			 */
			Node() : next(NULL), previous(NULL), data() {};
			Node(T _data) : data(_data), next(NULL), previous(NULL) {};
			
			~Node() {};
			
			T& content()
			{
				return data;
			};
		};
		
		Node * _head;
		Node * _tail;
		
		Node * currentnode;
	public:
		/**
		 *
		 * Constructor and Destructor
		 *
		 */
		LinkList() : _head(NULL), _tail(NULL) {};
		
		~LinkList()
		{
			Node * temp = _head->next;
			
			while (_head != NULL)
			{
				delete _head;
				_head = temp;
				temp = _head->next;
			}
		};
		/*
		 *
		 */
		T& operator[] (int i)
		{
			currentnode = _head;
			
			if (i < 0)
			{
				return _head->data;
			}
			
			while (i != 0)
			{
				if (currentnode->next == NULL)
				{
					return currentnode->data;
				}
				else
				{
					currentnode = currentnode->next;
					--i;
				}
			}
			
			return currentnode->data;
		};
		
		void append(T data)
		{
			if (_head == NULL)
			{
				_head = new Node (data);
				_tail = _head;
			}
			else
			{
				_tail->next = new Node (data);
				
				_tail->next->previous = _tail;
				_tail = _tail->next;
			}
		};
		
		void prepend(T data)
		{
			if (_head == NULL)
			{
				_head = new Node (data);
				_tail = _head;
			}
			else
			{
				_head->previous = new Node (data);
				
				_head->previous->next = _head;
				_head = _head->previous;
			}
		};
		
		void insertNext(T data)
		{
			if (currentnode == NULL)
			{
				return;
			}
			else
			{
				if (currentnode->next == NULL)
				{
					currentnode->next = new Node(data);
					_tail = currentnode->next;
				}
				else
				{
					Node * temp = new Node(data);
					temp->next = currentnode->next;
					temp->previous = currentnode;
					
					currentnode->next->previous = temp;
					currentnode->next = temp;
				}
			}
		};
		
		void insertPrevious(T data)
		{
			if (currentnode == NULL)
			{
				return;
			}
			else
			{
				if (currentnode->previous == NULL)
				{
					currentnode->previous = new Node (data);
					_head = currentnode->previous;
				}
				else
				{
					Node * temp = new Node(data);
					temp->next = currentnode;
					temp->previous = currentnode->previous;
					
					currentnode->previous->next = temp;
					currentnode->previous = temp;
				}
			}
		};
		
		void removeNext()
		{
			if (currentnode == NULL)
			{
				return;
			}
			else
			{
				if (currentnode->next == NULL)
				{
					return;
				}
				else if (currentnode->next == NULL)
				{
					delete currentnode->next;
					_tail = currentnode;
					_tail->next = NULL;
				}
				else
				{
					Node * temp = currentnode->next;
					currentnode->next = currentnode->next->next;
					currentnode->next->previous = currentnode;
					delete temp;
				}
			}
		};
		
		void removePrevious()
		{
			if (currentnode == NULL)
			{
				return;
			}
			else
			{
				if (currentnode->previous == NULL)
				{
					return;
				}
				else if (currentnode->previous->previous == NULL)
				{
					delete currentnode->previous;
					_head = currentnode;
					_head->previous = NULL;
				}
				else
				{
					Node * temp = currentnode->previous;
					currentnode->previous = currentnode->previous->previous;
					currentnode->previous->next = currentnode;
					delete temp;
				}
			}
		};
		
		void removeCurrent()
		{
			if (currentnode == NULL)
			{
				return;
			}
			else
			{
				if (currentnode == _tail && currentnode == _head)
				{
					delete currentnode;
					_tail = NULL;
					_head = NULL;
					currentnode = NULL;
				}
				else if (currentnode == _head)
				{
					_head = currentnode->next;
					_head->previous = NULL;
					delete currentnode;
					currentnode = _head;
				}
				else if (currentnode == _tail)
				{
					_tail = currentnode->previous;
					_tail->next = NULL;
					delete currentnode;
					currentnode = NULL;
				}
				else
				{
					Node * temp = currentnode->next;
					currentnode->next->previous = currentnode->previous;
					currentnode->previous->next = currentnode->next;
					delete currentnode;
					currentnode = temp;
				}
			}
		}
		/**
		 *
		 * Iterator
		 *
		 * Ex:
		 * 		for (A.start(); A.traversing(); A.next())
		 *		{
		 *	 		do somthing with A.current()
		 *		}
		 *
		 */
		T& start()
		{
			currentnode = _head;
			return currentnode->data;
		};
		
		T& end()
		{
			currentnode = _tail;
			return currentnode->data;
		}


		/* Warning: Infinite Loop!	*/


		bool traversing()
		{
			if (currentnode == NULL)
			{
				currentnode = _head;
				return false;
			}
			else
			{
				return true;
			}
		};
		
		bool reverseTraversing()
		{
			if (currentnode == NULL)
			{
				currentnode = _tail;
				return false;
			}
			else
			{
				return true;
			}
		}
		
		void next()
		{
			if (currentnode == NULL)
			{
				currentnode = _tail;
			}
			
			currentnode = currentnode->next;
		};
		
		void next(int i)
		{
			if (i < 0)
			{
				return;
			}
			
			while (i != 0 && currentnode != NULL)
			{
				currentnode = currentnode->next;
				--i;
			}
		};
		
		void previous()
		{
			if (currentnode == NULL)
			{
				currentnode = _head;
			}
			
			currentnode = currentnode->previous;
		}
		
		void previous(int i)
		{
			if (i < 0)
			{
				return;
			}
			
			while (i != 0 && currentnode != NULL)
			{
				currentnode = currentnode->previous;
				--i;
			}
		};
		
		T& current()
		{
			if (currentnode == NULL)
			{
				currentnode = _head;
				return currentnode->data;
			}
			
			return currentnode->data;
		}
	};

}

namespace algae
{
	template <typename T>
	class LinkListNode
	{
	public:
		LinkListNode * next;
		LinkListNode * previous;
		
		T data;
	};
}
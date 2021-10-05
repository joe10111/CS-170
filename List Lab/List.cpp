/*****************************************************************************/
/*!
\file:           List.cpp
\author          Joe Centeno
\par DP email:   joe.centeno\@digipen.edu
\par Course:     CS170
\par Assignment: Assignment 5  
\date:           7/2/2021
\brief
  Turning List Class into Template 
  
  Functions include:
    - Defulat Constructor
    - Non-Default Constructor
    - Copy Constructor
    - Destructor
    - push_front 
    - push_back 
    - pop_front 
    - front 
    - size 
    - empty 
    - clear 
    - new_node 

  Overloaded Operators:
    - =  
    - +  
    - += 
    - []
    - << 
    
Hours spent on assignment: 3
Specific portions that gave you the most trouble: 
  I spent an hoour copying over my previous code and then had to go back 
  and read my notes on templates, but besides that it was faily esay.
*/
/*****************************************************************************/

namespace CS170 //! Cs-170 NameSpace
{
  ////////////////////
  //! Static Members//
  ////////////////////

  template <typename T> //!< Init Nodes Alive
    int List<T>::Node::nodes_alive = 0;
  
  //!< List<T>::node_count
  /************************** *************************************************/
  /*!
  
  \brief
    Gets the number of nodes alive
  
  \return
    Returns the number of nodes alive.
  */
  /***************************************************************************/
  template <typename T>
    int List<T>::node_count(void)
    {
      return Node::nodes_alive; //! Returns Nodes Alive
    }
  
  ////////////////////////
  //! List::Node methods//
  ////////////////////////
  
  //!< List<T>::Node::Node(T value) : data(value)
  /***************************************************************************/
  /*!
  
  \brief
    Template Constructor for the Node Struct
  
  \param value
    Data to Insert into Node
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::Node::Node(T value) : data(value)
    {
      nodes_alive++;
    }
  
  //!< List<T>::Node::~Node()
  /***************************************************************************/
  /*!
  \brief
    Destructor 
  */
  /***************************************************************************/
  template <typename T>
    List<T>::Node::~Node()
    {
        // decrements node counter
      nodes_alive--;
    }

  ////////////////////////
  //! public methods//
  ////////////////////////
  
  //!< List<T>::List()
  /***************************************************************************/
  /*!
  
  \brief
    Template Constructor for List Class
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::List()
    {
        // assign pointers
      head_ = 0;
      tail_ = 0;
      
        // assign size counter
      size_ = 0;
    }
  
  //!< List<T>::List
  /***************************************************************************/
  /*!
  
  \brief
    Templated copy construcotr for List class.
  
  \param original
    A reference to the object you wish to copy.
  
  */
  /***************************************************************************/
  template<typename T>
    List<T>::List(const List& original)
    {
        // Init Pointers
      head_ = 0;
      tail_ = 0;
      
        // Init Size
      size_ = 0;
      
        // Node Pointer to Walk List
      Node* original_walker = original.head_;
      
        // While Nodes are valid
      while(original_walker)
      {
          // Push Node to Back 
        push_back(original_walker->data);
         
        original_walker = original_walker->next;
      }
    }

   //!< List<T>::List
  /***************************************************************************/
  /*!
  
  \brief
    Template non-default constructor for Class List
  
  \param array
    Array to Assign the Values

   \param size
     size
  
  */
  /***************************************************************************/
  template <typename T>
    List<T>::List(const T *array, int size)
    {
        // Init Pointers
      head_ = 0;
      tail_ = 0;
      
        // Init Size
      size_ = 0;
        
       // While There are Node to Add Push to Back  
      for(int i = 0; i < size; i++)
      {
        List::push_back(array[i]);
      }
    }
  
   //!< List<T>::~List()
  /***************************************************************************/
  /*!
  
  \brief
    Template Destructor for Class List
    
  */
  /***************************************************************************/
  template <typename T>
    List<T>::~List()
    {
        // call clear to destroy object
      clear();
    }
  
   //!< List<T>::push_front
  /***************************************************************************/
  /*!
  
  \brief
    Pushes an object to the front
  
  \param Value
    Data you want to insert 
  
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::push_front(const T& Value)
    {
      if(!head_)
      {
        head_ = new_node(Value);
        tail_ = head_;
        size_++;
        return; // Return 
      }
    
        // Make and Push New Node
      Node *push = new_node(Value);
    
      push->next = head_;
    
      head_ = push;
    
      size_++; // Increment Size
    }
  
   //!< List<T>::push_back
  /***************************************************************************/
  /*!
  
  \brief
    Pushses an object to the back of the list.
  
  \param Value
    A reference to the data you want to put in the object.
  
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::push_back(const T& Value)
    {
      if(!head_)
      {
        head_ = new_node(Value);
        tail_ = head_;
        size_++;
        return;
      }
    
      Node *push = new_node(Value);
    
      tail_->next = push;
    
      tail_ = push;
    
      size_++;
    }
   

   //!< List<T>::pop_front()
  /***************************************************************************/
  /*!
  
  \brief
    Pops the front piece of data in the list
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::pop_front()
    {
      if(empty())
          return; // Return if Empty
      
      Node *temp = head_->next;
      
      delete head_;
      
      head_ = temp;
      
      size_--;
    }
   
   //!< T List<T>::front()
  /***************************************************************************/
  /*!
  
  \brief
    Checks the value of the first data in the list
  
  */
  /***************************************************************************/
  template <typename T>
    T List<T>::front() const
    {
      return head_->data; // Return Data in Head
    }
  
   //!< List<T>::size()
  /***************************************************************************/
  /*!
  
  \brief
    Gets size of the object
  
  \return
     Returns Number Of Nodes in List
    
  */
  /***************************************************************************/
  template <typename T>
    int List<T>::size() const
    {
      return size_; // Returns Number Of Nodes in List
    }
   
   //!< bool List<T>::empty()
  /***************************************************************************/
  /*!
  
  \brief
    Checks if its Empty
  
  \return
    Return if empty (0 flase || 1 true)
    
  */
  /***************************************************************************/
  template <typename T>
    bool List<T>::empty() const
    {
      return size_ == 0 ? 1 : 0; // Return if empty (0 flase || 1 true)
    }
   
   //!< List<T>& List<T>::operator=
  /***************************************************************************/
  /*!
  
  \brief
    Overloads operator = for assignment
  
  \param rhs
    A reference to the object yo use in the assignment
  
  \return
    A reference to the List thats been modified
    
  */
  /***************************************************************************/
  template <typename T>
    List<T>& List<T>::operator=(const List& rhs)
    {
      if(this == &rhs)
        return *this; // Return This

      Node *walkerrhs = rhs.head_;

      while(walkerrhs)
      {
        List::push_back(walkerrhs->data);

        walkerrhs = walkerrhs->next;
      }

      return *this; // Return This
    }

   //!< List<T>::operator+
  /***************************************************************************/
  /*!
  
  \brief
    Overloads operator + 
  
  \param rhs
    A reference to the list
    
  \return
    A list populated with values
    
  */
  /***************************************************************************/
  template <typename T>
    List<T> List<T>::operator+(const List& rhs) const
    {
      Node *walkerlhs = head_;
      Node *walkerrhs = rhs.head_;
      
      List sum;
      
      while(walkerlhs)
      {
        sum.push_back(walkerlhs->data);
        
        walkerlhs = walkerlhs->next;
      }
      
      while(walkerrhs)
      {
        sum.push_back(walkerrhs->data);
        
        walkerrhs = walkerrhs->next;
      }
      
      return sum; // Return Sum
    }

   //!< List<T>::operator+=
  /***************************************************************************/
  /*!
  
  \brief
    Overloads operator += 
  
  \param rhs
    A reference to the list
  
  \return
    Left Hand List
    
  */
  /***************************************************************************/
  template<typename T>
    List<T>& List<T>::operator+=(const List& rhs)
    {
      Node *walkerrhs = rhs.head_;
      
      while(walkerrhs)
      {
        List::push_back(walkerrhs->data);
        
        walkerrhs = walkerrhs->next; 
      }

      return *this; // Left Hand List
    }

   //!< List<T>::operator[]
  /***************************************************************************/
  /*!
  
  \brief
    Overloads subscript operator for rvalues
  
  \param index
    How far into the list to go to access the data
  
  \return
    The data at the specified index
    
  */
  /***************************************************************************/
  template<typename T>
    const T& List<T>::operator[](int index) const
    {
      Node *walker = head_;
      
      for(int i = 0; i < index; i++)
        walker = walker->next;
      
      return walker->data; // Return Walker Data
    }
   
   //!< List<T>::operator[]
  /***************************************************************************/
  /*!
  
  \brief
    Overloads subcript operator for lvalues
  
  \param index
    How far into the list to go to access the data
    
  \return
    A reference to the data at the specified index
    
  */
  /***************************************************************************/
  template<typename T>
    T& List<T>::operator[](int index)
    {  
      Node *walker = head_;

      for(int i = 0; i < index; i++)
        walker = walker->next;
      
      return walker->data; // Return Walker Data
    } 
  
   //!< List<T>::clear()
  /***************************************************************************/
  /*!
  \brief
    Removes all of the nodes in the list
  */
  /***************************************************************************/
  template <typename T>
    void List<T>::clear()
    {
      while (!empty())
        pop_front();
    }

   ////////////////////////
   //! private methods/////
   ////////////////////////
  
   //! List<T>::Node *List<T>::new_node
  /***************************************************************************/
  /*!
  
  \brief
    Allocate a node, initialoze the data and the next pointer
  
  \param data
    The data to put in the node
  
  \return
    A pointer to the node
  */
  /***************************************************************************/
  template <typename T>
    typename List<T>::Node *List<T>::new_node(const T& data) const
    {
      Node *node = new Node(data); 
      node->next = 0;              
      return node; // Return Node
    }
  
} //!< namespace CS170


   ////////////////////////
   //! Non - Members  /////
   ////////////////////////

#include <iomanip>

 //!< CS170::operator<<
/*****************************************************************************/
/*!
\brief 
  Output the list into an ostream object
  
\param os 
  ostream object to output to

\param list 
  the List to output
  
\return
  The ostream object that was passed in
*/
/*****************************************************************************/
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the top
  typename CS170::List<T>::Node *pnode = list.head_;

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  return os; // Return Out Stream
}
#include <iostream>  
using namespace std;

class Book  
{  
   public:  
    int isbn;  
    string title;
    string author;
    string type;
    
    // Constructor with default arguments
    Book(int n=1244, string name="Sally's Nightmare", string writer="M.Jose", string category="Fiction")                  
    {  
      isbn = n;
      title=name;
      author=writer;
      type=category;
    }  
     
};  

int main()  
{  
  Book B1(15467, "The Picture of Dorian Gray", "Oscar Wilde", "Fiction");
  Book B2;   //1
  cout<<"Details of first book:\n"<< B1.isbn << endl<< B1.title<< endl<< B1.author<< endl<< B1.type<< endl;
  cout<<"\nDetails of second book: \n"<< B2.isbn<< endl<< B2.title<< endl<< B2.author<< endl<< B2.type;
  return 0;  
      }  
#include <iostream>

#include <algorithm> // for using transform
#include <string>
#include <cctype> // for using toupper

//#include <stdio.h>
#include <cstring>



using namespace std;


#define SUCCESS     0

const int keySize = 8;



int encrypt(string *message)
{

   const int modulo = message->size() % keySize;
   int nbrRows, paddingCharSize;


   if ( modulo != 0)
   {
     nbrRows = (message->size() / keySize ) + 1;
     paddingCharSize = keySize - modulo;
   }
   else
   {
     nbrRows = message->size() / keySize ;
     paddingCharSize = 0;
   }

   string backFillerStr(paddingCharSize,'.');


   message->insert(message->size(),backFillerStr);

//    (message->size() / keySize ) + 1 :  message->size() / keySize ;

   char* encryptArray[nbrRows];


   // Transpose the characters of the inial string  into the encryption matrix
   for (int i=0;i<nbrRows;i++)
   {
     encryptArray[i] = new char[keySize];
     memset(encryptArray[i], ' ', keySize*sizeof(char));
   }


    transform(message->begin(), message->end(), message->begin(),  ::toupper);

    cout << "Converted to Uppercase Mesage:" << endl;
    cout << *message << endl;


//    for ( std::string::iterator it=message->begin(), int row=0; it!=message->end(); ++it)
     int row;
     int index;
     for (index=0, row=0; index<message->size(); index++)
     {
        char nextChar =  message->at(index);
        int column = index % keySize;
        //std::cout << *it;
        encryptArray[row][column] = nextChar;

        if ( (index % keySize) == 7) row++;
     }



     string result;

     // Scan the matrix from colum to colum, top to bottom and append to the result string
     for (int i=0; i<keySize;i++)
     {
         for (int row=0; row<nbrRows; row++)
         {
            char next = encryptArray[row][i];
            result += next;
         }

         int a = 0;

     }





    for (int i=0;i<nbrRows;i++)
   {
     delete encryptArray[i];
   }

   cout << "\nResults\n" << result;

    return SUCCESS;
}

int main()
{

string initialMessage = "This is a message to encrypt using the transposition cipher. A key size has to be set big enough, so that the encrypted message is not too easy to decrypt.";


    cout << "Intial Mesage:" << endl;
    cout << initialMessage << endl;
    cout << "Message lenght is " <<  initialMessage.size() << endl;

    encrypt(&initialMessage);



   return 0;
}

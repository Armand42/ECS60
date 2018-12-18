#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <istream>
#include "BinaryTree.h"
using namespace std;

// SHOULD ONLY contain main() and additional classes


int main(int argc, char *argv[1]) {
string filename = argv[1];
ifstream characterFile;
characterFile.open(filename);

int frequencyArray[128]; // initializes all values to zero
for (int i = 0; i < 128; i++) {
    frequencyArray[i] = 0;
}
//int frequencyArray[1000];
char stringData[1000];
char characters;

string input;

int spaceCounter = 0;           //count spaces

int characterCount = 0;
int i = 0;
int counter;
int conversion;
while (getline(characterFile, input))  { 
    for (int i = 0; i < input.length(); i++) {
        if (input[i] >= 32 && input[i] <= '~'){ 
        frequencyArray[input[i] /*- 97*/]++;
        }
        cout << input[i];
        
        characterCount++;                           // just to know how many characters are in file
    }
                        
}

for (int k = 32; k < 128; k++) {
    if (frequencyArray[k] > 0) {
        

        cout <<  "\n" <<char(k /*+ 'a'*/) << " appears " << frequencyArray[k] << " times";
       
     
            // use find min function somehow and delete
        
    }

}


cout << "\n";
//cout << " " << " appears " << spaceCounter << " times ";
//cout << "\n" << " loopCount: " <<loopCount;


 

cout << "\nThere are: " << characterCount << " characters" << "\n";
//cout << "There are: " << spaceCounter << " spaces" << "\n";
//cout << "The frequency of this character is: " << countArray[i];










/*for (int i = 0; i < characterCount; i++) {
    cout << stringData[i];
}

// YOU WILL USE findMIN function for finding the minimum in the arrays


 while (stringData[i] != '\0') {
    if(stringData[i] >= 'a' && stringData[i] <= 'z') 
        countArray[stringData[i] - 'a']++;
        i++;
        
    
}
for (int i = 0; i <= characterCount; i++ ) {     // so does this shit
    if (countArray[i] != 0) {
      cout << i << "occurs " << frequency << " times ";
        
    }
}
//cout << spaceCounter;

*/


/*cout << "Enter in a string: " << endl;
cin.getline(stringData, 1000);*/

/*for (int i = 0; i < strlen(stringData); i ++) {
cout << stringData[i] << "\n";
}

char targetValue;*/

// for all characters
// if (stringData[i] >= '32' && stringData[i] <= '126')




// for lowercase characters between a-z
// if(stringData[i] >= 'a' && stringData[i] <= 'z')

// for uppercase characters A-Z
// if (stringData[i] >= 'A' && stringData[i] <= 'Z')

// for numbers 0 - 9
// if (stringData[i] >= '0' and stringData[i] <= '9')

//

/*for (int i = 0; i <= strlen(stringData); i++) {
    


    if (targetValue == stringData[i]) {
        frequency++;
    }
    cout << stringData[i];
}
cout << " The frequency of " << targetValue << " is " << frequency << endl;
*/ 




    return 0;
}
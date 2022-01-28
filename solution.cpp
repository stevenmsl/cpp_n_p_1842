#include <iostream>
#include <vector>
#include <tuple>
#include <cstring>
using namespace std;

/* takeaways
   - think of palindrome as a mirror:
     - it as two halves, and the first
       half is the mirror image of the
       second
     - example 1221
       - the first half is 12
       - the second half is 21
   - focus on the first half but remember
     to perform needed updates on the 
     second half to main a palindrome
     number whenever you make changes 
     to the first half
   - the most critical thing to remember
     when producing the smallest higher 
     palindrome is to start from the
     least significant digit and scan
     toward left two digits at a time 
     to find the candidate
     - when two digits at a time?
       this will make sure what
       have been scanned is in 
       descending order
*/

class Solution
{
public:
  string nextPalindrome(string num)
  {
    const int n = num.length();
    char numChars[n + 1];
    strcpy(numChars, num.c_str());

    if (n <= 3)
      return "";
    /* 
      - find the very last digit of the
        first half
      - examples: 
        - 1221, mid will be pointing to 
          the the second char: 1[2]21
        - 32123, mid will be pointing to 
          the the second char: 3[2]123
    */
    int mid = n / 2 - 1;
    /*
      - i will point at the digit
        that needs to be swapped
        with a less significant 
        digit  
    */
    int i, j;

    /*
      - scan through the first half from 
        right to left (less significant 
        to more significant)
      - compare two digits at a time
        - if the left digit is smaller
          than the right digit we have
          a chance to produce a higher
          palindrome
        - why? the right digit is less
          significant so if we move it
          toward the left direction 
          we can produce a higher number
        - example: 1221
          the first half is 12, we can 
          move 2 to the left to produce 
          a higher number 21
       - also we scan two digits at
         a time so when we find the
         candidate the digits being
         scanned will be in a descending 
         order
             
    */
    for (i = mid - 1; i >= 0; i--)
    {
      /* 
        - numChars[i+1] is the less 
          significant digit
      */
      if (numChars[i] < numChars[i + 1])
      {
        break;
      }
    }

    /* 
       - we can't find any smaller
         from the more significant digits
       - no way you can move the digit
         from right to left to create
         a higher number
       - example 2121
         - first half is 21 you can't
           produce a higher number than
           this     
    */
    if (i < 0)
    {
      return "";
    }

    /*
      - we now need to produce the next
        higher number by moving the less
        significant digit to the 
        left. The digit we move needs to 
        be higher than numChars[i];
      - we need to find the smallest
        from those that are higher
      - example 
        - let say the first half is 46975
        - the i will be pointing 6 -> 4[6]975
        - now we need to find the smallest
          number that are greater than 6 from
          975. We found 7 so the smallest
          is pointing at 7 -> 469[7]5
        - you swap them to get 47965
        - is it the next higer number
          - Nope; you need to reverse 
            965 to 569 to get it        
    */

    int smallest = i + 1;
    for (j = i + 2; j < mid; j++)
      if (numChars[j] > numChars[i] && numChars[j] < numChars[smallest])
        smallest = j;
    swap(numChars[i], numChars[smallest]);

    /* 
      - you need to swap it on the second half as well
      - how to find the corresponding digit on the second
        half?
        - example numChars = 132231        
        - the index of the very last digit is n - 1,
          which is 5 in this case
        - so the index of the counter part of the first digit
          is n - 1 - 0; so the counter part is numChars[5]  
        - how about the counter part index 1 ? 
          n - 1 - 1; so the counter part is numChars[5] 
        - so the formula for finding the counter part
          is n - 1 - i    
    */
    swap(numChars[n - 1 - i], numChars[n - 1 - smallest]);

    /*
      - how we scan the first half will guarantee
        that everything after i is in descending 
        order
        - we scan two digits at a time and stop
          once the left is smaller than the right
          that means what have been scanned so
          far the right is smaller that the left
          so it's in descending order
        - also when you swap the candidate
          with a digit that is smallest but larger
          than the candidate the descending order
          is still maintained 

      - we need to reverse to produce the smallest
        number
    */
    reverse(numChars, i + 1, mid);

    /* 
       - need to do the reverse on the 
         second half for the corresponding 
         range  
       - example 
         - 47965|56974
         - we want to reverse 965 ( i+1 to mid) 
           on the first half with 5 being the 
           last digit (mid)
         - so on the second part we need to
           start from the first digit of 
           second half to (n-1)-(i+1)
           , which will give us 569
       - note: you don't need to care if n is
         even or odd as the counter part index
         formula will always calculate it right
         (n-1) - index      
    */

    reverse(numChars, (n - 1) - mid, (n - 1) - (i + 1));

    return convertToString(numChars, n);
  }

  void reverse(char num[], int i, int j)
  {
    while (i < j)
    {
      swap(num[i], num[j]);
      i++;
      j--;
    }
  }

  string convertToString(char *a, int size)
  {
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
      s = s + a[i];
    }
    return s;
  }
};

string testFixture1()
{
  return "4697557964";
  //return "1221";
}
string testFixture2()
{
  return "46975357964";
}
string testFixture3()
{
  return "5432112345";
}

void test1()
{
  Solution sol;
  cout << "Test 1 - expect to see 4756996574" << endl;
  cout << sol.nextPalindrome(testFixture1()) << endl;
}

void test2()
{
  Solution sol;
  cout << "Test 2 - expect to see 47569396574" << endl;
  cout << sol.nextPalindrome(testFixture2()) << endl;
}

void test3()
{
  Solution sol;
  cout << "Test 3 - expect to see empty string" << endl;
  cout << sol.nextPalindrome(testFixture3()) << endl;
}

main()
{
  test1();
  test2();
  test3();
  return 0;
}
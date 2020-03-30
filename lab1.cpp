#include<iostream>
#include<string>

using namespace std;
int BinarytoInteger(string number){
  int value = 0;
  int counter = 1;//2^0
  string n = number;

  int length = n.length();
  for (int i = length - 1; i >= 0; --i){
    if (n[i] == '1')
      value += counter;
      counter = counter *2;
  }
  return value;
}
int HextoInteger(string number){
  int value = 0;
  int counter = 1;//16^0
  string n = number;
  int length = n.length();
  for (int i = length - 1; i >=0; --i){
    if(n[i] >= '0' && n[i] <= '9'){
    value += (n[i] - 48 ) * counter;
    counter = counter * 16;
  }
    else if (n[i] >= 'A' && n[i] <= 'F'){
      value += (n[i] - 55) * counter;
      counter = counter * 16;
    }
  }
  return value;
}
void DecToBinary(int number){
  int Binary[32];
  int i = 0;
  int n = 0;
  while (number > 0){
    Binary[i] = number % 2;
    number = number / 2;
    ++i;
  }

  for (int j = i - 1; j >= 0; --j){
    cout << Binary[j];
  }
  cout << endl;

}
void DecToHex(int number){
  char Hex[50];
  int i = 1;
  int n;
  while (number > 0){
    n = number % 16;
    if (n < 10 ){
      Hex[i] = n + 48;
      i++;}
    else{
      Hex[i] = n + 55;
      i++;}
      number = number/16;
  }
  for (int j = i-1; j >= 0; --j){
    cout << Hex[j];
  }
  cout << endl;
}
string AddBinary(string a, string b){
  string sum = "";
  int n = 0;
  int i = a.size() - 1;
  int j = b.size() - 1;
  while ( i >= 0 || j >= 0 || n == 1){
    n += ((i >= 0)? a[i] - '0': 0);
    n += ((j >= 0)? b[j] - '0': 0);
    sum = char(n % 2 + '0') + sum ;
    n/=2;
    --i;
    --j;
  }
  return sum;
}
void HexAdd(string a, string b){
  int sum1 = HextoInteger(a);
  int sum2 = HextoInteger(b);
  int sum3 = sum1 +sum2;
  DecToHex(sum3);
}
void HexMult(string a,string num){
  int sum1 = HextoInteger(a);
  int sum2 = HextoInteger(num);
  int sum3 = sum1 * sum2;
  DecToHex(sum3);
}

int Question8(int number){
  int sum = 0;
     sum = (number + 4) *3;
  return sum;}

  int Question8pt2(string number){
    int sum, sum1;
    sum1 = (BinarytoInteger(number) + 4 ) *3;
  //sum = DecToBinary(sum1);
  return sum1; }

  int Question8pt3(string number){
    int sum, sum1;

    sum1 = (HextoInteger(number) + 4) *3;
    //sum = DecToHex(sum1);

  return sum1;
}


int main(){
  //QUESTION 1
  string Binary;
  cout << "Enter Binary number...";
  cin >> Binary;
  cout << BinarytoInteger(Binary) << endl;
  //QUESTION 2
  string Hex;
  cout << "Enter Hexadecimal number...";
  cin >> Hex;
  cout << HextoInteger(Hex) << endl;
  //QESTION 3
  int DecimalNum;
  cout << "Enter Decimal number...";
  cin >> DecimalNum;
  DecToBinary(DecimalNum);
  //QUESTION 4
  int Decimal;
  cout <<"Enter Decimal number...";
  cin >> Decimal;
  DecToHex(Decimal);
  //Question 5
  string Binary1;
  string Binary2;
  cout << "Enter 2 binary numbers to add...(1-10)\n";
  cin >> Binary1 >> Binary2;
  cout << AddBinary(Binary1,Binary2) << endl;
  //QUESTION 6
  string Hex1, Hex2;
  cout << "Enter 2 Hex numbers to add...\n";
  cin >> Hex1 >> Hex2;
  HexAdd(Hex1, Hex2);
  //QUESTION 7
  string HexNum, HexNum2;
  cout << "Enter a Hex digit to multiply by...";
  cin >> HexNum;
  cout << "Enter a Hex number... ";
  cin >> HexNum2;
  HexMult(HexNum,HexNum2);
  //Question 8
  char ans;
  cout << "Chose what kind of number you want...(b for binary, d for decimal, h for hex)";
  cin >> ans;
  if (ans == 'd'){
    cout << "enter decimal number: ";
    cin >> Decimal;
    cout << Question8(Decimal)<<endl;
  }
  else if (ans == 'b'){
    cout << "Enter binary number: ";
    cin >> Binary;
    cout << Question8pt2(Binary)<<endl;
  }
  else if (ans == 'h'){
    cout << "Enter hex number: ";
    cin >> Hex;
    cout << Question8pt3(Hex)<<endl;
  }

  return 0;
}

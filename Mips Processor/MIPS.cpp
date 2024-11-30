#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int cti(char);
int STI(string);
int binToDecimal(int);
string decToBinary(int);
int lettersToNumbers(char);
string hexToBinary(string hex);
string subString(string,int, int);
char numToLetter(int);
char numToLetter(int);
string bintoHex(string bin);
void addZeros(string &s1, string &s2);

string operator&&(string s1, string s2){
    addZeros(s1,s2);
    string f = "";
    for(int i = s1.length()-1;i >= 0;i--){
        if(s1[i] == '1' && s2[i] == '1'){
            f = f+"1";
        }
        else{
            f=f+"0";
        }
    }
    string a = bintoHex(f);
    return a;
}

string operator||(string s1, string s2){
    s1 = hexToBinary(s1);
    s2 = hexToBinary(s2);
   
    addZeros(s1,s2);
    string f = "";
    for(int i = s1.length()-1;i >= 0;i--){
        if(s1[i] == '1' || s2[i] == '1'){
            f = "1"+f;
        }
        else{
            f="0"+f;
        }
    }
    string a = bintoHex(f);
    return a;
}
string operator^(string s1, string s2){
    addZeros(s1,s2);
    string f = "";
    for(int i = s1.length()-1;i >= 0;i--){
        if(s1[i] == '1' || s2[i] == '1' && !(s1[i] == '1' && s2[i] == '1')){
            f = f+"1";
        }
        else{
            f=f+"0";
        }
    }
    string a = bintoHex(f);
    return a;
}
string binToDec(string bin){
    int answer = 0;
    int tracker = 1;
    for(int i = bin.length()-1;i>=0;i--){
        if(bin[i]=='1'){
            answer+=tracker;
        }
        tracker*=2;
    }
    return to_string(answer);
}

string hexToDec(string hex){
    hex = hexToBinary(hex);
    hex = binToDec(hex);
    return hex;
}
string decToHex(long n){
    if(n == 0){
    return "0";
  }
  string str = "";
  string added = "";
  while(n != 0)
  {
    int dig = n%16;
    n = n/16;
    
    if(dig > 9){
        
        char c = numToLetter(dig);
        str = c + str;

    }
    else{
        str = to_string(dig) + str;
    }
   
  }
//I keep it as a string because the integer data type gets easily overloaded

  return str;
}
string ADD(string h1, string h2){
    int d1 = STI(hexToDec(h1));
    int d2 = STI(hexToDec(h2));
    long answer = d1+d2;
    cout<<answer<<endl;
    return decToHex(answer);

}
string SUB(string h1, string h2){
    int d1 = STI(hexToDec(h1));
    int d2 = STI(hexToDec(h2));
    long answer = d1-d2;
    if(answer < 0){
        answer*=-1;
    }
    return decToHex(answer);

}
void RFormat(string hex,map<int, vector<string> > reg){
    hex = hexToBinary(hex);
    hex = subString(hex,6,hex.length());
    int rs = binToDecimal(STI(subString(hex,0,5)));
    int rt = binToDecimal(STI(subString(hex,5,10)));
    int rd = binToDecimal(STI(subString(hex,10,15)));
    int ins =  binToDecimal(STI(subString(hex,20,26)));
    if(ins == 32){
        string set = ADD(reg[rs][0],reg[rt][0]);
        
        reg[rd][0] = set;
    }
    if(ins == 34){
        string set = SUB(reg[rs][0],reg[rt][0]);
        reg[rd][0] = set;
    }
    if(ins == 36){
        string set = (reg[rs][0]&&reg[rt][0]);
        reg[rd][0] = set;
    }
    if(ins == 37){
        string set = (reg[rs][0]||reg[rt][0]);
        reg[rd][0] = set;
    }
     if(ins == 38){
        string set = (reg[rs][0]^reg[rt][0]);
        reg[rd][0] = set;
    }
    cout<<"Register "<<rd<<" contains the value of "<<reg[rd][0]<<endl;
}
void IFormat(string hex,map<int, vector<string> > reg){
    hex = hexToBinary(hex);
    int opCode =  binToDecimal(STI(subString(hex,0,6)));
    int rs = binToDecimal(STI(subString(hex,6,11)));
    int rt = binToDecimal(STI(subString(hex,11,16)));
    int im = binToDecimal(STI(subString(hex,16,32)));
    if(opCode == 8){
        string set = ADD(reg[rs][0],to_string(im));
        reg[rt][0] = set;
    }
    if(opCode == 43){
        string set = ADD(reg[rs][1],to_string(im));
        reg[rt][0] = set;
    }
    cout<<"Register "<<rt<<" contains the value of "<<reg[rt][0]<<endl;
}
bool isHex(string hex){
    if(hex.length() > 8){
        cout<<"Too Long!"<<endl;
        return false;
    }
    if(hex.length() < 8){
        cout<<"Too Short!"<<endl;
        return false;
    }
    for(int i = 0;i < hex.length();i++){
        if(hex[i] > '9' || hex[i] < '0'){
            if(hex[i] < 'a' || hex[i] > 'f')
            {
                if(hex[i] < 'A' || hex[i] > 'F')
                {
                    cout<<"Invalid Character"<<endl;
                    return false;
                }
            }
        }
    }
    return true;
};
int main(){

    map<int, vector<string> > reg;
    reg[1].push_back("0009");
    reg[1].push_back("0103");
    reg[2].push_back("012A");
    reg[2].push_back("0104");
    reg[3].push_back("0015");
    reg[3].push_back("0105");
    reg[4].push_back("0023");
    reg[4].push_back("0106");
    reg[5].push_back("FF12");
    reg[5].push_back("0106");
    reg[6].push_back("0076");
    reg[6].push_back("0107");
    reg[7].push_back("FFC9");
    reg[7].push_back("0108");
    reg[8].push_back("0015");
    reg[8].push_back("0109");

    string quit= "c";
    string input;
    while(quit != "q"){
        cout<<"Enter hex: ";
        cin>>input;
        while(!isHex(input)){
            cout<<"Enter hex: ";
            cin>>input;
        }
        if(subString(input,0,2) == "00"){
            RFormat(input, reg);
        }
    }
    

    
};
int cti(char i)
{
  i = tolower(i);
  return i - '0';
}
int STI(string s)
{
    int c = 0;
    int meme = 1;
    for(int i = s.length()-1;i > -1; i--)
    {
        int v = cti(s[i])*(meme);
        c = c+v;
        meme = meme*10;
    }
    return c;
}
int binToDecimal(int n){
  
  int answer = 0;
//The variable that increases the power by 2 per placement
  int multi = 1;
  int added;
  while(n != 1 && n != 0)
  {
    added = (n%10) * multi;
    answer = answer + added;
    multi = multi * 2;
    n = n/10;
  }
  added = n * multi;
  answer = answer + added;
  return answer;
  
}
string decToBinary(int n)
{
  if(n == 0){
    return "0";
  }
  string str = "";
  string added = "";
  while(n != 0)
  {
    int dig = n%2;
    n = n/2;
    str = to_string(dig) + str;
  }
//I keep it as a string because the integer data type gets easily overloaded
  return str;
}
int lettersToNumbers(char c){
  c = char(tolower(c));
  return c - 87;
}
string hexToBinary(string hex){
  string answer = "";
  int value = 0;
  string seg = "";
  for(int i = hex.length()-1;i >= 0; i--)
  {

    if(hex[i] >= '0' && hex[i] <= '9')
    {
      value = cti(hex[i]);
      seg = decToBinary(value);
      
      if(seg.length() == 1){
        seg = "000"+seg;
   
      }
      else if(seg.length() == 2){
        seg = "00"+seg;
      }
      else if(seg.length() == 3){
        seg = "0"+seg;
      }
    }
    else{
      value = lettersToNumbers(hex[i]);
      seg = decToBinary(value);
    }
    
    answer = seg + answer;
  }

  return answer;
}
string subString(string str,int start, int end){
  string nn = "";
  for(int i = start;i < end;i++){
    nn+=str[i];
  }
  return nn;
}
char numToLetter(int i){
  return to_string(i)[1] + 49;
}
string bintoHex(string bin){
string hex = "";
int end  = bin.length();
int start = end;
while(start != 0){
start = end - 4;
if(start < 0){
  start = 0;
}
string curr = subString(bin,start,end);
int val = binToDecimal(STI(curr));
if(val < 10){
  hex = to_string(val) + hex;
}
else{
  hex = numToLetter(val) + hex;
}
end = start;
}
return hex;
}
// void addZeros(string s1, string s2){
// int diff = s1.length()-s2.length();
//     if(diff < 0){
//         diff*=-1;
//     }
//     string z = "";
//     for(int i = 0;i < diff;i++){
//         z+="0";
//     }
//     if(s1.length()>s2.length()){
//         s2 = z+s2;
//     }
//     else{
//         s1 = z+s1;
//     }
// }
void addZeros(string &s1, string &s2) {
    int diff = s1.length() - s2.length();
    if (diff < 0) diff = -diff;

    string zeros(diff, '0');
    if (s1.length() > s2.length()) {
        s2 = zeros + s2;
    } else {
        s1 = zeros + s1;
    }
}
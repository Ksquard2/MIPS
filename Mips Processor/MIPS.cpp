#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

int cti(char);
void printRegisters(map<int, vector<string> >);
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
void RFormat(string hex,map<int, vector<string> >& reg){
    hex = hexToBinary(hex);
    cout<<"Binary: "<<"(6)"<<subString(hex,0,6)<<" (5)";
    hex = subString(hex,6,hex.length());
    cout<<subString(hex,0,5)<<" (5)"<<subString(hex,5,10)<<" (5)"<<subString(hex,10,15)<<" (6)"<<subString(hex,20,26)<<endl;
    int rs = binToDecimal(STI(subString(hex,0,5)));
    cout<<"Rs: $"<<rs<<endl;
    int rt = binToDecimal(STI(subString(hex,5,10)));
    cout<<"Rt: $"<<rt<<endl;
    int rd = binToDecimal(STI(subString(hex,10,15)));
    cout<<"Rd: $"<<rd<<endl;
    int ins =  binToDecimal(STI(subString(hex,20,26)));
   
    if(ins == 32){
        cout<<"Instruction: "<<ins<<" -> add"<<" $"<<rs<<" "<<" $"<<rt<<" "<<" $"<<rd<<endl;
        string set = ADD(reg[rs][0],reg[rt][0]);
        reg[rd][0] = set;
    }
    if(ins == 34){
      cout<<"Instruction: "<<ins<<" -> subtraction"<<" $"<<rs<<" "<<" $"<<rt<<" "<<" $"<<rd<<endl;
        string set = SUB(reg[rs][0],reg[rt][0]);
        reg[rd][0] = set;
    }
    if(ins == 36){
        cout<<"Instruction: "<<ins<<" -> AND"<<" $"<<rs<<" "<<" $"<<rt<<" "<<" $"<<rd<<endl;
        string set = (reg[rs][0]&&reg[rt][0]);
        reg[rd][0] = set;
    }
    if(ins == 37){
        cout<<"Instruction: "<<ins<<" -> OR"<<" $"<<rs<<" "<<" $"<<rt<<" "<<" $"<<rd<<endl;
        string set = (reg[rs][0]||reg[rt][0]);
        reg[rd][0] = set;
    }
     if(ins == 38){
        cout<<"Instruction: "<<ins<<" -> XOR"<<" $"<<rs<<" "<<" $"<<rt<<" "<<" $"<<rd<<endl;
        string set = (reg[rs][0]^reg[rt][0]);
        reg[rd][0] = set;
    }

}
void IFormat(string hex, map<int, vector<string> >& reg){
    hex = hexToBinary(hex);
    
    cout<<"Binary: (6)"<<subString(hex,0,6)<<" (5)"<<subString(hex,6,11)<<" (5)"<<subString(hex,11,16)<<" (16)"<<subString(hex,16,32)<<endl;
    int opCode =  binToDecimal(STI(subString(hex,0,6)));
 
    int rs = binToDecimal(STI(subString(hex,6,11)));
    cout<<"Rs: $"<<rs<<endl;
    int rt = binToDecimal(STI(subString(hex,11,16)));
    cout<<"Rt: $"<<rt<<endl;
    int im = binToDecimal(STI(subString(hex,16,32)));
    cout<<"Immediate: "<<im<<endl;
    
    if(opCode == 8){
        cout<<"OpCode: "<<opCode<<" -> addi"<<" $"<<rs<<" "<<im<<" $"<<rt<<endl;
        string set = ADD(reg[rs][0],to_string(im));
        reg[rt][0] = set;
    }
    if (opCode == 35) { // LW
        cout<<"OpCode: "<<opCode<<" -> load word"<<" $"<<rs<<" "<<im<<" $"<<rt<<endl;
        string address = ADD(reg[rs][1], to_string(im));
        reg[rt][0] = address;
      
    }
    if (opCode == 43) { // SW
        cout<<"OpCode: "<<opCode<<" -> store word"<<" $"<<rs<<" "<<im<<" $"<<rt<<endl;
        string address = ADD(reg[rs][0], to_string(im));
        if(address.length() == 3){
          address = "0"+address;
        }
        else if(address.length() == 2){
          address = "00"+address;
        }
        reg[rt][1] = address;
    }
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
        cout<<"Enter hexidecimal: ";
        cin>>input;
        while(!isHex(input)){
            cout<<"Enter hex: ";
            cin>>input;
        }
        if(subString(input,0,2) == "00"){
            RFormat(input, reg);
        }
        else{
          IFormat(input, reg);
        }
        printRegisters(reg);
        cout<<"Press q to quit: ";
        cin>>quit;
    }
    cout<<"Thank you for using our MIPS Processor";

    
};
int cti(char i)
{
  i = tolower(i);
  return i - '0';
}
void printRegisters(map<int, vector<string> > regi) {
    cout << "Updated Register File:\n";
    for (auto& reg : regi) {
        cout << "$" << reg.first << ": " << setw(8) << setfill('0') << reg.second[0] << " memory: " << reg.second[1] << "\n";
    }
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
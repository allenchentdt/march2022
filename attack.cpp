#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

struct Coordinate{ int x, y;};

int max_value(map<int,int>& m){
   int max = 0;
   for(auto it = m.cbegin();it != m.cend();it++) if(it->second > max){
      max = it->second;
   }
   return max;
}

void delete_by(vector<int>& P, vector<int>& C, vector<int> delete_c){
   for(int i=0;i<delete_c.size();i++)
      for(int p=0;p<C.size();p++) if(C[p] == delete_c[i]) P[p]=0;
}

int sum(vector<int> P){
   int sum =0;
   for(int p=0;p<P.size();p++) if(P[p]) sum++;
   return sum;
} 

void find_delete(vector<int>& delete_c , map<int,int> same, int max){
   for(auto it = same.cbegin();it != same.cend();it++) if(it->second == max) delete_c.push_back(it->first);
} 

int find_min(vector<Coordinate> v){
   int min =0;
   int size = v.size();
   vector<int> X(size),Y(size), P(size);
   for(int p=0;p<size;p++){
      X[p] = v[p].x;
      Y[p] = v[p].y;
      P[p] = 1;
   }  
   int remain = sum(P);
   while(remain > 0){
      map<int, int> same_x, same_y;
      for(int p=0;p<size;p++) if(P[p]){
         same_x[X[p]]++;
         same_y[Y[p]]++;
      } 
      int max_x = max_value(same_x);
      int max_y = max_value(same_y);
      vector<int> delete_x;
      vector<int> delete_y;
      if(max_x > max_y){
         find_delete(delete_x,same_x,max_x);
         delete_by(P,X,delete_x);
         min+= delete_x.size();
      }else if(max_x == max_y){
         find_delete(delete_x,same_x,max_x);
         find_delete(delete_y,same_y,max_y);
         if(delete_x.size() > delete_y.size()) {delete_by(P,X,delete_x); min+= delete_x.size();}
         else {delete_by(P,Y,delete_y); min+= delete_y.size();}
      }else{
         find_delete(delete_y,same_y,max_y);
         delete_by(P,Y,delete_y); 
         min+= delete_y.size();
      }     
      remain = sum(P);
   }
   return min;
}
   
int main(){ 
   /*Input*/
   ifstream fin;
   fin.open("input.txt");
   string line;
   getline(fin,line); 
   stringstream ss(line);
   int T,t,N,n;  
   Coordinate c;
   ss >> T;
   vector <Coordinate> v[T];
   for(t=0;t<T;t++){ 
      getline(fin,line); 
      stringstream ss(line);
      ss >> N;
      for(n=0;n<N;n++){
         getline(fin,line);
         stringstream ss(line);
         ss >> c.x >> c.y;
         v[t].push_back(c);
      }
   }
   
   /*Output*/
   ofstream fout;  
   fout.open("output.txt");
   for(t=0;t<T;t++) fout << find_min(v[t]) << endl;
   fout.close();   
   return 0;
}

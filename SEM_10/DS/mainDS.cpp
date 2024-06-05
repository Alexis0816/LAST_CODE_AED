#include "DS.hpp"
int main(){
    vector<char> data = {'a','b','c','d','e','f','g','h'};
    //                    0   1   2   3   4   5   6   7
    DisjoinSet<char>* ds = new DisjoinSet<char>(data);
    cout<<"Conjuntos: "<<ds->sets()<<endl;// 8
    ds->Union(0, 2);//{0,2} 1,3,4,5,6,7
    ds->Union(5, 6);//{0,2} 1,3,4,{5,6},7
    ds->Union(1, 6);//{0,2} {1,5,6}, 3,4,7
    ds->Union(7, 0);//{0,2,7} {1,5,6}, 3, 4
    ds->Union(4, 3);//{0,2,7} {1,5,6}, {3,4}
    cout<<"Conjuntos: "<<ds->sets()<<endl;// 3
    cout<<"1 y 5 estan conectados?: "<<ds->is_connected(1, 5)<<endl; // 1
    cout<<"2 y 4 estan conectados?: "<<ds->is_connected(2, 4)<<endl; // 0
    ds->Union(2, 5);//{0,2,7,1,5,6}, {3,4}
    ds->Union(3, 1);//{0,2,7,1,5,6,3,4}
    cout<<"Conjuntos: "<<ds->sets()<<endl;// 1


    return 0;
}
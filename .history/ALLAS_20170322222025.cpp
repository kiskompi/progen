#include <string>
#include <iostream>
bool unique(std::string st){
    for(int pos = 0; pos < st.size(); ++pos){
        char buff = st.at(pos);
        for(int i = pos + 1; i < st.size(); ++i){
            if(st.at(i) == buff) return false;
        }
    }
    return true;
}

int main(){
    std::string stf = "asfasdfasdfasd";
    std::string stt = "asdfgh";
    std::cout<<unique(stf)<<std::endl<<unique(stt);
}
#include <bits/stdc++.h>

using namespace std;

map<string, string> mp = {
    {"int16_t[32]", "a"},
    {"int8_t","b"},
    {"uint8_t","B"},
    {"int16_t","h"},
    {"uint16_t","H"},
    {"int32_t","i"},
    {"uint32_t","I"},
    {"float","f"},
    {"double","d"},
    {"char[4]","n"},
    {"char[16]","N"},
    {"char[64]","Z"},
    {"int16_t * 100","c"},
    {"uint16_t * 100","C"},
    {"int32_t * 100","e"},
    {"uint32_t * 100","E"},
    {"int32_t latitude/longitude","L"},
    {"uint8_t flight mode","M"},
    {"int64_t","q"},
    {"uint64_t","Q"}};




bool is_forb(char x) {
    return(x == '.' || x == '(' || x == ')' || x == '>' || x == '-' || x == ';');
}


void sp_trim(string& str) {
    string t = "log_";
    for(char ch : str) {
        if(is_forb(ch)) {
            if(t.back() != '_') t +=  "_";
        } else {
            t.push_back(ch);
        }

    }
    if(!t.empty() && t.back() == '_') t.pop_back();
    str = t;
}



string build_act(string& model) {
    string ret = ("#define ACTIVE_LOG_" + model + "1");
    return ret;
}

string build_header(string& model, string& name_func) {
    string ret = ("#define AUX_LOG_" + model + " AP::logger().Write_" + name_func + "(\\");
    return ret;
}


int main() {
    cout << "===============ARQUIVO.CPP ====================\n\n";
    string model;
    cin >> model;
    cout << build_act(model) << endl;

    string name_func;
    cin >> name_func;
    cout << "\n\n";
    cout << build_header(model, name_func) << endl;
    
    
    vector<string> type, buffer;
    string test, curType;

    while(cin >> curType >> test) {
        sp_trim(test);
        buffer.push_back(test);
        type.push_back(curType);
    }


    for(int i = 0; i < buffer.size()-1; ++i) {
        cout << "\t" + buffer[i] + "," + " \\" << endl;
    }

    cout << "\t" + buffer.back() + ")" << endl;
    cout << "\n\n";

    cout << "=============== XMOBOTS_LOGS.H ====================\n\n";

    for(string &s : buffer) {
        s.erase(s.begin(), s.begin() + 4);
    }

    cout << "#define LOG_" <<  model << "_BASE(struct_enum)\\" << endl;
    cout << "\t{ (struct_enum), sizeof(log_" + model + "), \"EKFJ\",\\" << endl;
    cout << "\t\"Q";


    for(string it : type) {
        cout << mp[it];
    }
    cout << "\",\"t,";

    
    for(int i = 1; i <= type.size(); ++i) {
        cout << i;
        if(i != type.size()) cout << ",";
    }
    cout << "\",\"s";
    for(int i = 0; i < type.size(); ++i) {
        cout << "-";
    }

    cout << "\",\"F";
    for(int i = 0; i < type.size(); ++i) {
        cout << "0";
    }
    cout << "\"}\n";
    cout << endl;
    cout << "struct PACKED log_" + model + " {\n\tLOG_PACKET_HEADER;\n";
    cout << "\tuint64_t time_us;" << endl;

    for(int i = 0; i < buffer.size(); ++i) {
        cout << "\t" << type[i] << " " << buffer[i] << ";" << endl;
    }


    cout << "};\n\n";
}
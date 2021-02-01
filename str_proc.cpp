#include <bits/stdc++.h>

using namespace std;


const int MAX = 255;


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
    return(x == '.' || x == '(' || x == ')' || x == '>' || x == '-' || x == ';' || x == '[' || x == ']');
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
    string ret = ("#define ACTIVE_LOG_" + model + " 1");
    return ret;
}

string build_header(string& model, string& name_func) {
    string ret = ("#define AUX_LOG_" + model + " AP::logger().Write_" + name_func + "(\\");
    return ret;
}


int main() {
    cout << "===============ARQUIVO.CPP ====================\n\n";
    vector<string> model(MAX), name(MAX), name_func(MAX);
    vector<string> type[MAX], buffer[MAX], originals[MAX];

    string test, curType;
    int size = 0;
    cin >> model[size] >> name[size] >> name_func[size];
    while(cin >> curType) {
        if(curType == "END") {
            size++;
            cin >> model[size] >> name[size] >> name_func[size];
            continue;
        }
        cin >> test;
        originals[size].push_back(test);
        sp_trim(test);
        buffer[size].push_back(test);
        if(curType == "bool") curType = "uint8_t";
        if(curType == "int") curType = "int32_t";
        type[size].push_back(curType);
    }

    
    

    for(int j = 0; j < size; ++j) {
        cout << build_act(model[j]) << endl;
        cout << build_header(model[j], name_func[j]) << endl;
        for(int i = 0; i < buffer[j].size()-1; ++i) {
            cout << "\t" + buffer[j][i] + "," + " \\" << endl;
        }

        cout << "\t" + buffer[j].back() + ")" << endl;
        cout << "\n\n";
    }

      cout << "ATRIBUICAO PARA OS #if E #endif\n\n";
      for(int j = 0; j < size; ++j) {
        for(int i = 0; i < buffer[j].size(); ++i) {
            cout << '\t' << type[j][i] << " " << buffer[j][i] << " = " << originals[j][i] << ";\n";
        }
        cout << "\tAUX_LOG_" + model[j] << ";\n\n";
      }
    cout << "\n\n=============== XMOBOTS_LOGS.H ====================\n\n";

    for(int j = 0; j < size; ++j) {
        for(string &s : buffer[j]) {
            s.erase(s.begin(), s.begin() + 4);
        }

        cout << "#define LOG_" <<  model[j] << "_BASE(struct_enum)\\" << endl;
        cout << "\t{ (struct_enum), sizeof(log_" + model[j] + "), \"" + name[j] + "\",\\" << endl;
        cout << "\t\"Q";


        for(string it : type[j]) {
            cout << mp[it];
        }
        cout << "\",\"t,";

        
        for(int i = 1; i <= type[j].size(); ++i) {
            cout << i;
            if(i != type[j].size()) cout << ",";
        }
        cout << "\",\"s";
        for(int i = 0; i < type[j].size(); ++i) {
            cout << "-";
        }

        cout << "\",\"F";
        for(int i = 0; i < type[j].size(); ++i) {
            cout << "0";
        }
        cout << "\"}\n";
        cout << endl;
        cout << "struct PACKED log_" + model[j] + " {\n\tLOG_PACKET_HEADER;\n";
        cout << "\tuint64_t time_us;" << endl;

        for(int i = 0; i < buffer[j].size(); ++i) {
            cout << "\t" << type[j][i] << " " << buffer[j][i] << ";" << endl;
        }
        cout << "};\n\n";

    }
    cout << "=============== AP_LOGGER_H====================\n\n";
    
    string tmp[MAX];

    for(int j = 0; j < size; ++j) {
        tmp[j] = "Write_" + name_func[j] + "(";
        for(int i = 0; i < buffer[j].size(); ++i) {
            tmp[j] += type[j][i];
            tmp[j].push_back(' ');
            tmp[j] += buffer[j][i];
            if(i != buffer[j].size()-1) tmp[j].push_back(',');
        }
        cout << "void " << tmp[j];
        cout << ");\n\n\n";
    }


    cout << "===============LOG_STRUCTURE.H=======================\n";
    cout << "NAO ESQUECER O SHOULD_LOG_EKF!!!!!\n\n";

    for(int j = 0; j < size; ++j) {
        cout << "LOG_" + model[j] << ",\n";
    }
    
    for(int j = 0; j < size; ++j) {
        cout << "LOG_" << model[j] << "_BASE(LOG_" << model[j] << "),\\\n";
    }
    
    cout << "\n\n===============LOG_FILE_CPP====================\n\n";

    for(int j = 0; j < size; ++j) {
        cout << "void AP_Logger::";
        for(int i = 0; i < tmp[j].size(); ++i) {
            cout << tmp[j][i];
            if(tmp[j][i] == '(') cout << endl << '\t';
            if(tmp[j][i] == ',') cout << "\n\t"; 
        }

        cout << ")\n{\n";
        cout << "\tstruct log_" << model[j] << " pkt = {\n\t\tLOG_PACKET_HEADER_INIT(LOG_" + model[j] + "),\n";
        cout << "\t\ttime_us : AP_HAL::micros64(),\n";
        for(int i = 0; i < buffer[j].size(); ++i) {
            cout << "\t\t";
            cout << buffer[j][i] << " : " << buffer[j][i];
            if(i != buffer[j].size()-1) cout << ',';
            cout << endl;
        }
        cout << "\t};\n\tWriteBlock(&pkt, sizeof(pkt));\n} \n\n";
    }

    cout << "--------------------------------------------------------------\n\n\n";
    cout << "PARTE DO MATLAB, ALIMENTAR O WORKSPACE COM VARIAVEIS LOGADAS CONVERT_MODELO_LOGS.M\n\n";
    for(int j = 0; j < size; ++j) {
        string time = name[j] + "_time";
        cout << "\t" << time << " = 1e-6*" << name[j] << "(:,2);\n";
        int counter = 3;
        for(string& it : buffer[j]) {
            cout << "\t" << name[j] << "_" << it << " = [";
            cout << time << ", " << name[j] << "(:," << counter++ << ")];\n";
        }
        cout << "\n\n";
    }

}

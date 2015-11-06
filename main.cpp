#include <iostream>
#include <cstdlib>
#include <fstream>

#define MEM_NUM_WORDS 1025

using namespace std;

int main(int argc, char** argv) {
    cout << "PicoBlaze MEM Converter v. 0.2 (C) 2015 by Piotr Żurek" << endl;
    if(argc != 3) {
        cout << "Usage: " << argv[0] << " input_mem_file output_mem_file" << endl;
    } else {
        string filedata[MEM_NUM_WORDS];
        string outfiledata[MEM_NUM_WORDS];
        int ifd[MEM_NUM_WORDS];
        ifstream inmem(argv[1]);
        if(!inmem) {
            cerr << "Could not open input file!" << endl;
            return EXIT_FAILURE;
        } else {
            cout << "Input from: " << argv[1] << endl;
            int iter = 0;
            while(!inmem.eof() && iter < MEM_NUM_WORDS) {
                string cur;
                inmem >> cur;
                if(iter == 0 || cur[0] != '@') {
                    filedata[iter] = cur;
                    iter++;
                }
            }
        }
        inmem.close();
        filedata[0] = filedata[0].substr(1, filedata[0].length()-1);
        for(int i = 0; i < MEM_NUM_WORDS; i++) {
            sscanf(filedata[i].c_str(), "%x", ifd+i);
        }
        char buffer[5];
        for(int i = 0; i < MEM_NUM_WORDS; i++) {
            for(int j = 0; j < 5; j++) {
                buffer[j] = '\000';
            }
            if(i == 0) {
                sprintf(buffer, "%04X", ifd[i]);
                outfiledata[i] = "@";
                outfiledata[i] += buffer;
            } else {
                sprintf(buffer, "%05X", ifd[i]);
                outfiledata[i] = "";
                outfiledata[i] += buffer;
            }
        }
        int tmp = 0;
        ofstream outmem(argv[2]);
        if(!outmem) {
            cerr << "Could not open output file!" << endl;
            return EXIT_FAILURE;
        }
        for(int i = 0; i < MEM_NUM_WORDS; i++) {
            if(i == 0) {
                outmem << outfiledata[i] << "  ";
            } else {
                outmem << outfiledata[i];
                if(tmp < 15) {
                    outmem << " ";
                    tmp++;
                } else {
                    outmem << endl;
                    tmp = 0;
                }
            }
        }
        outmem.close();
        cout << "Output written to: " << argv[2] << endl;
    }
    return EXIT_SUCCESS;
}
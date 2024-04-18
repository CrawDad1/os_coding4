#include <iostream>
#include <deque>
#include "page_controller.cpp"
using namespace std;


void parse_input(int argc, char* argv[], int& max_frames, deque<int>& page_string){

    if(argc==1){
        cout << "Using example values: \n\n";

        page_string = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
        max_frames = 4;
        return;
    }

    // debug
    cout << "\n" << argv[1] << "\n";

    if(argv[1] == string("-h")){
        // print help and exit
        cout << "This program simulates page replacement algorithms.\n\n"
        << "usage: main.exe [max number of frames] [page list]\n"
        << "\t<page list>: a space spearated list of integers.\n"
        << "\n\n passing no arguments runs an example data set.\n";

        exit(0);
    }

    max_frames = stoi(argv[1]);

    for(int i = 2; i < argc; i++){
        try
        {
            page_string.push_back(stoi(argv[i]));
        }
        catch(const std::exception& e)
        {
            cout << "Unsupported input in arguments. Please provide a space separated list of integers.";
            exit(1);
        }
    }
}



int main(int argc, char* argv[]){
    /*Entry point for program*/

    deque<int> page_string;
    int max_frames;

    parse_input(argc, argv, max_frames, page_string);

    // FIFO algorithm
    cout << "For FIFO algorithm: " << endl;
    fifo_controller fifo = fifo_controller(max_frames);
    int step_count = 1;
    for(auto& i: page_string){
        cout << "\tStep " << step_count++ << ": ";
        fifo.reference(i);
        cout << endl;
    }
    cout << "\tTotal Faults for FIFO: [" << fifo.get_total_faults() << "]\n\n";
    
    
    // LRU algorithm
    cout << "For LRU algorithm: " << endl;
    lru_controller lru = lru_controller(max_frames);
    step_count = 1;
    for(auto& i: page_string){
        cout << "\tStep " << step_count++ << ": ";
        lru.reference(i);
        cout << endl;
    }
    cout << "\tTotal Faults for LRU: [" << lru.get_total_faults() << "]\n\n";

    // optimal algorithm
    // auto temp_string = page_string;
    cout << "For optimal algorithm: " << endl;
    opt_controller opt = opt_controller(max_frames);
    step_count = 1;
    for(auto i = page_string.begin(); i < page_string.end(); i++){
        cout << "\tStep " << step_count++ << ": ";
        opt.reference(deque<int>(i, page_string.end()));
        cout << endl;
    }
    cout << "\tTotal Faults for optimal algorithm: [" << opt.get_total_faults() << "]\n\n";

    return 0;
}
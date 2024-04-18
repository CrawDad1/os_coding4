#include <iostream>
#include <deque>

// Test inclusions
#include "fifo.cpp"
#include "lru.cpp"
#include "opt.cpp"

using namespace std;
int main(){
    /*Entry point for program*/

    // inputs
    // Page reference string: 1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5
    // Number of frames: 4
    deque<int> page_string = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int max_frames = 4;

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
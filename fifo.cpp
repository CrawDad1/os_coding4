#include <iostream>
#include <deque>
using namespace std;

class fifo_controller{
    /*class for implementing fifo page replacement algorithm*/
    deque<int> page_table;
    int max_pages;
    int total_faults;

    public:
    fifo_controller(int max):max_pages{max}, total_faults{0}, page_table{deque<int>()}{
    };

    int get_total_faults(){
        return this->total_faults;
    }
    
    void print_page_table(){
        cout << "{";
        for(auto i = this->page_table.begin(); i < this->page_table.end() - 1; i++){
            cout << *i << ", ";
        }
        cout << this->page_table.back() << "}";
    }

    void print_status(bool page_hit, int page_number){
        string fault_string = (page_hit)?"Page hit ":"Page Fault ";

        //  Page fault (1) - Page Table: {1}, Frames: [1], Faults: 1
        cout << fault_string << "(" << page_number << ") - " << "Page Table: ";
        print_page_table();
        cout << ", " << "Frames: [" << this->page_table.size()
        << "], Faults: " << this->total_faults;

        return;
    }
    
    void reference(int page_number){
        /*checks page_table for requested page and handles miss*/
        
        for(auto& i: page_table){
            if (i == page_number){
                print_status(true, page_number);
                return;
            }
        }

        this->total_faults++;
        if (this->page_table.size() < this->max_pages){
            // add new frame
            this->page_table.push_back(page_number);
        }
        else{
            // perform fifo shift
            // this->page_table.erase(this->page_table.begin());
            this->page_table.pop_front();
            this->page_table.push_back(page_number);
        }

        print_status(false, page_number);
        return;
    }
};
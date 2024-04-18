#include <iostream>
#include <deque>
using namespace std;

class lru_controller{
    /*class for implementing lru page replacement algorithm*/
    deque<int> page_table;
    int max_pages;
    int total_faults;

    public:
    lru_controller(int max):max_pages{max}, total_faults{0}, page_table{deque<int>()}{
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
        
        for(auto i = this->page_table.begin(); i < this->page_table.end(); i++){
            if (*i == page_number){
                // page hit
                // move to first frame
                this->page_table.push_front(*i);
                this->page_table.erase(i);

                print_status(true, page_number);
                return;
            }
        }

        this->total_faults++;
        if (this->page_table.size() < this->max_pages){
            // add new frame
            this->page_table.push_front(page_number);
        }
        else{
            // perform lru shift
            this->page_table.pop_back();
            this->page_table.push_front(page_number);
        }

        print_status(false, page_number);
        return;
    }
};
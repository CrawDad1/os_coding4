#include <iostream>
#include <deque>
using namespace std;

class page_controller{
    /*Base class for page_controller algorithmss*/
    protected:
    deque<int> page_table;
    int max_pages;
    int total_faults;

    public:
    page_controller(int max):max_pages{max}, total_faults{0}, page_table{deque<int>()}{
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
    
    virtual void reference(int page_number){};
};

class fifo_controller: public page_controller{
    /*class for implementing fifo page replacement algorithm*/

    public:
    fifo_controller(int max):page_controller(max){};
    
    void reference(int page_number) override{
        /*checks page_table for requested page and handles miss*/
        
        for(auto& i: this->page_table){
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

class lru_controller: public page_controller{
    /*class for implementing lru page replacement algorithm*/
    public:
    lru_controller(int max):page_controller(max){};

    void reference(int page_number) override{
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

class opt_controller: public page_controller{
    /*class for implementing opt page replacement algorithm*/
    public:
    opt_controller(int max):page_controller(max){};

    void delete_furthest(const deque<int>& page_string){
        int curr_dist = -1;
        int max_dist = -1;
        auto max_it = this->page_table.begin();

        for(auto table_it = this->page_table.begin(); table_it < this->page_table.end(); table_it++){
            for(auto string_it = page_string.begin(); string_it <= page_string.end(); string_it++){
                if (string_it == page_string.end()){
                    // no match in remaining pages
                    this->page_table.erase(table_it);
                    return;
                }
                if (*table_it == *string_it){
                    curr_dist = string_it - page_string.begin();
                    if(curr_dist > max_dist){
                        max_dist = curr_dist;
                        max_it = table_it;
                    }
                    break; // only need the first match
                }
            }
        } 

        // delete the location in the page tblae with the longest distance to next page hit
        this->page_table.erase(max_it);
    }

    void refrence(int page_number){
        cout << "This algorithm does not support single number reference.\n";
    }
    
    void reference(const deque<int>& page_string){
        /*checks page_table for requested page and handles miss
          since this implementation needs to 'see the future',
           the remaining page string is passed*/

        int page_number = page_string.front();
        
        for(auto i = this->page_table.begin(); i < this->page_table.end(); i++){
            if (*i == page_number){
                // page hit
                // do nothing
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
            // perform opt shift
            // find and delete the page that won't be used for the longest amount of time
            delete_furthest(page_string);
            this->page_table.push_back(page_number);
        }

        print_status(false, page_number);
        return;
    }
};

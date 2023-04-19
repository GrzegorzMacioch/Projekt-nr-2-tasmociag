#include <iostream>
#include <future>
#include <deque>
#include <ctime>
#include <stack>
#include <vector>

std::deque<float> tape_construction(int packages_number){
    std::deque<float> tape;
    float testsum;
    std::srand(std::time(nullptr));
    for (int i = 0; i < packages_number; i++){
        float random_number = 0;
        random_number = (std::rand() % 150)/10.0 + 0.1;
        tape.push_back(random_number);
        testsum += random_number;
    }
    std::cout<< "Testsum " << testsum <<std::endl;
    return tape;
}

void vehicles_loading (std::deque<float> working_tape, std::vector<std::stack<float>> vehicles, std::vector<float> max_capacity, std::vector<float> current_capacity){
    std::srand(std::time(nullptr));
    float buff2 = 0;
    while(!working_tape.empty())
    {
    float sum = 0, max_weight = 0, buff = 0;
    max_weight = (std::rand() % 100)/10.0 + 30.1;
    std::stack<float> capacity;
    std::cout<<"max_weight "<< max_weight << std::endl;
        while(sum <= max_weight && !working_tape.empty())
        {
        if(buff2 != 0){
            capacity.push(buff2);
            sum += buff2;
        }
        buff = working_tape.front();
        capacity.push(buff);
        working_tape.pop_front();
        sum += buff;
        buff2 = 0;
        std::cout<<"suma "<< sum <<std::endl;
        }
    if(sum > max_weight){
    sum = sum - buff;
    capacity.pop();
    }
    std::cout<<"suma calkowita "<< sum <<std::endl;
    vehicles.push_back(capacity);
    max_capacity.push_back(max_weight);
    current_capacity.push_back(sum);
    buff2 = buff;
    }
    for (int i=0; i < vehicles.size(); i++)
    {
            std::cout<<"Ciezarkowka nr : "<< i+1 <<std::endl;
            std::cout<<"Maksymalna pojemnosc : "<< max_capacity[i] <<std::endl;
            std::cout<<"Aktualna pojemnosc : "<< current_capacity[i] <<std::endl;
     }
}

int main(){
    int packages_number = 0;
    std::srand(std::time(nullptr));
    std::vector<std::stack<float>> vehicles;
    std::vector<float> max_capacity;
    std::vector<float> current_capacity;

    while (packages_number != 7)
    {
    std::cout<<"Wpisz liczbe paczek"<<std::endl;
    std::cin >> packages_number;
        if(packages_number > 0)
        {
        std::future<std::deque<float>> ready_tape = std::async(tape_construction, packages_number);
        auto working_tape = ready_tape.get();
         for (int i=0; i < packages_number; i++){
            std::cout << "Waga paczki nr"<< i+1 << " " << working_tape[i] <<std::endl ;
            }
            vehicles_loading (working_tape, vehicles, max_capacity, current_capacity);
        }
        else{
            std::cout<<"liczba paczek musi byc nie ujemna"<<std::endl;
        }
    }
    return 0;
}
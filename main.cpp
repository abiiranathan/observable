#include "observable.h"

int main() {
    DataStore<int> dataStore;

    // Subscribe to the observable using a lambda expression
    dataStore.getObservable().subscribe([](const int &value) {
        // Handle the emitted value
        std::cout << "Data changed: " << value << std::endl;


    });

    // Update the value in the data store
    dataStore.setValue(42);
    dataStore.setValue(600);
    return 0;
}

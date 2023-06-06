# Observable

Observable is a C++ library that provides a simple implementation of an observable pattern, allowing you to subscribe to and receive notifications when a value changes.

## Installation

Clone the repository and include the `observable.h` header in your project.

## Install globally

```bash
mkdir build && cd build
cmake ..
sudo cmake --build . --target install
```

## Usage

### Creating an Observable

To create an observable for a specific type, instantiate the `Observable` class:

```cpp
#include "observable.h"

Observable<int> observable;
```

## Subscribing to Observables

To subscribe to an observable and receive notifications when the value changes, use the subscribe method:

```cpp
observable.subscribe([](const int& value) {
    // Handle the value change
});
```

## Emitting Value Changes

To emit a value change and notify all subscribers, use the next method:

```cpp
observable.next(42);
```

### Creating a DataStore

The DataStore class provides a convenient way to store a value and associate it with an observable:

```cpp
DataStore<int> dataStore;
```

### Setting and Getting Values

To set a value in the data store and notify subscribers, use the setValue method:

```cpp
dataStore.setValue(42);
int value = dataStore.getValue();
```

### Getting the Observable

To access the associated observable for a data store, use the getObservable method:

```cpp
Observable<int>& observable = dataStore.getObservable();

```

# QSettingsWrapper

QSettingsWrapper is a class that provides a convenient wrapper around the Qt QSettings class. It simplifies working with application preferences and emits signals when preference values are changed.

## Usage

```cpp
#include <QCoreApplication>
#include <QDebug>
#include "observable.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QSettingsWrapper settingsWrapper;

    // Set a preference value
    settingsWrapper.setValue("name", "John Doe");

    // Retrieve the preference value
    QVariant value = settingsWrapper.getValue("name");
    qDebug() << "Name: " << value.toString();

    // Connect to the preferenceChanged signal
    QObject::connect(&settingsWrapper, &QSettingsWrapper::preferenceChanged, [](const QString& key, const QVariant& value) {
        qDebug() << "Preference changed: " << key << " = " << value;
    });


    // Update the preference value
    settingsWrapper.setValue("name", "Jane Smith");

    return app.exec();
}
```

## Example of using DataStore

Here's a complete example demonstrating the usage of the Observable library:

```cpp
#include "observable.h"
#include <iostream>

int main() {
    DataStore<int> dataStore;

    // Subscribe to the observable
    dataStore.getObservable().subscribe([](const int& value) {
        // Handle the emitted value. Do not update value inside here
        // to avoid infinite loops.
        std::cout << "Data changed: " << value << std::endl;
    });


    // Update the value in the data store
    dataStore.setValue(42);
    dataStore.setValue(600);
    return 0;
}
```

### Linking

If installed globally, link with your cmake project as below:

```cpp
#include <observable.h>

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
```

```cmake
cmake_minimum_required(VERSION 3.2)

project(hello LANGUAGES CXX)

find_package(observable REQUIRED)

qt_add_executable(app main.cpp)

target_link_libraries(app PRIVATE observable::observable)
```

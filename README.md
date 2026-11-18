## ДЗ 2

### Сборка и запуск

```sh
g++ -std=c++20 *.cpp -o main
./main
```

### [Команды](main.cpp#L94)

id - уникальный инвентарный номер, строка\
name - имя (без пробелов), строка; если в имени есть broken в любом виде, то устройство считается сломанным и не проходит техосмотр\
energy - расход энергии в кВт*ч за сутки неотрицательное число, дробная часть через точку\
score - оценка простоты использования от 1 до 10 (целое число)\
capacity - грузоподъёмность, положительное число, дробная часть через точку

| команда | что делает |
| --- | --- |
| `add scooter id name energy score` | добавить электросамокат |
| `add bike id name score` | добавить велосипед |
| `add ebike id name energy score` | добавить электровелосипед |
| `add helmet id name` | добавить шлем |
| `add dock id name energy` | добавить зарядную станцию |
| `add cargo id name energy score capacity` | добавить мопед с местом для груза (как у курьеров) |
| `list` | показать все объекты в порядке инвентарных номеров |
| `novice` | показать транспорт с простотой >= 6 |
| `energy` | показать суммарный суточный расход энергии всех устройств|
| `focus id` | выставить объект на витрину |
| `show_focus` | показать объект на витрине |
| `remove id` | удалить объект из парка |
| `max_energy` | показать объект с наибольшим расходом энергии |
| `report` | показать число объектов и суммарный суточный расход энергии |
| `quit` | выйти из программы |

### Примеры

Ввод

```
add scooter S-1 Scooter 2.5 8
add bike B-1 Bike 4
add ebike E-1 Ebike 1.5 7
add helmet H-1 Helmet
add dock D-1 Dock 10.0
add cargo C-1 Cargo 3.5 5 20
add scooter S-2 BrokenScooter 1.0 9
list
novice
energy
max_energy
focus S-1
show_focus
remove S-1
show_focus
report
quit
```

Вывод

```
error: inspection rejected
B-1 Bike
C-1 Cargo
D-1 Dock
E-1 Ebike
H-1 Helmet
S-1 Scooter
S-1 Scooter
E-1 Ebike
17.5
D-1 Dock 10.0
S-1 Scooter
expired
count: 5
energy: 15.0
```

### Схема наследования

- [EnergyConsumer](Inventory.h#L17)
- [InventoryItem](Inventory.h#L7)
  - [Helmet](Things.h#L6)
  - [DockStation](Things.h#L19) (+ EnergyConsumer)
  - [Transport](Transport.h#L8)
    - [ElectricScooter](Transport.h#L24) (+ EnergyConsumer)
    - [Bicycle](Transport.h#L35)
      - [ElectricBicycle](Transport.h#L42) (+ EnergyConsumer)
        - [ElectricCargoBicycle](Transport.h#L52)
- std::runtime_error
  - [FleetError](Errors.h#L7)
    - [InspectionRejected](Errors.h#L13)
    - [InvalidArgument](Errors.h#L18)

(где "+ EnergyConsumer" означает множественное наследование, в том числе и от этого класса)\
все наследование public

### Умные указатели
- [unique ptr](Fleet.cpp#L12) владеет объектом до приема в парк, таким образом если при проверке объекта будет ошибка, то объект удалится вместе с указателем
- [shared ptr](Fleet.h#L30) хранит объекты в парке
- [weak ptr](Fleet.h#L31) используется для отображения "транспорта дня", так, если транспорт удален, то это можно узнать через lock и вернуть expired

### Исключения
- [FleetError](Errors.h#L7) - базовый класс исключений
- [InspectionRejected](Errors.h#L13) - ошибка при техосмотре
- [InvalidArgument](Errors.h#L18) - любая ошибка ввода команды (есть кастомный текст ошибки)

### Шаблон
используется шаблон [`Registry<T>`](Registry.h) для добавления объектов в парк и их хранения там

### Перегрузка операторов <<, <, ==
- [<<](Inventory.cpp#L5) - печать информации об объекте
- [<](Inventory.cpp#L10) - сравнение инвентарных номеров
- [==](Inventory.cpp#L14) - сравнение инвентарных номеров для проверки на дубликаты

### "Креативная часть"
1) свой вид транспорта [ElectricCargoBicycle](Transport.h#L52) (мопед как у курьеров)
2) доп команда [max_energy](Fleet.cpp#L91) - показывает устройство с самым большим суточным потреблением энергии и empty если устройств, потребляющих электричество нет
3) доп команда [report](main.cpp#L138) - отображает количество объектов в парке и суммарное суточное энергопотребление

### Использование ИИ
объяснил что такое умные указатели, зачем нужны, как работают и где их стоит применить + помог с оформлением таблицы команд в readme + мелкие общие подсказки по языку\
ии код не писал, архитектуру не придумывал
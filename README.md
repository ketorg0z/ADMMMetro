
## Курсовая работа по дисциплине Алгоритмы Дискретной математики по теме "Задача о кратчайшем пути"  
### Савольский Л. А., Измайлов Л. С., Устинов А. М., Гаврин И. А.  
--- 
# Поиск кратчайших путей в Московском метрополитене #
  
## Постановка задачи  
Требуется найти кратчайший путь от одной станции метро до другой

* Имеется фрагмент московского метрополитена внутри кольцевой ветки (включая ее)
*  Для каждого перехода и проезда между станциями задано время (вес)

## Граф
Граф станций метро был задан как ассоциативный массив с номером станции в ключе и массивом пар в значении - в паре первым элементом является смежная станция, вторым - время проезда до неё.  

## Алгоритмы
Для поиска были выбраны несколько алгоритмов нахождения кратчайшего пути:

* Алгоритм Дейкстры
    * Сложность - O(N<sup>2</sup>)
* 1-k BFS  
    * Сложность - O(N*K + M)
# Код

## Задание графа:

``` c++
//Инициализация списка станций
const std::vector<std::string> stations = { "Okhotniy ryad",  "Teatralnaya", "Ploshyad revolutsii", "Tverskaya",
                                     ...
                                     "Belorusskaya 5",  "Mendeleevskaya",  "Novoslobodskaya",  "Prospekt mira 6",
                                     "Prospekt mira 5" };

//Инициализация графа, номера станций - индексы в списке станций
std::map<int, std::vector<std::pair<int, int>>> metro = {
  {0, {{1, 3}, {2, 3}, {7, 1}, {16, 1}}},
  {1, {{0, 3}, {2, 3}, {3, 1}, {22, 2}}},
  {2, {{0, 3}, {1, 3}, {14, 2}, {32, 2}}},
  {3, {{4, 3}, {5, 3}, {1, 1}, {27, 1}}},
  ...
  {56, {{55, 3}, {54, 2}, {31, 2}}}
};
```

<details>

  <summary>Список станций с индексами</summary>
  <p>
  <table>
  <tr>
  <td>
  Список станций:  <br>
  Okhotniy ryad	0  <br>
  Teatralnaya	1  <br>
  Ploshyad revolutsii	2 <br> 
  Tverskaya	3<br>
  Pushkinskaya	4<br>
  Chekhovskaya	5<br>
  Kuznetskiy most	6<br>
  Lubyanka	7<br>
  Chistye prudy	8<br>
  Turgenevskaya	9<br>
  Sretenskiy bulvar	10<br>
  Trubnaya	11<br>
  Tsvetnoy bulvar	12<br>
  Aleksandrovskiy sad	13<br>
  Arbatskaya 3	14<br>
  Borovitskaya	15<br>
  Biblioteka imeni Lenina	16<br>
  Arbatskaya 4	17<br>
  Kitay-gorod 6	18<br>
  Kitay-gorod 7	19<br>
  Tretyakovskaya 6	20<br>
  Tretyakovskaya 8	21<br>
  Novokuznetskaya	22<br>
  Polyanka	23<br>
  Kropotkinskaya	24<br>
  Smolenskaya 3	25<br>
  Smolenskaya 4	26<br>
  Mayakovskaya	27<br>
  Sukharevskaya	28<br>
  </td>
  <td>
  Krasnye vorota	29<br>
  Komsomolskaya 1	30<br>
  Komsomolskaya 5	31<br>
  Kurskaya 3	32<br>
  Chkalovskaya	33<br>
  Kurskaya 5	34<br>
  Marksistskaya	35<br>
  Taganskaya 7	36<br>
  Taganskaya 5	37<br>
  Paveletskaya 2	38<br>
  Paveletskaya 5	39<br>
  Serpuhovskaya	40<br>
  Dobryninskaya	41<br>
  Oktyabrskaya 6	42<br>
  Oktyabrskaya 5	43<br>
  Park kultury 1	44<br>
  Park kultury 5	45<br>
  Kievskaya 3	46<br>
  Kievskaya 4	47<br>
  Kievskaya 5	48<br>
  Barrikadnaya	49<br>
  Krasnopresnenskaya	50<br>
  Belorusskaya 2	51<br>
  Belorusskaya 5	52<br>
  Mendeleevskaya	53<br>
  Novoslobodskaya	54<br>
  Prospekt mira 6	55<br>
  Prospekt mira 5	56<br>
  </td>
  </tr>
  </table>
</p>
</details>


## Реализация Алгоритма Дейкстры

```c++
void Deykstry(int from, const int& to) {
  do {
    int min = 1000;
    int minst = 0;

    for (std::pair<int, int> st : metro[from]) {
      if (visited[st.first] == 0) {
        if (routes[st.first] > (routes[from] + st.second))   //Проверка оптимальности пути
          routes[st.first] = routes[from] + st.second;          //Запись нового пути в массив путей до каждой точки
      }
    }

    visited[from] = 1; //После постройки путей от рассматреваемой станции, помечаем её как пройденную

    for (int i = 0; i < visited.size(); ++i) { //Ищем следующую станцию из непосещённых станций с минимальным путём
      if (visited[i] == 0) {
        if (routes[i] < min) {
          min = routes[i];
          minst = i; //Найденная станция
        }
      }
    }

    from = minst; //Следующая цель
  } while (visited[to] != 1); //Цикл исполяется, пока мы не исследуем конечную точку
}
```

## Реализация 1-k BFS

```c++
void OneKBFS(const int& from, const int& to) {
  std::vector<std::queue<int>> atDist(4); //Создаём массив очередей станций, по увеличению пути
  atDist[0].push(from);  
  routes[from] = 0;
  int pos = 0, kol = 1; //pos - позиция, на которой рассматривается элемент в массиве очередей
                                       //kol - общее количество вершин во всех очередях
  routesVector[from] = -1;
  while (kol > 0 && visited[to] == 0) { //Исполняется, пока конечная вершина не исследована или пока не кончатся вершины в массиве очередей

    while (atDist[pos % 4].empty()) { //Выбираем длину пути, на котором исследуем новые вершины
      ++pos;
    }

    int u = atDist[pos % 4].front(); //Выбираем вершину
    atDist[pos % 4].pop();
    --kol;

    if (visited[u] == 0) {

      visited[u] = 1; //Помечаем как посещённую

      for (std::pair<int, int> station : metro[u]) { //Рассматриваем соседние с ней станции
        if (routes[station.first] > (routes[u] + station.second)) {

          routes[station.first] = routes[u] + station.second;
          routesVector[station.first] = u;

          atDist[routes[station.first] % 4].push(station.first); //Добавлям рассмотренные станции в очередь к исследованию

          ++kol;
        }
      }
    }
  }
}
```
## Пример работы программы

```shell
Okhotniy ryad	0
Teatralnaya	1 
...
Prospekt mira 6	55
Prospekt mira 5	56

Enter 'from' station index and 'to' station index below:
43 4

Deykstry

From: Oktyabrskaya 5	To: Pushkinskaya
11 mins
Oktyabrskaya 5 0
Park kultury 5 1
Kievskaya 5 3
Krasnopresnenskaya 6
Barrikadnaya 9
Pushkinskaya 11

1-k BFS

From: Oktyabrskaya 5	To: Pushkinskaya
11 mins
Oktyabrskaya 5 0
Park kultury 5 1
Kievskaya 5 3
Krasnopresnenskaya 6
Barrikadnaya 9
Pushkinskaya 11

```

## Эффективность решений

С помощью тестирования была найдена средняя скорость работы алгоритмов.  
Мы провели 1000 тестов нахождения пути от каждой станции до каждой станции для минимизации погрешностей.  
Результат: Алгоритм Дейкстры на 50-60% медленнее 1-k BFS в абсолютном большинстве случаев.

Пример средней скорости поиска:  
* Алгоритм Дейкстры - 0.000003845 секунды (3,845 микросекунды)  
* 1-k BFS - 0.000002094 секунды (2,094 микросекунды)
* Разница ~54.46%

Тест
```c++
  int durD = 0;
  int durB = 0;
  for (int k = 0; k < 1000; ++k) {
    int dur = 0;

    for (int i = 0; i < 57; ++i) {
      for (int j = 0; j < 57; ++j) {
        routes = std::vector<int>(stations.size(), 1000);
        visited = std::vector<int>(stations.size(), 0);

        auto start = std::chrono::high_resolution_clock::now();
        OneKBFS(i, j);  
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        dur += int(duration.count());
      }
    }

    dur /= (57 * 57);
    durB += dur;
    

    dur = 0;
    for (int i = 0; i < 57; ++i) {
      for (int j = 0; j < 57; ++j) {
        routes = std::vector<int>(stations.size(), 1000);
        visited = std::vector<int>(stations.size(), 0);

        routes[i] = 0;
        auto start = std::chrono::high_resolution_clock::now();
        Deykstry(i, j);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        dur += int(duration.count());
      }
    }

    dur /= (57 * 57);

    durD += dur;
  }

  std::cout << std::endl << "Average wall time taken by 1-k BFS algrorithm:" << std::endl << durB/1000.0 << " microseconds" << std::endl;
  std::cout << std::endl << "Average wall time taken Deykstra algrorithm:" << std::endl << durD/1000.0 << " microseconds" << std::endl;

```




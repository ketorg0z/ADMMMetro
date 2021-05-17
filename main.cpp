#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <stack>
#include <map>

//Инициализация списка станций
const std::vector<std::string> stations = { "Okhotniy ryad",  "Teatralnaya", "Ploshyad revolutsii", "Tverskaya",
                                     "Pushkinskaya", "Chekhovskaya", "Kuznetskiy most", "Lubyanka",  "Chistye prudy",
                                     "Turgenevskaya",  "Sretenskiy bulvar",  "Trubnaya",  "Tsvetnoy bulvar",  "Aleksandrovskiy sad",
                                     "Arbatskaya 3",  "Borovitskaya",  "Biblioteka imeni Lenina",  "Arbatskaya 4",
                                     "Kitay-gorod 6",  "Kitay-gorod 7",  "Tretyakovskaya 6",  "Tretyakovskaya 8",
                                     "Novokuznetskaya",  "Polyanka",  "Kropotkinskaya",  "Smolenskaya 3",
                                     "Smolenskaya 4",  "Mayakovskaya",  "Sukharevskaya",  "Krasnye vorota",
                                     "Komsomolskaya 1",  "Komsomolskaya 5",  "Kurskaya 3",  "Chkalovskaya",
                                     "Kurskaya 5",  "Marksistskaya",  "Taganskaya 7",  "Taganskaya 5",  "Paveletskaya 2",
                                     "Paveletskaya 5",  "Serpuhovskaya",  "Dobryninskaya",  "Oktyabrskaya 6",
                                     "Oktyabrskaya 5",  "Park kultury 1",  "Park kultury 5",  "Kievskaya 3",  "Kievskaya 4",
                                     "Kievskaya 5",  "Barrikadnaya",  "Krasnopresnenskaya",  "Belorusskaya 2",
                                     "Belorusskaya 5",  "Mendeleevskaya",  "Novoslobodskaya",  "Prospekt mira 6",
                                     "Prospekt mira 5" };

//Инициализация графа, номера станций - индексы в списке станций
std::map<int, std::vector<std::pair<int, int>>> metro = {
  {0, {{1, 3}, {2, 3}, {7, 1}, {16, 1}}},
  {1, {{0, 3}, {2, 3}, {3, 1}, {22, 2}}},
  {2, {{0, 3}, {1, 3}, {14, 2}, {32, 2}}},
  {3, {{4, 3}, {5, 3}, {1, 1}, {27, 1}}},
  {4, {{3, 3}, {5, 3}, {6, 2}, {49, 2}}},
  {5, {{3, 3}, {5, 3}, {12, 1}, {15, 2}}},
  {6, {{7, 3}, {4, 2}, {19, 1}}},
  {7, {{6, 3}, {0, 1}, {8, 2}}},
  {8, {{9, 3}, {10, 3}, {29, 1}, {7, 1}}},
  {9, {{8, 3}, {10, 3}, {28, 1}, {18, 1}}},
  {10, {{9, 3}, {8, 3}, {33, 2}, {11, 2}}},
  {11, {{12, 3}, {10, 2}}},
  {12, {{11, 3}, {53, 2}, {5, 1}}},
  {13, {{14, 3}, {15, 3}, {16, 3}, {17, 1}}},
  {14, {{13, 3}, {15, 3}, {16, 3}, {25, 2}, {2, 2}}},
  {15, {{13, 3}, {14, 3}, {16, 3}, {5, 2}, {23, 2}}},
  {16, {{13, 3}, {15, 3}, {14, 3}, {0, 1}, {24, 1}}},
  {17, {{13, 1}, {26, 2}}},
  {18, {{19, 3}, {9, 1}, {20, 2}}},
  {19, {{18, 3}, {36, 3}, {6, 1}}},
  {20, {{22, 3}, {21, 3}, {18, 2}, {42, 2}}},
  {21, {{20, 3}, {22, 3}, {35, 2}}},
  {22, {{20, 3}, {21, 3}, {38, 2}, {1, 2}}},
  {23, {{15, 2}, {40, 2}}},
  {24, {{16, 1}, {44, 2}}},
  {25, {{46, 1}, {14, 2}}},
  {26, {{47, 2}, {17, 2}}},
  {27, {{3, 1}, {51, 1}}},
  {28, {{9, 1}, {55, 1}}},
  {29, {{8,  1}, {30, 1}}},
  {30, {{31, 3}, {29, 1}}},
  {31, {{30, 3}, {56, 2}, {34, 3}}},
  {32, {{2, 2}, {34, 3}, {33, 3}}},
  {33, {{34, 3}, {32, 3}, {10, 2}}},
  {34, {{32, 3}, {33, 3}, {31, 3}, {37, 2}}},
  {35, {{37, 3}, {36, 3}, {21, 2}}},
  {36, {{37, 3}, {35, 3}, {19, 3}}},
  {37, {{36, 3}, {35, 3}, {34, 2}, {39, 1}}},
  {38, {{22, 2}, {39, 3}}},
  {39, {{38, 3}, {37, 1}, {41, 1}}},
  {40, {{41, 3}, {23, 2}}},
  {41, {{40, 3}, {39, 1}, {43, 1}}},
  {42, {{43, 3}, {20, 2}}},
  {43, {{42, 3}, {41, 1}, {45, 1}}},
  {44, {{45, 3}, {24, 2}}},
  {45, {{44, 3}, {43, 1}, {48, 2}}},
  {46, {{47, 3}, {48, 3}, {25, 1}}},
  {47, {{46, 3}, {48, 3}, {26, 2}}},
  {48, {{46, 3}, {47, 3}, {45, 2}, {50, 3}}},
  {49, {{50, 3}, {4, 2}}},
  {50, {{49, 3}, {48, 3}, {52, 2}}},
  {51, {{52, 3}, {27, 1}}},
  {52, {{51, 3}, {50, 2}, {54, 2}}},
  {53, {{54, 3}, {12, 2}}},
  {54, {{53, 3}, {52, 2}, {56, 2}}},
  {55, {{56, 3}, {28, 1}}},
  {56, {{55, 3}, {54, 2}, {31, 2}}}
};

std::vector<int> routes(stations.size(), 1000);  //Массив кратчайших путей до каждой точки, изначально - 1000
std::vector<int> visited(stations.size(), 0);         //Массив исследованных вершин, изначально заполнен нулями
std::vector<int> routesVector(stations.size()); //Массив пройденных станций для восстановления пути

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

std::vector<int> Output(const int& from, int to) {
  std::vector<int> visited_from(stations.size(), -1);
  visited_from[0] = to;
  int weight = routes[to];
  int k = 1;
  while (to != from)
  {
    for (int i = 0; i < stations.size(); ++i)
      for (std::pair<int, int> station : metro[i]) {
        if (station.first == to)
        {
          int temp = weight - station.second;
          if (temp == routes[i]) {
            weight = temp;
            to = i;
            visited_from[k] = i;
            k++;
          }
        }
      }
  }
  return visited_from;
}

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

int main() {

  for (int i = 0; i < stations.size(); ++i) {  //Вывод станций с индексами
    std::cout << stations[i] << '\t' << i << std::endl;
  }


  int from, to;   //Объявление переменных для индексов станции откуда едем и куда едем

  std::cout << std::endl << "Enter 'from' station index and 'to' station index below:" << std::endl;

  std::cin >> from >> to;  //Ввод

  //Алгоритм Дейкстры

  std::cout << std::endl << "Deykstry" << std::endl << std::endl;
  {
    routes[from] = 0;  //Задаём минимальный вес (время) начальной вершине, так как у нас нет отрицательных весов, мы берём 0

    Deykstry(from, to);  //Запускаем поиск кратчайших путей, внутри алгоритма самого позже впишу все пояснения тоже

    //Вывод
    std::cout << "From: " << stations[from] << "\tTo: " << stations[to] << std::endl;
    std::cout << routes[to] << " mins" << std::endl;

    std::vector<int> output = Output(from, to);  //Простраиваем путь от конца и до начала, чтобы вывести цепочку станций

    //Выводим станции с конца их появления в векторе, потому что нам удобнее смотреть как мы едем с начала
    for (int i = output.size() - 1; i >= 0; --i) {
      if (output[i] != -1) std::cout << stations[output[i]] << " " << routes[output[i]] << std::endl;
    }

  }

  //Сбрасываем до состояния по умолчанию
  routes = std::vector<int>(stations.size(), 1000);
  visited = std::vector<int>(stations.size(), 0);

  std::cout << std::endl << "1-k BFS" << std::endl << std::endl;

  //BFS
  {
    OneKBFS(from, to);  //Запускаем поиск кратчайших путей

    //Выводим
    std::cout << "From: " << stations[from] << "\tTo: " << stations[to] << std::endl; 

    std::cout << routes[to] << " mins" << std::endl;

    std::vector<int> path;
    for (int v = to; v != -1; v = routesVector[v])
      path.push_back(v);
    std::reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i)
      std::cout << stations[path[i]] << " " << routes[path[i]] << std::endl;
  }

  return 0;
}


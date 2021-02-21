#include <iostream>
#include <vector>

int main() {
    std::vector <int> v;
    int c = 1;
    v.push_back(1);
    std::cout << "Номер шага, Изменение емкости вектора в:" << std::endl;
    for (int i=1; i < 10; i++)
    {
      v.push_back(1);
      std::cout << i << " : ";
      std::cout <<  v.capacity()/c << std::endl;
      c = v.capacity();
    }
// В 2 раза увеличивается емкость вектора при нехватке памяти


    std::vector <int> v1;
    v1.reserve(5);
    int c1 = v1.capacity();
    std::cout<< std::endl<<"Заданный начальный размер: " << c1 << std::endl;
    std::cout << "Номер шага, Изменение емкости вектора в:" << std::endl;
    for (int i=1; i < 10; i++)
    {
      v1.push_back(1);
      if ( c1 != v1.capacity() )
      {
      std::cout << i << " : ";
      std::cout <<  v1.capacity()<< ' '<<c1 << std::endl;
      c1 = v1.capacity();
      }

    }
std::cout << std::endl << "Максимально возможный размер вектора"<< std::endl;
    std::vector <int> v2;
    int max_size = v2.max_size();
    std::cout << max_size << std::endl;
    v2.reserve(max_size+1);

	return 0;
}

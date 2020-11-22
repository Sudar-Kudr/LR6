/*  скопируйте, но нужно вставить кол-во студента у нас в списке снизу-3 (EGOR, ALEX,VLAD)
 
EGOR
lit 5
rus 5
math 5
geogr 4
ALEX
lit 5
rus 4
math 2
geogr 3
VLAD
lit 4
rus 2
math 2
geogr 5
 
 как вводить-см в конце
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

struct Disciplina{
    std::string name;
    int mark;
};

struct Student{
    std::string FIO;
    Disciplina dis[4];
};

std::ostream& operator<<(std::ostream& os, Disciplina& dis){
    os << dis.name << " " << dis.mark;
    return os;
}

std::ostream& operator<<(std::ostream& os, Student& stud){
    os << stud.FIO << " ";
    for (int i = 0; i < 4; i++) {
        os << stud.dis[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Disciplina& dis){
    is >> dis.name >> dis.mark;
    return is;
}

std::istream& operator>>(std::istream& is, Student& stud){
    is >> stud.FIO;
    for (int i = 0; i < 4; i++) {
        is >> stud.dis[i];
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, std::vector<Student>& studen){
    for (int i = 0; i < studen.size(); i++) {
        os << studen[i] << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, std::vector<Student>& studen){
    for (int i = 0; i < studen.size(); i++) {
        is >> studen[i];
    }
    return is;
}


int main()
{
    std::vector<Student> students;
    std::cout << "Введите количество студентов\n";
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        Student st;
        std::cin >> st;
        students.push_back(st);
    }
    
    
    //запись в файл
    std::ofstream file("students.txt");
    file << students;
    file.close();
 
    std::cout << "C файла\n";
    std::ifstream fromfile("students.txt");
    if(!fromfile){
        std::cout << "File not found!" << std::endl;
        return 1;
    }
    Student s;
    std::vector<Student> fromFile;
    while (fromfile >> s) {
        fromFile.push_back(s);
    }
    for (int i=0; i < fromFile.size(); i++)
        std::cout << fromFile[i] << std::endl;
    file.close();
    
    std::cout << "Cортировка\n";
    std::sort(fromFile.begin(), fromFile.end(), [](Student s1, Student s2){return s1.FIO < s2.FIO;});
    for (int i=0; i < fromFile.size(); i++)
        std::cout << fromFile[i] << std::endl;

    std::string nameDis;
    std::cout << "Введите дисциплину которую хотите проверить на неуд.\n";
    std::cin >> nameDis;
    std::cout << "Кол-во студеннтов, получивших неуд: ";
    long res = std::count_if(fromFile.begin(), fromFile.end(), [nameDis](Student s){
        for (int i = 0; i < 4; i++) {
            if(s.dis[i].mark < 3 && s.dis[i].name == nameDis)
                return true;
        }
        return false;
    });
    std::cout << res << std::endl;
    
    std::vector<Student> badstudents;
    for (int i = 0; i < fromFile.size(); i++) {
        for (int j = 0; j < 4; j++)
            if(fromFile[i].dis[j].mark < 3 && fromFile[i].dis[j].name == nameDis)
                badstudents.push_back(students[i]);
    }
    for (int i=0; i < badstudents.size(); i++)
        std::cout << badstudents[i] << std::endl;
    
    return 0;
}

/*
 Введите количество студентов
 3
 EGOR
 lit 5
 rus 5
 math 5
 geogr 4
 ALEX
 lit 5
 rus 4
 math 2
 geogr 3
 VLAD
 lit 4
 rus 2
 math 2
 geogr 5
 C файла
 EGOR lit 5 rus 5 math 5 geogr 4
 ALEX lit 5 rus 4 math 2 geogr 3
 VLAD lit 4 rus 2 math 2 geogr 5
 Cортировка
 ALEX lit 5 rus 4 math 2 geogr 3
 EGOR lit 5 rus 5 math 5 geogr 4
 VLAD lit 4 rus 2 math 2 geogr 5
 Введите дисциплину которую хотите проверить на неуд.
 math
 Кол-во студеннтов, получивших неуд:2
 EGOR lit 5 rus 5 math 5 geogr 4
 VLAD lit 4 rus 2 math 2 geogr 5
 Program ended with exit code: 0
 */

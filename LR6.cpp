/*  скопируйте, но нужно вставить кол-во студента у нас в списке снизу-3 (EGOROV, ALEXandrov,VLADov)
 
 Введите количество студентов
 3
 
 EGOROV Egor Egorovich
 lit 5
 rus ya 5
 math an 5
 geogr 2
 
 ALEXandrov alex alexovich
 lit 5
 rus ya 4
 math an 2
 geogr 3
 
 VLADov vlad dladych
 lit 4
 rus ya 3
 math an 2
 geogr 5

как вводить-см в конце
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

struct Disciplina{
    std::vector<std::string> name;
    int mark;
};

struct Student{
    std::string FIO[3];
    Disciplina dis[4];
};

std::ostream& operator<<(std::ostream& os, Disciplina& dis){
    for (int i=0; i<dis.name.size(); i++){
        os << dis.name[i] << " ";
    }
    os << dis.mark;
    return os;
}

std::ostream& operator<<(std::ostream& os, Student& stud){
    os << stud.FIO[0] << " " << stud.FIO[1] << " " << stud.FIO[2] << std::endl;
    for (int i = 0; i < 4; i++) {
        os << stud.dis[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Disciplina& dis){
    std::string name1;
        is >> name1;
    while (!(name1[0] > '1' && name1[0] < '6')) {
        dis.name.push_back(name1);
        is >> name1;
    }
    
    dis.mark = std::stoi(name1);
    
    return is;
}
std::istream& operator>>(std::istream& is, Student& stud){
    std::string namefio;
    std::cin >> namefio;
    std::string famfio;
    std::cin >> famfio;
    std::string otchfio;
    std::cin >> otchfio;
    stud.FIO[0] = namefio;
    stud.FIO[1] = famfio;
    stud.FIO[2] = otchfio;
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
    
    std::cout << "    Введите количество студентов\n";
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; i++) {
        std::cout << "    Введите студентa\n";
        Student st;
        std::cin >> st;
        students.push_back(st);
    }
    
    std::vector<Student> fromFile;
    bool key;
    std::cout << "    0 - text, 1 - binary" << std::endl;
    std::cin >> key;
    if(key == 0){
    //запись в файл
    std::ofstream file("students.txt");
    file << students;
    file.close();
 
    std::cout << "    C файла\n";
    std::ifstream fromfileS("students.txt");
    if(!fromfileS){
        std::cout << "File not found!" << std::endl;
        return 1;
    }
    Student s;
    
    std::string buf;
    int y = 0;
    while (fromfileS >> buf) {
        if (y < 3) {
            s.FIO[y] =buf;
            y++;
        }
        else {
            // предметы
            if (!(buf[0] > '1' && buf[0] < '6')) {
                s.dis[y-3].name.push_back(buf);
            }
            else {
                s.dis[y-3].mark = std::stoi(buf);
                y++;
            }
            if (y == 7) {
                fromFile.push_back(s);
                for (int g=0;g<4; g++) {
                    s.dis[g].name.clear();
                }
                y = 0;
            }
        }
    }
    for (int i=0; i<fromFile.size(); i++){
        for (int j=0; j<3; j++)
            std::cout << fromFile[i].FIO[j] <<"\n";
        for (int k=0; k<4; k++){
            for (int h=0; h<fromFile[i].dis[k].name.size(); h++){
                std::cout << fromFile[i].dis[k].name[h] <<" ";
            }
            std::cout<< fromFile[i].dis[k].mark <<"\n";
        }
    }
         fromfileS.close();
    }
    else{
        std::ofstream outputFile("students.bin", std::ios::binary);
        outputFile.write(reinterpret_cast<char*>(&students), sizeof(students));
        outputFile.close();
        
        std::ifstream inputFile("students.bin", std::ios::binary);
        inputFile.read(reinterpret_cast<char*>(&fromFile), sizeof(students));
        inputFile.close();
    }
    
    
    for (int i=0; i < fromFile.size(); i++)
        std::cout << fromFile[i] << std::endl;
   
    std::cout << "    Cортировка\n";
    std::sort(fromFile.begin(), fromFile.end(), [](Student s1, Student s2){
        if (s1.FIO[0] != s2.FIO[0])
            return s1.FIO[0] < s2.FIO[0];
        else if ( s1.FIO[0] == s2.FIO[0]) {
            if (s1.FIO[1] != s2.FIO[1])
                return s1.FIO[1] < s2.FIO[1];
            else if ( s1.FIO[1] == s2.FIO[1]){
                    return s1.FIO[2] < s2.FIO[2];
                }
        }return true;});
    
    for (int i=0; i < fromFile.size(); i++)
        std::cout << fromFile[i] << std::endl;

    std::string nameDis;
    std::cout << "    Введите дисциплину которую хотите проверить на неуд.\n";
    std::cin.ignore();
    getline(std::cin, nameDis);
    std::cout << "    Кол-во студеннтов, получивших неуд: ";
    long res = std::count_if(fromFile.begin(), fromFile.end(), [nameDis](Student s){
        for (int i = 0; i < 4; i++) {
            std::string nameD;
            std::vector<std::string> vecName = s.dis[i].name;
            for(int k = 0; k < vecName.size(); k++){
                nameD += vecName[k];
                if(k != vecName.size() - 1)
                    nameD += " ";
            }
            if(s.dis[i].mark < 3 && nameD == nameDis)
                return true;
        }
        return false;
    });
    std::cout << res << std::endl;

    std::vector<Student> badstudents;
    for (int i = 0; i < fromFile.size(); i++) {
        for (int j = 0; j < 4; j++){
            std::string nameD;
            std::vector<std::string> vecName = fromFile[i].dis[j].name;
            for(int k = 0; k < vecName.size(); k++){
                nameD += vecName[k];
                if(k != vecName.size() - 1)
                    nameD += " ";
            }
            if(fromFile[i].dis[j].mark < 3 && nameD == nameDis)
                badstudents.push_back(students[i]);
        }
    }
    for (int i=0; i < badstudents.size(); i++)
        std::cout << badstudents[i] << std::endl;
    
    return 0;
}
 
/*
 Введите количество студентов
 3
 EGOROV Egor Egorovich
 lit 5
 rus ya 5
 math an 5
 geogr 2
 ALEXandrov alex alexovich
 lit 5
 rus ya 4
 math an 2
 geogr 3
 VLADov vlad dladych
 lit 4
 rus ya 3
 math an 2
 geogr 5
 
 C файла
 EGOROV Egor Egorovich
 lit 5 rus 5 math 5 geogr 4
 ALEXandrov alex alexovich
 lit 5 rus 4 math 2 geogr 3
 VLADov vlad dladych
 lit 4 rus 2 math 2 geogr 5
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

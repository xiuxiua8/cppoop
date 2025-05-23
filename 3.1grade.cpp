/*
定义学生类：
（1）有平时（int）、期末成绩（int）、组成比例（float）三个私有数据成员；
（2）有成员函数setProp，根据键盘输入，设置组成比例，取值在0到1之间，比如0.4，则表示成绩=平时*40%+期末*60%；
（3）有计算并输出成绩函数compScore，根据组成比例计算并输出成绩。
定义教师类：
（1）有私有数据成员pStu，是学生对象指针；
（2）有构造函数，带整型参数，以其值为大小创建学生对象数组，用pStu指向；
（3）有成员函数assign，参数为数组下标，接收键盘输入，设置一个数组元素（学生对象）的平时、期末成绩。
（4）有成员函数show，参数为数组下标，用于调用一个学生对象的compScore函数，显示其成绩。
main函数中：
（1）先调用学生类的setProp函数，键盘输入并设置组成比例；
（2）键盘输入学生数，由此定义教师对象。
（3）调用assign函数，为数组中每个学生对象给平时、期末成绩，两个成绩由键盘输入；
（4）调用show函数，逐个计算并输出每个学生的成绩，以空格隔开。
举例1：
输入：0.4 3 70 90 60 80 55 88
输出：82 72 74.8
举例2：
输入：0.5 4 70 90 60 80 55 88 66 77
输出：80 70 71.5 71.5
要求：1、本题禁止使用友元函数、友元类。2、不允许有其它成员函数，比如setter/getter函数。*/
#include  <iostream>

class Student {
private:
    int dailyGrade;
    int finalGrade;
    static float proportion;
public:
    static void setProp(float p){
        proportion = p;
    }
    void setGrade(int dg, int fg) {
        dailyGrade = dg;
        finalGrade = fg;
    }
    float compScore() {
        float grade = dailyGrade * proportion + finalGrade * (1 - proportion);
        std::cout << grade << std::endl;
        return grade;
    }
};

float Student::proportion = 0;

class Teacher {
private:
    Student *pStu;
public:
    Teacher(int size) {
        pStu = new Student[size];
    }

    void assign(int index) {
        int dg;
        int fg;
        std::cin >> dg >> fg;
        pStu[index].setGrade(dg, fg);
    }

    void show(int index) {
        pStu[index].compScore();
    }

    void releaseMemory() {
        delete pStu;
    }

};

int main() {
    float prop;
    std::cin >> prop;
    Student::setProp(prop);

    int num;
    std::cin >> num;
    Teacher teacher(num);

    for(int i = 0; i < num; i++) {
        teacher.assign(i);
    }

    for(int i = 0; i < num; i++) {
        teacher.show(i);
    }
    teacher.releaseMemory();
}

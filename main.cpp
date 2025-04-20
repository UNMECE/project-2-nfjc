//Including standard libraries fro use in the code.
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//Simple Student class declaration. Assignment ran through this pretty well.
class Student {
protected:
    std::string first_name;
    std::string last_name;
    double gpa;
    int grad_year;
    std::string grad_semester;
    int enrolled_year;
    std::string enrolled_semester;
    std::string level;
//Also required by assignment so it was easy.
public:
    Student();
    virtual ~Student();
//Setters for inputting data.
    void setName(const std::string &first, const std::string &last);
    void setGPA(double g);
    void setGradInfo(int year, const std::string &semester);
    void setEnrolledInfo(int year, const std::string &semester);
    void setLevel(const std::string &lvl);

    virtual void writeToFile(std::ofstream &ofs) const;
};
//Initializes everything to blak/default values.
Student::Student() {
    first_name = "";
    last_name = "";
    gpa = 0.0;
    grad_year = 0;
    grad_semester = "";
    enrolled_year = 0;
    enrolled_semester = "";
    level = "";
}

Student::~Student() {}
//setName function... sets the name.
void Student::setName(const std::string &first, const std::string &last) {
    first_name = first;
    last_name = last;
}
//Sets GPA.
void Student::setGPA(double g) {
    gpa = g;
}
//Sets graduation year and semester.
void Student::setGradInfo(int year, const std::string &semester) {
    grad_year = year;
    grad_semester = semester;
}
//Sets enrolled year and semester.
void Student::setEnrolledInfo(int year, const std::string &semester) {
    enrolled_year = year;
    enrolled_semester = semester;
}
//Setting student level.
void Student::setLevel(const std::string &lvl) {
    level = lvl;
}
//Writes the fields to file to be stored.
void Student::writeToFile(std::ofstream &ofs) const {
    ofs << first_name << " " << last_name << "\n";
    ofs << gpa << "\n";
    ofs << enrolled_semester << " " << enrolled_year << "\n";
    ofs << grad_semester << " " << grad_year << "\n";
    ofs << level << "\n";
}
//Has constructor, destructor, setter, and override for writing to file.
class Art_Student : public Student {
private:
    std::string art_emphasis;
//Definitions for art student that are based off the default student obejct.
public:
    Art_Student();
    ~Art_Student();
    void setArtEmphasis(const std::string &emphasis);
    void writeToFile(std::ofstream &ofs) const override;
};

Art_Student::Art_Student() {
    art_emphasis = "";
}

Art_Student::~Art_Student() {}

void Art_Student::setArtEmphasis(const std::string &emphasis) {
    art_emphasis = emphasis;
}

void Art_Student::writeToFile(std::ofstream &ofs) const {
    Student::writeToFile(ofs);
    ofs << art_emphasis << "\n";
}
//DErived class of Physiics student similar to art student.
class Physics_Student : public Student {
private:
    std::string concentration;

public:
    Physics_Student();
    ~Physics_Student();
    void setConcentration(const std::string &conc);
    void writeToFile(std::ofstream &ofs) const override;
};
//SAme definitions as art student.
Physics_Student::Physics_Student() {
    concentration = "";
}

Physics_Student::~Physics_Student() {}

void Physics_Student::setConcentration(const std::string &conc) {
    concentration = conc;
}

void Physics_Student::writeToFile(std::ofstream &ofs) const {
    Student::writeToFile(ofs);
    ofs << concentration << "\n";
}
//Main function for function calls and outputting.
int main() {
    std::vector<Art_Student *> art_students;
    std::vector<Physics_Student *> physics_students;
//hard coding art and physics student values for use.
    for (int i = 0; i < 5; ++i) {
        Art_Student *a = new Art_Student();
        a->setName("ArtFirst" + std::to_string(i), "ArtLast" + std::to_string(i));
        a->setGPA(3.0);
        a->setEnrolledInfo(2020, "Fall");
        a->setGradInfo(2024, "Spring");
        a->setLevel("undergrad");
        if (i % 3 == 0) a->setArtEmphasis("Art Studio");
        else if (i % 3 == 1) a->setArtEmphasis("Art History");
        else a->setArtEmphasis("Art Education");
        art_students.push_back(a);
    }

    for (int i = 0; i < 5; ++i) {
        Physics_Student *p = new Physics_Student();
        p->setName("PhysicsFirst" + std::to_string(i), "PhysicsLast" + std::to_string(i));
        p->setGPA(3.0);
        p->setEnrolledInfo(2019, "Spring");
        p->setGradInfo(2023, "Fall");
        p->setLevel("grad");
        if (i % 2 == 0) p->setConcentration("Biophysics");
        else p->setConcentration("Earth and Planetary Sciences");
        physics_students.push_back(p);
    }
//Saving to file. This part was really hard to code.
    std::ofstream ofs("student_info.dat");
    for (int i = 0; i < art_students.size(); ++i) {
        art_students[i]->writeToFile(ofs);
    }
    for (int i = 0; i < physics_students.size(); ++i) {
        physics_students[i]->writeToFile(ofs);
    }
    ofs.close();
//Closing file and deleting memory to avoid errors.
    for (int i = 0; i < art_students.size(); ++i) {
        delete art_students[i];
    }
    for (int i = 0; i < physics_students.size(); ++i) {
        delete physics_students[i];
    }

    return 0;
}


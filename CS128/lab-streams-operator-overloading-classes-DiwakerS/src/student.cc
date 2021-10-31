#include "student.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "course.hpp"

using namespace std;

Student::Student(std::string name, std::string uin, std::string net_id) {
  name_ = name;
  uin_ = uin;
  net_id_ = net_id;
  major_ = "Undeclared";
  graduated_ = false;
}

Student::Student(string name,
                 string uin,
                 string net_id,
                 string major,
                 vector<Course> courses,
                 bool graduated) {
  name_ = name;
  uin_ = uin;
  net_id_ = net_id;
  major_ = major;
  for (size_t i = 0; i < courses.size(); i++) {
    courses_.push_back(courses.at(i));
  }
  graduated_ = graduated;
}

std::string Student::GetName() const { return name_; }

std::string Student::GetUIN() const { return uin_; }

std::string Student::GetNetId() const { return net_id_; }

std::string Student::GetMajor() const { return major_; }

bool Student::HasGraduated() const { return graduated_; }

const std::vector<Course>& Student::GetCourses() const { return courses_; }

void Student::SetName(std::string name) { name_ = name; }

void Student::SetMajor(std::string major) { major_ = major; }

bool Student::AddCourse(Course c) {
  for (size_t i = 0; i < courses_.size(); i++) {
    if (courses_.at(i).credits == c.credits && courses_.at(i).name == c.name) {
      return false;
    }
  }
  courses_.push_back(c);
  return true;
}

void Student::Graduate() {
  int total_credits = 0;
  for (size_t i = 0; i < courses_.size(); i++) {
    total_credits += courses_.at(i).credits;
  }
  if (total_credits >= 120) {
    graduated_ = true;
  }
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  os << "Name: " << s.GetName() << endl;
  os << "UIN: " << s.GetUIN() << endl;
  os << "Net Id: " << s.GetNetId() << endl;
  os << "Major: " << s.GetMajor() << endl;

  vector<Course> temp = s.GetCourses();
  int credits = 0;
  string courses = "";

  if (temp.size() != 0) {
    for (size_t i = 0; i < temp.size(); i++) {
      credits += temp.at(i).credits;
    }
    os << "Credits: " << credits << endl;

    os << "Courses: ";

    for (size_t i = 0; i < temp.size(); i++) {
      os << temp.at(i).name;
      if (i <= temp.size() - 2) {
        os << ", ";
      }
    }
    os << endl;
  } else {
    os << "Credits: "
       << "0" << endl;
    os << "Courses: " << endl;
  }
  string value = "False";
  if (s.HasGraduated()) {
    value = "True";
  }
  os << "Graduated: " << value;

  return os;
}